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

class Node{
    public:
        char character;
        Node* left;
        Node* right;

        Node(char ch);
};

extern const char letters[37];
extern const string morseLetters[37];
extern const string asciiMorseLetters[59];
extern Node* root;
extern Node* curr;

string n_CodeToStr(vector<string>);
string n_StrToCode(string);
void makeTree();
string e_StrToCode(string);
char getCode(string str);
string e_CodeToStr(vector<string>);


#endif
