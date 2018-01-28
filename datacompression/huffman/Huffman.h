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

    string encodeData(char *fileName, const map<int, string> &encodingMap, char *output);

    void writeResult(char *fileName, char *outputFile, string encodedString, int length, double rate, int nrOfSymbols);

    double calculateAverageNumberOfBitsPerCodeword(map<int, string> encodingMap, map<int, double> probabilityTable);

    void freeTree(Node *node);

    string encodeDataPair(char *name, map<int, string> map);

};


#endif //DATACOMPRESSION_HUFFMAN_H
