#include "../common.h"

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

Node* root = new Node(' ');
Node* curr = root;

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

string e_StrToCode(string textToChange)
{
    string newText = "";
    for (unsigned int i = 0; i < textToChange.size(); i++)
        newText += asciiMorseLetters[(int)textToChange[i]-32] + " ";
    
    return newText;
}

char getCode(string str)
{
    curr = root;
    for (int i = 0; i < str.size(); i++)
    {
        if(str[i]=='.')
            curr = curr->left;
        else
            curr = curr->right;
    }
    
    return curr->character;            
}

string e_CodeToStr(vector<string> textToChange)
{
    string newText = "";
    
    for (unsigned int i = 0; i < textToChange.size(); i++) 
        newText += getCode(textToChange[i]);
    
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
    
    do
    {
        cout << endl << "Enter 1 to convert String into Morse Code" << endl;
        cout << "Enter 2 to convert Morse Code into String" << endl;
        cout << "Enter -1 to exit." << endl << endl;

        makeTree();

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
                            textToChange.begin(), ::toupper);

                start = std::chrono::system_clock::now();
                newText = e_StrToCode(textToChange);
                end = std::chrono::system_clock::now(); 

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

                codeToChange = tokenize(text, ' ');

                start = std::chrono::system_clock::now();
                newText = e_CodeToStr(codeToChange);
                end = std::chrono::system_clock::now(); 

                elapsed_seconds = end - start;
                cout << endl << "Converted String: " << newText << endl;
                cout << "Elapsed time for our algorithm: " << 
                        elapsed_seconds.count() * 1000000 << " ms" << endl;
                break;

            case(-1):
                break;
            
            default:
                cout << "Invalid option." << endl;
        }

    } while(opt != -1);
}