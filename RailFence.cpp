/***
 * File: RailFence.cpp
 * Assignment: CMSC 202, Project 4
 * Author: Christian Stenoff
 * Date Created: 04/17/2022
 * Section: 54
 * E-mail: cstenof1@umbc.edu
 * Description: Contains the functions that encrypt or decrypt message using the
 *              RailFence cipher. Also formats both encrypted and decrypted
 *              messages for outputting a new file that can be reused with
 *              the program.
***/

#include "RailFence.h"

// Name: RailFence (Default Constructor)
// Desc: Constructor to build an empty RailFence Cipher (Defaults to 3 rails)
// Preconditions - None
// Postconditions - Creates a RailFence cipher
RailFence::RailFence(){}


// Name: RailFence (Overloaded Constructor)
// Desc: Constructor to build a populated RailFence Cipher (Defaults to 3 rails)
// Preconditions - Pass it the message, isEncrypted, and number of rails (any integer)
// Postconditions - Creates a RailFence cipher to be encrypted
RailFence::RailFence(string message, bool isEncrypted, int rails):
        Cipher(message,isEncrypted)
{m_rails = rails;}


// Name: RailFence (Destructor)
// Desc: Destructor - Anything specific part of RailFence to delete?
// Preconditions - ~RailFence exists
// Postconditions - RailFence destroyed
RailFence::~RailFence(){}


// Name: Encrypt
// Desc: Letters are placed on a fence rail based on the number of rails
//       Letters are read from one rail at a time into a single string
// Preconditions - Message exists
// Postconditions - A single encrypted string is stored
void RailFence::Encrypt()
{
    // Declare necessary constants and variables
    string inputMessage = GetMessage();
    int numCharacters = inputMessage.size();
    string railFence[m_rails][numCharacters];
    int row = 0;
    int col = 0;
    bool downFlag = false;
    string encryptedMessage = "";

    // Loop through grid and fill with marker
    for (int i = 0; i < m_rails; i++)
    {
        for (int j =0; j < numCharacters; j++)
        {railFence[i][j] = "*";}
    }

    // Loop through message to input it into the cipher grid
    for (int i = 0; i < numCharacters; i++)
    {
        // Identify upper and lower bounds of grid
        if (row == 0 )
        {downFlag = true;}
        else if (row == (m_rails - 1))
        {downFlag = false;}

        railFence[row][col] = inputMessage[i];
        col++;

        // Maintain proper up or down direction for encryption
        if (downFlag)
        {row++;}
        else
        {row--;}
    }

    // Loop through grid to extract encrypted message
    for (int i = 0; i < m_rails; i++)
    {
        for (int j = 0; j < numCharacters; j++)
        {
            if (railFence[i][j] != "*")
            {encryptedMessage += railFence[i][j];}
        }
    }
    // Set the message to the new encrypted message
    SetMessage(encryptedMessage);
}


// Name: Decrypt
// Desc: Single encrypted string is pushed back on the rails and reversed
// Preconditions - Message exists
// Postconditions - The decrypted string is stored
void RailFence::Decrypt()
{
    // Declare necessary constants and variables
    string inputMessage = GetMessage();
    int numCharacters = inputMessage.size();
    string railFence[m_rails][numCharacters];
    bool downFlag = false;
    string decryptedMessage = "";

    // Fill grid with markers
    for (int i = 0; i < m_rails; i++)
    {
        for (int j = 0; j< numCharacters; j++)
        {railFence[i][j] = "_";}
    }

    // Declare row and column counters
    int row = 0;
    int col = 0;

    // Loop through message and place new marker into zigzag pattern for decryption
    for (int i = 0; i < numCharacters; i++)
    {
        // Identify upper and lower bounds of grid
        if (row == 0)
        {downFlag = true;}
        else if (row == (m_rails - 1))
        {downFlag = false;}

        railFence[row][col++] = "*";

        // Maintain proper up or down directions for marker placement
        if (downFlag)
        {row++;}
        else
        {row--;}
    }

    // Declare counter for message index
    int messageIndex = 0;

    // Loop through grid to input the encrypted message into the decrypting cipher
    for (int i = 0; i < m_rails; i++)
    {
        for(int j = 0; j< numCharacters; j++)
        {
            if (railFence[i][j] == "*")
            {
                if (messageIndex < numCharacters)
                {railFence[i][j] = inputMessage[messageIndex++];}
            }
        }
    }

    // Reset row and column counters
    row = 0;
    col = 0;

    // Extract decrypted message from the grid in zigzag pattern
    for (int i = 0; i < numCharacters; i++)
    {
        // Identify upper and lower bounds of grid
        if (row == 0)
        {downFlag = true;}
        else if (row == (m_rails - 1))
        {downFlag = false;}

        // If grid place at [row][col] is not the * marker, concatenate that
        // character to the decrypted message
        if (railFence[row][col] != "*")
        {decryptedMessage += railFence[row][col++];}

        // Maintain proper up or down directions for deciphering message
        if (downFlag)
        {row++;}
        else
        {row--;}
    }
    // Set the message to the new decrypted message
    SetMessage(decryptedMessage);
}


// Name: ToString
// Desc - A function that returns the string of the object type
// Preconditions - The object exists
// Postconditions - The subtype is returned (RailFence in this case)
string RailFence::ToString()
{return "RailFence";}


// Name: FormatOutput()
// Desc - A function that returns the formatted output for Output function
// Preconditions - The object exists (use stringstream)
// Postconditions - r, delimiter, isencrypted, delimiter,
//                  message, delimiter, m_rails are returned for output
string RailFence::FormatOutput()
{
    // Declare necessary constants and variables
    string railFenceSymbolString = "r";
    string isEncryptedString;
    string messageString = GetMessage();
    string railsString = to_string(m_rails);
    string delimiterString = "|";

    // Set IsEncrypted correctly
    if (GetIsEncrypted())
    {isEncryptedString = "1";}
    else
    {isEncryptedString = "0";}

    // Concatenate elements of output
    string output = railFenceSymbolString + delimiterString + isEncryptedString +
                    delimiterString + messageString + delimiterString +
                    railsString;

    return output;
}
