//  prog5_1024.cpp
//     Text version of the game 1024, a variant of 2048 available online at:
//        http://gabrielecirulli.github.io/2048/
//     Object of game is to combine number tiles with the same value, accumulating
//     points as the game progresses, to try and create the tile with the value 1024.
//     Each move consists of sliding pieces to the left, up, right or down.
/*  Running program looks like:
 
     Manuel M Martinez
     UIC CS 141, Spring 2019
     Welcome to 1024.
     This program is based off of Gabriele Cirulli's game online at
     bit.ly/great2048
 
     For each move enter a direction as a letter key, as follows:
         W
       A S D
     where A=left,W=up, D=right and S=down.
 
     After a move, when two identical valued tiles come together they
     join to become a new single tile with the value of the sum of the
     two originals. This value gets added to the score.  On each move
     one new randomly chosen value of 2 or 4 is placed in a random open
     square.  User input of x exits the game.
 
     Game ends when you reach 1024.
 
     Score: 0
	 .     4     .     .

	 .     .     .     .

	 .     .     4     .

	 .     .     .     .
 
     1. Your move: a
 
     Score: 0
	 4     .     .     .

	 .     .     .     .

	 4     .     .     .

	 .     .     2     .
 
     2. Your move: a
     .
     .
     .
*/
/***
 * Mallavarapu:
 * 1) the header with the student information is missing
 * 2) Inconsistent blank spaces.
 * 3) use meaningful varaible names rather than i,j,k.
 * ***/
#include <iostream>     // For cin, cout, endl
#include <iomanip>      // used for setting output field size using setw
#include <cstdlib>      // For rand()
using namespace std;    // So we don't need std:: in front of every cin, cout, and endl

const int MaxBoardSize = 12;          // Max number of squares per side
const int MaxTileStartValue = 1024;   // Max tile value to start out on a 4x4 board


//--------------------------------------------------------------------
// Display Instructions
void displayInstructions()
{
    cout << "Welcome to 1024. \n"
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
    cout << "Game ends when you reach " << MaxTileStartValue << "." << endl;
}//end displayInstructions()

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
        cout << endl;
        cout << "Score: " << score << endl;
        cout << setw(9);
        
        //Loops through every single index in the board array 
        for( int i = 0; i < squaresPerSide * squaresPerSide; i++) 
        {
            
           //For every index value that is not zero and is divisible by the given squaresPerSide 
           //a new row is made 
           if(i != 0 && i%squaresPerSide == 0) 
           {
              cout << endl;

              cout << endl;
              cout << setw(9);

            }
           
           //If the value of board at index i is equal to zero then 
           //periods are displayed to show an empty spot on the board
           if( board[i] == 0) 
           {

               cout << ".";
               cout << setw(6);
            }
           //If the value of board at index i is not zero then the value of that position on the board is
           //displayed to the user 
           else 
           {

              cout << board[ i];
               cout << setw(6);

           }

       }    
          
}
//--------------------------------------------------------------------
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
                cout << "Congratulations!  You made it to " << maxTileValue << " !!!" << endl;
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
    cout << "\n" << "Resetting board \n" << "\n";
                    
    
    //Asks user for their desired board size 
    cout << "Enter the size board you want, between 4 and 12: " << endl;
    //User input of squaresPerSide (max) 
    cin >> max;
    
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
    cout << "Game ends when you reach " << maxTileValue << "." << endl;
    
    //Board is reset and every element in board is set to a value of zero 
    elements(board, max);
    
    //First two random elements are placed in the new board  
    placeRandomPiece( board, max);
    placeRandomPiece( board, max);
    
    
    
}


//---------------------------------------------------------------------------------------
int main()
{
    int score = 0;
    int squaresPerSide = 4;        // User will enter this value.  Set default to 4
    int board[MaxBoardSize * MaxBoardSize];          // space for largest possible board
    int previousBoard[ MaxBoardSize * MaxBoardSize];  // space for copy of board, used to see
                                                      //    if a move changed the board.
    int maxTileValue = MaxTileStartValue;  // 1024 for 4x4 board, 2048 for 5x5, 4096 for 6x6, etc.
    char userInput = ' ';                  // handles user input
    int move = 1;                          // user move counter
    
   
    displayInstructions();
    
    // Get the board size, create and initialize the board, and set the max tile value depending on board size
    elements(board, squaresPerSide);
    placeRandomPiece( board, squaresPerSide);
    placeRandomPiece( board, squaresPerSide);

    
    // Infinite loop to run program until user selects exit, board is full, or max tile value is reached
    while( true)
    {
        // Display the text-based board
        displayAsciiBoard( board, squaresPerSide, score);
        
        // Make a copy of the board.  After we then attempt a move, the copy will be used to
        // verify that the board changed, which only then allows randomly placing an additional
        // piece on the board and updating the move number.
        boardCopy(previousBoard, board, squaresPerSide);
        
        // Prompt for and handle user input
        cout << endl;
        cout << endl;
        cout << setw(1);
        cout << move << ". Your move: ";
        cin >> userInput;
        
        switch (userInput) {
            case 'x':
                    cout << endl;
                    cout << "Thanks for playing. Exiting program... \n\n";
                    exit( 0);
                    break;
            case 'r': //If user input 'r' then they have decided to resize and reset the board 
                //Function resetBoard is called in order to resize and reset the board and assign new squaresPerSide and maxTileValue
                resetBoard(board, squaresPerSide, maxTileValue, score, move);
                continue;//Will start from the beggining of the loop and display the brand new board  
                break;
                //***************
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
                    cin >> userIndex >> userValue;
                    
                    //board at userIndex is assigned the value of userValue
                    board[userIndex] = userValue;
                    continue;
                    //Goes back to the beggining of the loop 
            default:
                    cout << "Invalid input, please retry.";
                    continue;
                    break;
        }//end switch( userInput)
        
        // If the move resulted in pieces changing position, then it was a valid move
        // so place a new random piece (2 or 4) in a random open square and update the move number.
        // ...
        //changeValue is assigned with the return value of the function boardChange
        int changeValue = boardChange(previousBoard, board, squaresPerSide);
        
        //If the value of changeValue is equal to 1 then the board has changed and it will progress to the next move
        //with a random piece placed on the board 
        if(changeValue == 1)
        {
            placeRandomPiece( board, squaresPerSide);
            move++;
        }   
        
        //endValue is assigned with the return value of the function gameOver
        int endValue = gameOver(board, squaresPerSide, maxTileValue);
        
        //If the value of endValue is equal to 1 then the value of maxTileValue has been reached thus
        //the user has reached the end game and the game will end and display the final board 
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
              cout << "\n" << "No more available moves.  Game is over.\n" << "\n";
              displayAsciiBoard( board, squaresPerSide, score);//Display the final board 
              break;
        }
        
        
        
        //system("clear");   // Clear the screen in UNIX / Codio.  Should be "cls" on windows.
                             //     May not work in default Mac Xcode configuration, or some other environments.
    }//end while( true)

    return 0;
}//end main()
