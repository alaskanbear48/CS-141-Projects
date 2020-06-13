//  prog5_1024.cpp
//     Text and graphical version of the game 1024, a variant of 2048 available online at:
//        http://gabrielecirulli.github.io/2048/
//     Object of game is to combine number tiles with the same value, accumulating
//     points as the game progresses, to try and create the tile with the value 1024.
//     Each move consists of sliding pieces to the left, up, right or down.
// 
// Instructions:
//    To run the graphical version, first select the "Build and Run" option at the top of the window. You
//    can ignore the following error messages that will appear:
//         Failed to use the XRandR extension while trying to get the desktop video modes
//         Failed to use the XRandR extension while trying to get the desktop video modes
//         Failed to initialize inotify, joystick connections and disconnections won't be notified
//    To see the graphical output then select the "Viewer" option at the top of the window.
//    
// For more information about SFML graphics, see: https://www.sfml-dev.org/tutorials
// Be sure to close the old window each time you rebuild and rerun, to ensure you
// are seeing the latest output.
//
//
/*  Running the program (for the textual output) looks like:
	
	Manuel M Martinez
	UIC Spring 2019
	CS 141
	
*/
  
#include <SFML/Graphics.hpp> // Needed to access all the SFML graphics libraries
#include <iostream>          // Since we are using multiple libraries, now use std::
                             // in front of every cin, cout, endl, setw, and string 
#include <iomanip>           // used for setting output field size using setw
#include <cstdio>            // For sprintf, "printing" to a string
#include <cstring>           // For c-string functions such as strlen()  
#include <chrono>            // Used in pausing for some milliseconds using sleep_for(...)
#include <thread>            // Used in pausing for some milliseconds using sleep_for(...)

const int WindowXSize = 400;
const int WindowYSize = 500;
const int MaxBoardSize = 12;  // Max number of squares per side
const int MaxTileStartValue = 1024; 

//---------------------------------------------------------------------------------------
class Square {
	public:
		// Default Constructor 
		Square()
		{
			size = 0;
			xPosition = 0;
			yPosition = 0;
			color = sf::Color::Black;
			isVisible = false;
			isCaptured = false;
			text = "";		
		}
	
		// Fully-qualified constructor, used to set all fields
		Square( int theSize, int theXPosition, int theYPosition, 
			     const sf::Color &theColor, bool theVisibility, std::string theText)
		{
			// Set the class fields
			size = theSize;
			xPosition = theXPosition;
			yPosition = theYPosition;
			color = theColor;
			isVisible = theVisibility;
			isCaptured = false;   // By default squares have not been captured
			text = theText;
			// Use the values to set the display characteristics of theSquare
			theSquare.setSize( sf::Vector2f(theSize, theSize));
			theSquare.setPosition( theXPosition, theYPosition);   // Set the position of the square
			theSquare.setFillColor( theColor);
		}
			
		// Get (accessor) functions
		sf::RectangleShape getTheSquare() { return theSquare; }
		int getSize() { return size; }
		int getXPosition() { return xPosition; }
		int getYPosition() { return yPosition; }
		sf::Color& getColor() { return color; }
                bool getIsVisible() { return isVisible; }
		bool getIsCaptured() { return isCaptured; }
		std::string getText() { return text; }
	
		// Set (mutator) functions
		void setSize( int theSize) { 
			size = theSize; 
			theSquare.setSize( sf::Vector2f(theSize, theSize));
		}
		void setXPosition( int theXPosition) { 
			xPosition = theXPosition; 
			theSquare.setPosition( theXPosition, yPosition);   // Set the position of the square
		}
		void setYPosition( int theYPosition) { 
			yPosition = theYPosition; 
			theSquare.setPosition( xPosition, theYPosition);   // Set the position of the square
		}
		void setColor( sf::Color & theColor) { 
			color = theColor; 
			theSquare.setFillColor( theColor);    // Also update the color on the square itself
		}
		void setColor( int R, int G, int B) {
			sf::Color theNewColor( R, G, B);
			color = theNewColor;
			theSquare.setFillColor( theNewColor);
		}
		void setVisibility( bool theVisibility) { isVisible = theVisibility; }
		void setIsCaptured( bool isCaptured) { this->isCaptured = isCaptured; }
		void setText( std::string theText) { text = theText; }

		// Utility functions
		void displayText( sf::RenderWindow *pWindow, sf::Font theFont, sf::Color theColor, int textSize);
	
	private:
		int size;
		int xPosition;
		int yPosition;
		sf::Color color;
		bool isVisible;
		bool isCaptured;   // Indicates whether or not it is part of the captured area
		std::string text;
		sf::RectangleShape theSquare;

}; //end class Square


//---------------------------------------------------------------------------------------
// Square class utility function to create a sf::Text object to store and display text 
// associated with this Square.
// 
// Assuming we display output in sf::RenderWindow window(...), then call this function using: 
//    aSquare.displayTest( &window);
// or when using an array of Square pointers declared as:  Square *squaresArray[ 4];
// then call it using:  squaresArray[i]->displayText( &window);
void Square::displayText( 
		sf::RenderWindow *pWindow,   // The window into which we draw everything
		sf::Font theFont,            // Font to be used in displaying text   
		sf::Color theColor,          // Color of the font
		int textSize)                // Size of the text to be displayed
{	
	// Create a sf::Text object to draw the text, using a sf::Text constructor
	sf::Text theText( text,        // text is a class data member
					  theFont,     // font from a font file, passed as a parameter
					  textSize);   // this is the size of text to be displayed

	// Text color is the designated one, unless the background is Yellow, in which case the text
	// color gets changed to blue so we can see it, since we can't see white-on-yellow very well
	if( this->getColor() == sf::Color::Yellow) {
		theColor = sf::Color::Blue;
	}
	theText.setColor( theColor);

	// Place text in the corresponding square, centered in both x (horizontally) and y (vertically)
	// For horizontal center, find the center of the square and subtract half the width of the text 
	int theXPosition = xPosition + (size / 2) - ((strlen(text.c_str()) * theText.getCharacterSize()) / 2);
	// For the vertical center, from the top of the square go down the amount: (square size - text size) / 2
	int theYPosition = yPosition + (size - theText.getCharacterSize()) / 2;
	// Use an additional offset to get it centered
	int offset = 5;
	theText.setPosition( theXPosition + offset, theYPosition - offset);

	// Finally draw the Text object in the RenderWindow
	pWindow->draw( theText);
}


//---------------------------------------------------------------------------------------
// Initialize the font
void initializeFont( sf::Font &theFont)
{
	// Create the global font object from the font file
	if (!theFont.loadFromFile("arial.ttf"))
	{
		std::cout << "Unable to load font. " << std::endl;
		exit( -1);
	}	
}

//************************************************************************************************

// Display Instructions
void displayInstructions()
{
    std::cout << "Welcome to 1024. \n"
         << "  \n"
         << "For each move enter a direction as a letter key, as follows: \n"
		 << "    W    \n"
		 << "  A S D  \n"
		 << "where A=left,W=up, D=right and S=down. \n"
		 << "  \n"
		 << "After a move, when two identical valued tiles come together they    \n"
		 << "join to become a new single tile with the value of the sum of the   \n"
		 << "two originals. This value gets added to the score.  On each move    \n"
		 << "one new randomly chosen value of 2 or 4 is placed in a random open  \n"
		 << "square.  User input of x exits the game.                            \n"
		 << "  \n";
    std::cout << "Game ends when you reach " << MaxTileStartValue << "." << std::endl;
}//end displayInstructions()

//Struct Node is used to create Nodes with space to store the board, move number, score, and pNext
struct Node
{
  int undoBoard[ MaxBoardSize *  MaxBoardSize];
  int moveScore;
  int moveNumber;
  
    
  Node* pNext;  
    
};

//Deletes current node and moves pHead to the previous node 
void undoDelete(Node* &pHead)
{
    Node *pCopy = pHead;//Creates pointer pCopy and tells it to point to current node 
    
    pHead = pHead->pNext;//Moves pHead to point to the previous node     
    
    delete pCopy;//Deletes the current node as pHead is no longer pointing to it  
}

//Stores the board, move number, and score into a new node 
void snapShot(int move, int score, int board[], Node* &pHead, int max)
{
    //Creates pointer pTemp 
    Node* pTemp;

    //Creates new node which pTemp is pointing at 
    pTemp = new Node;
    for(int i = 0; i < max * max; i++)//Stores current board into the node 
    {
        pTemp->undoBoard[i] = board[i];
    }
    pTemp->moveScore = score;//Stores the score into the node  
    pTemp->moveNumber = move;//Stores the move number into the node 
    //pNext points to pHead which assigns it a null value in the first move
    pTemp->pNext = pHead;  
    pHead = pTemp;//pHead points to the same node as pNext
    
    
}

//Assigns all the values of the previous board to the current board using the values of a node in the list 
void undo(int &move, int &score, int board[], Node* &pHead, int max)
{
    
           
    score = pHead->moveScore;
    move = pHead->moveNumber;
    
    for(int i; i < max * max; i++)
    {
       board[i] = pHead->undoBoard[i];
    }
    
    
}

//Function used to switch given index values from the board array with each other 
void switching(int board[], int z, int index)
{
    
    //The value of board[z] is stored in integer m
    int m = board[z];
    
    //board[z] is assigned with the value of board[index]
    board[z] = board[index];
    //board[index] is now assigned the value of m which was the previous value of board[z]
    board[index] = m; 
    
    
    
    
}

//Moves pieces to the left side of the board
//Max is equivalent to squaresPerSide but is set to a shorter variable name 
void leftMove(int board[], int max, int& score)
{
    //Loop over every column
   for(int i = 0; i < max; i++)
   {
        
      //Loop over every row value in given column   
     //Moves values in current row and column
    for(int j = i; j <= max * max - max + i; j++)
        {
        
         
        int index = 0; //Sets the value of index to zero 
        int k = 1; //Assigns integer variable k to one 
        int g = max - 1; //Assigns integer variable g to the difference between the squares per side and one 
        int w = 0; //Assigns integer w to a zero value 
        
        //Checks if the value of array board at index j is equal to zeo
        if(board[j] == 0)
            {
               //If the index j is equivalent to variable g then the last column is skiped from being checked for possible moves 
               if(j == g)
               {
                   break;
               }
               
               //If the index j is not equal to g then the do loop is executed 
               //which checks for the nearest next non zero value in the current column 
               do
               {
                  //The value of variable index is assigned with the value of index j plus the current squares per side
                  //The sum is taken in order for the new index to be right of index j
                  index = j + k;
               
                  //If the board at the new index is not equal to zero then it is the nearest non zero number
                  if(board[index] != 0)
                  {
                     //Index j and the new index and the board array are sent to the switch function in order for the values of board 
                     //at j and index to be swithched 
                      switching(board, j, index);
                      break; //Exits the loop

                  }
               
               //If the nearest next non zero is not found then k is increased by 1 which is added to index j
               //which sets the value of index to increase and be one step more to the right        
               k = k + 1;
               //If the current index plus one is divisible by the current squares per side then there cannot be any more index values 
               //to the left to be checked thus ending the loop 
               w = (index + 1) % max;  
               
               //If w is not equal to zero which means there are more index values to be checked to the left then the loop keeps on executing
               }while(w != 0);
                
            }
            
           //Moves to the next row value in the current column
           j = j + max - 1; 
        }
    
    //Loop over every row value in given column   
   //combines row values in current column
    for(int j = i;j <= max * max - max + i; j++)
        {
            int newIndex = 0; //Sets newIndex to a value of zero 
            int n = 1; //Assigns intger n to a value of one 
            int f = max - 1; //Assigns integer f to the difference between max and one 
            int y = 0;
            
            //If the board value at index j is not equal to zero then the column will be checked for any 
            //same inter values 
            if(board[j] != 0)
            {
              //If index j is equal to f then the the column loop has reached its last iteration thus it will not check for any 
              //possible combinations 
               if(j == f)
               {
                   break;//Exits loop 
               }
               
               //This loop is designed to look for an equal value to index j
               do
               {
                //The newIndex is increased by n in order to find the nearest non zero value 
                //to the right of index j
                newIndex = j + n;
                
                //If the value of board at newIndex is not equal to zero then it is the nearest non zero to right of index j
                if(board[newIndex] != 0)
                {
                    //If the values of board at j and newIndex are equal then they are combined 
                    if(board[j] == board[newIndex])
                    {
                        //board at j is assigned with the summation of the values of board at j and newIndex
                        board[j] = board[j] + board[newIndex];
                        board[newIndex] = 0; //The value of board at newIndex is then assigned with the value of zero 
                        score = board[j] + score;//The score is calculated by the summation of the value of board at j and the value of score 
                        break; //Exits do loop 
                    
                    }
                    
                    break;//Exits Row loop 
                
                }
               
               //If the nearest non zero number is not equal to board at j then n is increased by one in order to increase the range to the right of j     
               //and find the next nearest non zero number to the right  
               n = n + 1;
               
               //If newIndex is increased by one and is divisible by max then there cannot be any more index values 
               //to the right to be checked for combination thus ending the do loop 
               y = (newIndex + 1) % max;
               
               //If y is not equal to zero it means there are more index values to be checked to the right thus the do loop keeps on executing
               }while(y != 0);
            }
            
           //Moves to the next row value in the current column
           j = j + max - 1;
            
        }

    }
}

//Moves pieces to the left side of the board
//Max is equivalent to squaresPerSide but is set to a shorter variable name 
void rightMove(int board[], int max, int& score)
{
      
    
    //Loop over every column
   for(int i = 0; i < max; i++)
   {
        
       
        //Loop over every row value in given column   
        //combines row values in current column
        for(int j =  max - i - 1;j <= max * max - 1 - i; j++)
        {
            
            int newIndex = 0; //Sets newIndex to a value of zero
            int n = 1; //Assigns intger n to a value of one 
            int y = 0; //Assigns integer y to a value of zero
            
            //If the board value at index j is not equal to zero then the column will be checked for any 
            //same inter values 
            if(board[j] != 0)
            {
               //If index j is equal to 0 then the the column loop has reached its last iteration thus it will not check for any 
              //possible combinations
               if(j == 0)
               {
                   break;//Exits loop 
               }
               
               //This loop is designed to look for the nearest non zero number of an equal value to index j 
               //for a combination between the two 
               do
               {
                
                //The newIndex is decreased by n in order to find the nearest non zero value 
                //to the left of index j  
                newIndex = j - n;
                
                //If the value of board at newIndex is not equal to zero then it is the nearest non zero to left of index j   
                if(board[newIndex] != 0)
                {
                    //If the values of board at j and newIndex are equal then they are combined 
                    if(board[j] == board[newIndex])
                    {
                        //board at j is assigned with the summation of the values of board at j and newIndex
                        board[newIndex] = board[j] + board[newIndex]; 
                        board[j] = 0; //The value of board at newIndex is then assigned with the value of zero 
                        score = board[newIndex] + score; //The score is calculated by the summation of the value of board at j and the value of score  
                        break;//Exits do loop 
                    
                    }
                    
                    break;//Exits Row loop 
                
                }
               
                //If the nearest non zero number is not equal to board at j then n is increased by one in order to increase the range to the left of j     
               //and find the next nearest non zero number to the left 
               n = n + 1;
               
                //If newIndex is increased by one and is divisible by max then there cannot be any more index values 
               //to the left to be checked for combination thus ending the do loop 
               y = newIndex % max;
               
               //If y is not equal to zero it means there are more index values to be checked to the left thus the do loop keeps on executing
               }while(y != 0);
            }
            
            //Moves to the next row value in the current column
            j = j + max - 1;
            
        }
    
     //Loop over every row value in given column   
    //Moves values in current row and column    
    for(int j = max - i - 1; j <= max * max - 1 - i; j++)
        {
         
        
        int index = 0; //Sets the value of index to zero
        int k = 1; //Assigns integer variable k to one
        int w = 0; //Assigns integer variable w to zero 
        
        //Checks if the value of array board at index j is equal to zeo
        if(board[j] == 0)
            {
                //If the index j is equivalent to zero then the last column is skiped from being checked for possible moves 
               if(j == 0)
               {
                   break;
               }
            
            
            //If the index j is not equal to zero then the do loop is executed 
            //which checks for the nearest next non zero value in the current column 
               do
               {
                 //The value of variable index is assigned with the value of index j plus the current squares per side
                 //The sum is taken in order for the new index to be left of index j
                  index = j - k;
               
                  //If the board at the new index is not equal to zero then it is the nearest non zero number 
                  if(board[index] != 0)
                  {
                     //Index j and the new index and the board array are sent to the switch function in order for the values of board 
                     //at j and index to be swithched  
                     switching(board, j, index);
                     break;//Exits the loop

                  }
               
                //If the nearest next non zero is not found then k is increased by 1 which is added to index j
               //which sets the value of index to increase and be one step more to the left 
               k = k + 1;
               
               //If the current index plus one is divisible by the current squares per side then there cannot be any more index values 
               //to the left to be checked thus ending the loop                    
               w = index % max;  
               
               //If w is not equal to zero which means there are more index values to be checked to the left then the loop keeps on executing    
               }while(w != 0);
                
            }
        
           //Moves to the next row value in the current column
           j = j + max - 1; 
        }
    

    }
}
 
//Moves pieces to the bottom side of the board
//Max is equivalent to squaresPerSide but is set to a shorter variable name
void downMove(int board[], int max, int& score)
{

    //Loop over every column
   for(int i = 0; i < max; i++)
   {
        
       
        //Loop over every row value in given column   
        //combines row values in current column
        for(int j = max * max - max + i;j >= i; j--)
        {
            int newIndex = 0;//Sets newIndex to a value of zero
            int n = max; //Assigns intger n to a value of one 
            int g = max * max - max + i; //Assigns integer g to the final value of the column

            //If the board value at index j is not equal to zero and not equal to the starting index of the column 
            //then the column will be checked for any same inter values
            if(board[j] != 0 && j != i)
            {
               //This loop is designed to look for the nearest non zero number of an equal value to index j 
               //for a combination between the two 
               do
               {
                
                //The newIndex is decreased by n in order to find the nearest non zero value 
                //to the top of index j    
                newIndex = j - n;
                
                //If the value of board at newIndex is not equal to zero then it is the nearest non zero to the top of index j
                if(board[newIndex] != 0)
                {
                    
                    //If the values of board at j and newIndex are equal then they are combined
                     if(board[j] == board[newIndex])
                    {
                        //board at j is assigned with the summation of the values of board at j and newIndex
                        board[j] = board[j] + board[newIndex];
                        board[newIndex] = 0; //The value of board at newIndex is then assigned with the value of zero 
                        score = board[j] + score;//The score is calculated by the summation of the value of board at j and the value of score
                        break;//Exits do loop
                    
                    }
               
                break;//Exits Row loop 
                }
                 
               //If the nearest non zero number is not equal to board at j then n is increased by max in order to increase the range to the top of j     
               //and find the next nearest non zero number to the up direction 
               n = n + max;
                   
                //If newIndex is not equal to i it means there are more index values to be checked to the top thus the do loop keeps on executing    
               }while(newIndex != i);
            }
            
                //Moves to the next row value in the current column
                j = j - max + 1;             
        }
    
       
     //Loop over every row value in given column   
    //Moves values in current row and column     
    for(int j = max * max - max + i;j >= i; j--)
        {
            
        int index = 0; //Sets the value of index to zero
        int k = max; //Assigns integer variable k to max 
        int d = max * max - max + i; //Assigns integer variable d to the final value of the column
 
        //Checks if the value of array board at index j is equal to zeo and not equal to i 
        if(board[j] == 0 && j != i)
            {
            
            //If the index j is not equal to i then the do loop is executed 
            //which checks for the nearest next non zero value in the current column
               do
               {
                
                //The value of variable index is assigned with the value of index j plus the current squares per side
                //The sum is taken in order for the new index to be on the top of index j   
                index = j - k;
               
                //If the board at the new index is not equal to zero then it is the nearest non zero number 
                if(board[index] != 0 && board[d] == 0)
                {
                    
                     //Index j and varaible d and the board array are sent to the switch function in order for the values of board 
                     //at j and d to be swithched  
                     switching(board, d, index);

                        break;//Exits the loop
                  }
                  else if(board[index] != 0)
                  {
                     
                      //Index j and the new index and the board array are sent to the switch function in order for the values of board 
                      //at j and index to be swithched  
                      switching(board, j, index);
                      break;//Exits the loop

                  }
                   
               //If the nearest next non zero is not found then k is increased by max which is added to index j
               //which sets the value of index to increase and be one step more to the top      
               k = k + max;
               
                //If index is not equal to i, it means there are more index values to be checked to the top. Thus the loop keeps on executing
               }while(index != i);
                
            }
        
           //Moves to the next row value in the current column
           j = j - max + 1; 
        }
    

    }
    
    
}

//Moves pieces to the top side of the board
//Max is equivalent to squaresPerSide but is set to a shorter variable name
void upMove(int board[], int max, int& score)
{
     //Loop over every column
   for(int i = 0; i < max; i++)
   {
        
       
        //Loop over every row value in given column   
        //combines row values in current column 
        for(int j = i;j <= max * max - max + i; j++)
        {
            int newIndex = 0;//Sets newIndex to a value of zero
            int n = max; //Assigns intger n to a value of max 
            
            //If the board value at index j is not equal to zero and not equal to the starting index of the column 
            //then the column will be checked for any same inter values
            if(board[j] != 0 && j != i)
            {
               //This loop is designed to look for the nearest non zero number of an equal value to index j 
               //for a combination between the two 
               do
               {
                
                //The newIndex is decreased by n in order to find the nearest non zero value 
                //to the top of index j
                newIndex = j - n;
                
                //If the value of board at newIndex is not equal to zero then it is the nearest non zero to the top of index j
                if(board[newIndex] != 0)
                {
                    //If the values of board at j and newIndex are equal then they are combined
                    if(board[j] == board[newIndex])
                    {
                        //board at j is assigned with the summation of the values of board at j and newIndex
                        board[j] = board[j] + board[newIndex];
                        board[newIndex] = 0; //The value of board at newIndex is then assigned with the value of zero 
                        score = board[j] + score;//The score is calculated by the summation of the value of board at j and the value of score
                        break;//Exits do loop
                    
                    }
                    
                    break;//Exits Row loop
                
                }
                   
                //If the nearest non zero number is not equal to board at j then n is increased by max in order to increase the range to the top of j     
               //and find the next nearest non zero number to the up direction 
                  n = n + max;
                   
                //If newIndex is not equal to i it means there are more index values to be checked to the top thus the do loop keeps on executing       
               }while(newIndex != i);
            }
            
            //Moves to the next row value in the current column
            j = j + max - 1;
            
        }
    
    //Loop over every row value in given column   
    //Moves values in current row and column      
    for(int j = i;j <= max * max - max + i; j++)
        {
            
        int index = 0; //Sets the value of index to zero
        int k = max; //Assigns integer variable k to max
        int g = max * max - max + i; //Assigns integer variable g to the final value of the column
        
        //Checks if the value of array board at index j is equal to zeo and not equal to g 
        if(board[j] == 0 && j != g)
            {
            
            //If the index j is not equal to g then the do loop is executed 
            //which checks for the nearest next non zero value in the current column
               do
               {
                
                 //The value of variable index is assigned with the value of index j plus the current squares per side
                //The sum is taken in order for the new index to be on the bottom of index j 
                 index = j + k;
               
                //If the board at the new index is not equal to zero then it is the nearest non zero number 
                if(board[index] != 0 && board[i] == 0)
                {
                    
                     //Index j and varaible i and the board array are sent to the switch function in order for the values of board 
                     //at j and i to be swithched
                     switching(board, i, index);

                        break;//Exits the loop
                  }
                  else if(board[index] != 0)
                  {
                      //Index j and the new index and the board array are sent to the switch function in order for the values of board 
                      //at j and index to be swithched
                      switching(board, j, index);
                      break;//Exits the loop

                  }
                   
                //If the nearest next non zero is not found then k is increased by max which is added to index j
               //which sets the value of index to increase and be one step more to the bottom      
               k = k + max;
               
               //If index is not equal to g, it means there are more index values to be checked to the bottom. Thus the loop keeps on executing
               }while(index != g);
                
            }
            
            //Moves to the next row value in the current column
           j = j + max - 1; 
        }
    

    }
    
  
}

//Displays Game Board 
void displayAsciiBoard( int board[], int squaresPerSide, int score)
{
        //Displays the current score to the user
        std::cout << std::endl;
        std::cout << std::setw(15) << "Score: " <<  score << std::endl;
        std::cout << std::setw(9);
        
        //Loops through every single index in the board array 
        for( int i = 0; i < squaresPerSide * squaresPerSide; i++) 
        {
            
           //For every index value that is not zero and is divisible by the given squaresPerSide 
           //a new row is made 
           if(i != 0 && i%squaresPerSide == 0) 
           {
              std::cout << std::endl;

              std::cout << std::endl;
              std::cout << std::setw(9);

            }
           
           //If the value of board at index i is equal to zero then 
           //periods are displayed to show an empty spot on the board
           if( board[i] == 0) 
           {

               std::cout << ".";
               std::cout << std::setw(6);
            }
           //If the value of board at index i is not zero then the value of that position on the board is
           //displayed to the user 
           else 
           {

               std::cout << board[ i];
               std::cout << std::setw(6);

           }

       }    
          
}

// Place a randomly selected 2 or 4 into a random open square on
// the board.
void placeRandomPiece( int board[], int squaresPerSide)
{
    // Randomly choose a piece to be placed (2 or 4)
    int pieceToPlace = 2;
    if( rand()%2 == 1) {
        pieceToPlace = 4;
    }
    
    // Find an unoccupied square that currently has a 0
    int index;
    do {
        index = rand() % (squaresPerSide*squaresPerSide);
    }while( board[ index] != 0);
    
    // board at position index is blank, so place piece there
    board[ index] = pieceToPlace;
    


}//end placeRandomPiece()

//Initialiaze elements as zero values for a new game  
void elements(int board[], int squaresPerSide)
{
    //Loops through every index in the board
    for(int i = 0; i < squaresPerSide * squaresPerSide; i++)
    {
           //The board at index i is assigned with a value of zero 
           board[i] = 0;            
    }
    
    
}

//Checks for a full board at any point in the game 
int fullBoard(int board[], int max, int maxTileValue)
{
    //Sets indexValue to zero 
    int indexValue = 0;
    
    //Loops through every index value in the board 
    //Collum
    for(int i = 0; i < max; i++)
    {
        //Row
        for(int j = i;j <= max * max - max + i; j++)
        {
            //If board at j is not equal to 0 then varaible indexValue is increased by one 
            if( board[j] != 0) 
            {
                indexValue++;
                
            }
                   
            //Moves to the next row value in the current column
            j = j + max - 1;
            
        }

        
    }
        
    
    //Returns the value of indexValue to main 
    return indexValue;

}

//Checks if the user has reached a game over at any move 
int gameOver(int board[], int max, int maxTileValue)
{
    
    
    //Loops through every index value on the board 
    //Collum
    for(int i = 0; i < max; i++)
    {
        //Row
        for(int j = i;j <= max * max - max + i; j++)
        {
            
            //If board at j is equal to the maxTileValue then the user 
            //has won the game 
            if( board[j] == maxTileValue) 
            {
                //Informs user that they have won the game 
                std::cout << "Congratulations!  You made it to " << maxTileValue << " !!!" << std::endl;
                //The value of 1 is returned to main 
                return 1;
            }
             
            //Moves to the next row value in the current column
            j = j + max - 1;
            
        }

        
    }
    
     //Loops through every index value on the board 
    //Collum
    for(int i = 0; i < max; i++)
    {
        //Row
        for(int j = i;j <= max * max - max + i; j++)
        {
            //If board at j is equal to zero then the value of zero will be returned to main 
            if( board[j] == 0) 
            {
                return 0;
            }
              
            
            //Moves to the next row value in the current column
            j = j + max - 1;
            
        }

        
    }
    
    
    
}

//Makes a copy of the current board
void boardCopy(int previousBoard[], int board[], int max)
{
    
    //Loops through every index value on the board
    //Collum
    for(int i = 0; i < max; i++)
    {
        //Row
        for(int j = i;j <= max * max - max + i; j++)
        {
            
            //previousBoard at j is assigned with the value of board at j 
            //this will copy the values of board into previousBoard
            previousBoard[j] = board[j];
                  
            //Moves to the next row value in the current column
            j = j + max - 1;
            
        }

        
    }
}

//Checks if a user move resulted in a change in the board 
int boardChange(int previousBoard[], int board[], int max)
{
    
    //Loops through every index value on the board
    //Collum
    for(int i = 0; i < max; i++)
    {
        //Row
        for(int j = i;j <= max * max - max + i; j++)
        {
            //If there is a value at j in previousBoard that is not the same in board at j
            //then 1 is returned to main as an indication that the boards are not the same  
            if( previousBoard[j] != board[j]) 
            {
                return 1;
            }
              
            //Moves to the next row value in the current column
            j = j + max - 1;
            
        }

        
    }
    
    //If 1 is not sent to main then zero is sent to main as indication that 
    //the boards are the same  
    return 0;
}

//Function serves as way for the user to resize the board and restart the game 
//Max is equivalent to squaresPerSide but is set to a shorter variable name
void resetBoard(int board[], int& max, int& maxTileValue, int& score, int& move)
{
    //Informs the user that they are resetting the board 
    std::cout << "\n" << "Resetting board \n" << "\n";
                    
    
    //Asks user for their desired board size 
    std::cout << "Enter the size board you want, between 4 and 12: " << std::endl;
    //User input of squaresPerSide (max) 
    std::cin >> max;
    
    //The score is reset to a value of zero 
    score = 0; 
    //The move number is reset to a value of one 
    move = 1;
    
    //maxTileValue is reset to constant MaxTileStartValue in order to calculate the corresponsing 
    //maxTileValue to the users new squaresPerSide
    maxTileValue = MaxTileStartValue;   
    
    //For every iteration the maxTileValue is doubled, thus giving the maxTileValue of 
    //the chosen board size 
    for( int i=4; i< max; i++) 
    {
        maxTileValue = maxTileValue * 2;   
    }

    //Informs user the new maximum tile value to reach in order to win the game  
    std::cout << "Game ends when you reach " << maxTileValue << "." << std::endl;
    
    //Board is reset and every element in board is set to a value of zero 
    elements(board, max);
    
    //First two random elements are placed in the new board  
    placeRandomPiece( board, max);
    placeRandomPiece( board, max);
    
    
    
}


int main()
{	
	int move = 1;               // User move counter
	int score = 0;                    // Cummulative score, which is sum of combined tiles
    int squaresPerSide = 4;           // User will enter this value.  Set default to 4
	int board[ MaxBoardSize * MaxBoardSize];          // space for largest possible board
    int previousBoard[ MaxBoardSize * MaxBoardSize];  // space for copy of board, used to see 

//*********************************************************************************    
    
    //    if a move changed the board.
	// Create the graphical board, an array of Square objects set to be the max size it will ever be.
	Square squaresArray[ MaxBoardSize * MaxBoardSize]; 
    int maxTileValue = MaxTileStartValue;  // 1024 for 4x4 board, 2048 for 5x5, 4096 for 6x6, etc.
    char userInput = ' ';     // Stores user input
	char aString[ 81];        // C-string to hold concatenated output of character literals

	// Create the graphics window
	sf::RenderWindow window(sf::VideoMode(WindowXSize, WindowYSize), "Program 5: 1024");
	std::cout << std::endl;
    // Create and initialize the font, to be used in displaying text.
	sf::Font font;  
	initializeFont( font);
	// Create the messages label at the bottom of the graphics screen, for displaying debugging information
	sf::Text messagesLabel( "Welcome to 1024", font, 20);
	// Make a text object from the font
	messagesLabel.setColor( sf::Color(255,255,255));
	// Place text at the bottom of the window. Position offsets are x,y from 0,0 in upper-left of window
	messagesLabel.setPosition( 0, WindowYSize - messagesLabel.getCharacterSize() - 5); 

//-----------------------------------------------------------------------------------------------------------------    
    //Assigns pointer pHead as NULL 
    Node *pHead = NULL;
        
	displayInstructions();
    
    // Get the board size, create and initialize the board, and set the max tile value
    elements(board, squaresPerSide);
    placeRandomPiece( board, squaresPerSide);
    placeRandomPiece( board, squaresPerSide);
	
    
    
//-----------------------------------------------------------------------------------------------------------------    
      
    
        
	    for( int i=0; i < squaresPerSide * squaresPerSide; i++) {
		// Allocate each square individually.
		// Store a string in each square which contains its number, in order of creation
		char name[ 81];
		// Squares with a 0 value should not have a number displayed
		if( board[ i] == 0) {
			strcpy( name, "");   // "print" a blank text string
		}
		else {
		   sprintf( name, "%d", board[ i]);   // "print" the square creation order number into a string to be stored in the square
		}
		// Set each array pointer have the address of a new Square, created with a Square constructor
        squaresArray[ i] = Square(95, (70 * (i%4) + (i%4)*30), (i / 4) * 100, sf::Color::White, true, name);//<------------
		// Draw the square
		window.draw( squaresArray[ i].getTheSquare());
		// Draw the text associated with the Square, in the window with the indicated color and text size
		int red = 0, green = 0, blue = 0;
		squaresArray[i].displayText( &window, font, sf::Color(red, green, blue), 45);//<--------------------
	}
	// Display the background frame buffer, replacing the previous RenderWindow frame contents.
	// This is known as "double-buffering", where you first draw into a background frame, and then
	// replace the currently displayed frame with this background frame.
	window.display();  
        
//-----------------------------------------------------------------------------------------------------------------    
         
    // Declare a pointer for the head of the list.  Add a node onto the list.  
    //The list may grow and shrink, but this first node should always be there.
    //Stores the current board, move number, and score into a new node and makes pHead point to it as the head of the list
    //Appends a node to the beggining of the list 
    snapShot(move, score, board, pHead, squaresPerSide); 
	
	// Run the program as long as the window is open.  This is known as the "Event loop".
	while (window.isOpen())
	{
		// Display both the graphical and text boards.
        displayAsciiBoard( board, squaresPerSide, score);
//-----------------------------------------------------------------------------------------------------------------    
   
  
      // Redraw all screen components to the background frame buffer
		for( int i=0; i< squaresPerSide * squaresPerSide; i++) {
            // Blank out the text on the selected squaresArray
            //Converts the values in array board into string values 
            std::string sValues = std::to_string(board[i]);
            //If a value is not "0" then it will be displayed in color 
            if(sValues != "0")
            {
               squaresArray[ i].setText(sValues);   
            }
            //If else then it will not be displayed. This is to avoid displaying zeroes on the board 
            else
            {
               squaresArray[ i].setText(" ");      
            }

		
			// Draw the square
			window.draw( squaresArray[ i].getTheSquare());
			// Draw the text associated with the Square, in the window with the indicated color and text size
			int red = 0, green = 0, blue = 0;
            
			squaresArray[i].displayText( &window, font, sf::Color(red, green, blue), 45);//<------------
            
		}

		// Construct string to be displayed at bottom of screen
        sprintf( aString, "Move %d", move);  // Print into aString
		messagesLabel.setString( aString);            // Store the string into the messagesLabel
		window.draw( messagesLabel);                  // Display the messagesLabel
		
		// Display the background frame buffer, replacing the previous RenderWindow frame contents.
		// This is known as "double-buffering", where you first draw into a background frame, and then
		// replace the currently displayed frame with this background frame.
		window.display();  
        
         
//-----------------------------------------------------------------------------------------------------------------    
        
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::setw(14) << "List: ";
        
        //Displays to the user which node in the link list they are currently in. Essentially were pHead is pointing at. 
        //Loops a certain amount of times depending on the current move value stored in the node. 
        //i is also being reduced by one in order for the list to start at the largest value. 
        for(int i = pHead->moveNumber; i > 0; i--)
       {
           //If the value of pHead->moveNumber is equal to 1 then that means the board as just started and it is 
           //at only the first move. However if i is equal to one at any point then the for loop breaks in order to not put a "->" 
           //infront of a 1. 
           if(pHead->moveNumber == 1 || i == 1)
           {
               std::cout << i;
           }
           else
           {
               std::cout << i << "->";
           }
           
       }
        
        // Make a copy of the board.  After we then attempt a move, the copy will be used to 
        // verify that the board changed, which only then allows randomly placing an additional  
        // piece on the board and updating the move number.
        boardCopy(previousBoard, board, squaresPerSide);

        
        // Prompt for and handle user input
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::setw(1);
        std::cout << pHead->moveNumber << ". Your move: ";
        std::cin >> userInput;
        switch (userInput) {
            case 'x':
                    std::cout << "Thanks for playing. Exiting program... \n\n";
                    exit( 0);
                    break;
            case 'u'://Case for undoing a move made by the user 
                if(pHead->moveNumber == 1)//Prevents the user to undo a move if they are in the first move of the game 
                {
                 std::cout << " *** You cannot undo past the beginning of the game.  Please retry. ***" << std::endl;
                 continue;//Returns to the beginning of the loop 
                }
                else//If the user is not undoing a move in the first move then they are allowed to undo 
                {
                std::cout << std::setw(24) << "* Undoing Move *" << std::endl;
                undoDelete(pHead);//Deletes the current node of the current board and moves pHead to point to the previous node  
                undo(move, score, board, pHead, squaresPerSide);//Assigns the values of the previous board stored in the node to the current board 
                window.clear();//Clears Graphic board
                continue;//Returns to beginning of loop 
                }
                    break;
            case 'r': //If user input 'r' then they have decided to resize and reset the board 
                //Function resetBoard is called in order to resize and reset the board and assign new squaresPerSide and maxTileValue
                resetBoard(board, squaresPerSide, maxTileValue, score, move);
                continue;//Will start from the beggining of the loop and display the brand new board  
                break;
           case 'w':
                upMove(board, squaresPerSide, score);
                break;
            case 's':
                downMove(board, squaresPerSide, score);
                break;
            case 'a':
                leftMove(board, squaresPerSide, score);
                break;
            case 'd':
                rightMove(board, squaresPerSide, score);
                break;    
            case 'p':
                    //If the user inputs 'p' then they have chosen to input a value into an index on the board 
                    int userIndex; //Chosen user index 
                    int userValue; //Chosen user value 
                    
                    //User input is stored 
                    std::cin >> userIndex >> userValue;
                    
                    //board at userIndex is assigned the value of userValue
                    board[userIndex] = userValue;
                    continue;
                    //Goes back to the beggining of the loop
            default:
                    std::cout << "Invalid input, please retry.";
                    continue;
                    break;
        }//end switch( userInput)
        
        // If the move resulted in pieces changing position, then it was a valid move
        // so place a new random piece (2 or 4) in a random open square and update move number.
        int changeValue = boardChange(previousBoard, board, squaresPerSide);
        
        if(changeValue == 1)
        {
                        
            placeRandomPiece( board, squaresPerSide);
            move++;
        } 
        
        // Add the new board, moveNumber and score to a new list node at the front of the list.
        //If the board changes then all the values in the board will be stored into a new node(append a node) 
        if(changeValue == 1)
        {
            //Appends a node to the beggining of the list 
            snapShot(move, score, board, pHead, squaresPerSide);
             
        } 
        
		// See if we're done
		int endValue = gameOver(board, squaresPerSide, maxTileValue);
        
        if(endValue == 1)
        {
            displayAsciiBoard( board, squaresPerSide, score);//Display the final board 
            break;
            
        }
        
        //fullValue is assigned with the return value of the function fullBoard
        int fullValue = fullBoard(board, squaresPerSide, maxTileValue);
        
        //If the value of fullValue is equal to the total of squaresPerSide * squaresPerSide then the board is full and 
        //there are no more possible moves to be made 
        if(fullValue == squaresPerSide * squaresPerSide)
        {
              std::cout << "\n" << "No more available moves.  Game is over.\n" << "\n";
              displayAsciiBoard( board, squaresPerSide, score);//Display the final board 
              break;
        }

		//system("clear");   // Clear the screen 
        window.clear();
        
		// Pause the event loop, so that Codio does not think it is a runaway process and kill it after some time
		std::this_thread::sleep_for(std::chrono::milliseconds( 50));

	}//end while( window.isOpen())

	return 0;
}//end main()
