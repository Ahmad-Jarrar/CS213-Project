#include "../common.h"

// Function to find the minimum cost
// to convert string str1 to str2
void convert_string(string str1, string str2)
{
    int found = 0;
    int size = 0;
    string final_string = "";

    // iterates over length of string to be 
    // converted (str2) twice
    for (int k = 0; k < str2.length(); k++)
    {
        string b_temp = "";
        found = 0;

        // finds the longest common string from
        // kth position of str2
        for (int i = k; i < str2.length(); i++)
        {
            // iterates over str1 to check for matches
            for (int j = found; j < str1.length(); j++)
            {
                // in case match found, append to 
                // temporary string 'b_temp'
                if (str1.at(j) == str2.at(i))
                {
                    found = j + 1;
                    string temp2(1, str2.at(i));
                    b_temp += temp2;
                    break;
                }
            }
        }

        // if 'b_temp' is bigger than currently found
        // substring, then update the longest common
        // substring found
        if (b_temp.length() > size)
        {
            final_string = b_temp;
            size = final_string.length();
        }
    }

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
        convert_string(str1, str2);
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