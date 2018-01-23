#include <iostream>

#include "../entropy/Entropy.h"
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Please, enter an input file and I will estimate the entropy for that source.\nAlso enter "
                       "an output file so I can store the result.\nCommand: ./yourprogram inputfile outputfile\n");
        return 0;
    }

    char *inputFile = argv[1];
    const char *outputFile = argv[2];


    entropy ent;
    pair<char*, unsigned long> byteArrayPair = ent.readFile(inputFile);
    cout << "The file size of requested file is:" << endl;
    cout << byteArrayPair.second << " " << "Bytes." << endl;

    map<char, double> probTable = ent.calculateProbability(byteArrayPair);

    double entropy = ent.calculateEntropy(probTable);

    cout << "The entropy of the requested file is:" << endl;
    cout << "H(X) = " << entropy << endl;
    return 0;
}