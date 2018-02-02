//
// Created by fredr on 2018-02-02.
//

#ifndef DATACOMPRESSION_LZW_H
#define DATACOMPRESSION_LZW_H

#include <array>

typedef unsigned int BYTE;

using namespace std;
class LZW {
public:

    void compress(char *fileName, char *outputFile);
    void decompress(char *fileName, char *outputFile);

};


#endif //DATACOMPRESSION_LZW_H
