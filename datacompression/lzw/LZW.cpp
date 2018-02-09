//
// Created by Fredrik on 2018-02-02.
//

#include "LZW.h"
#include "../frequency/Frequency.h"
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


vector<int> LZW::convertToBits(int x) {
    vector<int> ret;
    while(x) {
        if (x&1)
            ret.push_back(1);
        else
            ret.push_back(0);
        x>>=1;
    }
    reverse(ret.begin(),ret.end());
    return ret;
}

void LZW::compress(char *fileName, char *outputFile) {
    // Read the uncompressed file.
    Frequency freq;
    vector<unsigned int> uncompressed = freq.readFile(fileName);

    // Open the output file.
    ofstream outfile;
    outfile.open(outputFile, ios::app | ios::binary);

    // Build the dictionary.
    int dictSize = 256;
    map<string, int> dictionary;
    for (int i = 0; i < 256; i++) dictionary[string(1, i)] = i;


    // Main compression algorithm.
    string currentString;
    for (unsigned int i : uncompressed) {
        auto byte = static_cast<char>(i);
        string currentStringAndByte = currentString + byte;


        if (dictionary.find(currentStringAndByte) != dictionary.end()) {

            // If currentString plus one byte exists in the dictionary already, set currentString to that string.
            // Repeat the compression to check if we can find something better i we add another byte.

            currentString = currentStringAndByte;
        }
        else {

            // If currentString plus one byte don't exists in the dictionary, we add currentString plus one to the dictionary.
            // And we start over the compression by set currentString to the last reed byte.

            auto bitsToWrite = static_cast<int>(ceil(log2(dictSize)));
            vector<int> bitRepresentation = convertToBits(dictionary[currentString]);
            outfile << convertToString(bitsToWrite, bitRepresentation);
            dictionary[currentStringAndByte] = dictSize++;
            currentString = string(1, byte);
        }
    }

    if (!currentString.empty()){
        auto bitsToWrite = static_cast<int>(ceil(log2(dictSize)));
        vector<int> bitRepresentation = convertToBits(dictionary[currentString]);
        outfile << convertToString(bitsToWrite, bitRepresentation);
    }

    outfile.close();
    ifstream compressedFile;
    compressedFile.open(outputFile, ios::in | ios::binary | ios::ate);

    // Get the length of the compressed file file and calculate the space saving ratio.
    compressedFile.seekg(0, ios::end);
    auto compressedFileSize = static_cast<double>(compressedFile.tellg());
    auto originalFileSize = static_cast<double>(uncompressed.size()*8);
    compressedFile.close();
    double compressionRatio = compressedFileSize / originalFileSize;
    cout << "The file size of " << fileName << " " << "is:" << endl;
    cout << originalFileSize << " " << "Bits" << endl;
    cout << "The size of the LZW compressed file is:" << endl;
    cout << compressedFileSize << " Bits" << endl;
    cout << "Space Savings: " << (1 - compressionRatio) * 100 << "%" << endl;
    cout << "Rate: " << compressedFileSize/uncompressed.size() << " Bits/Symbol" << endl;
}

string LZW::convertToString(int bitsToWrite, const vector<int> &bitRepresentation) const {
    string res;
    for (int j = 0; j < bitsToWrite; ++j) {
                if(j >= bitRepresentation.size()) res = "0" + res;
                else res.append(to_string(bitRepresentation[j]));
            }
    return res;
}


void LZW::decompress(char *fileName, char *outputFile) {
    // Read the compressed file.
    Frequency freq;
    vector<unsigned int> compressed = freq.readFile(fileName);

    // Build the dictionary.
    int dictSize = 256;
    map<int, string> dictionary;
    for (int i = 0; i < 256; i++) dictionary[i] = string(1, i);

    // Read the first byte in the compressed file.
    string byte;
    int currentPosition = 0;
    int loop = 0;
    while(loop++ < static_cast<int>(ceil(log2(dictSize)))){
        byte += compressed[currentPosition++];
    }

    // Need to adjust the dictionary size here because we gonna read log(dictSize) number of bits.
    dictSize++;

    // Convert the byte string "10101001010101" to corresponding integer.
    string prev(1, stoi(byte, nullptr, 2));
    string result = prev;
    string entry;

    // Decompression algorithm.
    while (currentPosition < compressed.size()) {

        // Read a byte from the compression file.
        byte = "";
        loop = 0;
        while(loop++ < static_cast<int>(ceil(log2(dictSize)))){
            byte += compressed[currentPosition++];
        }

        // Convert the byte string "10101001010101" to corresponding integer.
        int curr = stoi(byte, nullptr, 2);

        // When we coding one symbol, prev, we know that prev is a prefix of the current symbol, curr.
        // Therefore we add previous symbol + the first symbol of current symbol to the dictionary.
        // The else if statement is when current symbol is a reference to itself.
        // Then entry is previous + first symbol of previous.
        // So we always build the dictionary up for possible combinations.
        if (dictionary.find(curr) != dictionary.end()) entry = dictionary[curr];
        else if (curr == dictSize-1) entry = prev + prev[0];

        result += entry;
        dictionary[dictSize++ - 1] = prev + entry[0];
        prev = entry;

    }
    // Open the output file and write the result.
    ofstream outfile;
    outfile.open(outputFile, ios::app | ios::binary);
    outfile << result;
    outfile.close();
}