// 215Lab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BST.h"
#include "BSTNode.h"

using namespace std;

int main()
{
    BST<int, string> bst;

    bst.insert(24, "twenty-four");
    bst.insert(77, "seventy-seven");
    bst.insert(70, "seventy");
    bst.insert(75, "seventy-five");
    bst.insert(66, "sixty-six");
    bst.insert(79, "seventy-nine");
    bst.insert(68, "sixty-eight");
    bst.insert(67, "sixty-seven");
    bst.insert(69, "sixty-nine");
    bst.insert(90, "ninety");
    bst.insert(85, "eighty-five");
    bst.insert(83, "eighty-three");
    bst.insert(87, "eighty-seven");
    bst.insert(65, "sixty-five");

    cout << "My BST tree size is: " << bst.size() << endl;

    cout << "My tree's structure is: \n";
    bst.print();

    cout << "Inorder printing of my tree:" << endl;
    bst.printInorder();
    cout << endl;

    cout << "Reverse order printing of my tree:" << endl;
    bst.printReverse();
    cout << endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
