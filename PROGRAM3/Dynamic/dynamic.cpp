#include "../common.h"

string longest_common_subseq(char *S1, char *S2, int m, int n) 
{
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

// Function to find the minimum cost
// to convert string str1 to str2
void find_characters(string str1, string str2)
{
    int n = str1.length();
    int m = str2.length();
 
    // declaring character array
    char str1_array[n + 1];
    char str2_array[m + 1];
 
    // copying the contents of the
    // string to char array
    strcpy(str1_array, str1.c_str());
    strcpy(str2_array, str2.c_str());

    string lcs = longest_common_subseq(str1_array, str2_array, n, m);

    int ptr = 0;
    
    // Compare lcs with first string to get the
    // characters which are to be deleted
    for (int i = 0; i < str1.size(); i++)
    {
        if (str1[i] == lcs[ptr])
            ptr++;
        else
            deletions.push_back(str1[i]);
    }

    ptr = 0;
    
    // Compare lcs with second string to get the
    // characters which are to be inserted
    for (int i = 0; i < str2.size(); i++)
    {
        if (str2[i] == lcs[ptr])
            ptr++;
        else
            insertions.push_back(str2[i]);
    }
}

int main()
{
    cout << endl << "Program 3: String conversion insertions and deletions.";
    cout << endl << "Dynamic Programming Approach.";
    cout << endl << endl << "This program takes in 2 strings, and outputs the";
    cout << endl << "characters to be inserted and deleted for conversion!";
    cout << endl << endl;
    cout << "You may enter -1 at any input prompt to exit." << endl << endl;

    string str1, str2;
    // keeps prompting for inputs until program terminated
    while (1)
    {
        // takes 2 strings as input
        str1 = enter_str(1);
        str2 = enter_str(2);

        // starts conversion along with clock
        auto start = chrono::steady_clock::now();
        find_characters(str1, str2);
        auto end = chrono::steady_clock::now();

        // prints the result and empties the vectors
        print_result();
        empty_vectors();

        cout << "Elapsed time for Dynamic Approach: ";
        cout << chrono::duration_cast<chrono::microseconds>(end - start).count()
            << " microseconds." << endl << endl;
    }

    return 0;
}