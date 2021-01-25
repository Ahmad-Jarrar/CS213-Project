// sources: https://medium.com/@matthewwestmk/finding-the-longest-common-subsequence-lcs-of-two-strings-c68f7ec201fe
// https://stackoverflow.com/questions/34412496/naive-approach-to-longest-common-subsequence
#include "../common.h"
#include "subseq.h"

int main()
{
    cout << endl << "Program 2: Longest common subsequence search.";
    cout << endl << "Naive approach." << endl << endl;
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

        auto start = chrono::steady_clock::now();
        result = longest_common_subseq(str1, str2);
        auto end = chrono::steady_clock::now();

        // prints the longest common substring
        print_result(result);

        cout << "Elapsed time for Naive: ";
        cout << chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << " microseconds." << endl << endl;
    }
}