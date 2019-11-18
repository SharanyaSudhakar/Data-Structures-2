#if defined(ISBST)  
#include "bst.cpp"
#else  
#include "treap.cpp"
#endif  

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
    #if !defined(ISBST) 
    bintree.displaySideways();
    #endif
    return 0;
}
