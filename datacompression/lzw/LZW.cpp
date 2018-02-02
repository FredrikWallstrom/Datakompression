//
// Created by fredr on 2018-02-02.
//

#include "LZW.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
#include <fstream>
#include <vector>


void loadDictionary(unordered_map<string,int> &dictionary){
    for (int i = 0; i < 256; ++i) {
        dictionary[string(1,i)] = i;
    }
}

void LZW::decompress(char *fileName, char *outputFile) {


}

void LZW::compress(char *fileName, char *outputFile) {
    string s;
    char byte;
    int sizeOfDictionary = 256;
    unordered_map<string,int> dictionary;
    loadDictionary(dictionary);

    // Open the file.
    ifstream file;
    file.open(fileName, ios::in|ios::binary|ios::ate);

    // Open the output file.
    ofstream outfile;
    outfile.open(outputFile, std::ios_base::app);

    // Start compress the file.
    while(true){
        byte = static_cast<char>(file.get());
        if(byte == EOF) break;


        // If dictionary contains s + byte
        if(dictionary.find(s+byte) != dictionary.end()){
            s += byte;
        }else{
            // Encode s to output file;
            outfile << s;
            // add s+byte to dictionary
            dictionary[s+byte] = sizeOfDictionary++;
            s = byte;
        }
    }
    // Encode s to output file.
    outfile << s;

    // Close the files.
    outfile.close();
    file.close();
}
