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

    /**
     * Compress function. It will read the file and compress it with static LZW compression algorithm.
     */
    void compress(char *fileName, char *outputFile);

    /**
     * Decompression function. It will read the compressed file and decompress it with LZW algorithm.
     */
    void decompress(char *fileName, char *outputFile);

private:

    vector<int> convertToBits(int x);

    string convertToString(int bitsToWrite, const vector<int> &bitRepresentation) const;
};


#endif //DATACOMPRESSION_LZW_H
