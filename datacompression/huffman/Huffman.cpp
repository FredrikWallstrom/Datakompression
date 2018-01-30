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

void Huffman::writeResult(char* fileName, char* outputFile, size_t length, string &encodedStringOneSymbol, double rateOneSymbol, string header){
    auto lengthBit = static_cast<double>(length*8);
    auto lengthEncodedString = static_cast<double>(encodedStringOneSymbol.size());
    auto lengthHeader = static_cast<double>(header.size()*8);
    double lengthHuffmanCode = lengthHeader+lengthEncodedString;

    ofstream outfile;
    outfile.open(outputFile, std::ios_base::app);

    outfile << "The file size of " << fileName  << " " <<  "is:" << endl;
    outfile << length << " " << "Bytes = " << lengthBit << " Bits." << endl;

    outfile << "Huffman coding with 1 symbols at a time:" << endl;
    outfile << "Length: " << lengthHuffmanCode << " Bits" << endl;
    outfile << "Compression rate: " << (1 - lengthHuffmanCode/lengthBit) * 100 << "%" << endl;
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

void Huffman::writeToFile(char *outputFile, map<int, double> &freqTable, string &encodedFile, string header){
    ofstream outfile;
    outfile.open(outputFile, std::ios_base::app);
    outfile << header;
    outfile << encodedFile;
    outfile.close();
}

string Huffman::buildHeader(map<int, int> &freqTable){
    string header;
    for(auto it: freqTable){
        header += to_string(it.first);
        header += ':';
        header += to_string(it.second);
        header += ' ';
    }
    header += '}';
    return header;
}

map<int, int> Huffman::readHeader(ifstream &file)
{
    map<int, int> freqTable;
    string letter;
    string freq;
    int character;
    bool afterColon  = false;

    while(true){
        character = file.get();
        if(character == '}'){
            break;
        }else if(character == ' '){
            freqTable[stoi(letter)] = stoi(freq);
            freq = "";
            letter = "";
            afterColon = false;
        }else if(character == ':'){
            afterColon = true;
        }else{
            if(afterColon){
                freq += to_string(character);
            }else{
                letter += to_string(character);
            }
        }
    }

    return freqTable;
}


int decodeDataHelper(ifstream &input, Node *root) {
    if(!root->left && !root->right){
        return root->ch;
    }
    else{
        char bit = input.get();

        if (bit == 1){
            decodeDataHelper(input, root->left);
        }else if(bit == 0){
            decodeDataHelper(input, root->right);
        }
    }
}


string decodeData(ifstream &input, Node* encodingTree) {
    string res;
    while(true){
        int result = decodeDataHelper(input, encodingTree);
        if (result == EOF){
            break;
        }else{
            res += result;
        }
    }
    return res;

}

void Huffman::compress(char *fileName, char *outputFile) {
    Frequency freq;

    pair<size_t, map<int, int> > freqTable = freq.calculateFrequency(fileName);
    string header = buildHeader(freqTable.second);

    map<int, double> probabilityTable = freq.calculateProbability(freqTable.second, freqTable.first);
    Node *root = buildTree(probabilityTable);
    // Go through the tree and store the Huffman codes in a map.
    map<int, string> encodingMap;
    buildEncodingMap(root, encodingMap, "");
    // Go through the file and encode the symbols with its corresponding code in the encoding map.
    string encodedFile = encodeData(fileName, encodingMap);

    // Write the result as strings to the output file.
    writeToFile(outputFile, probabilityTable, encodedFile, header);
    freeTree(root);

    // Only using this for the report. Show the rate and how much we can compress a single file.
 //   double rate = calculateAverageNumberOfBitsPerCodeword(encodingMap, probabilityTable);
 //   writeResult(fileName, outputFile, freqTable.first, encodedFile, rate, header);
}

void Huffman::decompress(char *fileName, char *outputFile){
    // Open the file.
    ifstream file;
    file.open(fileName, ios::in|ios::binary|ios::ate);
    file.seekg(0, ios::beg);

    map<int, int> freqTable = readHeader(file);

    // Calculate the length of the encoded file
    int pos = file.tellg();
    file.seekg(0, ios::end);
    int current = file.tellg();
    int length = current - pos;
    file.seekg(pos, ios::beg);

    Frequency freq;
    map<int, double> probabilityTable = freq.calculateProbability(freqTable, reinterpret_cast<size_t &>(length));
    Node* root = buildTree(probabilityTable);
    string decodedFile = decodeData(file, root);
    cout << decodedFile << endl;
    freeTree(root);


    // Close the file.
    file.close();
}


