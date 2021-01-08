#include <bits/stdc++.h>
using namespace std;

// Function to find the minimum cost
// to convert string a to b
void convertString(string a, string b)
{

    int count = 0;

    int freq_a[256] = {0}, freq_b[256] = {0};
    int delete_count = 0;
    int insert_count = 0;

    //store characters in a vector
    for (char c : a)
    {
        freq_a[(int)c]++;
    }

    for (char c : b)
    {
        freq_b[(int)c]++;
    }

    int j = 0;
    string b_temp = "";
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
        else
        {
            string temp1(1, b.at(i));
            b_temp += temp1;
        }
    }

    b = b_temp;

    for (int i = 0; i < a.length(); i++)
    {

        if (i < b.length() && a.at(i) == b.at(i))
        {

            continue;
        }
        else
        {

            string temp2(1, a.at(i));

            if (i < b.length())
            {
                b.insert(i, temp2);
            }
            else
                b += temp2;

            if (temp2 == " ")
                cout << "Inserted space" << endl;

            else
                cout << "Inserted: " << a.at(i) << endl;
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
