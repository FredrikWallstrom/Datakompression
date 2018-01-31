//
// Created by Fredrik Wallström on 2018-01-28.
//

#ifndef DATACOMPRESSION_FREQUENCY_H
#define DATACOMPRESSION_FREQUENCY_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;
typedef unsigned int BYTE;

class Frequency {

public:
    map<BYTE, int>  calculateFrequency(vector<BYTE> &fileData);
    map<BYTE, int> calculateFrequencyPairs(vector<BYTE> &fileData);
    map<BYTE, int> calculateFrequencyTripples(vector<BYTE> &fileData);
    map<BYTE, double> calculateProbability(map<BYTE, int> &frequencyTable, size_t &fileSize);

    vector<BYTE> readFile(char *fileName);
};


#endif //DATACOMPRESSION_FREQUENCY_H
