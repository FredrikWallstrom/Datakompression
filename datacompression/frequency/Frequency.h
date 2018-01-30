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

class Frequency {

public:
    pair<int, map<int, int> > calculateFrequency(char *fileName);
    map<int, int> calculateFrequencyPairs(char *name);
    map<int, int> calculateFrequencyTripples(char *name);
    map<int, double> calculateProbability(map<int, int> &frequencyTable, size_t &fileSize);
};


#endif //DATACOMPRESSION_FREQUENCY_H
