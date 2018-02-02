#include <iostream>

#include "../entropy/Entropy.h"
#include "../huffman/Huffman.h"
#include "../lzw/LZW.h"
#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <string>

using namespace std;

void huffmanCoding(char *inputFile, char *outputFile, const char *code){
    Huffman huffman;
    if(code == "Encode"){
        huffman.compress(inputFile, outputFile);
    }else if(code == "Decode"){
        huffman.decompress(inputFile, outputFile);
    }
}

void lzwCoding(char *inputFile, char *outputFile,  const char *code){
    LZW lzw;
    if(code == "Encode"){
        lzw.compress(inputFile, outputFile);
    }else if(code == "Decode"){
        lzw.decompress(inputFile, outputFile);
    }
}

void entropyEstimation(char *inputFile, char *outputFile){
    Entropy ent;
    ent.entropy(inputFile, outputFile);
}

int main(int argc, char *argv[]) {
    if(argc != 4){
        printf("Instructions to run this program:\nStyle of input should be: ./yourprogram -flag inputfile outputfile\n"
                       "Where the available flags is:\ne: Entropy estimation of inputfile, result is placed in outputfile"
                       "\nhc: Compress your inputfile with Huffman coding, resulting in outputfile"
                       "\nhd: Decompress your inputfile with Huffman coding to normal file, resulting in outputfile."
                       "\nlzwc: Compress your inputfile with LZW coding, resulting in outputfile."
                       "\nlzwd: Decompress your inputfile with LZW coding to normal file, resulting in outputfile.");
        return 0;
    }

    if(string(argv[1]) == "-e"){
        entropyEstimation(argv[2], argv[3]);
    }
    else if(string(argv[1]) == "-hc") {
        huffmanCoding(argv[2], argv[3], "Encode");
    }
    else if(string(argv[1]) == "-hd") {
        huffmanCoding(argv[2], argv[3], "Decode");
    }
    else if(string(argv[1]) == "-lzwc") {
        lzwCoding(argv[2], argv[3], "Decode");
    }
    else if(string(argv[1]) == "-lzwd") {
        lzwCoding(argv[2], argv[3], "Decode");
    }

    return 0;
}