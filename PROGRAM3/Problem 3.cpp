#include <bits/stdc++.h>
using namespace std;

// Function to find the minimum cost
// to convert string a to b
void convertString(string a, string b)
{
    \
    vector<char> char_a, char_b;

    //store characters in a vector
    for (char c : a)
    {
        
        char_a.push_back(c);
        cout<<"String a: "<<c<<endl;
    
    }

    for (char c : b)
    {
        
        char_b.push_back(c);
        cout<<"String b: "<<c<<endl;
    }

    int size;
    

    //find the smallest string
    size = min(char_a.size(), char_b.size());
    

    //insert characters
    for (int i = 0; i < size; ++i)
    {
        if (char_a[i] != char_b[i])
        {
            cout << "Inserted " << char_b[i] << endl;
            char_b[i] = char_a[i];
        }
    }


    //if string to be converted is greater remove characters
    if (char_b.size() > char_a.size())
    {
        char removed;
        int i = char_b.size();
        while (i > char_a.size()){
            removed = char_b.back();
        char_b.pop_back();
        cout << "Deleted " << removed << " from String b " <<endl;
        i--;
        }
    }
//if string to be converted is smaller add characters
    else
    {
        int i = char_b.size();
        char added;
        while (i < char_a.size())
        {
            added = char_a[i];
            char_b.push_back(added);
            cout << "Inserted " << char_a[i] << " at the end of the String b " << endl;
            i++;
        }
    }
    cout<<"Converted String: "<<endl;
    for (char c : char_b)
        cout<<c;
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