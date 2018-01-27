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

using namespace std;



// Struct that represents the nodes in the tree.
struct node{
    int ch;
    double prob;
    node *left, *right;
};

// Compare operator that makes sure that the lowest probability has highest priority.
struct nodeComp{
    bool operator()(node *n1, node *n2){
        return n1->prob > n2->prob;
    }
};

// Global variable that stores the root node of huffman tree.
node *root;

// Help function to allocate a new node.
node* generateNode(int ch, double prob, node *left, node *right){
    auto *n = new node();
    n->ch = ch;
    n->prob = prob;
    n->left = left;
    n->right = right;
    return n;
}

map<int, double> Huffman::calculateFrequency(char *fileName) {
    // Open the file.
    ifstream file;
    file.open(fileName, ios::in|ios::binary|ios::ate);

    // Get the length of the file.
    file.seekg(0, ios::end);
    auto fileSize = static_cast<size_t>(file.tellg());
    file.seekg(0, ios::beg);
    cout << "The length of the requested file is: " << fileSize << " " << "bytes" << endl;

    // Calculate the frequency.
    map<int, int> frequencyTable;
    int c;
    while(true){
        c = file.get();
        if(c == EOF){
            break;
        }
        frequencyTable[c]++;
    }

    // Close the file.
    file.close();

    // Calculate the probability.
    map<int, double> probabilityTable;
    for (auto &it : frequencyTable) {
        probabilityTable[it.first] = it.second/fileSize;
    }
    return probabilityTable;
}

void Huffman::buildTree(map<int, double> probabilityTable) {
    priority_queue<node*, vector<node*>, nodeComp> pq;

    // Create leaf node for each char and add it to the queue.
    for(auto i: probabilityTable){
        node* n = generateNode(i.first, i.second, nullptr, nullptr);
        pq.push(n);
    }

    while(pq.size() > 1){
        // Start build the tree. Remove the two nodes with the lowest probability.
        node *left = pq.top();
        pq.pop();
        node* right = pq.top();
        pq.pop();

        // Create new node with these two nodes above as children.
        // The probability of this node is the sum of the childrens probability.
        double probSum = left->prob + right->prob;
        node *n = generateNode('\0', probSum, left, right);
        pq.push(n);
    }

    root = pq.top();
}

void Huffman::encode(char *filename) {
    map<int, double> probabilityTable = calculateFrequency(filename);
    buildTree(probabilityTable);



}
