#include "WeatherLog.h"

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>

namespace
{
    std::string Trim(const std::string& text)
    {
        std::string::size_type start = 0;
        while (start < text.length() &&
               (text[start] == ' ' || text[start] == '\t' ||
                text[start] == '\r' || text[start] == '\n'))
        {
            ++start;
        }

        std::string::size_type end = text.length();
        while (end > start &&
               (text[end - 1] == ' ' || text[end - 1] == '\t' ||
                text[end - 1] == '\r' || text[end - 1] == '\n'))
        {
            --end;
        }

        return text.substr(start, end - start);
    }

    std::string GetDirectoryPart(const std::string& path)
    {
        std::string::size_type slashPos = path.find_last_of("/\\");
        if (slashPos == std::string::npos)
        {
            return "";
        }

        return path.substr(0, slashPos + 1);
    }

    bool ParseDateTime(const std::string& wastToken, Date& date, Time& time)
    {
        std::stringstream ss(Trim(wastToken));

        std::string datePart;
        std::string timePart;

        if (!(ss >> datePart >> timePart))
        {
            return false;
        }

        int day = 0;
        int month = 0;
        int year = 0;
        char slash1 = '\0';
        char slash2 = '\0';

        std::stringstream dateStream(datePart);
        if (!(dateStream >> day >> slash1 >> month >> slash2 >> year))
        {
            return false;
        }

        if (slash1 != '/' || slash2 != '/')
        {
            return false;
        }

        if (!date.Set(day, month, year))
        {
            return false;
        }

        std::stringstream timeStream(timePart);
        if (!(timeStream >> time))
        {
            return false;
        }

        return true;
    }

    bool ParseFloatField(const std::string& token, float& value)
    {
        std::string cleaned = Trim(token);

        if (cleaned.empty() || cleaned == "N/A")
        {
            return false;
        }

        char* endPtr = nullptr;
        value = static_cast<float>(std::strtod(cleaned.c_str(), &endPtr));

        return (endPtr != cleaned.c_str() && *endPtr == '\0');
    }

    double CalculatePearson(const std::vector<WeatherRecord>& records,
                            float (WeatherRecord::*getterX)() const,
                            float (WeatherRecord::*getterY)() const)
    {
        std::vector<double> xs;
        std::vector<double> ys;

        for (std::size_t i = 0; i < records.size(); ++i)
        {
            double x = (records[i].*getterX)();
            double y = (records[i].*getterY)();

            // Exclude records where solar radiation has been zeroed out
            // for filtered/noise handling.
            if ((getterX == &WeatherRecord::GetSolarRadiation && x == 0.0) ||
                (getterY == &WeatherRecord::GetSolarRadiation && y == 0.0))
            {
                continue;
            }

            xs.push_back(x);
            ys.push_back(y);
        }

        const int n = static_cast<int>(xs.size());
        if (n < 2)
        {
            return 0.0;
        }

        double sumX = 0.0;
        double sumY = 0.0;
        for (int i = 0; i < n; ++i)
        {
            sumX += xs[i];
            sumY += ys[i];
        }

        const double meanX = sumX / n;
        const double meanY = sumY / n;

        double numerator = 0.0;
        double sumSqX = 0.0;
        double sumSqY = 0.0;

        for (int i = 0; i < n; ++i)
        {
            const double dx = xs[i] - meanX;
            const double dy = ys[i] - meanY;

            numerator += dx * dy;
            sumSqX += dx * dx;
            sumSqY += dy * dy;
        }

        const double denominator = std::sqrt(sumSqX * sumSqY);
        if (denominator == 0.0)
        {
            return 0.0;
        }

        return numerator / denominator;
    }
}

WeatherLog::WeatherLog()
    : m_records(),
      m_recordsByMonth(),
      m_dates()
{
}

void WeatherLog::Clear()
{
    m_records.clear();
    m_recordsByMonth.clear();
    m_dates.Clear();
}

bool WeatherLog::LoadData(const std::string& sourceFile)
{
    Clear();

    std::ifstream source(sourceFile.c_str());
    if (!source)
    {
        return false;
    }

    const std::string baseDir = GetDirectoryPart(sourceFile);
    std::string csvName;

    while (std::getline(source, csvName))
    {
        csvName = Trim(csvName);

        if (csvName.empty())
        {
            continue;
        }

        const std::string fullPath = baseDir + csvName;
        std::ifstream csvFile(fullPath.c_str());
        if (!csvFile)
        {
            continue;
        }

        std::string line;

        // Skip header row
        if (!std::getline(csvFile, line))
        {
            continue;
        }

        std::stringstream headerStream(line);
        std::string columnName;
        int currentIndex = 0;

        int wastIndex = -1;
        int sIndex = -1;
        int tIndex = -1;
        int srIndex = -1;

        while (std::getline(headerStream, columnName, ','))
        {
            columnName = Trim(columnName);

            if (columnName == "WAST")
            {
                wastIndex = currentIndex;
            }
            else if (columnName == "S")
            {
                sIndex = currentIndex;
            }
            else if (columnName == "T")
            {
                tIndex = currentIndex;
            }
            else if (columnName == "SR")
            {
                srIndex = currentIndex;
            }

            ++currentIndex;
        }

        if (wastIndex == -1 || sIndex == -1 || tIndex == -1 || srIndex == -1)
        {
            continue;
        }

        while (std::getline(csvFile, line))
        {
            if (Trim(line).empty())
            {
                continue;
            }

            std::stringstream rowStream(line);
            std::string token;
            std::vector<std::string> fields;

            while (std::getline(rowStream, token, ','))
            {
                fields.push_back(token);
            }

            if (wastIndex >= static_cast<int>(fields.size()) ||
                sIndex >= static_cast<int>(fields.size()) ||
                tIndex >= static_cast<int>(fields.size()) ||
                srIndex >= static_cast<int>(fields.size()))
            {
                continue;
            }

            Date date;
            Time time;
            if (!ParseDateTime(fields[wastIndex], date, time))
            {
                continue;
            }

            float windSpeedMps = 0.0f;
            float temperature = 0.0f;
            float solarRadiation = 0.0f;

            if (!ParseFloatField(fields[sIndex], windSpeedMps) ||
                !ParseFloatField(fields[tIndex], temperature) ||
                !ParseFloatField(fields[srIndex], solarRadiation))
            {
                continue;
            }

            // Convert wind speed from m/s to km/h
            const float windSpeedKmh = windSpeedMps * 3.6f;

            // Assignment-1 style filtering: low solar radiation treated as zero
            if (solarRadiation < 100.0f)
            {
                solarRadiation = 0.0f;
            }

            WeatherRecord record;
            record.SetDate(date);
            record.SetTime(time);
            record.SetWindSpeed(windSpeedKmh);
            record.SetTemperature(temperature);
            record.SetSolarRadiation(solarRadiation);

            m_records.push_back(record);
            m_recordsByMonth[date.GetMonth()].push_back(record);
            m_dates.Insert(date);
        }
    }

    return true;
}

int WeatherLog::GetRecordCount() const
{
    return static_cast<int>(m_records.size());
}

bool WeatherLog::HasMonth(int month) const
{
    return m_recordsByMonth.find(month) != m_recordsByMonth.end();
}

double WeatherLog::CalculateCorrelationST(int month) const
{
    std::map<int, std::vector<WeatherRecord> >::const_iterator itr =
        m_recordsByMonth.find(month);

    if (itr == m_recordsByMonth.end())
    {
        return 0.0;
    }

    return CalculatePearson(itr->second,
                            &WeatherRecord::GetWindSpeed,
                            &WeatherRecord::GetTemperature);
}

double WeatherLog::CalculateCorrelationSR(int month) const
{
    std::map<int, std::vector<WeatherRecord> >::const_iterator itr =
        m_recordsByMonth.find(month);

    if (itr == m_recordsByMonth.end())
    {
        return 0.0;
    }

    return CalculatePearson(itr->second,
                            &WeatherRecord::GetWindSpeed,
                            &WeatherRecord::GetSolarRadiation);
}

double WeatherLog::CalculateCorrelationTR(int month) const
{
    std::map<int, std::vector<WeatherRecord> >::const_iterator itr =
        m_recordsByMonth.find(month);

    if (itr == m_recordsByMonth.end())
    {
        return 0.0;
    }

    return CalculatePearson(itr->second,
                            &WeatherRecord::GetTemperature,
                            &WeatherRecord::GetSolarRadiation);
}
