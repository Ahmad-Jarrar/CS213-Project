#include "../common.h"

// Function to find the minimum cost
// to convert string str1 to str2
void convert_string(string str1, string str2)
{
    int m = str1.size();
    int n = str2.size();
    int L[m+1][n+1];

    // using str1 2D Matrix for dynamic programming
    // L[i][j] stores length of longest common string 
    // for X[0:i] and Y[0:j]
    for(int i = 0; i < m + 1; i++)
    {
        for(int j = 0; j < n + 1; j++)
        {
            if(i == 0 || j == 0)
                L[i][j] = 0;
            else if(str1[i-1]==str2[j-1])
                L[i][j] = L[i-1][j-1] + 1;
            else
                L[i][j] = max(L[i-1][j], L[i][j-1]);        
        }
    }

    // Following code is used to find the common string 
    int index = L[m][n];

    // Create str1 character array to store the lcs string
    char lcs[index + 1];

    // Start from the right-most-bottom-most corner and 
    // one by one store characters in lcs[]
    int i = m, j = n;
    while( i > 0 && j > 0)
    {
        // If current character in X[] and Y are same, then 
        // current character is part of LCS
        if(str1[i-1] == str2[j-1])
        {
            lcs[index-1] = str1[i-1];
            i--;
            j--;
            index--;
        }

        // If not same, then find the larger of two and 
        // go in the direction of larger value
        else if(L[i-1][j] > L[i][j-1])
            i--;
        else
            j--;
    }

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

        auto start = chrono::steady_clock::now();
        convert_string(str1, str2);
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