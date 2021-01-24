#include "subseq.h"

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