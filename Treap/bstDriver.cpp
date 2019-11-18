#include "bst.cpp"
#include <string>
#include <iostream>

using namespace std;

int main()
{
    string str;
    BST<string, int> bintree;
    while (cin >> str)
        ++bintree[str];

    for (const auto& item : bintree) {
        cout << item.second << " " << item.first << endl;
    }

    bintree.displaySideways();

    return 0;
}
