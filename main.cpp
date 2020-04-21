/* ----------------------------------------------------------- 
    Program 1: Spam Email Filter
    
    Class: CS 251, Spring 2020
    Author: Frank Kasper
    
    Description:
    This program takes in a list of emails to be classified as spam. 
    The program then searches for emails that match the spam description
    and classifies them as spam or not spam. The ones that are spam 
    may be output into a seperate file.
-----------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include "ourvector.h"

using namespace std;

// LOADS SPAM FILE INTO VECTOR
void loadSpamFile(string input, ourvector<string> &spamList) 
{
    spamList.clear();
    string filename = input.substr(input.find(' ')+1, input.find('\0'));
    ifstream inFS;
    string fileString;
    
    inFS.open(filename);
    if (!inFS.is_open() ) {
      cout << "**Error, unable to open '" << filename << "'" << endl;
      return;
    }
    
    cout << "Loading '" << filename << "'" << endl;
    
    int spamEntrees = 0;
    getline(inFS, fileString);
	
    // reads in spam list from file
    while (!inFS.eof() ) {
        spamList.push_back(fileString);
        spamEntrees++;
        getline(inFS, fileString);
    }
    
    cout << "# of spam entrees: " << spamEntrees << endl << endl;
} // end load


// LISTS ALL ADDRESSES NEEDED TO FILTER SPAM
void displaySpamList (ourvector<string> spamList) 
{
    for (int i = 0; i < spamList.size(); i++) {
        cout << spamList.at(i) << endl;
    }
    cout << endl;
} // end display


// parses thru spam list to search for matching addresses using binary search
bool binarySearch ( string email, ourvector<string> &spamList) 
{
    int mid = 0;
    int low = 0;
    int high = spamList.size()-1;
    string middleEl;

    while (high >= low) 
	{
      mid = low + ((high - low) / 2);
      middleEl = spamList[mid];
                  
      if ( email == middleEl) {          
          return true;
      }
      else if (middleEl < email) {
         low = mid + 1;
      } 
      else if (middleEl > email){
          high = mid - 1;
      }
    }
    return false;
} // end binary search function


// CHECKS IF EMAIL IS IN THE SPAM LISTS
bool checkIfSpam(string input, ourvector<string> &spamList) 
{
    string email = input.substr(input.find(' ')+1, input.find('\0'));
    string username = email.substr(0, email.find('@'));
    string domain = email.substr(email.find('@') + 1, email.find('\0'));
    string spamFormat = domain + ":" + username;
    string spamAsterisk = domain + ":" + "*";
    
    //cout << email << "%" << endl  ; 
    cout << username << "%" << endl;
    cout << domain << "%" << endl;
       
        
    if (binarySearch(spamFormat, spamList) == true || binarySearch(spamAsterisk, spamList) == true) {
        return true;
    }        
    else {
        return false;
    }
} // end check


// filters thru email list to check for spam emails and 
// stores the non-spam into a seperate file
void filterThruEmail (string input, ourvector<string> &spamList) 
{
	// parse email info
    string twoFiles = input.substr(input.find(' ')+1, input.find('\0'));
    string emailfile = twoFiles.substr(0, twoFiles.find(' '));
    string outputfile = twoFiles.substr(twoFiles.find(' ')+1, twoFiles.find('\0'));
    ifstream inFS;
    ofstream outFS;
    ourvector<string> xList;
    
	// check files
    inFS.open(emailfile);
    outFS.open(outputfile);
    if (!inFS.is_open() ) {
      cout << "**Error, unable to open '" << emailfile << "'" << endl;
      return;
    }
    if (!outFS.is_open()) {
        cout << "**Error, unable to open '" << outputfile << "'" << endl;
        return;
    }
    
    int totalEmails = 0;
    int nonSpamEmails = 0;
    string number;
    string email;
    string subject;
    string username, domain;
    
    // read in info for first email
    inFS >> number;
    inFS >> email;
    getline(inFS, subject);
    username = email.substr(0, email.find('@') );
    domain = email.substr(email.find('@')+1, email.find(' ') );
    totalEmails++;
    
    if(checkIfSpam(input, spamList) == true ) {
        xList.push_back(email);
    }
    else {
        outFS << number << " " << email << subject << endl;
        nonSpamEmails++;
    }
    
    // read in information for rest of emails
    while (!inFS.eof() ) 
	{
        if(checkIfSpam(input, spamList) == true ) {
            spamList.push_back(email);
        }
        else {
            outFS << number << " " << email << subject << endl;
            nonSpamEmails++;
        }
        inFS >> number;
        inFS >> email;
        getline(inFS, subject);
        username = email.substr(0, email.find('@') );
        domain = email.substr(email.find('@')+1, email.find(' ') );
        totalEmails++;
    }
	
    // adjusts for added space at end of file
    totalEmails--;
    nonSpamEmails--;
    
    cout << "# emails processed: " << totalEmails << endl;
    cout << "# non-spam emails: " << nonSpamEmails << endl;
} // end filter


int main () {
    string userCommand;
    string input;
    ourvector<string> theSpamList;
    
    cout << "** Welcome to spam filtering app **" << endl;
    
    // loops through for command inputs
    do {
        cout << "Enter command or # to exit> ";
        getline(cin, input);
        userCommand = input.substr(0, input.find(' '));

        if (userCommand == "load" ) {
            loadSpamFile(input, theSpamList);
        }
        else if (userCommand == "display" ) {
            displaySpamList(theSpamList);
        }
        else if (userCommand == "check" ) {
            bool check = checkIfSpam(input, theSpamList);
            string email = input.substr(input.find(' ')+1, input.find('\0'));
            if (check == true){
                cout << email << " is spam" << endl << endl;
            }
            else {
                cout << email << " is not spam" << endl << endl;
            }
        }
        else if (userCommand == "filter" ) {
            filterThruEmail(input, theSpamList);
        }
        else if (userCommand == "#" ) {
            break;
        }
        else {
            cout << "**invalid command" << endl;
        }
    } while (true);
    
    return 0;
}
