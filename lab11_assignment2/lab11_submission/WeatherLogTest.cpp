#include <iostream>
#include "WeatherLog.h"

using std::cout;
using std::endl;

int main()
{
    cout << "===== WeatherLog Unit Test =====" << endl;

    WeatherLog log;

    cout << "\nTest 1: load data source" << endl;
    bool loaded = log.LoadData("data/data_source.txt");
    cout << "LoadData returned (expected 1): " << loaded << endl;

    cout << "\nTest 2: total record count" << endl;
    cout << "Record count (> 0 expected): " << log.GetRecordCount() << endl;

    cout << "\nTest 3: month existence checks" << endl;
    for (int month = 1; month <= 12; ++month)
    {
        cout << "HasMonth(" << month << "): " << log.HasMonth(month) << endl;
    }

    cout << "\nTest 4: correlation S_T for January" << endl;
    cout << "S_T January: " << log.CalculateCorrelationST(1) << endl;

    cout << "\nTest 5: correlation S_R for January" << endl;
    cout << "S_R January: " << log.CalculateCorrelationSR(1) << endl;

    cout << "\nTest 6: correlation T_R for January" << endl;
    cout << "T_R January: " << log.CalculateCorrelationTR(1) << endl;

    cout << "\nTest 7: invalid month 0" << endl;
    cout << "HasMonth(0) (expected 0): " << log.HasMonth(0) << endl;
    cout << "S_T month 0 (expected 0): " << log.CalculateCorrelationST(0) << endl;

    cout << "\nTest 8: invalid month 13" << endl;
    cout << "HasMonth(13) (expected 0): " << log.HasMonth(13) << endl;
    cout << "S_R month 13 (expected 0): " << log.CalculateCorrelationSR(13) << endl;

    cout << "\nTest 9: clear and reload" << endl;
    log.Clear();
    cout << "Record count after clear (expected 0): " << log.GetRecordCount() << endl;
    cout << "HasMonth(1) after clear (expected 0): " << log.HasMonth(1) << endl;

    bool reloaded = log.LoadData("data/data_source.txt");
    cout << "Reload returned (expected 1): " << reloaded << endl;
    cout << "Record count after reload (> 0 expected): " << log.GetRecordCount() << endl;

    cout << "\n===== End of WeatherLog Tests =====" << endl;
    return 0;
}
