//
// Created by Fredrik Wallström on 2018-01-22.
//

#include "Entropy.h"
#include <iostream>
#include <fstream>      // std::ifstream
#include <string>
#include <map>

using namespace std;

char * entropy::readFile(char *fileName) {
    // Open a ifstream.
    ifstream ifs;
    ifs.open(fileName, ios::in|ios::binary|ios::ate);

    if(ifs.is_open()) {
        // Get the length of the file.
        ifs.seekg(0, ios::end);
        auto length = static_cast<size_t>(ifs.tellg());
        ifs.seekg(0, ios::beg);

        // Read the data.
        auto * byteArray = new char[length + 1];
        ifs.read(byteArray, length);
        byteArray[length] = '\0';

        cout << "The file size of requested file is:" << endl;
        cout << length << endl;

        return byteArray;
    }
    return nullptr;
}

map<char, int> entropy::calculateFreq(const char *byteArray) {

    map<char, int> freqTable;

    int i = 0;
    while(byteArray[i] != '\0'){
        char byte = byteArray[i];
        map <char, int>::iterator iter ;
        iter = freqTable.find(byte) ;

        // Check if character is in the map or not.
        if (iter != freqTable.end()) iter->second += 1 ;
        else freqTable[byte] = 1 ;

        i++;
    }
    return freqTable;
}
