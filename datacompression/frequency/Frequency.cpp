/**
 *
 */

#include "Frequency.h"
#include <fstream>


map<BYTE, double> Frequency::calculateProbability(map<BYTE, int> &frequencyTable, size_t &fileSize){
    map<BYTE, double> probabilityTable;
    for (auto &it : frequencyTable) {
        probabilityTable[it.first] = static_cast<double>(it.second)/static_cast<double>(fileSize);
    }
    return probabilityTable;
}

vector<BYTE> Frequency::readFile(char* fileName){
    // Open the file.
    ifstream file;
    file.open(fileName, ios::in|ios::binary|ios::ate);

    // Get the length of the file.
    file.seekg(0, ios::end);
    auto fileSize = static_cast<size_t>(file.tellg());
    file.seekg(0, ios::beg);

    vector<unsigned char> fileData(fileSize);
    file.read(reinterpret_cast<char *>(&fileData[0]), fileSize);
    file.close();

    // Convert to BYTES (unsigned int)
    vector<BYTE> buffer;
    for(auto c : fileData){
        buffer.push_back(static_cast<BYTE>(c));
    }

    return buffer;
}

map<BYTE, int> Frequency::calculateFrequency(vector<BYTE> &fileData) {
    map<BYTE, int> frequencyTable;
    for (auto it : fileData) {
        frequencyTable[it]++;
    }

    return frequencyTable;
}

map<BYTE, int> Frequency::calculateFrequencyPairs(vector<BYTE> &fileData) {
    map<BYTE, int> frequencyTable;
    for (int i = 0; i < fileData.size(); ++i) {
        if(i+1 == fileData.size()) break;
        BYTE c1 = fileData[i];
        BYTE c2 = fileData[i+1];
        BYTE res = c1 << 8 | c2;
        frequencyTable[res]++;

        /*
        BYTE test1;
        BYTE test2;
        test1 = static_cast<BYTE>(res >> 8);
        test2 = static_cast<BYTE>(res & 0xFF);
        cout << test1 << endl;
        cout << test2 << endl;
         */

    }
    return frequencyTable;
}

map<BYTE, int> Frequency::calculateFrequencyTripples(vector<BYTE> &fileData) {
    map<BYTE, int> frequencyTable;
    for (int i = 0; i < fileData.size(); ++i) {
        if(i+2 == fileData.size()) break;
        BYTE c1 = fileData[i];
        BYTE c2 = fileData[i+1];
        BYTE c3 = fileData[i+2];
        BYTE r = c1 << 8 | c2;
        BYTE res = r << 8 | c3;
        frequencyTable[res]++;
    }
    return frequencyTable;
}