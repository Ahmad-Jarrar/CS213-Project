// source: https://iq.opengenus.org/longest-common-substring/
#include "../common.h"

string longest_common_substr(string str1, string str2)
{
    string ans;
    bool flg = false;

    for (int i = 0; i < str1.length(); i++)
    {
        for (int j = i; j < str1.length(); j++)
        {
		    // substring of str1 of length (j-i+1)
            string x = str1.substr(i, j - i + 1);
            int t = 0;
            for (int k = 0; k < str2.length(); k++)
            {
				// if character of substring matches
				// that of other string
                if(str2[k] == x[t])
                    t++;
				// if substring found
                else if(t == x.length())
                    break;
                else
                    t = 0;
            }
            if (t == x.length())
            {
                flg = true;
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
    cout << endl << "Program 2: Longest common substring search.";
    cout << endl << "Naive approach." << endl << endl;
    cout << "This program takes in 2 strings, and outputs the";
    cout << endl << "longest common substring!" << endl << endl;
    cout << "You may enter -1 at any input prompt to exit." << endl << endl;

    string str1, str2, result;
    // keeps prompting for inputs until program terminated
    while (1)
    {
        // takes 2 strings as input
        str1 = enter_str(1);
        str2 = enter_str(2);

        auto start = chrono::steady_clock::now();
        result = longest_common_substr(str1, str2);
        auto end = chrono::steady_clock::now();

        // prints the longest common substring
        print_result(result);

        cout << "Elapsed time for Naive: ";
        cout << chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << " microseconds." << endl << endl;
    }
    
    return 0;
}