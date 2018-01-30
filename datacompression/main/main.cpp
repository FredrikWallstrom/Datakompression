#include <iostream>

#include "../entropy/Entropy.h"
#include "../huffman/Huffman.h"
#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <string>

using namespace std;

void huffmanCoding(char *inputFile, char *outputFile, string code){
    Huffman huffman;
    if(code == "Encode"){
        huffman.compress(inputFile, outputFile);
    }else if(code == "Decode"){
        huffman.decompress(inputFile, outputFile);
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
                       "\nhe: Encrypt your inputfile with huffman coding, resulting in outputfile.huf"
                       "\nhd: Decrypt your inputfile.huf to normal file, resulting in outputfile.");
        return 0;
    }



    if(string(argv[1]) == "-e"){
        entropyEstimation(argv[2], argv[3]);
    }
    else if(string(argv[1]) == "-he") {
        huffmanCoding(argv[2], argv[3], "Encode");
    }
    else if(string(argv[1]) == "-hd") {
        huffmanCoding(argv[2], argv[3], "Decode");
    }
    return 0;
}