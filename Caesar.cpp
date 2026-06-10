/***
 * File: Caesar.cpp
 * Assignment: CMSC 202, Project 4
 * Author: Christian Stenoff
 * Date Created: 04/17/2022
 * Section: 54
 * E-mail: cstenof1@umbc.edu
 * Description: Contains the functions that encrypt or decrypt message using the
 *              Caesar cipher. Also formats both encrypted and decrypted messages
 *              for outputting a new file that can be reused with the program.
***/

#include "Caesar.h"

// Name: Caesar (Default Constructor)
// Desc: Constructor to build an empty Caesar Cipher (Defaults to shift 3)
// Preconditions - None
// Postconditions - Creates a Caesar cipher to be encrypted
Caesar::Caesar(){}


// Name: Caesar (Overloaded Constructor)
// Desc: Constructor to build a populated Caesar Cipher (Defaults to shift 3)
// Preconditions - Pass it the message, isEncrypted, and shift (any integer)
// Postconditions - Creates a Caesar cipher to be encrypted
Caesar::Caesar(string message, bool isEncrypted, int shift = 3):
        Cipher(message,isEncrypted)
{m_shift = shift;}


// Name: Caesar (Destructor)
// Desc: Destructor - Anything specific to Caesar to delete?
// Preconditions - ~Caesar exists
// Postconditions - Caesar destroyed
Caesar::~Caesar(){}


// Name: Encrypt
// Desc: Shifts characters right based on shift (lower stay lower, upper stay upper)
// Preconditions - Message exists
// Postconditions - Shifts each character "right".
void Caesar::Encrypt()
{
    // Declare necessary constants and variables
    int alphabetCount = 26;
    int isUpperMax = 90;
    int isLowerMax = 122;
    string inputMessage = GetMessage();
    int numCharacters = inputMessage.size();
    string encryptedMessage = "";

    for (int i = 0; i < numCharacters; i++)
    {
        // Check if character is a capital letter
        if (isupper(inputMessage[i]))
        {
            // Check if the shift will wrap around and adjust
            if (int (inputMessage[i] + m_shift > isUpperMax))
            {encryptedMessage += inputMessage[i] + (m_shift - alphabetCount);}
            // Otherwise, add the shifted letter to the encryption
            else
            {encryptedMessage += inputMessage[i] + m_shift;}
        }
        // Check if character is a lower case letter
        else if (islower(inputMessage[i]))
        {
            // Check if the shift will wrap around and adjust
            if (int(inputMessage[i] + m_shift > isLowerMax))
            {encryptedMessage += inputMessage[i] + (m_shift - alphabetCount);}
            // Otherwise, add the shifted letter to the encryption
            else
            {encryptedMessage += inputMessage[i] + m_shift;}
        }
        // Else, the character is not a letter,
        // add the character to the encryption without changing
        else
        {encryptedMessage += inputMessage[i];}
    }
    // Set the message to the new encrypted message
    SetMessage(encryptedMessage);
}


// Name: Decrypt
// Desc: Shifts characters left based on shift (lower stay lower, upper stay upper)
// Preconditions - Message exists
// Postconditions - Shifts each character "left".
void Caesar::Decrypt()
{
    // Declare necessary constants and variables
    int alphabetCount = 26;
    int isUpperMin = 41;
    int isLowerMin = 97;
    string inputMessage = GetMessage();
    int numCharacters = inputMessage.size();
    string decryptedMessage = "";

    for (int i = 0; i < numCharacters; i++)
    {
        // Check if character is a capital letter
        if (isupper(inputMessage[i]))
        {
            // Check if the shift will wrap around and adjust
            if (int (inputMessage[i] - m_shift < isUpperMin))
            {decryptedMessage += inputMessage[i] - (m_shift - alphabetCount);}
            // Otherwise, add the shifted letter to the decryption
            else
            {decryptedMessage += inputMessage[i] - m_shift;}
        }
        // Check if character is a lower case letter
        else if (islower(inputMessage[i]))
        {
            // Check if the shift will wrap around and adjust
            if ((int(inputMessage[i]) - m_shift) < isLowerMin)
            {decryptedMessage += inputMessage[i] - (m_shift - alphabetCount);}
            // Otherwise, add the shifted letter to the decryption
            else
            {decryptedMessage += inputMessage[i] - m_shift;}
        }
        // Else, the character is not a letter,
        // add the character to the decryption without changing
        else
        {decryptedMessage += inputMessage[i];}
    }
    // Set the message to the new decrypted message
    SetMessage(decryptedMessage);
}


// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (Caesar in this case)
string Caesar::ToString()
{return "Caesar";}


// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - c, delimiter, isencrypted, delimiter,
//                  message, delimiter, m_shift are returned for output
string Caesar::FormatOutput()
{
    // Declare necessary constants and variables
    string caesarSymbolString = "c";
    string isEncryptedString;
    string messageString = GetMessage();
    string shiftString = to_string(m_shift);
    string delimiterString = "|";

    // Set IsEncrypted correctly
    if (GetIsEncrypted())
    {isEncryptedString = "1";}
    else
    {isEncryptedString = "0";}

    // Concatenate elements of output
    string output = caesarSymbolString + delimiterString + isEncryptedString +
                    delimiterString + messageString + delimiterString +
                    shiftString;

    return output;
}
