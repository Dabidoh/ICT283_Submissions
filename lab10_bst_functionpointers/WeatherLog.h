#ifndef WEATHER_LOG_H
#define WEATHER_LOG_H

#include <map>
#include <string>
#include <vector>
#include "WeatherRecord.h"
#include "Bst.h"

/**
 * @class WeatherLog
 * @brief Stores weather records and provides query operations for Assignment 2.
 *
 * WeatherLog owns the loaded weather data and organises it for processing.
 * It uses a BST to store unique dates and a map to group records by month.
 */
class WeatherLog
{
public:
    /**
     * @brief Default constructor.
     */
    WeatherLog();

    /**
     * @brief Clears all loaded data.
     */
    void Clear();

    /**
     * @brief Loads weather data from all CSV files listed in a source file.
     *
     * @param sourceFile Path to data_source.txt.
     * @return true if the source file could be opened, false otherwise.
     */
    bool LoadData(const std::string& sourceFile);

    /**
     * @brief Gets the total number of loaded weather records.
     *
     * @return Number of records stored.
     */
    int GetRecordCount() const;

    /**
     * @brief Checks whether any data exists for the given month.
     *
     * @param month Month number in the range 1 to 12.
     * @return true if records exist for the month, false otherwise.
     */
    bool HasMonth(int month) const;

    /**
     * @brief Calculates Pearson correlation for wind speed and temperature.
     *
     * @param month Month number in the range 1 to 12.
     * @return Correlation value.
     */
    double CalculateCorrelationST(int month) const;

    /**
     * @brief Calculates Pearson correlation for wind speed and solar radiation.
     *
     * @param month Month number in the range 1 to 12.
     * @return Correlation value.
     */
    double CalculateCorrelationSR(int month) const;

    /**
     * @brief Calculates Pearson correlation for temperature and solar radiation.
     *
     * @param month Month number in the range 1 to 12.
     * @return Correlation value.
     */
    double CalculateCorrelationTR(int month) const;

private:
    std::vector<WeatherRecord> m_records;
    std::map<int, std::vector<WeatherRecord> > m_recordsByMonth;
    Bst<Date> m_dates;
};

#endif
