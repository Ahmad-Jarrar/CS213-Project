#include "subseq.h"

string longest_common_subseq(char *str1, char *str2, int m, int n) {
    int lcsMat[m + 1][n + 1];

    // Building the longest common subseq matrix
    for (int i = 0; i <= m; i++) 
    {
        for (int j = 0; j <= n; j++) 
        {
            // fill first row and column with zeroes
            if (i == 0 || j == 0)
                lcsMat[i][j] = 0;

            // if unequal, then add the current entry
            // as the maximum from either the adjacent
            // row cell or col cell (left or above)
            else if (str1[i - 1] != str2[j - 1])
                lcsMat[i][j] = max(lcsMat[i - 1][j], 
                    lcsMat[i][j - 1]);

            // if the row and col characters are same,
            // add current entry as the left diagonal 
            // entry + 1
            else
                lcsMat[i][j] = lcsMat[i - 1][j - 1] + 1;
        }
    }

    int index = lcsMat[m][n];
    char subseq[index + 1];
    subseq[index] = '\0';
    int i = m, j = n;

    // Iterating the longest common subseq matrix
    // starting from the maximum values
    while (i > 0 && j > 0) 
    {
        // if the values at str ends are equal
        if (str1[i - 1] == str2[j - 1]) 
        {
            // add the char to final subseq and 
            // move back in the arrays
            subseq[index - 1] = str1[i - 1];
            i--;
            j--;
            index--;
        }
        // if value greater than diagonal, move 
        // towards it
        else if (lcsMat[i - 1][j] > lcsMat[i][j - 1])
            i--;
        else
            j--;
    }

    return string(subseq);
}