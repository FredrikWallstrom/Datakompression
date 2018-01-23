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
    pair<char*, unsigned long> readFile(char *filename);
    map<char, double> calculateProbability(pair<char*, unsigned long> byteArrayPair);

    double calculateEntropy(map<char, double> probTable);
};


#endif //ENTROPY_ENTROPY_H
