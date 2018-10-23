/*
Binary search tree was written with the
help of a tutorial by Paul Programming
Binary Search Trees playlist
https://www.youtube.com/user/PaulProgramming/playlists
*/

#ifndef TOKENIZE_H_INCLUDED
#define TOKENIZE_H_INCLUDED
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class word
{
    public:
    string text;
    string token;

    void tokenizeLine (string, word, int);
    void query (string, word, int);
    void textAnalysis (word, int);
};

class tree
{
    private:

        struct node
        {
            string token;
            node* left;
            node* right;
        };

        node* root;

        void addLeafPrivate (string text, string token, node* Ptr);
        void printNodePrivate (node* Ptr);
        bool nodeValuePrivate(string PtrToken, string token);
        void translatePrivate(node* Ptr);

    public:

        tree();
        node* createLeaf (string token);
        void addLeaf (string text, string token);
        void printNode ();
        bool nodeValue(string PtrToken, string token);
        void translate ();

};

tree::tree()
{
    root = NULL;
}

tree::node* tree::createLeaf (string token)
{
    node* n = new node;
    n->token = token;
    n->left = NULL;
    n->right = NULL;

    return n;
}

void tree::addLeaf (string text, string token)
{
    addLeafPrivate (text, token, root);

    return;
}

void tree::addLeafPrivate (string text, string token, node* Ptr)
{
    if (root == NULL)
    {
        root = createLeaf(token);
    }
    else if (!nodeValue(Ptr->token, token))
    {
        if (Ptr->left != NULL)
        {
            cout << "Next pointer left" <<endl;
            addLeafPrivate(text, token, Ptr->left);
        }
        else
        {
            if (text.empty())
            {
                Ptr->left = createLeaf (token);
            }
            else
            {
                Ptr->left = createLeaf (text);
            }
        }
    }
    else if (nodeValue(Ptr->token, token))
    {
        if (Ptr->right != NULL)
        {
            cout << "Next pointer right" <<endl;
            addLeafPrivate(text, token, Ptr->right);
        }
        else
        {
            if (text.empty())
            {
                Ptr->right = createLeaf (token);
            }
            else
            {
                Ptr->right = createLeaf (text);
            }
        }
    }
    else
    {
        cout << "error when adding node" << endl;
    }
}

void tree::printNode ()
{
    printNodePrivate (root);

    return;
}

void tree::printNodePrivate (node* Ptr)
{
    if (root != NULL)
    {
        if (Ptr->left != NULL)
        {
            printNodePrivate (Ptr->left);
        }

        cout << "(" << Ptr->token << ")";

        if (Ptr->right != NULL)
        {
            printNodePrivate (Ptr->right);
        }
    }
    else
    {
        cout << "Tree is empty" << endl;
    }

    return;
}

bool tree::nodeValue (string PtrToken, string token)
{
    return (nodeValuePrivate(PtrToken, token));
}

bool tree::nodeValuePrivate(string PtrToken, string token)
{
    //Simple sentence structure
    if ((PtrToken == "S") && ((token == "NPh") || (token == "VPh")))
    {
        if (token == "NPh")
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    //Noun Phrase Side
    else if (PtrToken == "NPh")
    {
        cout << "Noun Phrase side: NPh" << endl;

        if ((token == "N") || (token == "PN"))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    //Verb Phrase side
    else if (PtrToken == "VPh")
    {
        cout << "Verb Phrase side: VPh" << endl;

        if ((token == "AD") || (token == "DN") || (token == "DR") ||
            (token == "DP") || (token == "AV"))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        cout << "At node" << endl;

        if ((token == "N") || (token == "PN"))
        {
            return false;
        }
        else if ((token == "AD") || (token == "DN") || (token == "DR") ||
            (token == "DP"))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

void tree::translate ()
{
    translatePrivate (root);

    return;
}

void tree::translatePrivate (node* Ptr)
{
    if (root != NULL)
    {
        if (Ptr->token == "S")
        {
            if (Ptr->left != NULL)
            {
                translatePrivate (Ptr->left);
            }
            if (Ptr->right != NULL)
            {
                translatePrivate (Ptr->right);
            }
        }
        else if (Ptr->token == "NPh")
        {
            cout << "\nThe Subject of the sentence is:\n" << endl;
            if (Ptr->left != NULL)
            {
                translatePrivate (Ptr->left);
            }
            if (Ptr->right != NULL)
            {
                translatePrivate (Ptr->right);
            }
        }
        else if (Ptr->token == "VPh")
        {
            cout << "\n\nThe Action is:\n" << endl;

            if (Ptr->right != NULL)
            {
                translatePrivate (Ptr->right);
            }

            if (Ptr->left != NULL)
            {
                translatePrivate (Ptr->left);
            }

        }
        else if (Ptr->right != NULL)
        {
            cout << Ptr->token << " ";
            translatePrivate (Ptr->right);
        }
        else if (Ptr->left != NULL)
        {
            cout << Ptr->token << " ";
            translatePrivate (Ptr->left);
        }
        else
        {
            cout << Ptr->token << " ";
            return;
        }

    }
    else
    {
        cout << "Tree is empty" << endl;
    }

    return;
}

void tokenizeLine (string line, word wordArray [], int arraySize)
{
    stringstream  stream(line);
    string word;

    cout << "\nTokenizing text...\nTokens are:\n" << endl;

    stream >> word;
    cout << word;

    cout << ": stored in Element 0" << endl;

    wordArray[0].text = word;

    for (int i = 1; i < arraySize; i++)
    {
        stream >> word;
        cout << word;

        wordArray[i].text = word;

        cout << ": stored in Element " << i << endl;
    }

    cout << "\nTokenization finished\n" <<endl;

    return;
}

void query (string dictionaryPath, word wordArray[], int arraySize)
{
    ifstream dictionary;
    string dictionaryParse;
    string dictionaryToken;
    bool match = 0;

    //Open Dictionary File
    cout << "Opening dictionary..." << endl;

    dictionary.open( dictionaryPath );

    cout << "Dictionary open" << endl;

    while(dictionary)
    {
        //Get Sentence line ending at ":"
        getline(dictionary, dictionaryParse);

        for (int i = 0; i < arraySize; i++)
        {
            if (wordArray[i].text == "")
            {
                break;
            }
            else
            {
                match = 0;

                //Display the elements present in the array of
                cout << "\nElement examined is: " << i << " the word being compared is: ";
                cout << wordArray[i].text << endl;

                while (match == 0)
                {
                    cout << dictionaryParse << endl;

                    if (dictionaryParse == wordArray[i].text)
                    {
                        cout << "Match found" << endl;

                        match = 1;

                        getline(dictionary, dictionaryToken);

                        wordArray[i].token = dictionaryToken;

                        cout << wordArray[i].text << " is a: " << wordArray[i].token << endl;

                        dictionary.clear();
                        dictionary.seekg(0, ios::beg);
                    }
                    else
                    {
                        cout << "No match" << endl;

                        getline(dictionary, dictionaryParse);
                    }

                    getline(dictionary, dictionaryParse);
                }
            }
        }

        break;
    }

    //Close File
    dictionary.close();

    for (int i = 0; i < arraySize; i++)
    {
        if (wordArray[i].text == "")
        {
            break;
        }
        else
        {
            //Display the elements present in the array
            cout << "\nElement examined is: " << i << " the word is: ";
            cout << wordArray[i].text << endl;

            cout << "\nThe token for this word is " << wordArray[i].token << endl;
        }
    }

    return;
}

void textAnalysis (word wordArray[], int arraySize)
{
    tree newTree;

    cout << "Empty tree created\n" << endl;

    //Set up the three nodes that make up a common English sentence
    cout << "Setting up simple sentence tree\n" << endl;

    newTree.addLeaf("", "S");
    newTree.addLeaf("", "NPh");
    newTree.addLeaf("", "VPh");

    cout << "English simple sentence tree ready\n" << endl;

    cout << "Nodes are:" << endl;

    newTree.printNode();

    cout << "\n\nParsing word array\n" << endl;

    for (int i = 0; i < arraySize; i++)
    {
        cout << "Starting at (S)" << endl;

        cout << "Word is: " << wordArray[i].text << endl;

        newTree.addLeaf(wordArray[i].text, wordArray[i].token);

        cout << "Created " << "(" <<wordArray[i].text << ")" << " node\n" << endl;
    }

    cout << "\nPrinting tree...\n" << endl;

    cout << "Nodes are:" << endl;

    newTree.printNode();

    cout << "\n\nFinished printing tree" << endl;

    newTree.translate();

    return;
}

#endif // TOKENIZE_H_INCLUDED
