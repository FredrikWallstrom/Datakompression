//
// Created by Fredrik Wallström on 2018-01-26.
//

#ifndef DATACOMPRESSION_HUFFMAN_H
#define DATACOMPRESSION_HUFFMAN_H

#include <iostream>
#include <map>

using namespace std;

class Huffman {
public:
    void encode(char* filename);

    void buildTree(map<int, double> map);

    map<int, double> calculateFrequency(char *fileName);
};


#endif //DATACOMPRESSION_HUFFMAN_H
