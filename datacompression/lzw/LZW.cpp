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

    // This is the main compression algorithm.
    string currentString;
    for (unsigned int i : uncompressed) {
        auto byte = static_cast<char>(i);
        string currentStringAndByte = currentString + byte;

        // If currentString plus one Byte exists in the dictionary already, set currentString to that string.
        if (dictionary.find(currentStringAndByte) != dictionary.end()){
            currentString = currentStringAndByte;
        }
            // If currentString plus ont Byte don't exists in the dictionary. Output corresponding bits of the value to output.
            // Here we have static LZW so we can choose how many bits we output.
            // Also add the currentString plus one Byte to the dictionary if is not full.
        else {
            // Make sure we writem minimum number of bits to output file.
            // log2(dictsize) bits.
            auto bitsToWrite = static_cast<int>(ceil(log2(dictSize)));
            // Convert to bitRepresentation.
            vector<int> bitRepresentation = convertToBits(dictionary[currentString]);
            outfile << convertToString(bitsToWrite, bitRepresentation);
            // Write to output file and add to dictionary.
            dictionary[currentStringAndByte] = dictSize++;
            // Set currentString to the last reed byte.
            currentString = string(1, byte);
        }
    }

    if (!currentString.empty()){
        auto bitsToWrite = static_cast<int>(ceil(log2(dictSize)));
        vector<int> bitRepresentation = convertToBits(dictionary[currentString]);
        outfile << convertToString(bitsToWrite, bitRepresentation);
    }

    // Close the file
    outfile.close();

    // Open the compressed file.
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
}

string LZW::convertToString(int bitsToWrite, const vector<int> &bitRepresentation) const {
    string res = "";
    for (int j = 0; j < bitsToWrite; ++j) {
                if(j > bitRepresentation.size()-1) res = "0" + res;
                else res.append(to_string(bitRepresentation[j]));
            }
    return res;
}


void LZW::decompress(char *fileName, char *outputFile) {

    /*
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
    while(loop++ < STATIC_BITS){
        byte += compressed[currentPosition++];
    }

    // Convert the byte string "10101001010101" to corresponding integer.
    string prev(1, stoi(byte, nullptr, 2));
    string result = prev;
    string entry;

    // Decompression algorithm.
    while (currentPosition < compressed.size()) {

        // Read a byte from the compression file.
        byte = "";
        loop = 0;
        while(loop++ < STATIC_BITS){
            byte += compressed[currentPosition++];
        }

        // Convert the byte string "10101001010101" to corresponding integer.
        int curr = stoi(byte, nullptr, 2);

        // When we coding one symbol, prev, we know that prev is a prefix of the current symbol, curr.
        // Therefore we add prev + entry[0] to the dictionary.
        // So we always build the dictionary up for possible combinations.
        // The entry is either the corresponding string in dictionary if the symbol exists.
        // Or it is the previous string plus the first symbol in previous.
        if (dictionary.count(curr)) entry = dictionary[curr];
        else if (curr == dictSize) entry = prev + prev[0];
        result += entry;
        if(dictSize != exp2(static_cast<double>(STATIC_BITS))) dictionary[dictSize++] = prev + entry[0];
        prev = entry;

    }

    // Open the output file and write the result.
    ofstream outfile;
    outfile.open(outputFile, ios::app | ios::binary);
    outfile << result;
    outfile.close();


     */
}