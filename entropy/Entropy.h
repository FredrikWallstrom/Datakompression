//
// Created by Fredrik Wallström on 2018-01-22.
//

#ifndef ENTROPY_ENTROPY_H
#define ENTROPY_ENTROPY_H


#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;


class entropy {
public:
    char *readFile(char *filename);
    map<char, int> calculateFreq(const char *string);
};


#endif //ENTROPY_ENTROPY_H
