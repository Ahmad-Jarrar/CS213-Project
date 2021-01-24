#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <string>
#include <algorithm>
#include <chrono> 
#include <ctime> 
#include <vector>
#include <sstream>

using namespace std;

extern const char letters[37];
extern const string morseLetters[37];
extern const string asciiMorseLetters[59];

vector<string> tokenize(string, char); 

#endif