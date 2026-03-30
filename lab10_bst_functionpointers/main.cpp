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

int main()
{
    WeatherLog log;

    if (!log.LoadData("data/data_source.txt"))
    {
        cout << "Error: failed to load data." << endl;
        return 1;
    }

    int month = 0;
    cout << "Enter month (1-12): ";
    cin >> month;

    if (month < 1 || month > 12)
    {
        cout << "Error: invalid month." << endl;
        return 1;
    }

    if (!log.HasMonth(month))
    {
        cout << "No data for " << MonthName(month) << endl;
        return 0;
    }

    cout << std::fixed << std::setprecision(6);

    cout << "Sample Pearson Correlation Coefficient for "
         << MonthName(month) << endl;

    cout << "S_T: " << log.CalculateCorrelationST(month) << endl;
    cout << "S_R: " << log.CalculateCorrelationSR(month) << endl;
    cout << "T_R: " << log.CalculateCorrelationTR(month) << endl;

    return 0;
}
