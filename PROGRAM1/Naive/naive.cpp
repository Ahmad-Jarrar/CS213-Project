#include "../common.h"

// Initializing character array needed for processing
const char letters[37] = { ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 
                        'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 
                        'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 
                        'x', 'y', 'z', '1', '2', '3', '4', '5', 
                        '6', '7', '8', '9', '0' };

// Initializing morse code array needed for processing
const string morseLetters[37] = {"   ", "._", "_...", "_._.", "_..", 
                                ".", ".._.", "__.", "....", "..", 
                                ".___", "_._", "._..", "__", "_.", 
                                "___", ".__.", "__._", "._.", "...", 
                                "_", ".._", "..._", ".__", "_.._", 
                                "_.__", "__..", ".____", "..___", 
                                "...__", "...._", ".....", "_....", 
                                "__...", "___..", "____.", "_____"};

// Converts morse code to string
string n_CodeToStr(vector<string> textToChange)
{
    string newText = "";

    // iterates over given morse code
    for (unsigned int i = 0; i < textToChange.size(); i++) 
    {
        // iterates over morse code array to get index pos
        for (unsigned short j = 0; j < 37; j++) 
        {
            // if match is found, appends ascii character with
            // same index in ascii array
            if (textToChange[i] == morseLetters[j]) 
            {
                newText += letters[j];
                break;
            }        
        }
    }
    return newText;
}

// Converts string to morse code
string n_StrToCode(string textToChange)
{
    string newText = "";

    // iterates over given ascii characters
    for (unsigned int i = 0; i < textToChange.size(); i++) 
    {
        // iterates over ascii array to get index pos
        for (unsigned short j = 0; j < 37; j++) 
        {
            // if match is found, appends morse code with
            // same index in morse code array
            if (textToChange[i] == letters[j]) 
            {
                newText += morseLetters[j] + " ";
                break;
            }        
        }
    }
    return newText;
}

// Driver code
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
        // prompts user for conversion type input
        cout << endl << "Enter 1 to convert String into Morse Code" << endl;
        cout << "Enter 2 to convert Morse Code into String" << endl;
        cout << "Enter -1 to exit." << endl << endl;

        cout << "Input: ";
        cin >> opt;
        cout << endl;

        // if input not integer, break out of loop
        if(!cin)
            break;

        switch(opt)
        {
            case(1):
                textToChange = "";
                newText = "";

                cout << "Enter Text: " << endl;
                getline(cin>>ws, textToChange);

                // converts all characters to lowercase
                transform(textToChange.begin(), textToChange.end(), 
                            textToChange.begin(), ::tolower);
                
                // starts conversion along with clock
                start = std::chrono::system_clock::now();
                newText = n_StrToCode(textToChange);
                end = std::chrono::system_clock::now(); 

                // prints time and output
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

                // tokenizes morse code on spaces
                codeToChange = tokenize(text, ' ');

                // starts conversion along with clock
                start = std::chrono::system_clock::now();
                newText = n_CodeToStr(codeToChange);
                end = std::chrono::system_clock::now(); 

                // prints time and output
                elapsed_seconds = end - start;
                cout << endl << "String: " << newText << endl;
                cout << "Elapsed time for Naive: " << 
                        elapsed_seconds.count() * 1000 << " ms" << endl;
                break;

            case(-1):
                break;
            
            default:
                cout << "Invalid option" << endl;
        }

    } while(opt != -1);
}