/***
 * File: Ong.cpp
 * Assignment: CMSC 202, Project 4
 * Author: Christian Stenoff
 * Date Created: 04/17/2022
 * Section: 54
 * E-mail: cstenof1@umbc.edu
 * Description: Contains the functions that encrypt or decrypt message using the
 *              Ong cipher. Also formats both encrypted and decrypted messages
 *              for outputting a new file that can be reused with the program.
***/

#include "Ong.h"

// Name: Ong (Default Constructor)
// Desc: Constructor to build an empty Ong Cipher
// Preconditions - None
// Postconditions - Creates an Ong cipher to be encrypted
Ong::Ong(){}


// Name: Ong (Overloaded Constructor)
// Desc: Constructor to build a populated Ong Cipher
// Preconditions - Pass it the message and isEncrypted
// Postconditions - Creates an Ong cipher to be encrypted
Ong::Ong(string message, bool isEncrypted):
        Cipher(message, isEncrypted){}


// Name: Ong (Destructor)
// Desc: Destructor - Anything unique to Ong to delete?
// Preconditions - ~Ong exists
// Postconditions - Ong destroyed
Ong::~Ong(){}


// Name: IsVowel (Helper function)
// Desc: Returns true if vowel, space, or punctuation
// Preconditions - Message exists
// Postconditions - Returns true or false as above
bool Ong::IsVowel(char inputChar)
{
    // Declare list of vowels, including the blank space and punctuation to
    // prevent unnecessary "ong" additions or removals
    char vowelList[] = {'A','E','I','O','U',
                          'a','e','i','o','u',
                           ' ',',',';','.','-','(',
                          ')', '"'};
    int numVowels = 18;

    // Check character against list of vowels and punctuation
    for (int i = 0; i < numVowels; i++)
    {
        if (inputChar == vowelList[i])
        {return true;}
        else{}
    }
    return false;
}


// Name: Encrypt
// Desc: If vowel then vowel and dash displayed. dog = dong-o-gong
// If consonant then consonant and ong and dash displayed.
// Preconditions - Message exists
// Postconditions - Encrypts as above
void Ong::Encrypt()
{
    // Declare necessary constants and variables
    string inputMessage = GetMessage();
    int numCharacters = inputMessage.size();
    string encryptedMessage = "";

    // Loop through the message
    for (int i = 0; i < numCharacters; i++)
    {
        // If character is not a vowel, add the letter plus "ong"
        if (!IsVowel(inputMessage[i]))
        {encryptedMessage += inputMessage[i] + ong;}

        // Otherwise, just add the letter
        else
        {encryptedMessage += inputMessage[i];}

        // Check if the next index exists
        if (i+1 < numCharacters)
        {
            // Check if the current index and the next index are not blank spaces
            if (inputMessage[i] != ' ' && inputMessage[i+1] != ' ')
            {
                // If true, add a dash
                encryptedMessage += '-';
            }
        }
    }
    // Set the message to the new encrypted message
    SetMessage(encryptedMessage);
}


// Name: Decrypt
// Desc: Removes the dashes and "ong" when necessary cong-a-tong = cat
// Double check words like "wrong" so that they work correctly!
// Preconditions - Message exists
// Postconditions - Original message is displayed
void Ong::Decrypt()
{
    // Declare necessary constants and variables
    string inputMessage = GetMessage();
    int numCharacters = inputMessage.size();
    string decryptedMessage = "";

    // Loop through message
    for (int i = 0; i < numCharacters; i++)
    {
        // If character is a dash, do nothing
        if(inputMessage[i] == '-')
        {}

        // Else if character is not a vowel, add the letter to the new
        // decrypted message and skip the next 3 indexes since they are "ong"
        else if (!IsVowel(inputMessage[i]))
        {
            decryptedMessage += inputMessage[i];
            i = i + 3;
        }
        // Otherwise, add the character to the new decrypted message
        else
        {decryptedMessage += inputMessage[i];}
    }
    // Set the message to the new decrypted message
    SetMessage(decryptedMessage);
}


// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Ong in this case)
string Ong::ToString()
{return "Ong";}


// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - o, delimiter, isencrypted, delimiter,
//                  message, delimiter, blank are output
string Ong::FormatOutput()
{
    // Declare necessary constants and variables
    string ongSymbolString = "o";
    string isEncryptedString;
    string messageString = GetMessage();
    string blankString = " ";
    string delimiterString = "|";

    // Set IsEncrypted correctly
    if (GetIsEncrypted())
    {isEncryptedString = "1";}
    else
    {isEncryptedString = "0";}

    // Concatenate elements of output
    string output = ongSymbolString + delimiterString + isEncryptedString +
                    delimiterString + messageString + delimiterString +
                    blankString;

    return output;
}
