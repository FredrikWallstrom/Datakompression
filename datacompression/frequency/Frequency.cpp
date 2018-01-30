/**
 *
 */

#include "Frequency.h"
#include <fstream>

map<int, double> Frequency::calculateProbability(map<int, int> &frequencyTable, size_t &fileSize){
    map<int, double> probabilityTable;
    for (auto &it : frequencyTable) {
        probabilityTable[it.first] = static_cast<double>(it.second)/static_cast<double>(fileSize);
    }
    return probabilityTable;
}

pair<int, map<int, int> > Frequency::calculateFrequency(char *fileName) {
    // Open the file.
    ifstream file;
    file.open(fileName, ios::in|ios::binary|ios::ate);

    // Get the length of the file.
    file.seekg(0, ios::end);
    auto fileSize = static_cast<size_t>(file.tellg());
    file.seekg(0, ios::beg);

    // Calculate the frequency.
    map<int, int> frequencyTable;
    int c;
    while(true){
        c = file.get();
        if(c == EOF) break;
        frequencyTable[c]++;
    }

    // Close the file.
    file.close();

    return make_pair(fileSize, frequencyTable);
}

map<int, int> Frequency::calculateFrequencyPairs(char *fileName) {
    // Open the file.
    ifstream file;
    file.open(fileName, ios::in|ios::binary|ios::ate);

    // Calculate the frequency of pairs.
    map<int, int> frequencyTable;
    int c1;
    int c2;
    long int pos = 0;
    while(true){
        file.seekg(pos, ios::beg);
        c1 = file.get();
        c2 = file.get();
        if(c1 == EOF || c2 == EOF) break;
        int number = c1 << 8 | c2;
        frequencyTable[number]++;
        pos++;
    }
    // Close the file.
    file.close();

    return frequencyTable;
}

map<int, int> Frequency::calculateFrequencyTripples(char *fileName) {
    // Open the file.
    ifstream file;
    file.open(fileName, ios::in|ios::binary|ios::ate);

    // Calculate the frequency of pairs.
    map<int, int> frequencyTable;
    int c1;
    int c2;
    int c3;
    int pos = 0;
    while(true){
        file.seekg(pos, ios::beg);
        c1 = file.get();
        c2 = file.get();
        c3 = file.get();
        if(c1 == EOF || c2 == EOF || c3 == EOF) break;
        int n1 = c1 << 8 | c2;
        int n2 = n1 << 8 | c3;
        frequencyTable[n2]++;
        pos++;
    }
    // Close the file.
    file.close();
    return frequencyTable;
}