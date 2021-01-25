#include "subseq.h"

string longest_common_subseq(string str1, string str2)
{
    // if either of the string is empty, return empty string
    if(str1.empty() || str2.empty())
        return "";
    
    // extract substring starting from second 
    // index upto the of string
    string str1Sub = str1.substr(1);
    string str2Sub = str2.substr(1);

    // if there is no match, send with one original and one substring
    if(str1[0] != str2[0])
    {
        string temp1 = longest_common_subseq(str1Sub, str2);
        string temp2 = longest_common_subseq(str1, str2Sub);
        
        // return whichever is the longer subsequence found
        if(temp1.length() >= temp2.length())
            return temp1;
        else
            return temp2;
    }
    // if theres a match between str1 and str2 first characters
    else
    {
        // add the match to the var 'firstOfStr1'
        string firstOfStr1 = "";
        firstOfStr1 += str1[0];

        // recursive call on str1Sub and str2Sub
        firstOfStr1 += longest_common_subseq(str1Sub, str2Sub);
        return str1[0] + longest_common_subseq(str1Sub, str2Sub);
    }
}