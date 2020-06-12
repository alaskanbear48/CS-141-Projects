/* Prog2Contagion.cpp

   Program #2: Play the game of Contagion against another person
               This is a variation of Ataxx, a version of which can
               be played online at: http://www.classikgames.com/ataxx.html
   Class: CS 141
   Date: 1/27/2019
   Author: *** YOUR NAME HERE ***

   Grading Rubric:
     55% Passes Codio run-time tests (some cases below are split into multiple tests)
          5 Handles both upper and lower case user input
          5 Handles making adjacent move for each player
         10 Handles making jump move for each player
          5 Handles pass move 
          2 Error message and retry when source position does not belong to player
          2 Error message and retry when destination position is not empty
          6 Error message and retry when destination is not one or two squares away
            in horizontal, vertical, or diagonal line
         15 Flips opponent pieces adjacent to move destination
          5 When board is filled correctly identifies winner and exits program

     45% Programming Style:
         10 Meaningful Identifier Names.
         10 Comments, header, and meaningful variable names
         10 Functional Decomposition 
         10 Appropriate data and control structures
          5 Code Layout
*/
#include <iostream>
#include <cstdlib>   // for exit() and abs()
#include <cmath>
#include <cctype>
#include <string>
using namespace std;


// The 25 board position variables may be global variables, but no other variables may be global.
char  p1, p2, p3, p4, p5,
      p6, p7, p8, p9,p10,
     p11,p12,p13,p14,p15,
     p16,p17,p18,p19,p20,
     p21,p22,p23,p24,p25;


//-----------------------------------------------------------------------------------------
// Display the game instructions

// *** Yuwei: aboveFlip, belowFlip, etc. are very similar, combine them into one flip function.

//This function checks for an adjacent piece above the players chosen piece 
//Index and the value of are used in the void function
void aboveFlip(char index , char value)
{
    //A new index is calculated in order to determine the location of the adjacent box in
    //any given direction. This is achieved by substracting or adding a specific number.
    char newIndex = index - 5;
    
    //Swtich statement is used to save program lines and are a much simpler alternative to if statements
    //the new Index is used by the switch statement
    switch(newIndex)
    {
        
        //Each case statement uses conditional operators as substitutes for varius if statements.
        //I did this in order to use less lines of code.
        case 'A': p1 = (p1 != ' ') ? value: ' '; break; //This is a simplified version of an if statement. What it does is it checks if p1 is a blank space and if its not then its 
        case 'B': p2 = (p2 != ' ') ? value: ' '; break; //assigned the value of the current player. However if it is a blank space then it assigned a blank space and nothing changes
        case 'C': p3 = (p3 != ' ') ? value: ' '; break;
        case 'D': p4 = (p4 != ' ') ? value: ' '; break;
        case 'E': p5 = (p5 != ' ') ? value: ' '; break;
        case 'F': p6 = (p6 != ' ') ? value: ' '; break;
        case 'G': p7 = (p7 != ' ') ? value: ' '; break;
        case 'H': p8 = (p8 != ' ') ? value: ' '; break;
        case 'I': p9 = (p9 != ' ') ? value: ' '; break;
        case 'J': p10 = (p10 != ' ') ? value: ' '; break;
        case 'K': p11 = (p11 != ' ') ? value: ' '; break;
        case 'L': p12 = (p12 != ' ') ? value: ' '; break;
        case 'M': p13 = (p13 != ' ') ? value: ' '; break;
        case 'N': p14 = (p14 != ' ') ? value: ' '; break;
        case 'O': p15 = (p15 != ' ') ? value: ' '; break;
        case 'P': p16 = (p16 != ' ') ? value: ' '; break;
        case 'Q': p17 = (p17 != ' ') ? value: ' '; break;
        case 'R': p18 = (p18 != ' ') ? value: ' '; break;
        case 'S': p19 = (p19 != ' ') ? value: ' '; break;
        case 'T': p20 = (p20 != ' ') ? value: ' '; break;
            break;
        default: break;

    }
    
}
//There are a total of 8 different adjacent function checkers which are all very similar to each other
//The only difference between each of them is that none check the same rows. This removes the posibility for the 
//program to go out of bounds thus allowing the program to run efficiently. 
//In addition each function has a different newIndex which allows the function to know which location it is checking


//This function checks for an adjacent piece below the players chosen piece 
void belowFlip(char index , char value)
{
    char newIndex = index + 5;
    
    switch(newIndex)
    {
        
        case 'F': p6 = (p6 != ' ') ? value: ' '; break;
        case 'G': p7 = (p7 != ' ') ? value: ' '; break;
        case 'H': p8 = (p8 != ' ') ? value: ' '; break;
        case 'I': p9 = (p9 != ' ') ? value: ' '; break;
        case 'J': p10 = (p10 != ' ') ? value: ' '; break;
        case 'K': p11 = (p11 != ' ') ? value: ' '; break;
        case 'L': p12 = (p12 != ' ') ? value: ' '; break;
        case 'M': p13 = (p13 != ' ') ? value: ' '; break;
        case 'N': p14 = (p14 != ' ') ? value: ' '; break;
        case 'O': p15 = (p15 != ' ') ? value: ' '; break;
        case 'P': p16 = (p16 != ' ') ? value: ' '; break;
        case 'Q': p17 = (p17 != ' ') ? value: ' '; break;
        case 'R': p18 = (p18 != ' ') ? value: ' '; break;
        case 'S': p19 = (p19 != ' ') ? value: ' '; break;
        case 'T': p20 = (p20 != ' ') ? value: ' '; break;
        case 'U': p21 = (p21 != ' ') ? value: ' '; break;
        case 'V': p22 = (p22 != ' ') ? value: ' '; break;
        case 'W': p23 = (p23 != ' ') ? value: ' '; break;
        case 'X': p24 = (p24 != ' ') ? value: ' '; break;
        case 'Y': p25 = (p25 != ' ') ? value: ' '; break;
        default: break;

    }
    
}

//This function checks for an adjacent piece to the right of the players chosen piece 
void rightFlip(char index , char value)
{
    char newIndex = index + 1;
    
    switch(newIndex)
    {
        case 'B': p2 = (p2 != ' ') ? value: ' '; break;
        case 'C': p3 = (p3 != ' ') ? value: ' '; break;
        case 'D': p4 = (p4 != ' ') ? value: ' '; break;
        case 'E': p5 = (p5 != ' ') ? value: ' '; break;
        case 'G': p7 = (p7 != ' ') ? value: ' '; break;
        case 'H': p8 = (p8 != ' ') ? value: ' '; break;
        case 'I': p9 = (p9 != ' ') ? value: ' '; break;
        case 'J': p10 = (p10 != ' ') ? value: ' '; break;
         case 'L': p12 = (p12 != ' ') ? value: ' '; break;
        case 'M': p13 = (p13 != ' ') ? value: ' '; break;
        case 'N': p14 = (p14 != ' ') ? value: ' '; break;
        case 'O': p15 = (p15 != ' ') ? value: ' '; break;
        case 'Q': p17 = (p17 != ' ') ? value: ' '; break;
        case 'R': p18 = (p18 != ' ') ? value: ' '; break;
        case 'S': p19 = (p19 != ' ') ? value: ' '; break;
        case 'T': p20 = (p20 != ' ') ? value: ' '; break;
        case 'V': p22 = (p22 != ' ') ? value: ' '; break;
        case 'W': p23 = (p23 != ' ') ? value: ' '; break;
        case 'X': p24 = (p24 != ' ') ? value: ' '; break;
        case 'Y': p25 = (p25 != ' ') ? value: ' '; break;
        default: break;

    }
    
}

//This function checks for an adjacent piece to the left of the players chosen piece 
void leftFlip(char index , char value)
{
    char newIndex = index - 1;
    
    switch(newIndex)
    {
        case 'A': p1 = (p1 != ' ') ? value: ' '; break;
        case 'B': p2 = (p2 != ' ') ? value: ' '; break;
        case 'C': p3 = (p3 != ' ') ? value: ' '; break;
        case 'D': p4 = (p4 != ' ') ? value: ' '; break;
        case 'F': p6 = (p6 != ' ') ? value: ' '; break;
        case 'G': p7 = (p7 != ' ') ? value: ' '; break;
        case 'H': p8 = (p8 != ' ') ? value: ' '; break;
        case 'I': p9 = (p9 != ' ') ? value: ' '; break;
        case 'K': p11 = (p11 != ' ') ? value: ' '; break;
        case 'L': p12 = (p12 != ' ') ? value: ' '; break;
        case 'M': p13 = (p13 != ' ') ? value: ' '; break;
        case 'N': p14 = (p14 != ' ') ? value: ' '; break;
        case 'P': p16 = (p16 != ' ') ? value: ' '; break;
        case 'Q': p17 = (p17 != ' ') ? value: ' '; break;
        case 'R': p18 = (p18 != ' ') ? value: ' '; break;
        case 'S': p19 = (p19 != ' ') ? value: ' '; break;
        case 'U': p21 = (p21 != ' ') ? value: ' '; break;
        case 'V': p22 = (p22 != ' ') ? value: ' '; break;
        case 'W': p23 = (p23 != ' ') ? value: ' '; break;
        case 'X': p24 = (p24 != ' ') ? value: ' '; break;
        
        default: break;

    }
    
}

//This function checks for an adjacent piece above to the right of the players chosen piece 
void upRightFlip(char index , char value)
{
    char newIndex = index - 4;
    
    switch(newIndex)
    {
        
        case 'B': p2 = (p2 != ' ') ? value: ' '; break;
        case 'C': p3 = (p3 != ' ') ? value: ' '; break;
        case 'D': p4 = (p4 != ' ') ? value: ' '; break;
        case 'E': p5 = (p5 != ' ') ? value: ' '; break;
        case 'G': p7 = (p7 != ' ') ? value: ' '; break;
        case 'H': p8 = (p8 != ' ') ? value: ' '; break;
        case 'I': p9 = (p9 != ' ') ? value: ' '; break;
        case 'J': p10 = (p10 != ' ') ? value: ' '; break;
        case 'L': p12 = (p12 != ' ') ? value: ' '; break;
        case 'M': p13 = (p13 != ' ') ? value: ' '; break;
        case 'N': p14 = (p14 != ' ') ? value: ' '; break;
        case 'O': p15 = (p15 != ' ') ? value: ' '; break;
        case 'Q': p17 = (p17 != ' ') ? value: ' '; break;
        case 'R': p18 = (p18 != ' ') ? value: ' '; break;
        case 'S': p19 = (p19 != ' ') ? value: ' '; break;
        case 'T': p20 = (p20 != ' ') ? value: ' '; break;
        default: break;

    }
    
}

//This function checks for an adjacent piece above to the left of the players chosen piece 
void upLeftFlip(char index , char value)
{
    char newIndex = index - 6;
    
    switch(newIndex)
    {
        case 'A': p1 = (p1 != ' ') ? value: ' '; break;
        case 'B': p2 = (p2 != ' ') ? value: ' '; break;
        case 'C': p3 = (p3 != ' ') ? value: ' '; break;
        case 'D': p4 = (p4 != ' ') ? value: ' '; break;
        
        case 'F': p6 = (p6 != ' ') ? value: ' '; break;
        case 'G': p7 = (p7 != ' ') ? value: ' '; break;
        case 'H': p8 = (p8 != ' ') ? value: ' '; break;
        case 'I': p9 = (p9 != ' ') ? value: ' '; break;
        
        case 'K': p11 = (p11 != ' ') ? value: ' '; break;
        case 'L': p12 = (p12 != ' ') ? value: ' '; break;
        case 'M': p13 = (p13 != ' ') ? value: ' '; break;
        case 'N': p14 = (p14 != ' ') ? value: ' '; break;
       
        case 'P': p16 = (p16 != ' ') ? value: ' '; break;
        case 'Q': p17 = (p17 != ' ') ? value: ' '; break;
        case 'R': p18 = (p18 != ' ') ? value: ' '; break;
        case 'S': p19 = (p19 != ' ') ? value: ' '; break;
        case 'T': p20 = (p20 != ' ') ? value: ' '; break;
            
        default: break;

    }
    
}

//This function checks for an adjacent piece below to the right of the players chosen piece 
void downRightFlip(char index , char value)
{
    char newIndex = index + 6;
    
    switch(newIndex)
    {
        
        
        case 'G': p7 = (p7 != ' ') ? value: ' '; break;
        case 'H': p8 = (p8 != ' ') ? value: ' '; break;
        case 'I': p9 = (p9 != ' ') ? value: ' '; break;
        case 'J': p10 = (p10 != ' ') ? value: ' '; break;
        
        case 'L': p12 = (p12 != ' ') ? value: ' '; break;
        case 'M': p13 = (p13 != ' ') ? value: ' '; break;
        case 'N': p14 = (p14 != ' ') ? value: ' '; break;
        case 'O': p15 = (p15 != ' ') ? value: ' '; break;
       
        case 'Q': p17 = (p17 != ' ') ? value: ' '; break;
        case 'R': p18 = (p18 != ' ') ? value: ' '; break;
        case 'S': p19 = (p19 != ' ') ? value: ' '; break;
        case 'T': p20 = (p20 != ' ') ? value: ' '; break;
            
        case 'V': p22 = (p22 != ' ') ? value: ' '; break;
        case 'W': p23 = (p23 != ' ') ? value: ' '; break;
        case 'X': p24 = (p24 != ' ') ? value: ' '; break;
        case 'Y': p25 = (p25 != ' ') ? value: ' '; break;
        default: break;

    }
    
}

//This function checks for an adjacent piece below to the left of the players chosen piece 
void downLeftFlip(char index , char value)
{
    char newIndex = index + 4;
    
    switch(newIndex)
    {
        
        case 'F': p6 = (p6 != ' ') ? value: ' '; break;
        case 'G': p7 = (p7 != ' ') ? value: ' '; break;
        case 'H': p8 = (p8 != ' ') ? value: ' '; break;
        case 'I': p9 = (p9 != ' ') ? value: ' '; break;
        
        case 'K': p11 = (p11 != ' ') ? value: ' '; break;
        case 'L': p12 = (p12 != ' ') ? value: ' '; break;
        case 'M': p13 = (p13 != ' ') ? value: ' '; break;
        case 'N': p14 = (p14 != ' ') ? value: ' '; break;
       
       
        case 'P': p16 = (p16 != ' ') ? value: ' '; break;
        case 'Q': p17 = (p17 != ' ') ? value: ' '; break;
        case 'R': p18 = (p18 != ' ') ? value: ' '; break;
        case 'S': p19 = (p19 != ' ') ? value: ' '; break;
        
        case 'U': p21 = (p21 != ' ') ? value: ' '; break;
        case 'V': p22 = (p22 != ' ') ? value: ' '; break;
        case 'W': p23 = (p23 != ' ') ? value: ' '; break;
        case 'X': p24 = (p24 != ' ') ? value: ' '; break;
        
        default: break;

    }
    
}

//The purpose of this function is to assign the first move of the player to a blank character value.
//This is due to the program recognizing it is a jump move which means that the value of the source jumps to its new location
//but the original source is left blank.

//The function uses the row and column of the original source
void jumpMove( char row, char column)
{
    
    //Row and Column is used to identify the original source of the move.
    //Each if statement checks for every postion on the board and once it is matched 
    //with the row and column it assigns that value to blank
    if (row == 'A' && column == '1')
    {
        p1 = ' ';
    }
    else if (row == 'A' && column == '2')
    {
        p2 = ' ';
    }
    else if (row == 'A' && column == '3')
    {
        p3 = ' ';
    }
    else if (row == 'A' && column == '4')
    {
        p4 = ' ';
    }
    else if (row == 'A' && column == '5')
    {
        p5 = ' ';
    }
    else if (row == 'B' && column == '1')
    {
        p6 = ' ';
    }
    else if (row == 'B' && column == '2')
    {
        p7 = ' ';
    }
    else if (row == 'B' && column == '3')
    {
        p8 = ' ';
    }
    else if (row == 'B' && column == '4')
    {
        p9 = ' ';
    }
    else if (row == 'B' && column == '5')
    {
        p10 = ' ';
    }
    else if (row == 'C' && column == '1')
    {
        p11 = ' ';
    }
    else if (row == 'C' && column == '2')
    {
        p12 = ' ';
    }
    else if (row == 'C' && column == '3')
    {
        p13 = ' ';
    }
    else if (row == 'C' && column == '4')
    {
        p14 = ' ';
    }
    else if (row == 'C' && column == '5')
    {
        p15 = ' ';
    }
    else if (row == 'D' && column == '1')
    {
        p16 = ' ';
    }
    else if (row == 'D' && column == '2')
    {
        p17 = ' ';
    }
    else if (row == 'D' && column == '3')
    {
        p18 = ' ';
    }
    else if (row == 'D' && column == '4')
    {
        p19 = ' ';
    }
    else if (row == 'D' && column == '5')
    {
        p20 = ' ';
    }
    else if (row == 'E' && column == '1')
    {
        p21 = ' ';
    }
    else if (row == 'E' && column == '2')
    {
        p22 = ' ';
    }
    else if (row == 'E' && column == '3')
    {
        p23 = ' ';
    }
    else if (row == 'E' && column == '4')
    {
        p24 = ' ';
    }
    else if (row == 'E' && column == '5')
    {
        p25 = ' ';
    }
  
}

// *** Yuwei: getAvalue, getBvalue, etc. are very similar, combine them into one getValues function.
//Gets value from only posible row A locations
char getAvalue(char number)
{
    //Sets value to a blank space
    char value = ' ';
    
    //Switch statement checks for the location given by number 
    switch(number )
    {
        //If a case is matched then the value is assigned with the value of that location
        case  '1': value =  p1; break;
        case  '2': value =  p2; break;
        case  '3': value =  p3; break;
        case  '4': value =  p4; break;
        case  '5': value =  p5; break;
        default: cout<<endl<<"***Invalid Source"<<endl;
     
  
    }

    //The value of the location is then returned
    return value;
      
}

//Each getValue function functions the same way as the one above 
//the only difference is there is a function for each individual row.

//Gets value from only posible row B locations
char getBvalue(char number)
{
     char value = ' ';
    
     switch(number )
    {
        case  '1': value =  p6; break;
        case  '2': value =  p7; break;
        case  '3': value =  p8; break;
        case  '4': value =  p9; break;
        case  '5': value =  p10; break;
        default: cout<<endl<<"***Invalid Source"<<endl;
     
  
    }

    return value;
      
}

//Gets value from only posible row C locations
char getCvalue(char number)
{
     char value = ' ';
    
     switch(number )
    {
        case  '1': value =  p11; break;
        case  '2': value =  p12; break;
        case  '3': value =  p13; break;
        case  '4': value =  p14; break;
        case  '5': value =  p15; break;
        default: cout<<endl<<"***Invalid Source"<<endl;
     
  
    }

    return value;
      
}

//Gets value from only posible row D locations
char getDvalue(char number)
{
     char value = ' ';
    
     switch(number )
    {
        case  '1': value =  p16; break;
        case  '2': value =  p17; break;
        case  '3': value =  p18; break;
        case  '4': value =  p19; break;
        case  '5': value =  p20; break;
        default: cout<<endl<<"***Invalid Source"<<endl;
     
  
    }

    return value;
      
}

//Gets value from only posible row E locations
char getEvalue(char number)
{
     char value = ' ';
    
     switch(number )
    {
        case  '1': value =  p21; break;
        case  '2': value =  p22; break;
        case  '3': value =  p23; break;
        case  '4': value =  p24; break;
        case  '5': value =  p25; break;
        default: cout<<endl<<"***Invalid Source"<<endl;
     
  
    }

    return value;
      
}



//Sets a new value to the new location chosen by the player. This function checks for a location in row A 
char setAvalue(char number, char value)
{
    //Index is initialize which will be used to identify adjacent directions relative to the new postion 
    //chosen by the player. 
    char index;
    
    //Switch statement is used to assign new char value to the new location 
    switch(number )
    {
        //Each case statement uses a simplified if statement in oder to save lines
        //Each statement checks for blank spaces which returns a Z index which gives a warning to the user for an invalide move.
        //However if there is no invalid move then index is assign a value and a new value is set the chosen player location 
        case  '1': index = (p1 != ' ') ? 'Z' : 'A'; p1 = (index == 'A') ? value: value; break;
        case  '2': index = (p2 != ' ') ? 'Z' : 'B'; p2 = (index == 'B') ? value: value; break;
        case  '3': index = (p3 != ' ') ? 'Z' : 'C'; p3 = (index == 'C') ? value: value; break;
        case  '4': index = (p4 != ' ') ? 'Z' : 'D'; p4 = (index == 'D') ? value: value; break;
        case  '5': index = (p5 != ' ') ? 'Z' : 'E'; p5 = (index == 'E') ? value: value; break;
        default:  cout<<endl<<"***Invalid Destination"<<endl;
     
  
    }
    
    //Index is returned for use in adjacent operations
    return index;
}

//Likewise the following functions are all used to check for each individual row from row A to E. They are all 
//very similar with the difference being is the index assigned depends on the row being checked by the function. 
//For example Row A and E will not have the same indexes assigned due to being in different locations 

//Sets a new value to the new location chosen by the player. This function checks for a location in row B 
char setBvalue(char number, char value)
{
        char index;
    
    switch(number )
    {
        case  '1': index = (p6 != ' ') ? 'Z' : 'F'; p6 = (index == 'F') ? value: value; break;
        case  '2': index = (p7 != ' ') ? 'Z' : 'G'; p7 = (index == 'G') ? value: value; break;
        case  '3': index = (p8 != ' ') ? 'Z' : 'H'; p8 = (index == 'H') ? value: value; break;
        case  '4': index = (p9 != ' ') ? 'Z' : 'I'; p9 = (index == 'I') ? value: value; break;
        case  '5': index = (p10 != ' ') ? 'Z' : 'J'; p10 = (index == 'J') ? value: value; break;
        default:  cout<<endl<<"***Invalid Destination"<<endl;
     
  
    }
    return index;
}

//Sets a new value to the new location chosen by the player. This function checks for a location in row C 
char setCvalue(char number, char value)
{
    char index;
    
    switch(number )
    {
        case  '1': index = (p11 != ' ') ? 'Z' : 'K'; p11 = (index == 'K') ? value: value; break;
        case  '2': index = (p12 != ' ') ? 'Z' : 'L'; p12 = (index == 'L') ? value: value; break;
        case  '3': index = (p13 != ' ') ? 'Z' : 'M'; p13 = (index == 'M') ? value: value; break;
        case  '4': index = (p14 != ' ') ? 'Z' : 'N'; p14 = (index == 'N') ? value: value; break;
        case  '5': index = (p15 != ' ') ? 'Z' : 'O'; p15 = (index == 'O') ? value: value; break;
        default:  cout<<endl<<"***Invalid Destination"<<endl;
     
  
    }
    
    return index;
}

//Sets a new value to the new location chosen by the player. This function checks for a location in row D 
char setDvalue(char number, char value)
{
    char index;
    
    switch(number )
    {
        case  '1': index = (p16 != ' ') ? 'Z' : 'P'; p16 = (index == 'P') ? value: value; break;
        case  '2': index = (p17 != ' ') ? 'Z' : 'Q'; p17 = (index == 'Q') ? value: value; break;
        case  '3': index = (p18 != ' ') ? 'Z' : 'R'; p18 = (index == 'R') ? value: value; break;
        case  '4': index = (p19 != ' ') ? 'Z' : 'S'; p19 = (index == 'S') ? value: value; break;
        case  '5': index = (p20 != ' ') ? 'Z' : 'T'; p20 = (index == 'T') ? value: value; break;
        default:  cout<<endl<<"***Invalid Destination"<<endl;
     
  
    }
    return index;
}

//Sets a new value to the new location chosen by the player. This function checks for a location in row E 
char setEvalue(char number, char value)
{
    
    char index;
    
        switch(number )
    {
        case  '1': index = (p21 != ' ') ? 'Z' : 'U'; p21 = (index == 'U') ? value: value; break;
        case  '2': index = (p22 != ' ') ? 'Z' : 'V'; p22 = (index == 'V') ? value: value; break;
        case  '3': index = (p23 != ' ') ? 'Z' : 'W'; p23 = (index == 'W') ? value: value; break;
        case  '4': index = (p24 != ' ') ? 'Z' : 'X'; p24 = (index == 'X') ? value: value; break;
        case  '5': index = (p25 != ' ') ? 'Z' : 'Y'; p25 = (index == 'Y') ? value: value; break;
        default:  cout<<endl<<"***Invalid Destination"<<endl;
     
  
    }
    return index;
}

//The purpose of this function is to identify the row in which the player made the first move and then pass
//the column to another function where the char value of that postion will be assigned and retrived
char getValue(char letter, char number)
{
    //Checks for the corresponding row the user chose
    switch ( letter)
    {
        //For each case the column value is sent to the corresponding function for a value to be retrived
        case  'A': getAvalue(number); break;
        case  'B': getBvalue(number); break;
        case  'C': getCvalue(number); break;
        case  'D': getDvalue(number); break;
        case  'E': getEvalue(number); break;
        default: cout<<endl<<"***Invalid Source"<<endl;           
    }
    
}

//The purpose of this function is to set a new value to the chosen location made by the user. In addition it
//can inform the user that their chosen location is invalid. In addition it sets a new index value. 
char setValueAt(char letter, char number, char value)
{
    //Checks for the corresponding row
    switch ( letter)
    {
        //For each case the column value along with the value that was retrived is sent to its corresponding function
        case  'A': setAvalue(number, value); break;
        case  'B': setBvalue(number, value); break;
        case  'C': setCvalue(number, value); break;
        case  'D': setDvalue(number, value); break;
        case  'E': setEvalue(number, value); break;
        default:  cout<<endl<<"***Invalid Destination"<<endl;
    }
    
    
    
}

//Displays instructions to user 
void displayInstructions()
{
    cout << " \n"
         << "Welcome to the 2-player game of Contagion, where the point of the game is    \n"
         << "to capture as much of the board as possible.  On each move you must enter \n"
         << "the row and column position of one of your current pieces (e.g. a1) and   \n"
         << "the row and column of an empty destination, which must be one or two      \n"
         << "squares away.  Moves can be made horizontally, vertically, or diagonally. \n"
         << " \n"
         << "If the destination is one square away, then an additional piece for you   \n"
         << "is placed in the destination square.  If the destination is two squares   \n"
         << "away (a jump move), then the original piece is moved to that destination. \n"
         << "jumping over a single square or any player's piece.                       \n"
         << " \n"
         << "After a piece has been moved, all opponent pieces adjacent to the         \n"
         << "destination are changed to match the piece of the user making the move.   \n"
         << "Player X moves first.     \n"
         << " \n"
         << "A valid first move, for instance, could be: a1 a2  which since it is just \n"
         << "one square away, would put an additional X on square a2.  Alternatively   \n"
         << "if the first move is:  a1 c3  then since it is two squares away, the piece\n"
         << "currently at a1 would be moved to destination c3.                         \n"
         << endl;
}






//Displays an updated board to the user in wich they can base their move on. 
void displayBoard()
{
    cout << "    1   2   3   4   5  \n"
         << "  ---------------------\n"
         << "A | " <<  p1 << " | " <<  p2 << " | " <<  p3 << " | " <<  p4 << " | " <<  p5 << " | A \n"
         << "  |---|---|---|---|---| \n"
         << "B | " <<  p6 << " | " <<  p7 << " | " <<  p8 << " | " <<  p9 << " | " << p10 << " | B \n"
         << "  |---|---|---|---|---| \n"
         << "C | " << p11 << " | " << p12 << " | " << p13 << " | " << p14 << " | " << p15 << " | C \n"
         << "  |---|---|---|---|---| \n"
         << "D | " << p16 << " | " << p17 << " | " << p18 << " | " << p19 << " | " << p20 << " | D \n"
         << "  |---|---|---|---|---| \n"
         << "E | " << p21 << " | " << p22 << " | " << p23 << " | " << p24 << " | " << p25 << " | E \n"
         << "  ---------------------\n"
         << "    1   2   3   4   5  \n"
         << endl;
}

//The purpose of this function is to check the score of the game and allow the program to 
//identify a winner of the game 
void gameScore(int &scoreX, int &scoreO)
{
    //Each score is set to 0 
    scoreX = 0;
    scoreO = 0;
    
    //The for loop checks every single row and column for X's and O's
    for( char row = 'A'; row <= 'E'; row++)
        {
            for( char col = '1'; col <= '5'; col++)
            {
                //The functions to get a value are used to check for values at that specific location. 
                char c = getValue(row, col);
                
                //If the location is equal to X then the scoreX is updated or vise versa with O
                if (c == 'X')
                {
                    scoreX++;
                }
                else if (c == 'O')
                {
                    scoreO++;
                }
            }
        }
      
}



//-----------------------------------------------------------------------------------------
int main() {
    // Set initial values for the global board variables to all be blank
    p1=p2=p3=p4=p5=p6=p7=p8=p9=p10=p11=p12=p13=p14=p15=p16=p17=p18=p19=p20=p21=p22=p23=p24=p25= ' ';
    // Set corner starting positions
    p1=p25= 'X';
    p5=p21= 'O';
    
    // Variables to store user input for current row and column, and destination row and column
    char oLetter;
    char oNumber;
    
    //Varibales are used to store the new row and column that the user chooses 
    char nLetter;
    char nNumber;
    
    //Used for new value set  
    char newValue;
    
    //Varible used for adjacent identification 
    char index;
    
    //Varibale checks for which player is moving their piece 
    char moveChar;
    //Move counter begins at one 
    int turn = 1;
    
    //Scores for each player by dafault starts with a score of two each 
    int scoreX = 2;
    int scoreO = 2;
    
    //Welcomes player 
    cout << "Welcome to the 2-player game of Contagion. \n"
         << endl;

    // Main loop to play game
    while( true) {
    
        // Display board and handle first character of user input
        displayBoard();
        
       //Used to check which player is taking their turn either X or O
        int oddEven = turn % 2;
        
        //Player X only moves in odd rounds and O player moves in even rounds 
        if(oddEven != 0)
        {
            moveChar = 'X';
        }
        else 
        {
            moveChar = 'O';
        }
        
        //Informs the player whose turn is it and which round it is 
        cout << turn << ". " << "Enter 'i' for instructions, 'x' to exit, or move for " << moveChar << ": ";
        cin >> oLetter;//Input row 
        oLetter = toupper(oLetter);//Converts row character to upper case 
        
        //If the first character is P then the player passes and the next round goes to the next player 
        if(oLetter == 'P')
        {
            turn++;
            continue;
        }
        
        cin >> oNumber;//Input column
        
        cin >> nLetter;//Input new row
        cin >> nNumber;//Input new column
        
        cout << endl;
        
        //Converts row characters to upper case 
         oLetter = toupper(oLetter);
         nLetter = toupper(nLetter);
        
        //Checks for adjacent moves or jump moves 
        int letterDifference = abs(oLetter - nLetter);
        int numberDifference = abs(oNumber - nNumber);
        
        // Check to see if user input was 'i' for instructions or 'x' to exit
        if( oLetter == 'I') {
            displayInstructions();
            continue;       // Loop back up to retry move
        }
        //Cheks for the user wanting to exit the program
        else if( oLetter == 'X') {
            displayBoard();
            
           
            break;  // Break out of enclosing loop, to exit the game.
        }
        else {
            
             //If statement checks for an adjacent move  
            if((letterDifference == 0 && numberDifference == 1) ||
               (letterDifference == 1 && numberDifference == 0) ||
               (letterDifference == 1 && numberDifference == 1)
              ){
            
              
              //New value is retrived from original source 
                newValue = getValue(oLetter, oNumber);
               
                //If the new value does not belong to the current player move then the player needs to go again 
                if(newValue != moveChar)
                {
                    cout << "*** Invalid move.  Current piece must belong to you. Please retry." << endl;
                    continue;
                }
                
                //Index is retrived from function in order to check for adjacent locations 
                index = setValueAt(nLetter, nNumber, newValue);
                 
                //If the index returns as Z then that means that the move is invalid as the destination is empty
                if(index == 'Z')
                {
                    cout << "*** Invalid move.  Destination must be empty. Please retry." << endl;
                    continue;
                }
                
                //Each of the functions checks for an adjacent piece at any direction 
               aboveFlip(index, newValue);
               belowFlip(index, newValue);
               rightFlip(index, newValue);
               leftFlip(index, newValue);
               upRightFlip(index, newValue);
               upLeftFlip(index, newValue);
               downRightFlip(index, newValue);
               downLeftFlip(index, newValue);
        
            }
            //If statement checks for a jump move which if it is then the original source is set to a blank space
            else if((letterDifference == 0 && numberDifference == 2) ||
                    (letterDifference == 2 && numberDifference == 0) ||
                    (letterDifference == 2 && numberDifference == 2)
                   ){
                
               //New value is retrived from original source
               newValue = getValue(oLetter, oNumber);
               
                //If the new value does not belong to the current player move then the player needs to go again 
                if(newValue != moveChar)
                {
                    cout << "*** Invalid move.  Current piece must belong to you. Please retry." << endl;
                    continue;
                }
                
               //function sets the original source into a blank space 
                jumpMove(oLetter, oNumber);
               
                //Index is retrived from function in order to check for adjacent locations 
               index = setValueAt(nLetter, nNumber, newValue);
               
                 //If the index returns as Z then that means that the move is invalid as the destination is empty
                if(index == 'Z')
                {
                    cout << "*** Invalid move.  Destination must be empty. Please retry." << endl;
                    continue;
                }
                
               //Each of the functions checks for an adjacent piece at any direction 
               aboveFlip(index, newValue);
               belowFlip(index, newValue);
               rightFlip(index, newValue);
               leftFlip(index, newValue);
               upRightFlip(index, newValue);
               upLeftFlip(index, newValue);
               downRightFlip(index, newValue);
               downLeftFlip(index, newValue);
              }
        //If the move is not adjacent or a jump move then the player is notified 
        else
        {
            cout <<"*** Invalid move.  A move must be one or two squares away. Please retry. " << endl;
                continue;
        }
             
            //Checks for game score 
            gameScore(scoreX, scoreO);
            
            //used to check for full board 
            int sum = scoreX + scoreO;
            
            //Checks a full board 
           if (sum == 25)
           {
               displayBoard();
               break;
           }
            
            turn++;
        
        
        
        }
    } //end while( true)

    //Notifies the winner of the game 
    if(scoreO == scoreX)
            {
                cout << "Tie game." << endl;
            }
             if(scoreO > scoreX)
            {
                cout << "O wins!" << endl;
            }
             if(scoreX > scoreO)
            {
                cout << "X wins!" << endl;
            }
    
    //Informs the program is exiting 
    cout << "Exiting program... \n"
                 << endl;
    
    return 0;
} // end main()