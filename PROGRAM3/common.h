#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string.h>
#include <chrono>

using namespace std;

extern vector<char> insertions;
extern vector<char> deletions;

void print_result();
void empty_vectors();
string enter_str(int);

#endif