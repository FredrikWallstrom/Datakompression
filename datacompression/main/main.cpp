#include <iostream>

#include "../entropy/Entropy.h"
#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("Please, enter an input file and I will estimate the entropy for that source.\nAlso enter "
                       "an output file so I can store the result.\nCommand: ./yourprogram inputfile outputfile\n");
        return 0;
    }

    char *inputFile = argv[1];

    const char *outputFile = argv[2];
    ofstream outfile;
    outfile.open(outputFile, std::ios_base::app);

    entropy ent;
    vector<char> byteArray = ent.readFile(inputFile);
    outfile << "The file size of " << inputFile  << " " <<  "is:" << endl;
    outfile << byteArray.size() << " " << "Bytes." << endl;


    map<char, int> freqArray = ent.calcFreq(byteArray);
    map<char, int> freqArrayDouble = ent.calcDoubleFreq(byteArray);
    map<char, int> freqArrayTripple = ent.calcTrippleFreq(byteArray);

    vector<double> probArray = ent.calcProb(freqArray, byteArray.size());
    vector<double> probArrayDouble = ent.calcProb(freqArrayDouble, byteArray.size());
    vector<double> probArrayTripple = ent.calcProb(freqArrayTripple, byteArray.size());

    double order0 = ent.calculateEntropy(probArray);
    double order1 = ent.calculateEntropy(probArrayDouble);
    double order2 = ent.calculateEntropy(probArrayTripple);
    outfile << "The entropy is:" << endl;
    outfile << "Markov source of order k = 0:  " << "H(Xi,...,Xi+k) = " << order0 << endl;
    outfile << "Markov source of order k = 1:  " << "H(Xi,...,Xi+k) = " << order1 << endl;
    outfile << "Markov source of order k = 2:  " << "H(Xi,...,Xi+k) = " << order2 << endl;

    outfile << "This gives:" << endl;
    outfile << "Markov source of order k = 0:  " << "H(Xi) = " << order0 << endl;
    outfile << "Markov source of order k = 1:  " << "H(Xi|Xi-k) = " << order1 - order0 << endl;
    outfile << "Markov source of order k = 2:  " << "H(Xi|Xi-1, Xi-k) = " << order2 - order0 - (order1 - order0) << endl;
    outfile << endl;

    outfile.close();
    return 0;
}