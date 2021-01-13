// source: https://iq.opengenus.org/longest-common-substring/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string.h>
#include <chrono>

using namespace std;

string enter_str(int num)
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

void print_result(string str)
{
	cout << endl << "Result:" << endl;

    // if string is -1, it means no common substring
	if (str == "-1")
		cout << "No common substring found!" << endl;
	else
	{
		cout << "Longest common substring: " << str << endl;
		cout << "Length of substring: " << str.length() << endl;
	}
}

string longest_common_substr(string a,string b)
{
    string ans;
    int flg = 0;

    for (int i = 0; i < a.length(); i++)
    {
        for (int j = i; j < a.length(); j++)
        {
		    // substring of a of length (j-i+1)
            string x = a.substr(i, j - i + 1);
            int t = 0;
            for (int k = 0; k < b.length(); k++)
            {
				// if character of substring matches
				// that of other string
                if(b[k] == x[t])
                    t++;
				// if substring found
                else if(t == x.length())
                    break;
                else
                    t=0;
            }
            if (t == x.length())
            {
                flg = 1;
				// if the length of found substring 
				// is greater than that of result 
				// update result
                if(ans.length() < x.length())
                    ans = x;
            }
        }
    }

    if (flg)
        return ans;

    // if no common substring found
    else
        return "-1";
}

int main()
{
	cout << endl << "Longest common substring search: Naive approach";
	cout << endl << endl << "This program takes in 2 strings, and outputs";
	cout << endl << "the longest common substring!" << endl << endl;
	cout << "You may enter -1 at any input prompt to exit." << endl << endl;

    // keeps prompting for inputs until program terminated
	while (1)
	{
        // takes 2 strings as input
		string str1 = enter_str(1);
		string str2 = enter_str(2);

		auto start = chrono::steady_clock::now();

        // finds longest common substring in str1 and str2
		string result = longest_common_substr(str1, str2);

		auto end = chrono::steady_clock::now();

        // prints the longest common substring
	    print_result(result);

	    cout << "Time taken: ";
	    cout << chrono::duration_cast<chrono::microseconds>(end - start).count();
	    cout << " microseconds."<< endl << endl;
	}
    
    return 0;
}