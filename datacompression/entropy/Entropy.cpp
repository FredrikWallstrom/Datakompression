//
// Created by Fredrik Wallström on 2018-01-22.
//

#include "Entropy.h"
#include <iostream>
#include <fstream>      // std::ifstream
#include <string>
#include <map>
#include <math.h>

using namespace std;

pair<char*, unsigned long> entropy::readFile(char *fileName) {
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

        return make_pair(byteArray, length);
    }
    return make_pair(nullptr, 0);
}

map<char, double> entropy::calculateProbability(pair<char*, unsigned long> byteArrayPair) {

    map<char, int> freqTable;
    int i = 0;
    while(byteArrayPair.first[i] != '\0'){
        char byte = byteArrayPair.first[i];
        map <char, int>::iterator iter ;
        iter = freqTable.find(byte) ;

        // Check if character is in the map or not.
        if (iter != freqTable.end()) iter->second += 1 ;
        else freqTable[byte] = 1 ;

        i++;
    }

    map<char, double> probTable;
    for (auto &it : freqTable) {
        double prob = it.second / (double)byteArrayPair.second;
        probTable[it.first] = prob;
    }


    return probTable;
}

double entropy::calculateEntropy(map<char, double> probTable) {
    double entropy = 0.0;

    for (auto &it : probTable) {
        entropy += it.second * log2(it.second);
    }
    return entropy * -1;
}
