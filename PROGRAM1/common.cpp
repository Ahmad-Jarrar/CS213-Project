#include "common.h"

// Initializing characters needed for processing
const char letters[37] = { ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 
                        'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 
                        'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 
                        'x', 'y', 'z', '1', '2', '3', '4', '5', 
                        '6', '7', '8', '9', '0' };

// Initializing morse characters needed for processing
const string morseLetters[37] = {"   ", "._", "_...", "_._.", "_..", 
                                ".", ".._.", "__.", "....", "..", 
                                ".___", "_._", "._..", "__", "_.", 
                                "___", ".__.", "__._", "._.", "...", 
                                "_", ".._", "..._", ".__", "_.._", 
                                "_.__", "__..", ".____", "..___", 
                                "...__", "...._", ".....", "_....", 
                                "__...", "___..", "____.", "_____"};

// Initializing ascii morse characters needed for processing
const string asciiMorseLetters[59] = { "   ", "", "", "", "", "", 
                                    "", "", "", "", "", "", "", "", 
                                    "", "", "_____", ".____", "..___", 
                                    "...__", "...._", ".....", "_....", 
                                    "__...", "___..", "____.", "", "", 
                                    "", "", "", "", "", "._", "_...", 
                                    "_._.", "_..", ".", ".._.", "__.", 
                                    "....", "..", ".___", "_._", "._..", 
                                    "__", "_.", "___", ".__.", "__._", 
                                    "._.", "...", "_", ".._", "..._", 
                                    ".__", "_.._", "_.__", "__.."};

vector<string> tokenize(string text, char delimiter) 
{
	string s;
	stringstream ss(text);
	vector<string> tokens;

	while (getline(ss, s, delimiter)) 
	{
		if (s == "")
			continue;

		tokens.push_back(s);
	}
	return tokens;
}