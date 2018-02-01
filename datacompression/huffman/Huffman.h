//
// Created by Fredrik Wallström on 2018-01-26.
//

#ifndef DATACOMPRESSION_HUFFMAN_H
#define DATACOMPRESSION_HUFFMAN_H

#include <iostream>
#include <map>
#include <fstream>

using namespace std;
typedef unsigned int BYTE;

struct Node{
    BYTE byte;
    int freq;
    Node *left, *right;
};

class Huffman {

public:

    /**
     * Main function that is called from main when the user wants to compress a file.
     * It will go through every necessary steps like, build frequency table, build tree, build encoding map and so on.
     */
    void compress(char* filename, char* outputFile);

    /**
     * This function is called when the user wants to decompress a already compressed file.
     * The necessary steps is called to reclaim the file, like read header, build coding tree and so on.
     */
    void decompress(char *fileName, char *outputFile);



private:

    /**
     * Helper function that will allocate memory for a new node and assign the parameters for it.
     */
    Node *generateNode(BYTE byte, int freq, Node *left, Node *right);

    /**
     * This function will build the header so we can decode the huffman file.
     * The header consist of the frequency table.
     */
    string buildHeader(map<BYTE, int> &freqTable);

    /**
     * Builds the huffman tree, consisting of nodes with byte, frequency, right- and left childs.
     */
    Node* buildTree(map<BYTE, int> map);

    /**
     * Builds the encoding map, translating every byte to an code if bits. Like A:1000100101 and so on.
     */
    void buildEncodingMap(Node *root, map<BYTE, string> &encodingMap, string path);

    /**
     * This function reads one byte at a time (the character) and looks for this character in the map.
     * It will append the corresponding code to the result string.
     */
    string encodeData(char *fileName, map<BYTE, string> &encodingMap);

    /**
     * Function that iterates over all nodes and delete them.
     */
    void freeTree(Node *node);

    /**
     * This function will write the header and the encoded string together as a string to the output file.
     */
    void writeToFile(char *outputFile, string &encodedFile, string header);

    /**
     * This function is only used to print the results, how much we can compress and the rate. Used for the report.
     */
    void writeResult(char *fileName, char *outputFile, size_t length, string &encodedStringOneSymbol, double rateOneSymbol, string header);

    /**
     * Self descripted, reads the header and return the frequency table as a map.
     */
    map<int, int> readHeader(ifstream &inputfile);

    /**
     * This function is only used for the report. calculates average number of bits per codeword.
     */
    double calculateAverageNumberOfBitsPerCodeword(map<BYTE, string> &encodingMap, map<BYTE, double> &probabilityTable);

    /**
     * Function that will read the inputted huffman file and iterate down in the huffman tree.
     * When it reach a leaf it will append that character to the decoded string and than repeat until whole file is reed.
     */
    string decode(Node *root, ifstream &file, int length);
};


#endif //DATACOMPRESSION_HUFFMAN_H
