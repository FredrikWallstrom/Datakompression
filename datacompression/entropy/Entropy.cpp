//
// Created by Fredrik Wallström on 2018-01-22.
//

#include "Entropy.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <math.h>

using namespace std;

vector<char> entropy::readFile(char const *fileName) {

    // Open the file.
    std::ifstream file;
    file.open(fileName);

    // Get the length of the file.
    file.seekg(0, ios::end);
    auto fileSize = static_cast<size_t>(file.tellg());
    file.seekg(0, ios::beg);

    // Create a vector to hold all the bytes in the file.
    std::vector<char> data(fileSize, 0);

    // Read the file
    file.read(&data[0], fileSize);
    return data;
}

double entropy::calculateEntropy(vector<double> freqArray) {
    double entropy = 0.0;
    for (double i : freqArray) {
        if(i > 0) entropy -= i * log2(i);

    }
    return entropy;
}

map<char, int> entropy::calcFreq(vector<char> byteArray) {
    map<char, int> freq;

    for (int j = 0; j < byteArray.size(); ++j) {
        if (freq.find(byteArray[j]) == freq.end() ) {
            // Not found.
            freq[byteArray[j]] = 1;
        } else {
            // Found.
            freq[byteArray[j]]++;
        }
    }
    return freq;
}

map<char, int> entropy::calcDoubleFreq(vector<char> byteArray) {
    map<char, int> doubleFreq;

    for (int j = 0; j < byteArray.size(); ++j) {
        if((j+1) >= byteArray.size()) continue;
        char byte = byteArray[j] + byteArray[j+1];

        if (doubleFreq.find(byte) == doubleFreq.end() ) {
            // Not found.
            doubleFreq[byte] = 1;
        } else {
            // Found.
            doubleFreq[byte]++;
        }
    }
    return doubleFreq;
}

map<char, int> entropy::calcTrippleFreq(vector<char> byteArray) {
    map<char, int> trippleFreq;

    for (int j = 0; j < byteArray.size(); ++j) {
        if((j+2) >= byteArray.size()) continue;
        char byte = byteArray[j] + byteArray[j+1] + byteArray[j+2];

        if (trippleFreq.find(byte) == trippleFreq.end() ) {
            // Not found.
            trippleFreq[byte] = 1;
        } else {
            // Found.
            trippleFreq[byte]++;
        }
    }
    return trippleFreq;
}

vector<double> entropy::calcProb(map<char, int> freqArray, unsigned long length) {
    vector<double> probArray;

    for (map<char,int>::iterator it=freqArray.begin(); it!=freqArray.end(); ++it){
        double prob = (double) it->second / (double)length;
    //    cout << prob << endl;
        probArray.push_back(prob);
    }

    return probArray;
}



