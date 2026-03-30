#include <iostream>
#include <fstream>
#include <string>
#include "DateTreeLoader.h"
#include "Bst.h"
#include "Date.h"

using std::cout;
using std::endl;
using std::ofstream;
using std::string;

static void PrintDate(const Date& d)
{
    cout << d << ' ';
}

static void WriteFile(const string& path, const string& content)
{
    ofstream out(path.c_str());
    out << content;
}

int main()
{
    cout << "===== DateTreeLoader Unit Test =====" << endl;

    // Test data files
    WriteFile("loader_test_source.txt",
              "loader_test_1.csv\n"
              "loader_test_2.csv\n"
              "missing_file.csv\n");

    WriteFile("loader_test_1.csv",
              "WAST,Other\n"
              "30/6/2016 9:00,x\n"
              "1/1/2015 10:00,x\n"
              "bad_timestamp,x\n"
              "\n");

    WriteFile("loader_test_2.csv",
              "WAST,Other\n"
              "30/6/2016 11:00,x\n"
              "15/3/2017 8:00,x\n");

    cout << "\nTest 1: load from data source with valid, duplicate, invalid and missing files" << endl;
    Bst<Date> tree1;
    DateLoadReport report1 = LoadDatesFromDataSource("loader_test_source.txt", tree1, cout);

    cout << "Files opened (expected 2): " << report1.filesOpened << endl;
    cout << "Files failed (expected 1): " << report1.filesFailed << endl;
    cout << "Rows read (expected 5): " << report1.rowsRead << endl;
    cout << "Dates inserted (expected 3): " << report1.datesInserted << endl;
    cout << "Duplicates rejected (expected 1): " << report1.duplicatesRejected << endl;
    cout << "Invalid rows (expected 1): " << report1.invalidRows << endl;

    cout << "Tree inorder (expected 1/1/2015 30/6/2016 15/3/2017): ";
    tree1.InOrder(PrintDate);
    cout << endl;

    cout << "\nTest 2: missing source file" << endl;
    Bst<Date> tree2;
    DateLoadReport report2 = LoadDatesFromDataSource("does_not_exist.txt", tree2, cout);

    cout << "Files opened (expected 0): " << report2.filesOpened << endl;
    cout << "Files failed (expected 1): " << report2.filesFailed << endl;
    cout << "Rows read (expected 0): " << report2.rowsRead << endl;
    cout << "Dates inserted (expected 0): " << report2.datesInserted << endl;
    cout << "Duplicates rejected (expected 0): " << report2.duplicatesRejected << endl;
    cout << "Invalid rows (expected 0): " << report2.invalidRows << endl;

    WriteFile("loader_date_file.txt",
              "30/6/2016\n"
              "1/1/2015\n"
              "30/6/2016\n"
              "15/3/2017\n");

    cout << "\nTest 3: load from plain date file" << endl;
    Bst<Date> tree3;
    DateLoadReport report3 = LoadDatesFromDateFile("loader_date_file.txt", tree3, cout);

    cout << "Files opened (expected 1): " << report3.filesOpened << endl;
    cout << "Files failed (expected 0): " << report3.filesFailed << endl;
    cout << "Rows read (expected 4): " << report3.rowsRead << endl;
    cout << "Dates inserted (expected 3): " << report3.datesInserted << endl;
    cout << "Duplicates rejected (expected 1): " << report3.duplicatesRejected << endl;
    cout << "Invalid rows (expected 0): " << report3.invalidRows << endl;

    cout << "Tree inorder (expected 1/1/2015 30/6/2016 15/3/2017): ";
    tree3.InOrder(PrintDate);
    cout << endl;

    cout << "\n===== End of DateTreeLoader Tests =====" << endl;
    return 0;
}
