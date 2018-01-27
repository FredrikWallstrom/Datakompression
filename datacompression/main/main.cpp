#include <iostream>

#include "../entropy/Entropy.h"
#include "../huffman/Huffman.h"
#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

void huffmanCoding(char *inputFile, char *outputFile, string code){
//    ofstream outfile;
//    outfile.open(outputFile, std::ios_base::app);


    Huffman huffman;
    if(code == "Encode"){
        huffman.encode(inputFile);
    }else{

    }
}

void entropyEstimation(char *inputFile, char *outputFile){
  //  ofstream outfile;
  //  outfile.open(outputFile, std::ios_base::app);



    entropy ent;
    ent.calculateEntropy(inputFile, outputFile);


/*
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
    */
}

int main(int argc, char *argv[]) {
    if(argc != 4){
        printf("Instructions to run this program:\nStyle of input should be: ./yourprogram -flag inputfile outputfile\n"
                       "Where the available flags is:\ne: Entropy estimation of inputfile, result is placed in outputfile"
                       "\nhe: Encrypt your inputfile with huffman coding, resulting in outputfile."
                       "\nhd: Decrypt your huffmanfile to normal file, resulting in outputfile.\""
                       "\nhd: Decrypt your inputfile with huffman coding, resulting in outputfile");
        return 0;
    }


    if(strncmp(argv[1], "-e", 2) == 0){
        entropyEstimation(argv[2], argv[3]);
    }
    if(strncmp(argv[1], "-he", 2) == 0) {
        huffmanCoding(argv[2], argv[3], "Encode");
    }

    return 0;
}