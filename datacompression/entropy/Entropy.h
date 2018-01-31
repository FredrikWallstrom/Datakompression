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
typedef unsigned int BYTE;

class Entropy {

public:
    void entropy(char* fileName, char *outputFile);

private:
    double calculateEntropy(map<BYTE, double> probabilityTable);
    void writeToFile(char *name, char *file, unsigned long int length, double k0, double k1, double k2);

};


#endif //ENTROPY_ENTROPY_H
