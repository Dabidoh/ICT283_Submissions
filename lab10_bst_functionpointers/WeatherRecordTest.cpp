#include <iostream>
#include "WeatherRecord.h"

using std::cout;
using std::endl;

int main()
{
    cout << "===== WeatherRecord Unit Test =====" << endl;

    cout << "\nTest 1: default constructor" << endl;
    WeatherRecord r1;
    cout << "Default date (expected 1/1/2000): " << r1.GetDate() << endl;
    cout << "Default time (expected 0:0): " << r1.GetTime() << endl;
    cout << "Default wind speed (expected 0): " << r1.GetWindSpeed() << endl;
    cout << "Default solar radiation (expected 0): " << r1.GetSolarRadiation() << endl;
    cout << "Default temperature (expected 0): " << r1.GetTemperature() << endl;

    cout << "\nTest 2: parameterized constructor" << endl;
    Date d(30, 6, 2016);
    Time t(9, 0);
    WeatherRecord r2(d, t, 12.5f, 300.0f, 24.5f);
    cout << "Date (expected 30/6/2016): " << r2.GetDate() << endl;
    cout << "Time (expected 9:0): " << r2.GetTime() << endl;
    cout << "Wind speed (expected 12.5): " << r2.GetWindSpeed() << endl;
    cout << "Solar radiation (expected 300): " << r2.GetSolarRadiation() << endl;
    cout << "Temperature (expected 24.5): " << r2.GetTemperature() << endl;

    cout << "\nTest 3: setters" << endl;
    WeatherRecord r3;
    r3.SetDate(Date(1, 1, 2015));
    r3.SetTime(Time(14, 30));
    r3.SetWindSpeed(20.0f);
    r3.SetSolarRadiation(500.0f);
    r3.SetTemperature(31.2f);

    cout << "Date (expected 1/1/2015): " << r3.GetDate() << endl;
    cout << "Time (expected 14:30): " << r3.GetTime() << endl;
    cout << "Wind speed (expected 20): " << r3.GetWindSpeed() << endl;
    cout << "Solar radiation (expected 500): " << r3.GetSolarRadiation() << endl;
    cout << "Temperature (expected 31.2): " << r3.GetTemperature() << endl;

    cout << "\nTest 4: negative wind speed rejected" << endl;
    r3.SetWindSpeed(-5.0f);
    cout << "Wind speed unchanged (expected 20): " << r3.GetWindSpeed() << endl;

    cout << "\nTest 5: negative solar radiation rejected" << endl;
    r3.SetSolarRadiation(-10.0f);
    cout << "Solar radiation unchanged (expected 500): " << r3.GetSolarRadiation() << endl;

    cout << "\nTest 6: negative solar on default record stays zero" << endl;
    WeatherRecord r4;
    r4.SetSolarRadiation(-1.0f);
    cout << "Solar radiation (expected 0): " << r4.GetSolarRadiation() << endl;

    cout << "\n===== End of WeatherRecord Tests =====" << endl;
    return 0;
}
