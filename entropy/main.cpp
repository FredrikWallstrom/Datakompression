#include <iostream>

#include "Entropy.h"
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    printf("This program was called with \"%s\".\n", argv[0]);

    if (argc < 2) {
        printf("Please, enter an input file and I will estimate the entropy for that source.\nAlso enter "
                       "an output file so I can store the result.\nCommand: ./yourprogram inputfile outputfile\n");
        return 0;
    }

    char *inputFile = argv[1];
    const char *outputFile = argv[2];


    entropy ent;
    char *byteArray = ent.readFile(inputFile);
    map<char, int> freq = ent.calculateFreq(byteArray);

    cout << freq.size() << " " << freq.at('a') << endl;
    return 0;
}