/*
Written by Andrew Yahnke

Computer Science Capstone
Spring 2018
Dr. Rosemary Mullick



Written with the help of:
Paul Programming
https://www.youtube.com/user/PaulProgramming/

“Natural-Language Understanding.”
Elements of Artificial Intelligence: Using Common LISP
by Steven L. Tanimoto
W.H. Freeman and Company, 1995
pages 351–400
*/


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Tokenize.h"

using namespace std;

int main (void)
{
    ifstream inputFile;
    string inputData;
    vector <string> inputVector;

    //Paths
    string filePath = "\\Desktop\\AY_Sentence.txt";
    string dictionaryPath = "AY_Dictionary.txt";

    string currentInput;
    string buffer;

    word wordArray[50];
    int arraySize = 0;

    cout << "****************************************************************************************************" << endl;

    //Open File
    cout << "\nOpening file..." << endl;

    inputFile.open( filePath );

    if (!inputFile.is_open())
    {
        return 1;
    }
    else
    {
        cout << "File is open" << endl;
    }

    while(inputFile)
    {
        //Get Sentence line ending at "." from inputFile and store it in inputData then push to inputVector
        getline(inputFile, inputData, '.');

        if (!inputData.empty())
        {
            inputVector.push_back (inputData);
        }
    }

    cout << "Input file parsing finished\n" << endl;

    //Close File
    inputFile.close();

    cout << "****************************************************************************************************" << endl;

    //Access the array of Line Strings
    cout << "\nAccessing vector..." << endl;
    cout << "\nThere are " << inputVector.size() << " elements.\nElements are:\n" << endl;

    //Display the elements present in the array
    for (unsigned i = 0; i  < inputVector.size(); i++)
    {
        cout << inputVector[i] << endl;
    }

    cout << "\nEnd of array\n" << endl;

    cout << "All sentences are stored\n" << endl;

    for (unsigned i = 0; i  < inputVector.size(); i++)
    {

        //Save the current line selected in a string variable
        currentInput = inputVector[i];

        cout << "The current sentence is: " << currentInput << "\n" << endl;

        cout << "Please enter the number of words in the sentence: ";

        cin >> arraySize;

        cout << "\nBeginning analysis\n" << endl;

        cout << "****************************************************************************************************" << endl;

        cout << "\n[Press Enter]\n" << endl;
        cin.ignore();
        cin.get();

        //Break the line into words
        tokenizeLine (currentInput, wordArray, arraySize);

        cout << "****************************************************************************************************\n" << endl;

        cout << "\n[Press Enter]\n" << endl;
        cin.get();

        //Search dictionary for word definitions
        query (dictionaryPath, wordArray, arraySize);

        cout << "\n****************************************************************************************************\n" << endl;

        cout << "\n[Press Enter]\n" << endl;
        cin.get();

        //
        textAnalysis (wordArray, arraySize);

        cout << "\n\n****************************************************************************************************\n" << endl;

        cout << "\n[Press Enter]\n" << endl;
        cin.get();
    }

    cout << "Exiting Program" << endl;

    return (0);
}

