// source: https://www.geeksforgeeks.org/print-longest-common-substring/
#include "../common.h"

string longest_common_substr(string str1, string str2)
{
    // Store length of both strings
    int m = str1.length();
    int n = str2.length();

    // Matrix to store result of two rows consequetively
    int dp[2][n+1];

    // var 'res' stores length of lcs
    // var 'end' stores endpoint of lcs in str1
    // var 'row' indicates which row of matrix is current
    int curr = 0, res = 0, end = 0;
    
    // Loops over str1 length
    for(int i = 0; i <= m; i++)
    {
        // Loops over str2 length
        for(int j = 0; j <= n; j++)
        {
            // For a particular value of i and j, matrix
            // Stores the locs length in str1 and str2
            if(i == 0 || j == 0)
                dp[curr][j] = 0;

            else if(str1[i - 1] == str2[j - 1])
            {
                dp[curr][j] = dp[1 - curr][j - 1] + 1;
                if(res < dp[curr][j])
                {
                    res = dp[curr][j];
                    end = i - 1;
                }
            }
            else
                dp[curr][j] = 0;
        }

        // Switch between rows, current is previous and
        // Previous is current
        curr = 1 - curr;
    }

    // Lcs is from index (end - result + 1) for size 'res'
    if(res != 0)
        return str1.substr(end - res + 1, res);
    // If no common substring, return "-1"
    else
        return "-1";
}

int main()
{
    cout << endl << "Program 2: Longest common substring search.";
    cout << endl << "Optimized approach." << endl << endl;
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

        cout << "Elapsed time for Optimized: ";
        cout << chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << " microseconds." << endl << endl;
    }
    
    return 0;
}