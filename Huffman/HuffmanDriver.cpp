#include "Heap.cpp"
#include "HuffmanTree.cpp"
#include "bitStream.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <map>
#include <string>
#include <ctype.h>
#include <limits.h>
#include <bitset>

using namespace std;

template<typename Data, typename Priority>
void encodeFile(string& filename, string& sourceFile, HuffmanTree<Data, Priority>& tree)
{
    cerr << "\nENDCODE TABLE (with padding):\n\n";
    pair<int, string> codedSymbols[UCHAR_MAX + 1];
    for (auto& item : tree.getFreqTable())
    {
        int tempLen = item.second.size();
        codedSymbols[(int)item.first].first = tempLen;
        int zerolength = (tempLen % 8 == 0) ? 8 : tempLen % 8;
        for (int i = zerolength; i < 8; i++)
            item.second.append("0");
        codedSymbols[(int)item.first].second = item.second;
        if (isprint(item.first))
            cerr << " " << item.first;
        else
            cerr << "\\n";
        cerr << ": " << item.second << endl;
    }
    BitStream bitout(true, filename);
    cerr << "\nENCODE TABLE (with hex):\n\n";

    for (int i = 0; i < UCHAR_MAX + 1; i++)
    {
        int len = codedSymbols[i].first;
        char c = char(len);
        bitout.putbyte(c);
        if (len != 0)
        {
            bitout.putstring(codedSymbols[i].second);
            if (isprint(char(i)))
                cerr << setw(3) << char(i);
            else
                cerr << setw(3) << "\\n";
            cerr << setw(4) << dec << len << " " << hex << stoull(codedSymbols[i].second, 0, 2) << endl;
        }
    }

    //adding letter count in file
    string countStr = bitset<32>(tree.getRoot()->priority()).to_string();
    cerr << "\n\nletter count in file:  " << countStr << " : " << dec << tree.getRoot()->priority() << endl;
    char c = char(countStr.size());
    bitout.putbyte(c);

    int zerolength = (countStr.size() % 8 == 0) ? 8 : countStr.size() % 8;

    for (int i = zerolength; i < 8; i++)
    {
        cerr << 0;
        bitout.putBit(0);
    }
    bitout.putstring(countStr);

    //cerr << " " << sourceFile;
    //encoding file.
    ifstream  inFile(sourceFile);
    Data letter;

    if (!inFile) {
        cerr << "Unable to open file";
        exit(1); // terminate with error
    }

    while (inFile.get(letter)) {
        string huff = tree.getPattern(letter);
        bitout.putstring(huff);
    }

    inFile.close();
}

template<typename Data, typename Priority>
void decodeFile(string& filename, string& destFile)
{
    cerr << "\nDECODE TABLE:\n\n";
    HuffmanTree<Data, Priority> tree;
    BitStream bitin(false, filename);
    string str = "";
    int num = 0;
    do {
        int len = int(bitin.getByte());
        if (len != 0)
        {
            str = "";
            Data d = char(num);
            if (isprint(char(num)))
                cerr << char(num);
            else
                cerr << " ";
            cerr << " - " << len << ": ";
            for (int i = 0; i < len; i++)
                str += (bitin.getBit() == 0) ? '0' : '1';
            cerr << str << endl;
            tree.addPattern(d, str);
        }
        num++;
    } while (num != UCHAR_MAX + 1);
    tree.makeTree();

    //count
    str = "";
    int len = int(bitin.getByte());
    for (int i = 0; i < len; i++)
        str += (bitin.getBit() == 0) ? '0' : '1';

    bitin.emptyBuffer();
    unsigned long count = bitset<32>(str).to_ulong();
    cerr << "\n\nCOUNT: .." << len << ".. " << str << " : " << dec << count << endl;

    cerr << "\n\nTREE after decode from file\n";
    tree.dump();

    //read compressed file
    ofstream  inFile;
    inFile.open(destFile);
    Node<Data, Priority>* current = tree.getRoot();
    while (!bitin.isEOF() && count > 0)
    {
        if (bitin.getBit() == 0)
            current = current->left();
        else
            current = current->right();

        Data d = current->data();
        if (d)
        {
            cerr << d;
            inFile << d;
            current = tree.getRoot();
            count--;
        }
    }
    inFile.close();
}

map<char, int> checkFrequency(string filename) {
    ifstream  inFile(filename);
    char letter;
    map<char, int> freqTable;

    if (!inFile) {
        cerr << "Unable to open file";
        exit(1); // terminate with error
    }

    while (inFile.get(letter)) {
        ++freqTable[letter];
    }

    inFile.close();

    int maxFreq = 0;
    for (const auto& item : freqTable) {
        maxFreq = (item.second > maxFreq) ? item.second : maxFreq;
    }

    cerr << "max Frequency: " << maxFreq << endl;

    for (const auto& item : freqTable)
    {
        //print hex and character
        if (isprint(item.first))
            cerr << hex << setw(9) << (int)item.first << " " << setw(2) << item.first;
        else
            cerr << hex << setw(9) << (int)item.first << setw(2) << " ";

        //printing frequency
        cerr << " " << setw(11) << dec << item.second << "    ";

        //printing bar chart
        int iMax = ceil(50 * ((double)item.second / (double)maxFreq));
        for (int i = 0; i < iMax; i++)
            cerr << "*";
        cerr << endl;
    }
    return freqTable;
}

int main()
{
    string sourceFile = "test.txt";
    map<char, int> freqTable = checkFrequency(sourceFile);
    Heap<char, int> heapTree;

    for (auto item : freqTable)
        heapTree.push(item.first, item.second);

    heapTree.dump();

    cerr << "\n\nPriority Queue done: Huffman Tree encoding begins...\n" << endl;

    HuffmanTree<char, int> tree;
    tree.makeTree(heapTree);

    tree.dump();

    string filename = "test1.huff";
    encodeFile<char, int>(filename, sourceFile, tree);
    string destFile = "test1.puff";
    decodeFile<char, int>(filename, destFile);
    cerr << endl;
    return 0;
}