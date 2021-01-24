#include "common.h"

vector<char> insertions;
vector<char> deletions;

string enter_str(int num)
{
    // prompt user for input, and store in string
	cout << endl << "Please Enter String " << num 
		<< ":" << endl;

    string str;
	getline(cin, str);

    // if user enters -1, program is terminated
	if (str == "-1")
		exit(EXIT_SUCCESS);

	return str;
}

void print_result()
{
	cout << endl << "Result:" << endl;

	cout << "Insertions: ";
	for (int i = 0; i < insertions.size(); i++)
		cout << insertions[i] << " ";
	cout << endl;

	cout << "Deletions: ";
	for (int i = 0; i < deletions.size(); i++)
		cout << deletions[i] << " ";
	cout << endl;
}

void empty_vectors()
{
	while (!insertions.empty())
		insertions.pop_back();
	
	while (!deletions.empty())
		deletions.pop_back();
}