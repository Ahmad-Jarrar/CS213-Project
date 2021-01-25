// sources: https://www.geeksforgeeks.org/printing-longest-common-subsequence/
// https://www.programiz.com/dsa/longest-common-subsequence
#include "../common.h"
#include "subseq.h"

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