#include "common.h"


const char letters[37] = { ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                             't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };

const string morseLetters[37] = { "   ", "._", "_...", "_._.", "_..", ".", ".._.", "__.", "....", "..", ".___", "_._", "._..",
                                  "__", "_.", "___", ".__.", "__._", "._.", "...", "_", ".._", "..._", ".__", "_.._", "_.__", 
                                  "__..", ".____", "..___", "...__", "...._", ".....", "_....", "__...", "___..", "____.", "_____"};

const string asciiMorseLetters[59] = { "   ", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                    "_____", ".____", "..___", "...__", "...._", ".....", "_....", "__...", "___..", "____.",
                                    "", "", "", "", "", "", "",
                                    "._", "_...", "_._.", "_..", ".", ".._.", "__.", "....", "..", ".___", "_._", "._..",  "__",
                                    "_.", "___", ".__.", "__._", "._.", "...", "_", ".._", "..._", ".__", "_.._", "_.__", "__.."};


Node :: Node(char ch)
: character(ch)
{}

Node* root = new Node(' ');
Node* curr = root;

vector<string> 
tokenize (string command, char delimiter) 
{
	string s;
	stringstream ss(command);
	vector<string> tokens;

	while (getline(ss, s, delimiter)) 
	{
		if (s == "")
			continue;

		tokens.push_back(s);
	}
	return tokens;
}


int main()
{
    int opt;
    string newText = "";

    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
    
    do
    {
        cout <<"\nPress 1 to convert string into Morse code"<<endl;
        cout <<"Press 2 to convert Morse code into string"<<endl;
        cout <<"Press -1 to exit"<<endl;

        makeTree();

        cin >> opt;
        switch(opt)
        {
            case(1):
            {
                string textToChange = "";
                newText = "";
                cout << "Enter text you want to change to Morse code" << endl;
                getline(cin>>ws, textToChange);

                transform(textToChange.begin(), textToChange.end(), textToChange.begin(), ::tolower);
                
                start = std::chrono::system_clock::now();
                newText = n_StrToCode(textToChange);
                end = std::chrono::system_clock::now(); 

                elapsed_seconds = end - start;
                cout << "\nConverted Morse Code: " << newText << endl;
                cout << "Elapsed time for naive: " << elapsed_seconds.count() * 1000 << "ms" << endl;

                transform(textToChange.begin(), textToChange.end(), textToChange.begin(), ::toupper);


                start = std::chrono::system_clock::now();
                newText = e_StrToCode(textToChange);
                end = std::chrono::system_clock::now(); 

                elapsed_seconds = end - start;
                cout << "Converted Morse Code: " << newText << endl;
                cout << "Elapsed time for our algorithm: " << elapsed_seconds.count() * 1000 << "ms" << endl;


                break;
            }

            case(2):
            {
                string text = "";
                newText = "";

                cout << "Enter Morse code you want to change to text" << endl;
                getline(cin>>ws, text);

                vector<string> textToChange = tokenize(text,' ');

                start = std::chrono::system_clock::now();
                newText = n_CodeToStr(textToChange);
                end = std::chrono::system_clock::now(); 

                elapsed_seconds = end - start;
                cout << "\nConverted String: " << newText << endl;
                cout << "Elapsed time for naive: " << elapsed_seconds.count() * 1000 << "ms" << endl;

                start = std::chrono::system_clock::now();
                newText = e_CodeToStr(textToChange);
                end = std::chrono::system_clock::now(); 

                elapsed_seconds = end - start;
                cout << "Converted String: " << newText << endl;
                cout << "Elapsed time for our algorithm: " << elapsed_seconds.count() * 1000 << "ms" << endl;

            }

            case(-1):
            {
                break;
            }
            
            default:
                cout<<"Invalid option" << endl;;    
        }
    }while(opt != -1);
}