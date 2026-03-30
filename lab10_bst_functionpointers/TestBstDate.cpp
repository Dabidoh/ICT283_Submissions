#include <iostream>
#include "Bst.h"
#include "Date.h"

using std::cout;
using std::endl;

void PrintDate(const Date& d)
{
    cout << d << ' ';
}

int g_count = 0;

void CountDate(const Date&)
{
    ++g_count;
}

void TestByValue(Bst<Date> tree)
{
    cout << "Pass-by-value inorder: ";
    tree.InOrder(PrintDate);
    cout << endl;
}

void TestByReference(Bst<Date>& tree)
{
    cout << "Pass-by-reference inorder: ";
    tree.InOrder(PrintDate);
    cout << endl;
}

void TestByConstReference(const Bst<Date>& tree)
{
    cout << "Pass-by-const-reference inorder: ";
    tree.InOrder(PrintDate);
    cout << endl;
}

int main()
{
    cout << "===== Bst<Date> Unit Test =====" << endl;

    Bst<Date> dateTree;

    Date d1(30, 6, 2016);
    Date d2(30, 12, 2016);
    Date d3(1, 1, 2015);
    Date d4(15, 3, 2017);
    Date d5(30, 6, 2016);

    cout << "\nTest 1: empty tree search" << endl;
    cout << "Search 30/6/2016 (expected 0): " << dateTree.Search(d1) << endl;

    cout << "\nTest 2: insert dates" << endl;
    cout << "Insert d1 (expected 1): " << dateTree.Insert(d1) << endl;
    cout << "Insert d2 (expected 1): " << dateTree.Insert(d2) << endl;
    cout << "Insert d3 (expected 1): " << dateTree.Insert(d3) << endl;
    cout << "Insert d4 (expected 1): " << dateTree.Insert(d4) << endl;

    cout << "InOrder (expected chronological): ";
    dateTree.InOrder(PrintDate);
    cout << endl;

    cout << "PreOrder: ";
    dateTree.PreOrder(PrintDate);
    cout << endl;

    cout << "PostOrder: ";
    dateTree.PostOrder(PrintDate);
    cout << endl;

    cout << "\nTest 3: search existing and missing" << endl;
    cout << "Search d2 (expected 1): " << dateTree.Search(d2) << endl;
    cout << "Search duplicate-value date d5 (expected 1): " << dateTree.Search(d5) << endl;
    cout << "Search 1/1/2022 (expected 0): " << dateTree.Search(Date(1, 1, 2022)) << endl;

    cout << "\nTest 4: duplicate insert" << endl;
    cout << "Insert duplicate d5 (expected 0): " << dateTree.Insert(d5) << endl;
    cout << "InOrder unchanged: ";
    dateTree.InOrder(PrintDate);
    cout << endl;

    cout << "\nTest 5: invariant check" << endl;
    cout << "CheckInvariant (expected 1): " << dateTree.CheckInvariant() << endl;

    cout << "\nTest 5a: null callback traversal" << endl;
    dateTree.InOrder(nullptr);
    cout << "Null callback completed without crash" << endl;

    cout << "\nTest 5b: node count using traversal callback" << endl;
    g_count = 0;
    dateTree.InOrder(CountDate);
    cout << "Node count (expected 4): " << g_count << endl;

    cout << "\nTest 6: copy constructor / pass by value" << endl;
    TestByValue(dateTree);

    cout << "\nTest 7: pass by reference" << endl;
    TestByReference(dateTree);

    cout << "\nTest 8: pass by const reference" << endl;
    TestByConstReference(dateTree);

    cout << "\nTest 9: assignment operator" << endl;
    Bst<Date> tree2;
    tree2 = dateTree;
    cout << "Assigned tree inorder: ";
    tree2.InOrder(PrintDate);
    cout << endl;

    cout << "\nTest 10: self-assignment" << endl;
    tree2 = tree2;
    cout << "tree2 after self-assignment: ";
    tree2.InOrder(PrintDate);
    cout << endl;

    cout << "\nTest 11: deep copy independence" << endl;
    Bst<Date> tree3;
    tree3.Insert(Date(10, 1, 2020));
    tree3.Insert(Date(5, 1, 2020));
    tree3.Insert(Date(15, 1, 2020));

    Bst<Date> tree4 = tree3;
    tree3.Clear();

    cout << "Original after clear (expected empty): ";
    tree3.InOrder(PrintDate);
    cout << endl;

    cout << "Copied tree should still have values: ";
    tree4.InOrder(PrintDate);
    cout << endl;

    cout << "\nTest 12: clear" << endl;
    dateTree.Clear();
    cout << "IsEmpty (expected 1): " << dateTree.IsEmpty() << endl;
    cout << "InOrder after clear: ";
    dateTree.InOrder(PrintDate);
    cout << endl;

    cout << "\nTest 13: empty traversals" << endl;
    Bst<Date> emptyTree;
    cout << "Empty inorder: ";
    emptyTree.InOrder(PrintDate);
    cout << endl;
    cout << "Empty preorder: ";
    emptyTree.PreOrder(PrintDate);
    cout << endl;
    cout << "Empty postorder: ";
    emptyTree.PostOrder(PrintDate);
    cout << endl;

    cout << "\nTest 14: clear empty tree" << endl;
    emptyTree.Clear();
    cout << "IsEmpty after clear on empty tree (expected 1): " << emptyTree.IsEmpty() << endl;

    cout << "\n===== End of Tests =====" << endl;
    return 0;
}
