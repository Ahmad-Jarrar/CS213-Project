#include "common.h"

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