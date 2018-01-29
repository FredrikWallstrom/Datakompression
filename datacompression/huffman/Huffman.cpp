//
// Created by Fredrik Wallström on 2018-01-26.
//


#include "Huffman.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <math.h>
#include <queue>
#include "Huffman.h"
#include "../frequency/Frequency.h"

using namespace std;

// Compare operator that makes sure that the lowest probability has highest priority.
struct nodeComp{
    bool operator()(Node *n1, Node *n2){
        return n1->prob > n2->prob;
    }
};


// Help function to allocate a new node.
Node* generateNode(int ch, double prob, Node *left, Node *right){
    auto *n = new Node();
    n->ch = ch;
    n->prob = prob;
    n->left = left;
    n->right = right;
    return n;
}

Node* Huffman::buildTree(map<int, double> probabilityTable) {
    priority_queue<Node*, vector<Node*>, nodeComp> pq;

    // Create leaf node for each char and add it to the queue.
    for(auto i: probabilityTable){
        Node* n = generateNode(i.first, i.second, nullptr, nullptr);
        pq.push(n);
    }

    while(pq.size() != 1){
        // Start build the tree. Remove the two nodes with the lowest probability.
        Node *left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        // Create new parent node with these two nodes above as children.
        // The probability of this node is the sum of the childrens probability.
        double probSum = left->prob + right->prob;
        Node *n = generateNode('\0', probSum, left, right);
        pq.push(n);
    }
    return pq.top();
}


void buildEncodingMap(Node* root, map<int, string> &encodingMap, string path) {
    if(root == nullptr) return;

    // Leaf node found.
    if(root->left == nullptr && root->right == nullptr) encodingMap[root->ch] = path;

    buildEncodingMap(root->left, encodingMap, path + "0");
    buildEncodingMap(root->right, encodingMap, path + "1");
}

/*
 * This function reads one byte at a time (the character) and looks for this character in the map.
 * it Iterate over the path (string) and writes each character as an int to the ouputstream.
 */
string Huffman::encodeData(char *fileName, const map<int, string> &encodingMap, char *output) {
    string result;
    // Open the file.
    ifstream file;
    file.open(fileName, ios::in|ios::binary|ios::ate);

    file.seekg(0, ios::beg);

    while(true){
        int character = file.get();
        if (character == EOF){
            break;
        }
        else{
            string s = encodingMap.at(character);
            result += s;
        }
    }
    // Close the file.
    file.close();

    return result;
}

string Huffman::encodeDataPair(char *fileName, map<int, string> encodingMap) {
    string result;
    // Open the file.
    ifstream file;
    file.open(fileName, ios::in|ios::binary|ios::ate);

    int c1;
    int c2;
    int pos = 0;
    while(true){
        file.seekg(pos, ios::beg);
        c1 = file.get();
        c2 = file.get();
        if(c1 == EOF || c2 == EOF) break;
        int c = c1 + c2;
        string s = encodingMap.at(c);
        result += s;
        pos++;
    }
    // Close the file.
    file.close();

    return result;
}

void Huffman::writeResult(char* fileName, char* outputFile, string encodedString, int length, double rate, int nrOfSymbols){
    double lengthBit = static_cast<double>(length*8);
    double lengthEncodedString = static_cast<double>(encodedString.size());

    ofstream outfile;
    outfile.open(outputFile, std::ios_base::app);

    outfile << "The file size of " << fileName  << " " <<  "is:" << endl;
    outfile << length << " " << "Bytes." << endl;
    outfile << "Which is equal to: " << lengthBit << " Bits" << endl;
    outfile << "Coding with " << nrOfSymbols << " symbol at a time:" << endl;
    outfile << "The encoded file is: " << lengthEncodedString << " Bits" << endl;
    outfile << "Which means we got " << (1 - lengthEncodedString/lengthBit) * 100 << "% compression rate with this "
            "Huffman coding algorithm" << endl;
    outfile << "The rate is: " << rate << " Bits/Symbol" << endl;
    outfile << endl;
    outfile.close();
}

double Huffman::calculateAverageNumberOfBitsPerCodeword(map<int, string> encodingMap, map<int, double> probabilityTable){
    double anobpc = 0.0;

    for(auto it: encodingMap){
        auto length = static_cast<double>(it.second.size());
        int c = it.first;
        auto it1 = probabilityTable.find(c);
        if (it1 != probabilityTable.end()){
            anobpc += length * it1->second;
        }
    }
    return anobpc;
}

void Huffman::freeTree(Node* node) {
    if (node == nullptr){
    }
    else{
        freeTree(node->right);
        node->right = nullptr;
        freeTree(node->left);
        node->left = nullptr;
        // delete the root of the subtree
        delete node;
    }
}

void Huffman::compress(char *fileName, char *outputFile) {

    Frequency freq;


    pair<int, map<int, double> > probabilityPair = freq.calculateFrequency(fileName);
/*
    Node *root = buildTree(probabilityPair.second);

    // Go through the tree and store the Huffman codes in a map.
    map<int, string> encodingMap;
    buildEncodingMap(root, encodingMap, "");

    for(auto it:encodingMap){
        cout << it.first << " " << it.second << endl;
    }

    string encodedFile = encodeData(fileName, encodingMap, outputFile);
    double anobpc = calculateAverageNumberOfBitsPerCodeword(encodingMap, probabilityPair.second);
    double rate = anobpc/1.0;
    writeResult(fileName, outputFile, encodedFile, probabilityPair.first, rate, 1);

    freeTree(root);


    map<int, double> probabilityTable = freq.calculateFrequencyPairs(fileName);
    Node *root1 = buildTree(probabilityTable);

    // Go through the tree and store the Huffman codes in a map.

    map<int, string> testMap;
    buildEncodingMap(root1, testMap, "");

    for(auto it:testMap){
        cout << it.first << " " << it.second << endl;
    }

    string test = encodeDataPair(fileName, testMap);
    double anobpc = calculateAverageNumberOfBitsPerCodeword(testMap, probabilityTable);
    double rate = anobpc/2.0;
    writeResult(fileName, outputFile, test, probabilityPair.first, rate, 2);


    freeTree(root1);

 */
}


