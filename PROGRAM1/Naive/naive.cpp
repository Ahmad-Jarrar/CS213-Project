#include "../common.h"

string n_CodeToStr(vector<string> textToChange)
{
    string newText = "";
    for (unsigned int i = 0; i < textToChange.size(); i++) 
    {
        for (unsigned short j = 0; j < 37; j++) 
        {
            if (textToChange[i] == morseLetters[j]) 
            {
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
    for (unsigned int i = 0; i < textToChange.size(); i++) 
    {
        for (unsigned short j = 0; j < 37; j++) 
        {
            if (textToChange[i] == letters[j]) 
            {
                newText += morseLetters[j] + " ";
                break;
            }        
        }
    }
    return newText;
}

int main()
{
    int opt;
    string newText = "", textToChange = "", text = "";
    vector<string> codeToChange;

    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;

    cout << endl << "Program 1: Conversion between Morse Code & String";
    cout << endl << "Naive Approach." << endl;
    
    do
    {
        cout << endl << "Enter 1 to convert String into Morse Code" << endl;
        cout << "Enter 2 to convert Morse Code into String" << endl;
        cout << "Enter -1 to exit." << endl << endl;

        cout << "Input: ";
        cin >> opt;
        cout << endl;

        if(!cin)
            break;

        switch(opt)
        {
            case(1):
                textToChange = "";
                newText = "";

                cout << "Enter Text: " << endl;
                getline(cin>>ws, textToChange);

                transform(textToChange.begin(), textToChange.end(), 
                            textToChange.begin(), ::tolower);
                
                start = std::chrono::system_clock::now();
                newText = n_StrToCode(textToChange);
                end = std::chrono::system_clock::now(); 

                elapsed_seconds = end - start;
                cout << endl << "Morse Code: " << newText << endl;
                cout << "Elapsed time for Naive: " << 
                        elapsed_seconds.count() * 1000 << " ms" << endl;
                break;

            case(2):
                text = "";
                newText = "";

                cout << "Enter Morse Code: " << endl;
                getline(cin>>ws, text);

                codeToChange = tokenize(text, ' ');

                start = std::chrono::system_clock::now();
                newText = n_CodeToStr(codeToChange);
                end = std::chrono::system_clock::now(); 

                elapsed_seconds = end - start;
                cout << endl << "String: " << newText << endl;
                cout << "Elapsed time for Naive: " << 
                        elapsed_seconds.count() * 1000000 << " ms" << endl;
                break;

            case(-1):
                break;
            
            default:
                cout << "Invalid option" << endl;
        }

    } while(opt != -1);
}