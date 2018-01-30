//
// Created by Fredrik Wallström on 2018-01-22.
//

#include "Entropy.h"
#include "../frequency/Frequency.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <math.h>

using namespace std;

void Entropy::entropy(char *fileName, char *outputFile) {
    Frequency freq;
    pair<size_t , map<int, int> > freqTable = freq.calculateFrequency(fileName);
    size_t fileLength = freqTable.first;
    map<int, double> probabilityTable = freq.calculateProbability(freqTable.second, fileLength);
    double entropyK0 = calculateEntropy(probabilityTable);

    map<int, int> freqTablePair = freq.calculateFrequencyPairs(fileName);
    map<int, double> probabilityTablePair = freq.calculateProbability(freqTablePair, fileLength);
    double entropyK1 = calculateEntropy(probabilityTablePair);

    map<int, int> freqTableTripple = freq.calculateFrequencyTripples(fileName);
    map<int, double> probabilityTableTripple = freq.calculateProbability(freqTableTripple, fileLength);
    double entropyK2 = calculateEntropy(probabilityTableTripple);

    writeToFile(fileName, outputFile, fileLength, entropyK0, entropyK1, entropyK2);
}

double Entropy::calculateEntropy(map<int, double> probabilityTable) {
    double entropy = 0.0;
    for (auto &it : probabilityTable) entropy -= it.second * log2(it.second);
    return entropy;
}

void Entropy::writeToFile(char *fileName, char *outputFile, int length, double k0, double k1, double k2) {
    ofstream outfile;
    outfile.open(outputFile, std::ios_base::app);
    outfile << "The file size of " << fileName  << " " <<  "is:" << endl;
    outfile << length << " " << "Bytes." << endl;
    outfile << "The entropy is:" << endl;
    outfile << "k = 0:  " << "H(Xi,...,Xi+k) = " << k0 << endl;
    outfile << "k = 1:  " << "H(Xi,...,Xi+k) = " << k1 << endl;
    outfile << "k = 2:  " << "H(Xi,...,Xi+k) = " << k2 << endl;
    outfile << "The chain rule gives the conditional entropys:" << endl;
    outfile << "k = 0:  " << "H(Xi) = " << k0 << endl;
    outfile << "k = 1:  " << "H(Xi|Xi-k) = " << k1 - k0 << endl;
    outfile << "k = 2:  " << "H(Xi|Xi-1, Xi-k) = " << k2 - k0 - (k1 - k0) << endl;
    outfile << endl;
    outfile.close();
}


