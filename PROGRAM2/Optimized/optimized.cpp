// source: https://www.geeksforgeeks.org/printing-longest-common-subsequence/
#include "../common.h"

string longest_common_subseq(char *S1, char *S2, int m, int n) {
    int LCS_table[m + 1][n + 1];

    // Building the matrix in bottom-up way
    for (int i = 0; i <= m; i++) 
    {
        for (int j = 0; j <= n; j++) 
        {
            if (i == 0 || j == 0)
                LCS_table[i][j] = 0;
            else if (S1[i - 1] == S2[j - 1])
                LCS_table[i][j] = LCS_table[i - 1][j - 1] + 1;
            else
                LCS_table[i][j] = max(LCS_table[i - 1][j], LCS_table[i][j - 1]);
        }
    }

    int index = LCS_table[m][n];
    char lcsAlgo[index + 1];
    lcsAlgo[index] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) 
    {
        if (S1[i - 1] == S2[j - 1]) {
            lcsAlgo[index - 1] = S1[i - 1];

            i--;
            j--;
            index--;
        }
        else if (LCS_table[i - 1][j] > LCS_table[i][j - 1])
            i--;
        else
            j--;
    }

    // Printing the sub sequences
    //cout << "S1 : " << S1 << "\nS2 : " << S2 << "\nLCS: " << lcsAlgo << "\n";
    cout << "i" << endl;

    return string(lcsAlgo);
}

int main()
{
    cout << endl << "Program 2: Longest common subsequence search.";
    cout << endl << "Optimized approach." << endl << endl;
    cout << "This program takes in 2 strings, and outputs the";
    cout << endl << "longest common subsequence!" << endl << endl;
    cout << "You may enter -1 at any input prompt to exit." << endl << endl;

    string str1, str2, result;
    // keeps prompting for inputs until program terminated
    while (1)
    {
        // takes 2 strings as input
        str1 = enter_str(1);
        str2 = enter_str(2);
 
        int n = str1.length();
        int m = str2.length();
     
        // declaring character array
        char str1_array[n + 1];
        char str2_array[m + 1];
     
        // copying the contents of the
        // string to char array
        strcpy(str1_array, str1.c_str());
        strcpy(str2_array, str2.c_str());

        auto start = chrono::steady_clock::now();
        result = longest_common_subseq(str1_array, str2_array, n, m);
        auto end = chrono::steady_clock::now();

        // prints the longest common substring
        print_result(result);

        cout << "Elapsed time for Optimized: ";
        cout << chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << " microseconds." << endl << endl;
    }
    
    return 0;
}