#include <iostream>
#include <cstdlib>
#include <vector>
#include <string.h>

using namespace std;

string enter_str(int num)
{
    /* prompt user for input, and store in string */
	cout << endl << "Please Enter String " << num << ":" << endl;

    string str;
	getline(cin, str);

    /* if user enters -1, program is terminated */
	if (str == "-1")
		exit(EXIT_SUCCESS);

	return str;
}

void print_result(string str)
{
	cout << endl << "Result:" << endl;

    /* if string is -1, it means no common substring */
	if (str == "-1")
		cout << "No common substring found!" << endl << endl;
	else
	{
		cout << "Longest common substring: " << str << endl;
		cout << "Length of substring: " << str.length() << endl << endl;
	}
}

string longest_common_substr(string str1, string str2)
{
    /* Store length of both the strings */
    int m = str1.length();
    int n = str2.length();
 
 	/* Var 'maxlen' stores length of lcs
 	   Var 'end' stores end of lcs in str1
 	   Matrix 'mat' stores maxlen of 2 rows consecutively
	   Var 'row' tracks which row is current row of 'mat'
 	*/
    int maxlen = 0, row = 0, end, mat[2][n];
 
    /* mat[row][j] is iterated on alternative rows in each iteration
       of i, and the longest common substring length is stored in the
       current row (by referring to the previously stored value as well) */

    register int i = 0;
    register int j = 0;

    for (i = 0; i <= m; ++i) 
    {
        for (j = 0; j <= n; ++j) 
        {
            if (!(i == 0 || j == 0) && (str1[i - 1] == str2[j - 1])) 
            {
                mat[row][j] = mat[1 - row][j - 1] + 1;

                if (mat[row][j] > maxlen) 
                {
                    maxlen = mat[row][j];
                    end = i - 1;
                }
            }

            else
                mat[row][j] = 0;
        }
 
        /* Switch between rows (curr is prev, prev is curr) */
        row = 1 - row;
    }
 
    /* Longest common substring is from end - maxlen + 1 for size maxlen */
    if (maxlen != 0)
        return str1.substr(end - maxlen + 1, maxlen);

    /* If there is no common substring, return -1 */
 	else
 		return "-1";
}

int main()
{
	cout << endl << "Welcome!" << endl << endl;
	cout << "This program takes in 2 strings, and outputs" << endl;
	cout << "the longest common substring!" << endl << endl;
	cout << "You may enter -1 at any input prompt to exit." << endl << endl;

    /* keeps prompting for inputs until program terminated */
	while (1)
	{
        /* takes 2 strings as input */
		string str1 = enter_str(1);
		string str2 = enter_str(2);

        /* finds longest common substring in them */
		string result = longest_common_substr(str1, str2);

        /* prints the longest common substring */
	    print_result(result);
	}
    
    return 0;
}