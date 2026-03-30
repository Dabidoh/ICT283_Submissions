#include "DateTreeLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>

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

    bool ParseDateOnlyFromTimestamp(const std::string& token, Date& date)
    {
        // Expected token format:
        // "1/01/2007 9:00"

        std::string cleaned = Trim(token);

        std::string::size_type spacePos = cleaned.find(' ');
        if (spacePos == std::string::npos)
        {
            return false;
        }

        std::string datePart = cleaned.substr(0, spacePos);

        std::stringstream ss(datePart);
        int day = 0;
        int month = 0;
        int year = 0;
        char slash1 = '\0';
        char slash2 = '\0';

        if (!(ss >> day >> slash1 >> month >> slash2 >> year))
        {
            return false;
        }

        if (slash1 != '/' || slash2 != '/')
        {
            return false;
        }

        return date.Set(day, month, year);
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
}

DateLoadReport::DateLoadReport()
    : filesOpened(0),
      filesFailed(0),
      rowsRead(0),
      datesInserted(0),
      duplicatesRejected(0),
      invalidRows(0)
{
}

DateLoadReport LoadDatesFromDataSource(
    const std::string& sourceFile,
    Bst<Date>& dateTree,
    std::ostream& log
)
{
    DateLoadReport report;

    std::ifstream source(sourceFile.c_str());
    if (!source)
    {
        log << "Error: could not open source file: " << sourceFile << '\n';
        report.filesFailed = 1;
        return report;
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
            log << "Error: could not open CSV file: " << fullPath << '\n';
            ++report.filesFailed;
            continue;
        }

        ++report.filesOpened;
        log << "Reading: " << fullPath << '\n';

        std::string line;

        // Skip header row
        if (!std::getline(csvFile, line))
        {
            continue;
        }

        while (std::getline(csvFile, line))
        {
            if (Trim(line).empty())
            {
                continue;
            }

            ++report.rowsRead;

            std::stringstream ss(line);
            std::string firstField;

            if (!std::getline(ss, firstField, ','))
            {
                log << "Invalid row (missing timestamp field): " << line << '\n';
                ++report.invalidRows;
                continue;
            }

            Date tempDate;
            if (!ParseDateOnlyFromTimestamp(firstField, tempDate))
            {
                log << "Invalid timestamp field: " << firstField << '\n';
                ++report.invalidRows;
                continue;
            }

            if (dateTree.Insert(tempDate))
            {
                ++report.datesInserted;
            }
            else
            {
                ++report.duplicatesRejected;
                log << "Duplicate date rejected: " << tempDate << '\n';
            }
        }
    }

    return report;
}

DateLoadReport LoadDatesFromDateFile(
    const std::string& dateFile,
    Bst<Date>& dateTree,
    std::ostream& log
)
{
    DateLoadReport report;

    std::ifstream infile(dateFile.c_str());
    if (!infile)
    {
        log << "Error: could not open date file: " << dateFile << '\n';
        report.filesFailed = 1;
        return report;
    }

    ++report.filesOpened;

    Date tempDate;
    while (infile >> tempDate)
    {
        ++report.rowsRead;

        if (dateTree.Insert(tempDate))
        {
            ++report.datesInserted;
        }
        else
        {
            ++report.duplicatesRejected;
            log << "Duplicate date rejected: " << tempDate << '\n';
        }
    }

    return report;
}
