#include "../common.h"

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

string 
e_StrToCode(string textToChange)
{
    string newText = "";
    for (unsigned int i = 0; i < textToChange.size(); i++)
        newText += asciiMorseLetters[(int)textToChange[i]-32] + " ";
    
    return newText;
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



string 
e_CodeToStr(vector<string> textToChange)
{
    string newText = "";
    for (unsigned int i = 0; i < textToChange.size(); i++) 
        newText += getCode(textToChange[i]);
    
    return newText;
}