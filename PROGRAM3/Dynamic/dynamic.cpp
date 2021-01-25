#include "../common.h"
#include "../../PROGRAM2/Optimized/subseq.h"

// Function to find the minimum cost
// to convert string str1 to str2
void find_characters(string str1, string str2)
{
    int n = str1.length();
    int m = str2.length();

    deletions = "";
    insertions = "";
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
    for (register int i = 0; i < str1.size(); ++i)
    {
        if (str1[i] == lcs[ptr])
            ptr++;
        else
            deletions = deletions +  "\'" + str1[i] + "\' ";
    }

    ptr = 0;

    // Compare lcs with second string to get the
    // characters which are to be inserted
    for (register int i = 0; i < str2.size(); ++i)
    {
        if (str2[i] == lcs[ptr])
            ptr++;
        else
            insertions = insertions + "\'" + str2[i] + "\' ";
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
        

        cout << "Elapsed time for Dynamic Approach: ";
        cout << chrono::duration_cast<chrono::microseconds>(end - start).count()
             << " microseconds." << endl
             << endl;
    }

    return 0;
}
