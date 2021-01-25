#include "common.h"


string deletions;
string insertions;

string enter_str(int num)
{
	// prompt user for input, and store in string
	cout << endl
		 << "Please Enter String " << num
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
	cout << endl
		 << "Result:" << endl;

	cout << "Insertions: ";
	cout << insertions;
	cout << endl;

	cout << "Deletions: ";
	cout << deletions;
	cout << endl;
}

