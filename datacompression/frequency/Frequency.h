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
    /**
     * Open the file and read it, store the bytes as unsigned ints int a vector.
     */
    vector<BYTE> readFile(char *fileName);

    /**
     * Calculate the frequency of a single symbol in the file, return a map with the symbol and the frequency.
     */
    map<BYTE, int>  calculateFrequency(vector<BYTE> &fileData);

    /**
     * Calculate the frequency of pair of symbols. Just append two bytes to a single unsigned int.
     * Like 10010001 and 11110000 will be 1001000111110000.
     * Return a map with the unsigned int number and the frequency.
     */
    map<BYTE, int> calculateFrequencyPairs(vector<BYTE> &fileData);

    /**
    * Calculate the frequency of tripples of symbols. Just append three bytes to a single unsigned int.
    * Like 10010001, 11110000 and 00001111 will be 100100011111000000001111.
    * Return a map with the unsigned int number and the frequency.
    */
    map<BYTE, int> calculateFrequencyTripples(vector<BYTE> &fileData);

    /**
     * Function that will take the frequency table and calculate the probability of the symbols.
     */
    map<BYTE, double> calculateProbability(map<BYTE, int> &frequencyTable, size_t &fileSize);
};


#endif //DATACOMPRESSION_FREQUENCY_H
