//
// Created by Fredrik on 2018-02-02.
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

static const int BITS_TO_WRITE = 15;
static auto MAX_SIZE_DICTIONARY = static_cast<const int>(exp2(BITS_TO_WRITE));

void loadDictionaryStringKey(unordered_map<string,int> &dictionary){
    for (int i = 0; i < 256; ++i) {
        dictionary[string(1, i)] = i;

    }
}

void loadDictionaryIntKey(unordered_map<int, string> &dictionary){
    for (int i = 0; i < 256; ++i) {
        dictionary[i] = string(1, i);
    }
}

void LZW::decompress(char *fileName, char *outputFile) {
    string s;
    char byte, res;
    char prevCode;
    char currCode;

    int sizeOfDictionary = 256;
    unordered_map<int, string> dictionary;
    loadDictionaryIntKey(dictionary);
    
    // Open the file.
    ifstream file;
    file.open(fileName, ios::in | ios::binary | ios::ate);

    // Get the length of the original file.
    file.seekg(0, ios::end);
    auto originalFileSize = static_cast<double>(file.tellg());
    file.seekg(0, ios::beg);


  //  prevCode = static_cast<char>(file.get());
   // cout << prevCode;


    std::vector<char> result(BITS_TO_WRITE);
    char hej;
    while(true){
        hej = static_cast<char>(file.get());
        if(hej == EOF) break;
        result[0] = hej;
        for (int j = 1; j < 15; ++j) {
            hej = static_cast<char>(file.get());
            result[j] = hej;
        }

        int number = 0;
        int bits = 14;
        auto test = static_cast<int>(exp2(bits));
        cout << result.size() << endl;
        for (int i = 0; i <= 14; ++i) {
            // Taking minus 48 since 0 is interpreted as 48 in ascii table.
            number += (result[i] - 48) * test;
            bits--;
            test = static_cast<int>(exp2(bits));
        }




      /*  s = dictionary[currCode];
       // cout << s << endl;
     //   res += static_cast<char>(s);
        byte = s[0];
        dictionary[sizeOfDictionary++] = prevCode + byte;
        prevCode = currCode;
        */
    }


    file.close();


}

void LZW::compress(char *fileName, char *outputFile) {
    string s;
    char byte;
    int sizeOfDictionary = 256;
    unordered_map<string, int> dictionary;
    loadDictionaryStringKey(dictionary);

    // Open the file.
    ifstream file;
    file.open(fileName, ios::in | ios::binary | ios::ate);

    // Get the length of the original file.
    file.seekg(0, ios::end);
    auto originalFileSize = static_cast<double>(file.tellg());
    file.seekg(0, ios::beg);

    // Open the output stream.
    ofstream outfile;
    outfile.open(outputFile, ios::app | ios::binary);

    // Start compress the file.
    while (true) {
        byte = static_cast<char>(file.get());
        if (byte == EOF) break;

        // If dictionary contains s + byte.
        if (dictionary.find(s + byte) != dictionary.end()) {
            s += byte;
        } else {
            if(!dictionaryIsFull(sizeOfDictionary)){
                // Encode s to result string.
                cout << dictionary[s] << endl;
                outfile << bitset<BITS_TO_WRITE>(static_cast<unsigned long long int>(dictionary[s]));
                // Add s + byte to dictionary.
                dictionary[s + byte] = sizeOfDictionary++;
                s = byte;
            }else{
                outfile << bitset<BITS_TO_WRITE>(static_cast<unsigned long long int>(dictionary[s]));
                s = byte;
            }

        }
    }
    // Encode s to result string.
    outfile << bitset<BITS_TO_WRITE>(static_cast<unsigned long long int>(dictionary[s]));

    // Close the file.
    outfile.close();
    file.close();

    // Open the compressed file.
    ifstream compressedFile;
    compressedFile.open(outputFile, ios::in | ios::binary | ios::ate);

    // Get the length of the compressed file file.
    compressedFile.seekg(0, ios::end);
    auto compressedFileSize = static_cast<double>(compressedFile.tellg());
    originalFileSize = originalFileSize*8;
    compressedFile.close();

    double rate = compressedFileSize / originalFileSize;
    cout << "The file size of " << fileName << " " << "is:" << endl;
    cout << originalFileSize << " " << "Bits" << endl;
    cout << "The size of the LZW compressed file is:" << endl;
    cout << compressedFileSize << " Bits" << endl;
    cout << "Compression rate: " << (1 - rate) * 100 << "%" << endl;
}

bool LZW::dictionaryIsFull(int sizeOfDictionary) {
    return sizeOfDictionary == (MAX_SIZE_DICTIONARY);
}
