//
// Created by Fredrik Wallström on 2018-01-26.
//

#ifndef DATACOMPRESSION_HUFFMAN_H
#define DATACOMPRESSION_HUFFMAN_H

#include <iostream>
#include <map>
#include <fstream>

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

    void writeResult(char *fileName, char *outputFile, size_t length, string &encodedStringOneSymbol, double rateOneSymbol, string header);

    double calculateAverageNumberOfBitsPerCodeword(map<int, string> &encodingMap, map<int, double> &probabilityTable);

    void freeTree(Node *node);

    void writeToFile(char *outputFile, map<int, double> &freqTable, string &encodedFile, string header);

    void decompress(char *fileName, char *outputFile);

    string buildHeader(map<int, int> &freqTable);

    map<int, int> readHeader(ifstream &inputfile);
};


#endif //DATACOMPRESSION_HUFFMAN_H
