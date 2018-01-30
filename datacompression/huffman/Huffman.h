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
    int freq;
    Node *left, *right;
};

class Huffman {
public:
    void compress(char* filename, char* outputFile);

    Node* buildTree(map<int, int> map);

    string encodeData(char *fileName, const map<int, string> &encodingMap);

    void writeResult(char *fileName, char *outputFile, size_t length, string &encodedStringOneSymbol, double rateOneSymbol, string header);

    double calculateAverageNumberOfBitsPerCodeword(map<int, string> &encodingMap, map<int, double> &probabilityTable);

    void freeTree(Node *node);

    void writeToFile(char *outputFile, string &encodedFile, string header);

    void decompress(char *fileName, char *outputFile);

    string buildHeader(map<int, int> &freqTable);

    map<int, int> readHeader(ifstream &inputfile);

    Node *generateNode(int ch, int freq, Node *left, Node *right);
};


#endif //DATACOMPRESSION_HUFFMAN_H
