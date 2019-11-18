// original.cc
//
// Copyright 2013, 2018 Systems Deployment, LLC
// Author: Morris Bernstein (morris@systems-deployment.com)

#include <iostream>
#include <map>

using namespace std;

int main() {
    map<string, int> count;
    string word;
    while (cin >> word) { ++count[word]; }
    for (auto& item : count) {
        cout << item.second << "  " << item.first << endl;
    }
    return 0;
}