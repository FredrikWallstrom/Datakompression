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
    Node *left;
    Node *right;
    Node *parent;

    // Create leaf node for each char and add it to the queue.
    for(auto i: probabilityTable){
        Node* n = generateNode(i.first, i.second, nullptr, nullptr);
        pq.push(n);
    }

    while(pq.size() > 1){
        // Start build the tree. Remove the two nodes with the lowest probability.
        left = pq.top();
        pq.pop();
        right = pq.top();
        pq.pop();

        // Create new parent node with these two nodes above as children.
        // The probability of this node is the sum of the childrens probability.
        double probSum = left->prob + right->prob;
        parent = generateNode('\0', probSum, left, right);
        pq.push(parent);
    }
    return pq.top();
}


void buildEncodingMap(Node* root, map<int, string> &encodingMap, string path) {
    if(root == nullptr) {
        return;
    } else if(root->left == nullptr && root->right == nullptr) {
        encodingMap[root->ch] = path;
    }else{
        buildEncodingMap(root->left, encodingMap, path + "0");
        buildEncodingMap(root->right, encodingMap, path + "1");
    }
}

/*
 * This function reads one byte at a time (the character) and looks for this character in the map.
 * it Iterate over the path (string) and writes each character as an int to the ouputstream.
 */
string Huffman::encodeData(char *fileName, const map<int, string> &encodingMap) {
    string result;
    // Open the file.
    ifstream file;
    file.open(fileName, ios::in|ios::binary|ios::ate);
    file.clear();
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

void Huffman::writeResult(char* fileName, char* outputFile, int length, string &encodedStringOneSymbol, double rateOneSymbol){
    auto lengthBit = static_cast<double>(length*8);
    auto lengthEncodedStringOneSymbol = static_cast<double>(encodedStringOneSymbol.size());

    ofstream outfile;
    outfile.open(outputFile, std::ios_base::app);

    outfile << "The file size of " << fileName  << " " <<  "is:" << endl;
    outfile << length << " " << "Bytes = " << lengthBit << " Bits." << endl;

    outfile << "Huffman coding with 1 symbols at a time:" << endl;
    outfile << "Length: " << lengthEncodedStringOneSymbol << " Bits" << endl;
    outfile << "Compression rate: " << (1 - lengthEncodedStringOneSymbol/lengthBit) * 100 << "%" << endl;
    outfile << "Rate: " << rateOneSymbol << " Bits/Symbol" << endl;

    outfile << endl;
    outfile.close();
}

double Huffman::calculateAverageNumberOfBitsPerCodeword(map<int, string> &encodingMap, map<int, double> &probabilityTable){
    double anobpc = 0.0;
    for(auto it: encodingMap){
        auto length = static_cast<double>(it.second.size());
        int c = it.first;
        anobpc += probabilityTable[c] * length;
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
    Node *root = buildTree(probabilityPair.second);
    // Go through the tree and store the Huffman codes in a map.
    map<int, string> encodingMap;
    buildEncodingMap(root, encodingMap, "");
    // Go through the file and encode the symbols with its corresponding code in the encoding map.
    string encodedFile = encodeData(fileName, encodingMap);
    double rate = calculateAverageNumberOfBitsPerCodeword(encodingMap, probabilityPair.second);
    freeTree(root);
    writeResult(fileName, outputFile, probabilityPair.first, encodedFile, rate);
}


