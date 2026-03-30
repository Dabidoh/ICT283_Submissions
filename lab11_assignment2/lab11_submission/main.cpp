#include <iostream>
#include <iomanip>
#include "WeatherLog.h"

using std::cin;
using std::cout;
using std::endl;

static const char* MonthName(int month)
{
    static const char* MONTH_NAMES[] =
    {
        "",
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };

    if (month < 1 || month > 12)
    {
        return "Invalid";
    }

    return MONTH_NAMES[month];
}

static void RunOption1(const WeatherLog& log)
{
    int month = 0;
    int year = 0;

    cout << "Enter month (1-12): ";
    cin >> month;
    cout << "Enter year: ";
    cin >> year;

    const std::vector<WeatherRecord> filtered = log.GetRecordsForMonthYear(month, year);

    if (filtered.empty())
    {
        cout << MonthName(month) << " " << year << ": No Data" << endl;
        return;
    }

    cout << std::fixed << std::setprecision(6);
    cout << MonthName(month) << " " << year << ":" << endl;
    cout << "Average wind speed: "
         << log.CalculateAverageWindSpeed(month, year) << " km/h" << endl;
    cout << "Sample stdev: "
         << log.CalculateWindSpeedStdev(month, year) << endl;
}

static void RunOption2(const WeatherLog& log)
{
    int year = 0;
    cout << "Enter year: ";
    cin >> year;

    cout << year << endl;
    cout << std::fixed << std::setprecision(6);

    for (int month = 1; month <= 12; ++month)
    {
        const std::vector<WeatherRecord> filtered = log.GetRecordsForMonthYear(month, year);

        if (filtered.empty())
        {
            cout << MonthName(month) << ": No Data" << endl;
        }
        else
        {
            cout << MonthName(month)
                 << ": average: " << log.CalculateAverageTemperature(month, year)
                 << " degrees C, stdev: "
                 << log.CalculateTemperatureStdev(month, year)
                 << endl;
        }
    }
}

static void RunOption3(const WeatherLog& log)
{
    int month = 0;
    cout << "Enter month (1-12): ";
    cin >> month;

    if (month < 1 || month > 12)
    {
        cout << "Error: invalid month." << endl;
        return;
    }

    if (!log.HasMonth(month))
    {
        cout << "No data for " << MonthName(month) << endl;
        return;
    }

    cout << std::fixed << std::setprecision(6);
    cout << "Sample Pearson Correlation Coefficient for "
         << MonthName(month) << endl;
    cout << "S_T: " << log.CalculateCorrelationST(month) << endl;
    cout << "S_R: " << log.CalculateCorrelationSR(month) << endl;
    cout << "T_R: " << log.CalculateCorrelationTR(month) << endl;
}

static void RunOption4(const WeatherLog& log)
{
    int year = 0;
    cout << "Enter year: ";
    cin >> year;

    if (log.WriteWindTempSolarFile(year, "WindTempSolar.csv"))
    {
        cout << "Data successfully written to WindTempSolar.csv" << endl;
    }
    else
    {
        cout << "Error writing WindTempSolar.csv" << endl;
    }
}

static void DisplayMenu()
{
    cout << "\n===== Assignment 2 Menu =====" << endl;
    cout << "1. Average wind speed for a specified month and year" << endl;
    cout << "2. Average ambient temperature for each month of a specified year" << endl;
    cout << "3. Sample Pearson Correlation Coefficient" << endl;
    cout << "4. Export WindTempSolar.csv" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter option: ";
}

int main()
{
    WeatherLog log;

    if (!log.LoadData("data/data_source.txt"))
    {
        cout << "Error: failed to load data." << endl;
        return 1;
    }

    int option = 0;

    do
    {
        DisplayMenu();
        cin >> option;

        switch (option)
        {
            case 1:
                RunOption1(log);
                break;

            case 2:
                RunOption2(log);
                break;

            case 3:
                RunOption3(log);
                break;

            case 4:
                RunOption4(log);
                break;

            case 5:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid option." << endl;
                break;
        }
    }
    while (option != 5);

    return 0;
}
