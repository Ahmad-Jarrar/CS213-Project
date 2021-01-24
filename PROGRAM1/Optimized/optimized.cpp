#include "../common.h"

// Initializing morse code with order corresponding
// to their english characters in ascii table
const string asciiMorseLetters[59] = { "   ", "", "", "", "", "", 
                                    "", "", "", "", "", "", "", "", 
                                    "", "", "_____", ".____", "..___", 
                                    "...__", "...._", ".....", "_....", 
                                    "__...", "___..", "____.", "", "", 
                                    "", "", "", "", "", "._", "_...", 
                                    "_._.", "_..", ".", ".._.", "__.", 
                                    "....", "..", ".___", "_._", "._..", 
                                    "__", "_.", "___", ".__.", "__._", 
                                    "._.", "...", "_", ".._", "..._", 
                                    ".__", "_.._", "_.__", "__.."};

// Node for tree used to convert morse code
// to string
class Node{
    public:
        char character;
        Node* left;
        Node* right;

        Node(char ch)
        {
            character = ch;
        }
};

// A root node with space so that unknown
// characters get replaced with space
Node* root = new Node(' ');
Node* curr = root;

// Creating tree hierarchy from the root, where '.' means
// left child, and '_' means right child
void makeTree()
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

// Convert from string to morse code
string e_StrToCode(string textToChange)
{
    string newText = "";

    // get the morse code directly from asciiMorseLetters array and  
    // append them to 'newText'
    for (unsigned int i = 0; i < textToChange.size(); i++)
        newText += asciiMorseLetters[(int)textToChange[i]-32] + " ";
    
    return newText;
}

// Gets the ascii character by iterating the tree hierarchy using
// the morse code provided
char getCharacter(string code)
{
    // setting current node to root node for every character
    curr = root;
    for (int i = 0; i < code.size(); i++)
    {
        // go to left child if the code is '.'
        if(code[i] == '.')
            curr = curr->left;
        // go to right child if the code is '_'
        else
            curr = curr->right;
    }
    
    return curr->character;            
}

// Converts morse code to string
string e_CodeToStr(vector<string> codeToChange)
{
    string newText = "";
    
    // iterates over tokenized code, and appends the
    // corresponding ascii characters to 'newText'
    for (unsigned int i = 0; i < codeToChange.size(); i++) 
        newText += getCharacter(codeToChange[i]);
    
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
    cout << endl << "Optimized Approach." << endl;
    
    // builds tree hierarchy for conversion
    makeTree();

    do
    {
        // Prompts user for conversion type input
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
                            textToChange.begin(), ::toupper);

                // starts conversion along with clock
                start = std::chrono::system_clock::now();
                newText = e_StrToCode(textToChange);
                end = std::chrono::system_clock::now(); 

                // prints time and output
                elapsed_seconds = end - start;
                cout << endl << "Morse Code: " << newText << endl;
                cout << "Elapsed time for Optimized: " << 
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
                newText = e_CodeToStr(codeToChange);
                end = std::chrono::system_clock::now(); 

                // prints time and output
                elapsed_seconds = end - start;
                cout << endl << "Converted String: " << newText << endl;
                cout << "Elapsed time for Optimized: " << 
                        elapsed_seconds.count() * 1000 << " ms" << endl;
                break;

            case(-1):
                break;
            
            default:
                cout << "Invalid option." << endl;
        }

    } while(opt != -1);
}