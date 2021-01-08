#include <bits/stdc++.h>
using namespace std;

// Function to find the minimum cost
// to convert string a to b
void convertString(string a, string b)
{

    int count = 0;
    //vector<char> char_a, char_b;
    int freq_a[256] = {0}, freq_b[256] = {0};
    int delete_count = 0;
    int insert_count = 0;

    //store characters in a vector
    for (char c : a)
    {
        //char_a.push_back(c);
        freq_a[(int)c]++;
    }

    for (char c : b)
    {

        // /    char_b.push_back(c);
        freq_b[(int)c]++;
    }

    for (int i = 0; i < b.length(); i++)
    {

        if (freq_a[(int)b.at(i)] < freq_b[(int)b.at(i)])
        {
            if (b.at(i) == ' ')
                cout << "Deleted Space" << endl;
            else
                cout << "Deleted " << b.at(i) << endl;

            freq_b[(int)b.at(i)]--;
            delete_count++;
        }
    }

    for (int i = 0; i < a.length(); i++)
    {
        if (freq_b[(int)a.at(i)] == 0)
        {
            if (a.at(i) == ' ')
                cout << "Inserted Space" << endl;
            else
                cout << "Inserted " << a.at(i) << endl;
            insert_count++;
        }
    }

    cout << "Minimum Number of deletions: " << delete_count << endl;
    cout << "Minimum Number of insertions: " << insert_count << endl;
}

// Driver Code
int main()
{
    string a, b;
    cout << "Enter the string to be converted: " << endl;
    getline(cin, b);
    cout << "Enter the string to be matched: " << endl;
    getline(cin, a);

    // Function Call
    convertString(a, b);

    return 0;
}
