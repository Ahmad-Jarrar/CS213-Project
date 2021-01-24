#include "../common.h"

string longest_common_subseq(string str1, string str2)
{
    // variables to hold substrings of str1 and str2
    string str1Sub = "";
    string str2Sub = "";

    // if the 'str1' is not emptied, extract out from
    // second pos upto end of string into 'str1Sub'
    if(!str1.empty())
        str1Sub = str1.substr(1);

    // if the 'str2' is not emptied, extract out from
    // second pos upto end of string into 'str2Sub'
    if(!str2.empty())
        str2Sub = str2.substr(1);

    // if either of the string is empty, return empty string
    if(str1.empty() || str2.empty())
        return "";

    // if theres a match between str1 and str2 first characters
    if(str1[0] == str2[0])
    {
        // add the match to the var 'firstOfStr1'
        string firstOfStr1 = "";
        firstOfStr1 += str1[0];

        // recursive call on str1Sub and str2Sub
        firstOfStr1 += longest_common_subseq(str1Sub, str2Sub);
        return str1[0] + longest_common_subseq(str1Sub, str2Sub);
    }
    else
    {
        string a = longest_common_subseq(str1Sub, str2);
        string b = longest_common_subseq(str1, str2Sub);
        
        if(a.length() > b.length())
            return a;
        else
            return b;
    }
}

// Function to find the minimum cost
// to convert string str1 to str2
void find_characters(string str1, string str2)
{
    int found = 0;
    int size = 0;
    string final_string = "";

    final_string = longest_common_subseq(str1, str2);

    int ptr = 0;

    // compare lcs with first string to get the
    // characters which are to be deleted
    for (int i = 0; i < str1.size(); i++)
    {
        if (str1[i] == final_string[ptr])
            ptr++;
        else
            deletions.push_back(str1[i]);
    }

    ptr = 0;

    // compare lcs with second string to get the
    // characters which are to be inserted
    for (int i = 0; i < str2.size(); i++)
    {
        if (str2[i] == final_string[ptr])
            ptr++;
        else
            insertions.push_back(str2[i]);
    }
}

int main()
{
    cout << endl << "Program 3: String conversion insertions and deletions.";
    cout << endl << "Brute Force Approach.";
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

        cout << "Elapsed time for Brute Approach: ";
        cout << chrono::duration_cast<chrono::microseconds>(end - start).count()
            << " microseconds." << endl << endl;
    }

    return 0;
}