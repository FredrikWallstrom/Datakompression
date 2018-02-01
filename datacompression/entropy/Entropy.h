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
    /**
    * Function that will be called to calculate the entropy.
    * It will estimate the probability both for single symbol, pair of symbols and tripples of symbols
    * and than calculate the entropy with the chain rule.
    */
    void entropy(char* fileName, char *outputFile);

private:
    /**
    * Help function to calculate the entropy.
    **/
    double calculateEntropy(map<BYTE, double> probabilityTable);

    /**
    * Help function that will write the result of the calculations to a file.
    */
    void writeToFile(char *name, char *file, unsigned long int length, double k0, double k1, double k2);

};


#endif //ENTROPY_ENTROPY_H
