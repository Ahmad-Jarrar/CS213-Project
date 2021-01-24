#include "common.h"

string 
enter_str(int num)
{
    // prompt user for input, and store in string
	cout << endl << "Please Enter String " << num << ":" << endl;

    string str;
	getline(cin, str);

    // if user enters -1, program is terminated
	if (str == "-1")
		exit(EXIT_SUCCESS);

	return str;
}

void 
print_result(string str)
{
	cout << endl << "Result:" << endl;

    // if string is -1, it means no common substring
	if (str == "")
		cout << "No common subsequence found!" << endl;
	else
	{
		cout << "Longest common subsequence: " << str << endl;
		cout << "Length of subsequence: " << str.length() << endl;
	}
}