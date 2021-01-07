#include <iostream>
#include <string>
#include <algorithm>
#include <chrono> 
#include <ctime> 
#include <vector>
#include <sstream>

using namespace std;

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


class Node{
    public:
        char character;
        Node* left;
        Node* right;

        Node(char ch){
            character = ch;
        }
};

Node* root = new Node(' ');
Node* curr = root;

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

string e_StrToCode(string textToChange)
{
    string newText = "";
    for (unsigned int i = 0; i < textToChange.size(); i++)
        newText += asciiMorseLetters[(int)textToChange[i]-32] + " ";
    
    return newText;
}

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



void
makeTree()
{
    root->left = new Node('e');
    root->right = new Node('t');
    root->left->left = new Node('i');
    root->left->right = new Node('a');
    root->right->left = new Node('n');
    root->right->right = new Node('m');
    root->left->left->left = new Node('s');
    root->left->left->right = new Node('u');
    root->right->left->left = new Node('d');
    root->left->right->left = new Node('r');
    root->right->left->right = new Node('k');
    root->left->right->right = new Node('w');
    root->right->right->left = new Node('g');
    root->right->right->right = new Node('o');
    root->left->left->left->left = new Node('h');
    root->left->left->left->right = new Node('v');
    root->left->left->right->left = new Node('f');
    root->left->right->left->left = new Node('l');
    root->right->left->left->left = new Node('b');
    root->left->left->right->right = new Node('#');
    root->left->right->right->left = new Node('p');
    root->right->left->left->right = new Node('x');
    root->right->left->right->left = new Node('c');
    root->right->right->left->left = new Node('z');
    root->left->right->right->right = new Node('j');
    root->right->left->right->right = new Node('y');
    root->right->right->left->right = new Node('q');
    root->right->right->right->left = new Node('#');
    root->right->right->right->right = new Node('#');
    root->left->left->left->left->left = new Node('5');
    root->right->left->left->left->left = new Node('6');
    root->left->left->left->left->right = new Node('4');
    root->right->right->left->left->left = new Node('7');
    root->left->left->left->right->right = new Node('3');
    root->right->right->right->left->left = new Node('8');
    root->left->left->right->right->right = new Node('2');
    root->right->right->right->right->left = new Node('9');
    root->left->right->right->right->right = new Node('1');
    root->right->right->right->right->right = new Node('0');
}

char
getCode(string str)
{
    curr = root;
    for (int i = 0; i<str.size(); i++)
        if(str[i]=='.')
            curr = curr->left;
        else
            curr = curr->right;

    return curr->character;            
}



string e_CodeToStr(vector<string> textToChange)
{
    string newText = "";
    for (unsigned int i = 0; i < textToChange.size(); i++) 
        newText += getCode(textToChange[i]);
    
    return newText;
}

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