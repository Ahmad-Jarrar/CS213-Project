#include <bits/stdc++.h>
using namespace std;

// Function to find the minimum cost
// to convert string a to b
void convertString(string a, string b)
{

    int delete_count = 0;
    int insert_count = 0;

    int found = 0;
    int size = 0;
    string final_string = "";

    for (int k = 0; k < a.length(); k++)
    {
        string b_temp = "";
        found = 0;

        for (int i = k; i < a.length(); i++)
        {

            for (int j = found; j < b.length(); j++)
            {

                if (b.at(j) == a.at(i))
                {
                    found = j + 1;
                    string temp2(1, a.at(i));
                    b_temp += temp2;
                    break;
                }
            }
        }
        if (b_temp.length() > size)
        {
            final_string = b_temp;
            size = final_string.length();
        }
    }

    cout << final_string << endl;
    cout << a << endl;
    cout << b << endl;

    int ptr = 0;

    for (int i = 0; i < b.size(); i++)
    {
        if (b[i] == final_string[ptr])
            ptr++;
        else
        {
            if (b[i] == ' ')
                cout << "Deleted space" << endl;
            else
                cout << "Deleted character: " << b[i] << endl;
            delete_count++;
        }
    }
    ptr = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] == final_string[ptr])
            ptr++;
        else
        {
            if (a[i] == ' ')
                cout << "Inserted space" << endl;
            else
                cout << "Insert character: " << a[i] << endl;
            insert_count++;
        }
    }

    cout << "Minimum Number of deletions: " << delete_count << endl;
    cout << "Minimum Number of insertions: " << insert_count << endl;
}

// Driver Code
int main()
{
    do
    {
        cout << "Want to exit the program type -1" << endl;
        string a, b;
        cout << "Enter the string to be converted or exit the program: " << endl;
        getline(cin >> ws, b);
        if (b == "-1")
            break;
        
        cout << "Enter the string to be matched: " << endl;
        getline(cin >> ws, a);
        convertString(a, b);

    } while (true);
    // Function Call

    return 0;
}
