//
// Created by Fredrik Wallström on 2018-01-22.
//

#ifndef ENTROPY_ENTROPY_H
#define ENTROPY_ENTROPY_H


#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class entropy {
public:
    vector<char> readFile(char const *filename);
    map<char, int> calcFreq(vector<char> byteArray);
    map<char, int> calcDoubleFreq(vector<char> byteArray);
    double calculateEntropy(vector<double> freqArray);


    map<char, int> calcTrippleFreq(vector<char> vector);

    vector<double> calcProb(map<char, int> freqArray, unsigned long i);
};


#endif //ENTROPY_ENTROPY_H
