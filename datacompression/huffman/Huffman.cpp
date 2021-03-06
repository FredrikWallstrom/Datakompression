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

// Compare operator that makes sure that the lowest frequency has highest priority.
struct nodeComp{
    bool operator()(Node *n1, Node *n2){
        return n1->freq > n2->freq;
    }
};


// Help function to allocate a new node.
Node* Huffman::generateNode(BYTE b, int freq, Node *left, Node *right){
    auto *n = new Node();
    n->byte = b;
    n->freq = freq;
    n->left = left;
    n->right = right;
    return n;
}

Node* Huffman::buildTree(map<BYTE, int> freqTable) {
    priority_queue<Node*, vector<Node*>, nodeComp> pq;
    Node *left;
    Node *right;
    Node *parent;

    // Create leaf node for each char and add it to the queue.
    for(auto i: freqTable){
        Node *n = generateNode(i.first, i.second, nullptr, nullptr);
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
        int freqSum = left->freq + right->freq;
        parent = generateNode('\0', freqSum, left, right);
        pq.push(parent);
    }
    return pq.top();
}


void Huffman::buildEncodingMap(Node* root, map<BYTE, string> &encodingMap, string path) {
    if(root == nullptr) {
        return;
    } else if(root->left == nullptr && root->right == nullptr) {
        encodingMap[root->byte] = path;
    }else{
        buildEncodingMap(root->left, encodingMap, path + "0");
        buildEncodingMap(root->right, encodingMap, path + "1");
    }
}

string Huffman::encodeData(char *fileName, map<BYTE, string> &encodingMap) {
    string result;
    // Open the file.
    ifstream file;
    file.open(fileName, ios::in|ios::binary|ios::ate);
    file.clear();
    file.seekg(0, ios::beg);

    while(true){
        auto character = static_cast<BYTE>(file.get());
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

double Huffman::calculateAverageNumberOfBitsPerCodeword(map<BYTE, string> &encodingMap, map<BYTE, double> &probabilityTable){
    double anobpc = 0.0;
    for(auto it: encodingMap){
        auto length = static_cast<double>(it.second.size());
        BYTE c = it.first;
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
        // Delete the root of the subtree.
        delete node;
    }
}

void Huffman::writeToFile(char *outputFile, string &encodedFile, string header){
    ofstream outfile;
    outfile.open(outputFile, std::ios_base::app);
    outfile << header;
    outfile << encodedFile;
    outfile.close();
}

string Huffman::buildHeader(map<BYTE, int> &freqTable){
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
    char character;
    bool afterColon  = false;

    while(true){
        character = static_cast<char>(file.get());
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
                freq += character;
            }else{
                letter += character;
            }
        }
    }
    return freqTable;
}
string Huffman::decode(Node *root, ifstream &file, int length)
{
    string res;
    Node *node = root;
    for (int i = 0; i != length; ++i)
    {
        auto bit = file.get();
        if (bit == 48) {            // Left child
            node = node->left;
        } else if(bit == 49) {      // Right child
            node = node->right;
        }
        if (node->left == nullptr && node->right == nullptr)
        {
            res += static_cast<char>(node->byte);
            node = root;
        }
    }
    return res;
}

void Huffman::compress(char *fileName, char *outputFile) {
    Frequency freq;
    vector<BYTE> fileData = freq.readFile(fileName);
    unsigned long int fileLength = fileData.size();
    map<BYTE, int> freqTable = freq.calculateFrequency(fileData);

    // Build this header so we can restore the encoded file.
    string header = buildHeader(freqTable);

    // Build encoding tree
    Node *root = buildTree(freqTable);

    // Go through the tree and store the Huffman codes in a map.
    map<BYTE, string> encodingMap;
    buildEncodingMap(root, encodingMap, "");

    // Go through the file and encode the symbols with its corresponding code in the encoding map.
    string encodedFile = encodeData(fileName, encodingMap);
    freeTree(root);

    // Write the result as string to the output file.
    writeToFile(outputFile, encodedFile, header);

   // Only using to print the result in the console.
    map<BYTE, double> probabilityTable = freq.calculateProbability(freqTable, fileLength);
    double rate = calculateAverageNumberOfBitsPerCodeword(encodingMap, probabilityTable);
    writeResult(fileName, fileLength, encodedFile, rate, header);
}


void Huffman::decompress(char *fileName, char *outputFile){
    // Open the file.
    ifstream file;
    file.open(fileName, ios::in|ios::binary|ios::ate);
    file.seekg(0, ios::beg);

    // Restore the frequency table.
    map<int, int> freqTableInt = readHeader(file);

    // Cast all int to unsigned int, BYTE, don't know if this is necessary.
    map<BYTE, int> freqTable;
    for(auto it:freqTableInt) freqTable[static_cast<BYTE>(it.first)] = it.second;

    // Calculate the length of the encoded file
    auto pos = static_cast<int>(file.tellg());
    file.seekg(0, ios::end);
    auto current = static_cast<int>(file.tellg());
    int length = current - pos;
    file.seekg(pos, ios::beg);

    // Build the tree and decode the file.
    Node* root = buildTree(freqTable);
    string decodedFile = decode(root, file, length);
    freeTree(root);

    // Close the file.
    file.close();

    // Write the result to the given output file.
    ofstream outfile;
    outfile.open(outputFile, std::ios_base::app);
    outfile << decodedFile;
    outfile.close();
}

void Huffman::writeResult(char* fileName, size_t length, string &encodedStringOneSymbol, double rateOneSymbol, string header){
    auto lengthBit = static_cast<double>(length*8);
    auto lengthEncodedString = static_cast<double>(encodedStringOneSymbol.size());
    auto lengthHeader = static_cast<double>(header.size()*8);
    double lengthHuffmanCode = lengthHeader+lengthEncodedString;

    cout << "The file size of " << fileName  << " " <<  "is:" << endl;
    cout << length << " " << "Bytes = " << lengthBit << " Bits." << endl;
    cout << "Huffman coding with 1 symbols at a time:" << endl;
    cout << "Length: " << lengthHuffmanCode << " Bits" << endl;
    cout << "Compression rate: " << (1 - lengthHuffmanCode/lengthBit) * 100 << "%" << endl;
    cout << "Rate: " << rateOneSymbol << " Bits/Symbol" << endl;

}



