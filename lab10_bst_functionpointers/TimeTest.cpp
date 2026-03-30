#include <iostream>
#include <sstream>
#include "Time.h"

using std::cout;
using std::endl;

int main()
{
    cout << "===== Time Unit Test =====" << endl;

    cout << "\nTest 1: default constructor" << endl;
    Time t1;
    cout << "Default time (expected 0:0): " << t1 << endl;

    cout << "\nTest 2: parameterized constructor" << endl;
    Time t2(9, 30);
    cout << "Constructed time (expected 9:30): " << t2 << endl;

    cout << "\nTest 3: getters" << endl;
    cout << "Hour (expected 9): " << t2.GetHour() << endl;
    cout << "Minute (expected 30): " << t2.GetMinute() << endl;

    cout << "\nTest 4: SetTime" << endl;
    t2.SetTime(14, 45);
    cout << "Updated time (expected 14:45): " << t2 << endl;

    cout << "\nTest 5: valid input operator>>" << endl;
    std::stringstream goodInput("7:05");
    Time t3;
    goodInput >> t3;
    cout << "Read time (expected 7:5): " << t3 << endl;
    cout << "Stream fail state (expected 0): " << goodInput.fail() << endl;

    cout << "\nTest 6: invalid separator input" << endl;
    std::stringstream badInput1("9-30");
    Time t4;
    badInput1 >> t4;
    cout << "Stream fail state (expected 1): " << badInput1.fail() << endl;

    cout << "\nTest 7: invalid hour" << endl;
    std::stringstream badInput2("25:10");
    Time t5;
    badInput2 >> t5;
    cout << "Stream fail state (expected 1): " << badInput2.fail() << endl;

    cout << "\nTest 8: invalid minute" << endl;
    std::stringstream badInput3("10:75");
    Time t6;
    badInput3 >> t6;
    cout << "Stream fail state (expected 1): " << badInput3.fail() << endl;

    cout << "\n===== End of Time Tests =====" << endl;
    return 0;
}
