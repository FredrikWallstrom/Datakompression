//
// Created by Fredrik Wallström on 2018-01-26.
//

#ifndef DATACOMPRESSION_HUFFMAN_H
#define DATACOMPRESSION_HUFFMAN_H

#include <iostream>
#include <map>

using namespace std;

struct Node{
    int ch;
    double prob;
    Node *left, *right;
};

class Huffman {
public:
    void compress(char* filename, char* outputFile);

    Node* buildTree(map<int, double> map);

    string encodeData(char *fileName, const map<int, string> &encodingMap);

    void writeResult(char *fileName, char *outputFile, int length, string &encodedStringOneSymbol, double rateOneSymbol);

    double calculateAverageNumberOfBitsPerCodeword(map<int, string> &encodingMap, map<int, double> &probabilityTable);

    void freeTree(Node *node);
};


#endif //DATACOMPRESSION_HUFFMAN_H
