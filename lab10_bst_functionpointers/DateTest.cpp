#include <iostream>
#include <sstream>
#include "Date.h"

using std::cout;
using std::endl;

int main()
{
    cout << "===== Date Unit Test =====" << endl;

    cout << "\nTest 1: default constructor" << endl;
    Date d1;
    cout << "Default date (expected 1/1/2000): " << d1 << endl;

    cout << "\nTest 2: valid Set()" << endl;
    Date d2;
    cout << "Set 30/6/2016 (expected 1): " << d2.Set(30, 6, 2016) << endl;
    cout << "Date value (expected 30/6/2016): " << d2 << endl;

    cout << "\nTest 3: invalid month low" << endl;
    Date d3;
    cout << "Set 1/0/2016 (expected 0): " << d3.Set(1, 0, 2016) << endl;

    cout << "\nTest 4: invalid month high" << endl;
    cout << "Set 1/13/2016 (expected 0): " << d3.Set(1, 13, 2016) << endl;

    cout << "\nTest 5: invalid day low" << endl;
    cout << "Set 0/6/2016 (expected 0): " << d3.Set(0, 6, 2016) << endl;

    cout << "\nTest 6: invalid day high" << endl;
    cout << "Set 32/6/2016 (expected 0): " << d3.Set(32, 6, 2016) << endl;

    cout << "\nTest 7: invalid year low" << endl;
    cout << "Set 1/1/1899 (expected 0): " << d3.Set(1, 1, 1899) << endl;

    cout << "\nTest 8: invalid year high" << endl;
    cout << "Set 1/1/2101 (expected 0): " << d3.Set(1, 1, 2101) << endl;

    cout << "\nTest 9: IsValid()" << endl;
    Date d4(15, 3, 2017);
    cout << "Date 15/3/2017 valid (expected 1): " << d4.IsValid() << endl;

    cout << "\nTest 10: operator==" << endl;
    Date d5(15, 3, 2017);
    cout << "d4 == d5 (expected 1): " << (d4 == d5) << endl;

    cout << "\nTest 11: operator<" << endl;
    Date d6(1, 1, 2015);
    cout << "d6 < d4 (expected 1): " << (d6 < d4) << endl;

    cout << "\nTest 12: operator>" << endl;
    cout << "d4 > d6 (expected 1): " << (d4 > d6) << endl;

    cout << "\nTest 13: valid input operator>>" << endl;
    std::stringstream goodInput("30/6/2016");
    Date d7;
    goodInput >> d7;
    cout << "Read date (expected 30/6/2016): " << d7 << endl;
    cout << "Stream fail state (expected 0): " << goodInput.fail() << endl;

    cout << "\nTest 14: invalid input operator>>" << endl;
    std::stringstream badInput("30-6-2016");
    Date d8;
    badInput >> d8;
    cout << "Stream fail state (expected 1): " << badInput.fail() << endl;

    cout << "\n===== End of Date Tests =====" << endl;
    return 0;
}
