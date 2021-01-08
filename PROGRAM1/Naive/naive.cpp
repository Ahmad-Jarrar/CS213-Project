#include "../common.h"

string n_CodeToStr(vector<string> textToChange)
{
    string newText = "";
    for (unsigned int i = 0; i < textToChange.size(); i++) {
        for (unsigned short j = 0; j < 37; j++) {
            if (textToChange[i] == morseLetters[j]) {
                newText += letters[j];
            break;
            }        
        }
    }
    return newText;
}

string n_StrToCode(string textToChange)
{
    string newText = "";
    for (unsigned int i = 0; i < textToChange.size(); i++) {
        for (unsigned short j = 0; j < 37; j++) {
            if (textToChange[i] == letters[j]) {
                newText += morseLetters[j] + " ";
            break;
            }        
        }
    }
    return newText;
}