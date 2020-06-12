//  prog4TweetGenerator.cpp
//     Generate somewhat random tweets based on a datafile.
//
//  CS 141 Spring 2019
//  Author: *** YOUR NAME(s) HERE ***
//
//  Open up a data file and find a starting point for some set of consecutive words
//  and print the starting word.
//
//  Next find all occurrences in the datafile of those consecutive words, and collect the set
//  of words that immediately follow each of those occurrences.  Choose one of the words
//  in this newly created set and add it to the set of consecutive words, shifting them
//  over by one so the first word gets overwritten by the second, and so on.
//
//  Repeat this process until >=30 words are displayed and an end-of-sentence word is found,
//  or until a displayed word has a newline or a return character at the end of it.
//
#include <iostream>
#include <cctype>       // For the letter checking functions
#include <fstream>      // For file input
#include <vector>
#include <cstring>      // For strlen()
#include <cstdlib>      // For rand()
using namespace std;

//---------------------------------------------------------------------
void getInputWords( vector<string> &allWords)   // List of all the words in the selected input file
{
    // Prompt for and get user choice for which data file to use
    cout << "Menu Options: \n"
         << "  1. Use Trump tweets \n"
         << "  2. Use Dalai Lama tweets \n"
         << "  3. Use Mixed Trump / Dalai Lama tweets \n"
         << "  4. Use small test file \n"
         << "  5. Use tiny test file \n"
         << "Your choice: ";
    int dataSelectionOption;
    cin >> dataSelectionOption;
    
    ifstream inputFileStream;  // declare the input file stream
    // open input file and verify
    switch( dataSelectionOption) {
        case 1: inputFileStream.open("TrumpTweets.txt"); break;
        case 2: inputFileStream.open("DalaiLamaTweets.txt"); break;
        case 3: inputFileStream.open("TrumpLama.txt"); break;
        case 4: inputFileStream.open("Test.txt"); break;
        case 5: inputFileStream.open("tiny.txt"); break;
        default: cout << "Invalid option chosen, exiting program. ";
            exit( -1);
            break;
    }
    if( !inputFileStream.is_open()) {
        cout << "Could not find input file.  Exiting..." << endl;
        exit( -1);
    }
    
    char c = ' ';
    char inputWord[ 81];
    
    // Read a character at a time from the input file, separating out individual words.
    inputWord[ 0] = '\0';
    int index = 0;
    while( inputFileStream.get(c)) {
        if( ! isprint( c) && c != '\r' && c != '\n') {
            continue;   // Skip non-printable characters and get the next one
        }
        if( c != ' ') {
            // If it is not a return or newline, add it to the string.
            // If it is a return or newline character, only add it if there
            //    are already other characters in the string.
            if( (c != '\r' && c != '\n') ||
                ( (c == '\r' || c == '\n') && index > 0)
              ) {
                inputWord[ index++] = c;
            }
        }
        // End the word when encountering a space or a return character.
        if( c == ' ' || c == '\r' || c == '\n'){
            // Null terminate the input word. Store it if its length is > 0 and it is printable.
            inputWord[ index] = '\0';
            if( strlen( inputWord) > 0 && isprint( inputWord[0])) {
                allWords.push_back( string( inputWord));
            }
            // Check for special case where there is a space at the end of the line.  We don't want
            // to lose the end of line character ('\n' or '\r'), so we concatenate it to the
            // last word that was previously stored on the list.  First check to see if this is the case:
            if( (c == '\r' || c == '\n') && strlen( inputWord) == 0) {
                long indexOfLastWord = allWords.size() - 1;
                allWords.at( indexOfLastWord).append("\r");
            }
            
            index = 0;    // Restart the index for the next word
        }
    }//end while( inputFileStream...)
}

//--------------------------------------------------------------------------------------------

//The function is tasked with finding the starting words of all the sentences
//and stores them into the vector startWords and uses vector allWords to retrive all 
//starting words. 
void getStartWords( vector<string> &startWords, vector<string> allWords)
{
  
  //The element at 0 of allWords is added at the end of the vector startWords
  startWords.push_back(allWords.at(0));
  
  //For loop has the size of vector allWords iterations
  for(int i = 0; i < allWords.size(); i++)
  {
    
    //Can store up to 32 bits which is necessary in order to store the size of the vector allWords
    long wordSize = allWords.at(i).size();
    
    char choice = allWords.at(i)[wordSize - 1];
    
    //If the loop finds either a \r or a \n character which are return characters
    //then the word after them are starting words and are thun identified and stored
    if(choice == '\r')
      {
        
      if(i < (allWords.size() - 1))
        {
          
          startWords.push_back(allWords.at(i + 1));
        
        }
      
      }
      else if(choice == '\n')
      {
        
      if(i < (allWords.size() - 1))
        {
          
          startWords.push_back(allWords.at(i + 1));
        
        }
        
      }
    
  }
  
}

//-------------------------------------------------------------------------------------------------------------------------------

void checkWords( vector<string> startWords,  // List of first words in sentences
                 vector<string> allWords,    // All words from input file
                 vector<string> wordList,    // List of all words following search phrase
                 string nextWord)            // Nexts word found after search phrase
{
    int debugMenuOption = 0;
    
    do {
        // Prompt for and get user choice for which debug option to use
        cout << " \n"
             << "    >>> Debug menu options: <<<\n"
             << "        1. Display a start word \n"
             << "        2. Display one of all words \n"
             << "        3. Display wordWindow and next words \n"
             << "        4. Exit debugging \n"
             << "    Your choice -> ";
        cin >> debugMenuOption;
        
        int wordIndexValue = 0;    // Used to read user input for debug options below
        
        switch( debugMenuOption) {
            case 1: cout << "    Enter an index value from 0 to " << startWords.size()-1 << " to display a start word: ";
                    cin >> wordIndexValue;
                    cout << "    " << startWords.at( wordIndexValue) << endl;
                    break;
            case 2: cout << "    Enter an index value from 0 to " << allWords.size()-1 << " to display one of all words: ";
                    cin >> wordIndexValue;
                    cout << "    " << allWords.at( wordIndexValue) << endl;
                    break;
            case 3: cout << "    WordWindow and next words are: ";
                    for( int i=0; i<wordList.size(); i++) {
                        cout << wordList.at( i) << " ";
                    }
                    cout << nextWord <<endl;
                    break;
        }//end switch(...)
    }while( debugMenuOption != 4);
    
}//end debug()

//---------------------------------------------------------------------

//Finds the sequence of words in the allWords vector and creates a new list in which that sequence is stored 
void getNextWord( vector<string> wordList, vector<string> allWords, string &nextWord)
{
  
  //Vector newSequenceList is created in order to store the new list of words 
  vector<string> newSequenceList;
  
  
  //The for loop only iterates equal to the differnce between the sizes of allWords and wordList
  for(int i = 0; i < allWords.size() - wordList.size(); i++)
  {
    
    
    //Tells the function if words match in the vector allWords
    bool allMatch = false;
    
    //Operator Long is used to allow the for bigger bit storage
    long listSize = wordList.size();
    
    //Loop iterates equal to the size of vector listSize
    for(int k = 0; k < listSize; k++)
    {
      
      //if a word in allWords is not equall to a word in wordList then 
      //all match is set to false 
      if((allWords.at(i + k).compare(wordList.at(k)) != 0))
      {
        
        allMatch = true;
        
        break;
        
      }
      
    }
    
    //If words on the list do match the words on allWords then the words are then 
    //pushed back into the new vector forming  a new list of words 
    if(allMatch == false)
    {
      
      newSequenceList.push_back(allWords.at(i + listSize));
    
    }
  
  }
  
  //Finds a random index between 0 and the size of the new word list 
  int index = rand() % newSequenceList.size();
  
  //The random index is used to assign the string nextWord with a random word of the list newSequenceList
  nextWord = newSequenceList.at(index);
  
}


//---------------------------------------------------------------------
int main()
{
    vector<string> allWords;   // List of all input words
    vector<string> startWords; // List of words that start sentences, to use
                               // in starting generated tweets.

    cout << "Welcome to the tweet generator. " << endl << endl;
    
    getInputWords( allWords);
    
    // You must write the function shown below, and call it from here:
    getStartWords( startWords, allWords);
    
    //Set Variable as string named nextWord
    string nextWord;
    
    // Allow looping to give more than one tweet
    int wordWindowWidth = 0;
    
    char userInput = ' ';

    //This varibale lets the compiler know if the user has chosen the debug option on the menu 
    int debugChoice; 
  
  
    // Main loop
    while( userInput != 'X') {
        cout << endl;
        cout << "Enter x to exit, or d/c to debug/continue followed by word window size: ";
        cin >> userInput;
        
      //Converts any lower case letters into upper case letters 
        userInput = toupper( userInput);    // fold user input into upper case
        
        if( userInput == 'X') 
        {
          
            break;   // Exit program
        
        }
        
        //If the user input is of the character D or d then the varible debugChoice will equal to 1
        //this will let the program know that the user has chosen to debug 
        else if(userInput == 'D')
        {
          
          debugChoice = 1; 
          
        }
        
        // Read in the wordWindowWidth to be used in both the "continue" and the "debug" modes
        cin >> wordWindowWidth;

        vector< string> wordList;   // Stores the list of consecutive words that are searched for
        
        // Find a random starting word in the startWords list
        // A random starting word is found using the rand() operator and the random number can only be within the 
        // vectors startWords size
        int randStartWord = rand() % startWords.size();
        
        // Find the selected startWord within the allWords list, and remember its position
        int startStartWord = 0;
        
        //The for loop goes through all of the indexes stored in the vector allWords to find the selected startStartWord
        for(int i = 0; i < allWords.size(); i++)
        {
          
          //The operator compare is used to compare the two strings 
          if(startWords.at(randStartWord).compare( allWords.at(i)) == 0)
          {
          
            
            //Starting word is assigned variable i 
            startStartWord = i;
            
            //If the summation of the start word and width of the word window is greater than the size
            //of the vector allWords then a message is prompted to the user
            if(startStartWord + wordWindowWidth > allWords.size())
            
            {
              
              
              //Prompt being shown to user 
              cout << "Start word " << startWords.at(randStartWord) << " doesn't have " << wordWindowWidth << " words after it in allWords. Exiting..." << endl;
              
              
            }
            
            //Breaks from the loop 
            break;
            
          }
        
        
        }
      
      
        // Store the chosen number of consecutive starting words
        // For loop goes through a certain amount of iterations depending on the size of the wordWindowWidth
        for(int i = 0; i < wordWindowWidth; i++)
        {
        
          
          //the push_back operator is used to push elements of vector allWords at the starting index + i into the end of the vector 
          //wordList. 
          wordList.push_back(allWords.at(startStartWord + i));
          
          
        }
        
//-------------------------------------------------------------------------------------------------------------------------------------            
          
            // Search for adjacent wordWindow words in allWords and find all the words that
           // follow the sequence of that word sequence.  Choose one at random and call it nextWord.
          // If in checkWordsMode then allow displaying single word values using the checkWords(...) function, then exit the program.
        
       int wordCounter = 0;
          
        while( true) {
          
          
          //Uses function getNextWord to find the next word sequence
          getNextWord( wordList, allWords, nextWord);
          
           //If the user chose the debug option in the menu then the if statement uses the function 
          //checkWords and sends three varibles 
          if(debugChoice == 1)
            {
              
              //checkWords is used to debug all of the existing word sequences 
              checkWords(startWords, allWords, wordList, nextWord);
       
            
            //Since the exit value is zero then the program is succesfully terminated  
              exit(0);
            
            }
            
            // Display the first word in the wordWindow
            cout << " " << wordList.at(0);
            wordCounter++;
            
          
          // If the first word in the wordWindow ends in a return, then we're done with our output for this tweet.
          // long is used to support 32 bits which would not be able to be hold by the int value 
          long g = wordList.at(0).size();
  
          
          //Prompt is shown to user in the case of g being equal to 0
          if(g == 0)
          {
            
            //Prompt shown to user   
            cout << "Abnormal condition where nextWord is: " << nextWord << " with length: " << g << ". Exiting..." << endl; 
          
          }
          
          //Assigns the char value choice with either \r or \n which was an input by the user 
          //in the case one of them is chosen then the loop breaks 
          char choice = wordList.at(0).at(g - 1);
          
          if(choice == '\r')
          {
            
            break;
            
          }
          else if(choice == '\n')
          {
             
            break;
           
          }
          
          
          // If there have been >= 30 words and the word ends with '.', '.' or '!' or '?', then we're done with output for this tween
          if(wordCounter >= 30)
          {
            if(choice == '.')
            {
              
              break;
            
            }
            else if(choice == '!')
            {
              
              break;
            
            }
            else if(choice == '?')
            {
              
              break;
              
            }
           
          
          }
          
          
            // Shift words "left" to prepare for next round, shifting nextWord into the "right" of the wordWindow words. 
            long listSize = wordList.size();
            
            //For loop goes through the size of iterations as listSize minus one element 
            for( int i=0; i < listSize - 1; i++) 
            {
              
                wordList.at( i) = wordList.at( i+1);
              
            }
            
            
            //Assigns vector wordList at a certain element with string nextWord
            wordList.at(listSize - 1) = nextWord;
          
                        
        }//end while( true)
        
      
    }// end while( userInput != 'x')
    
  
    cout << endl << endl;
    
    
  return 0;
}//end main()
