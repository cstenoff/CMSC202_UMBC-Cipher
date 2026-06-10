/***
 * File: CipherTool.cpp
 * Assignment: CMSC 202, Project 4
 * Author: Christian Stenoff
 * Date Created: 04/17/2022
 * Section: 54
 * E-mail: cstenof1@umbc.edu
 * Description: Contains the functions necessary to utilize the Cipher parent
 *              class and the Caesar, RailFence, and Ong child classes.
***/

#include "CipherTool.h"

// Name: CipherTool Constructor
// Desc - Creates a new CipherTool and sets m_filename based on string passed
// Preconditions - Input file passed and populated with Cipher
// Postconditions - CipherTool created
CipherTool::CipherTool(string inputFileName)
{m_filename = inputFileName;}


// Name: CipherTool Destructor
// Desc - Calls destructor for all ciphers in m_ciphers
// Preconditions - m_ciphers is populated
// Postconditions - m_ciphers deallocated and vector emptied
CipherTool::~CipherTool()
{
    for (unsigned int i = 0; i < m_ciphers.size(); i++)
    {
        delete m_ciphers.at(i);
        m_ciphers.at(i) = nullptr;
    }
    cout << "All ciphers have been deleted." << endl;
}


// Name: LoadFile
// Desc - Opens file and reads in each Cipher. Each Cipher dynamically allocated
// and put into m_ciphers (c is Caesar, r is RailFence, and o is Ong)
// Preconditions - Input file passed and populated with Ciphers
// Postconditions - m_ciphers populated with Ciphers
void CipherTool::LoadFile()
{
    // Declare necessary constants and variables
    string caesarSymbol = "c";
    string railfenceSymbol = "r";
    string ongSymbol = "o";

    string cipherType;
    string isEncryptedString;
    string message;
    string keyString;
    Cipher * tempCipher;

    // Open document to extract ciphers from
    ifstream cipherDoc;
    cipherDoc.open(m_filename);

    // Extract cipher data
    while(getline(cipherDoc,cipherType,'|') &&
          getline(cipherDoc,isEncryptedString,'|') &&
          getline(cipherDoc,message,'|') &&
          getline(cipherDoc,keyString,'\n'))
    {
        // Convert string to bool value
        bool isEncryptedBool = StringToBoolean(isEncryptedString);

        // If cipher has the Ong symbol, create new Ong cipher
        if (cipherType == ongSymbol)
        {tempCipher = new Ong(message, isEncryptedBool);}

        // Otherwise, cipher is either Caesar or RailFence
        else
        {
            // Convert key from string to integer
            int keyInt = stoi(keyString);

            // If cipher has Caesar symbol, create new Caesar cipher
            if (cipherType == caesarSymbol)
            {tempCipher = new Caesar(message, isEncryptedBool, keyInt);}

            // Else if cipher has RailFence symbol, create new railfence cipher
            else if (cipherType == railfenceSymbol)
            {tempCipher = new RailFence(message, isEncryptedBool, keyInt);}
        }
        // Add new cipher to vector of all ciphers
        m_ciphers.push_back(tempCipher);
    }
    // Close doc when complete
    cipherDoc.close();
}


// Name: StringToBoolean
// Desc - Helper function that converts a string to a boolean for reading in file
// Preconditions - Passed string of either 0 or 1
// Postconditions - Returns false if 0 else true
bool CipherTool::StringToBoolean(string input)
{
    // Declare necessary variable
    bool isEncrypted;

    // Convert string to bool value
    if (input == "0")
    {isEncrypted = false;}
    else
    {isEncrypted = true;}

    return isEncrypted;
}


// Name: DisplayCiphers
// Desc - Displays each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Displays ciphers
void CipherTool::DisplayCiphers()
{
    // Declare necessary variable
    int numCiphers = m_ciphers.size();

    // Display all available ciphers
    for (int i = 0; i < numCiphers; i++)
    {
        string message = m_ciphers[i]->GetMessage();
        string cipherType = m_ciphers[i]->ToString();

        cout << i+1 << ". \"" << message << "\" (" << cipherType << ")\n" << endl;
    }
}


// Name: EncryptDecrypt
// Desc - Encrypts or decrypts each of the ciphers in the m_ciphers
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - Either Encrypts or Decrypts each cipher in m_ciphers
void CipherTool::EncryptDecrypt(bool isEncrypted)
{
    // Declare necessary constants and variables
    int numCiphers = m_ciphers.size();
    int counter = 0;

    // If cipher is encrypted, run decryption function
    if (isEncrypted)
    {
        for (int i = 0; i < numCiphers; i++)
        {
            if(m_ciphers[i]->GetIsEncrypted())
            {
                m_ciphers[i]->Decrypt();
                m_ciphers[i]->ToggleEncrypted();
                counter++;
            }
        }
        // If any ciphers are decrypted, print how many were decrypted
        if (counter > 0)
        {cout << counter << " ciphers have been decrypted.\n" << endl;}

        // Otherwise, print that those ciphers are already decrypted
        else
        {cout << "The ciphers are already decrypted.\n" << endl;}
    }

    // Otherwise, if the cipher is decrypted, run encryption function
    else
    {
        for (int i = 0; i < numCiphers; i++)
        {
            if (!m_ciphers[i]->GetIsEncrypted())
            {
                m_ciphers[i]->Encrypt();
                m_ciphers[i]->ToggleEncrypted();
                counter++;
            }
        }
        // If any ciphers are encrypted, print how many were encrypted
        if (counter > 0)
        {cout << counter << " ciphers have been encrypted.\n" << endl;}

        // Otherwise, print that those ciphers are already encrypted
        else
        {cout << "The ciphers are already encrypted.\n" << endl;}
    }
}


// Name: Export
// Desc - Exports each of the ciphers in the m_ciphers (so they can be reused)
// Preconditions - Input file passed and m_ciphers populated
// Postconditions - All ciphers exported
void CipherTool::Export()
{
    // Declare necessary constants and variables
    int numCiphers = m_ciphers.size();
    int counter = 0;
    string exportFileName;

    // Get name for export file from user
    cout << "What would you like to call the export file?" << endl;
    cin >> exportFileName;

    // Begin export file
    ofstream exportFile;

    // Open export file
    exportFile.open(exportFileName);

    // Loop through the ciphers, format them, and then write them to the file
    // that is being exported
    for (int i = 0; i < numCiphers; i++)
    {
        string tempLine = m_ciphers[i]->FormatOutput();
        exportFile << tempLine << endl;
        counter++;
    }
    // State how many ciphers were exported to the new file
    cout << counter << " ciphers have been exported." << endl;

    // Close new exported doc
    exportFile.close();
}


// Name: Menu
// Desc - Displays menu and returns choice
// Preconditions - m_ciphers all populated
// Postconditions - Returns choice
int CipherTool::Menu()
{
    // Declare necessary constants and variables
    int menuMin = 1;
    int menuMax = 5;
    int userInput;

    // Display main menu and take user input command
    cout << "What would you like to do?" << endl;
    cout << "1. Display All Ciphers" << endl;
    cout << "2. Encrypt All Ciphers" << endl;
    cout << "3. Decrypt All Ciphers" << endl;
    cout << "4. Export All Ciphers" << endl;
    cout << "5. Quit" << endl;
    cin >> userInput;

    // Validate user input
    while (userInput < menuMin or userInput > menuMax)
    {
        cout << "Please enter a valid choice between 1 and 5." << endl;
        cout << "1. Display All Ciphers" << endl;
        cout << "2. Encrypt All Ciphers" << endl;
        cout << "3. Decrypt All Ciphers" << endl;
        cout << "4. Export All Ciphers" << endl;
        cout << "5. Quit" << endl;
        cin >> userInput;
    }
    return userInput;
}


// Name: Start
// Desc - Loads input file, allows user to choose what to do
// Preconditions - m_ciphers populated with ciphers
// Postconditions - none
void CipherTool::Start()
{
    // Declare necessary constants and variables
    int displayCommand = 1;
    int encryptCommand = 2;
    int decryptCommand = 3;
    int exportCommand = 4;
    int quitCommand = 5;
    int menuChoice = 0;

    // Load ciphers
    LoadFile();

    // Run program until user quits
    while (menuChoice != quitCommand)
    {
        menuChoice = Menu();

        if (menuChoice == displayCommand)
        {DisplayCiphers();}

        else if (menuChoice == encryptCommand)
        {EncryptDecrypt(false);}

        else if (menuChoice == decryptCommand)
        {EncryptDecrypt(true);}

        else if (menuChoice == exportCommand)
        {Export();}

        else
        {cout << "Thanks for playing!\n" << endl;}
    }
}
