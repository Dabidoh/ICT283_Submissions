#include <iostream>
#include "Bst.h"
#include "Date.h"
#include "DateTreeLoader.h"

using std::cout;
using std::endl;

void TestByValue(Bst<Date> tree)
{
    cout << "Pass-by-value inorder: ";
    tree.InOrder();
    cout << endl;
}

void TestByReference(const Bst<Date>& tree)
{
    cout << "Pass-by-reference inorder: ";
    tree.InOrder();
    cout << endl;
}

int main()
{
    Bst<Date> dateTree;

    DateLoadReport report =
        LoadDatesFromDataSource("data/data_source.txt", dateTree, cout);

    cout << "\n===== Load Report =====" << endl;
    cout << "Files opened: " << report.filesOpened << endl;
    cout << "Files failed: " << report.filesFailed << endl;
    cout << "Rows read: " << report.rowsRead << endl;
    cout << "Dates inserted: " << report.datesInserted << endl;
    cout << "Duplicates rejected: " << report.duplicatesRejected << endl;
    cout << "Invalid rows: " << report.invalidRows << endl;

    cout << "\nInOrder (chronological): ";
    dateTree.InOrder();
    cout << endl;

    cout << "PreOrder: ";
    dateTree.PreOrder();
    cout << endl;

    cout << "PostOrder: ";
    dateTree.PostOrder();
    cout << endl;

    cout << "\nBST invariant holds: " << dateTree.CheckInvariant() << endl;

    cout << "Search 30/6/2016: " << dateTree.Search(Date(30, 6, 2016)) << endl;
    cout << "Search 1/1/2099: " << dateTree.Search(Date(1, 1, 2099)) << endl;

    TestByValue(dateTree);
    TestByReference(dateTree);

    return 0;
}
