/* ------------------------------------------------
   prog1RockPaperScissors.cpp
 
   Program #1: Play the game of Paper / Rock / Scissors against the computer.
   Class: CS 141
   Author: *** PUT YOUR NAME HERE ***  // *** Abhinav: Header information should include your name as author
	 
	 See the program description page on the course web site at bit.ly/cs141
	 Within Codio you can run the solution by doing the following steps:
   1. Select the Tools / Terminal menu option
	 2. Within the terminal window, type in:  ./solution

   Grading Rubric:
		 55 Execution points
						  Option 1: (Computer always chooses R) and:
					 2		 User input of X immediately exits program
					 3		 User input of x (lower case) immediately exits program
				  10		 Program handles both lower and upper case user input (e.g. 'r' and 'R'); also
					          move number increments each move
				  15		 Score updates correctly for all user inputs: r, p, s
						  Option 2: Computer's move is random and:
					 7		 Predetermined input sequence correctly leads to computer win
				   8		 Predetermined input sequence correctly leads to human win
		         Option 3: 
           2     Correctly displays and updates the graphical score
		       8     Correctly displays and updates the graphical score, with assessment results hidden

		 45 Programming Style (Given only if program runs substantially correctly)
					10 Meaningful identifier names
					10 Comments: Has header.  Comments on each block of code.
					15 Appropriate data and control structures.  Code duplication is avoided.
					10 Code Layout: Appropriate indentation and blank lines.
 
   Having sample program output is not required within this header of your program, though it is helpful.
	 
	 
*/

#include <iostream>    
#include <cstdlib>     
#include <string>

using namespace std;

int main()
{
    
    cout << "CS 141 Program #1: Rock/Paper/Scissors                                \n"
         << endl
         << "Welcome to the game of Rock/Paper/Scissors where you play against     \n"
         << "the computer.  On each move the computer will choose R, P, or S, then \n"
         << "the user will be prompted for their choice, and then the score will   \n"
         << "be updated.  P beats R, R beats S, and S beats P. The score starts    \n"
         << "at 0.  Add one if the person wins, subtract one if the computer wins. \n"
         << "The game ends if the score reaches -5 or + 5.                         \n"
         << "User input of 'x' or 'X' causes the game to exit.                     \n"
         << endl
         << "Here we go!  \n"
         << endl;
    
    
    //Default starting score lenght is stored into a string 
    string line = ".................";
    //The character '^' is stored into a char variable which is used to point to the score value on the number line  
    char pointer = '^';
    
    //The number line used in the graphical score is stored into a string variable
    string nGraphics = " -5 -4 -3 -2 -1  0  1  2  3  4  5";
    //Line used below the number line is stored in string variable
    string lGraphics = "----------------------------------";
  
    //Stores the users selection in an int variable of how the computer chooses its move 
    int computerChoiceVersion; 
    //Stores the computers choice of move which could be 'R', 'P', and 'S' 
    char computerChoice;
    //Used for displaying what move number the user is currently on
    int x = 1;  // *** Abhinav: Use more meaningful variable names
    //Stores the users choice of move which could be 'R', 'P', and 'S' or thier lowercase counterparts
    char userMove; 
    //Stores the points of the game and increases or decresses based on a user or computer win 
    int pScore = 0;
    
    //Menu is displayed asking the user to select how the computer chooses its move based on 3 options
    cout << "Select how the computer chooses its move: \n"
         << "1. Always choose Rock \n"
         << "2. Random guess \n"
         << "3. Random guess with graphical score \n"
         << "Enter your choice: ";
    //Users choice is stored into variable computerChoiceVersion
    cin >> computerChoiceVersion;
    cout << endl;//Used for indentation

   //The characters for each move the computer can choose are stored on a characted array  
    char element[3] = {'R', 'P', 'S'};
   
   //If the user picks option one from the menu the if branch will execute  
   if(computerChoiceVersion == 1)
   {
     //The variable computerChoice is assigned a character value of 'R'  
     computerChoice = element[0];//The character value is given by the array with an index of zero
   
   }
     cout << endl;//Used for new line 
    
  //This is the main loop of the program
  //The while loop checks for the score of the player and terminates whenever it has a score of 5 or -5  
  while(pScore < 5 && pScore > -5)
   {
        
        //If the user chooses option 2 or 3 the variable computerChoice is assigned with a random move 
        //that could vary between 'R', 'P', or 'S' 
        if(computerChoiceVersion == 2 || computerChoiceVersion == 3)
        {
        
        //A random number is generated and is stored into an integer variable 
        int randomNumber = rand();
        //The random number is then limited to only 3 different numbers which would be 0, 1, or 2
        int machineNumber = randomNumber % 3;
        
        //The new random number is then used as the index for the array that holds the 
        //three different move types. Therefore a the computer appears to choose a random move   
        computerChoice = element[machineNumber];
            
        }  // *** Abhinav: Use consistent indents
        
        //Asks the user to input their prefered move 
        cout << x << ". " << "Your move: ";//The x variable changes depending on what round the user is in 
        
        //The user input is assigned as a char variable named userMove 
        cin >> userMove;
        
        //This if statement is used to terminate the loop if the user inputs either 'X' or 'x' when asked for their move 
        if(userMove == 'X' || userMove == 'x')
        {
            //Informs the user that the program is being exited 
            cout << "Exiting program..." << endl;
          
            //The break statement terminates the while loop 
            break;
        }
        
        cout << endl;//Used for identation 
        
        //Once the user chooses their move it is then shown what the computer chosed as a move 
        //which is determined by the users choice at the menu selection
        cout << "   Computer chose " << computerChoice << endl;
        
      //This if statement checks for a tie between the user and the computer.
      //Since the computer can only choose upper case letters then the first condition is
      //when both choose upercase letters. The second condition is when the user chooses a lowercase letter 
      //which is always going to be 32 places greater than its uppercase in the ascii table. 
      //Thus 32 is added to the computers choice to make it lowercase thus checking if their the same characters   
      if(computerChoice == userMove || userMove == computerChoice + 32)
        {
            //The message of a tie will only appear if the user chooses options 1 or 2 as option 3 does not display a tie message 
            if(computerChoiceVersion == 2 || computerChoiceVersion == 1)
            {
            
             //Informs the user of a tie and the score 
             cout << "Tie. " << "Score: " << pScore << endl;
           
            }
            
            //The game round is incremented by one 
            x++;
            cout << endl;//Used for a new line 
            
            //The continue statement prevents the loop to continue further and instead returns to the beginning of the 
            //loop and checks for the loop condition to be true 
            continue;
            
        }
        
        //This small section of the code assigns any lowercase moves made by the player to be 
        //assigned with their uppercase counterpart. This is too simplify the code when comparing moves between the user and computer 
        if(userMove == 'r')
        {
           userMove = 'R';
        }
        else if(userMove == 'p')
        {
           userMove = 'P';
        }
        else if(userMove == 's')
        {
           userMove = 'S';
        }
               
       //This condition checks for a win condition in which the user picks a winning move 
        if(computerChoice == 'R' && userMove == 'P')
        {
           
           //User Score is automotically incremented by one due to a user win  
           ++pScore;
          
          //The user is informed that they won the round/point and the overall score of the game is shown 
          //This is only shown if the user picked option one or two in the starting menu  
          if(computerChoiceVersion == 2 || computerChoiceVersion == 1)
            {
            cout << "   User's point. " << "Score: " << pScore << endl;
            }
          
          //If the user picked option 3 it displays a graphical score  
          else if(computerChoiceVersion == 3)
            {
                cout << "   User's point. " << endl;//Informs the user that they won a point 
            
                //Becuase the user won the string line is incremented by .append which 
                //adds  "..." to the oveall lenght of the string. This is in order to push the pointer to the right score. 
                line = line.append("...");
                cout << nGraphics << endl;//Displays number line 
                cout << lGraphics << endl;//Displays dash line 
                //Displays a dotted line with pointer that indicates the overall score of the game  
                cout << line << pointer <<endl;
            }
            
            x++; //The game round is incremented by one 
            cout << endl;//Used for a new line
          
            //The continue statement prevents the loop to continue further and instead returns to the beginning of the 
            //loop and checks for the loop condition to be true 
            continue;
           }
         
        //This condition checks for a win condition in which the computer picks a winning move
        else if(computerChoice == 'R' && userMove == 'S')
        {
           //User Score is automotically decreased by one due to a computer win  
           --pScore;
           
           //The user is informed that the computer won the round/point and the overall score of the game is shown 
           //This is only shown if the user picked option one or two in the starting menu 
           if(computerChoiceVersion == 2 || computerChoiceVersion == 1)
            {
            cout << "   Computer's point. " << "Score: " << pScore << endl;
            }
            
           //If the user picked option 3 it displays a graphical score
           else if(computerChoiceVersion == 3)
            {
                cout << "   Computer's point. " << endl;//Informs the user that the computer won a point 
             
                //Since the computer won a round the string line is reduced in size. This is done by .substr which
                //takes the current size of the string with .size and subtracts it by 3 thus moving back the pointer
                line = line.substr(0, line.size() - 3);
                cout << nGraphics << endl;//Displays number line 
                cout << lGraphics << endl;//Displays dash line 
                //Displays a dotted line with pointer that indicates the overall score of the game 
                cout << line << pointer <<endl;
            }
          
            x++; //The game round is incremented by one 
            cout << endl;//Used for a new line
          
            //The continue statement prevents the loop to continue further and instead returns to the beginning of the 
            //loop and checks for the loop condition to be true 
            continue;
        }
    
        //This condition checks for a win condition in which the user picks a winning move 
        else if(computerChoice == 'P' && userMove == 'S')
        {
           //User Score is automotically incremented by one due to a user win  
           ++pScore;
          
          //The user is informed that they won the round/point and the overall score of the game is shown 
          //This is only shown if the user picked option one or two in the starting menu  
          if(computerChoiceVersion == 2 || computerChoiceVersion == 1)
            {
            cout << "   User's point. " << "Score: " << pScore << endl;
            }
          
          //If the user picked option 3 it displays a graphical score  
          else if(computerChoiceVersion == 3)
            {
                cout << "   User's point. " << endl;//Informs the user that they won a point
            
                //Becuase the user won the string line is incremented by .append which 
                //adds  "..." to the oveall lenght of the string. This is in order to push the pointer to the right score. 
                line = line.append("...");
                cout << nGraphics << endl;//Displays number line 
                cout << lGraphics << endl;//Displays dash line 
                //Displays a dotted line with pointer that indicates the overall score of the game  
                cout << line << pointer <<endl;
            }
            
            x++; //The game round is incremented by one 
            cout << endl;//Used for a new line
          
            //The continue statement prevents the loop to continue further and instead returns to the beginning of the 
            //loop and checks for the loop condition to be true 
            continue;
        }
    
        //This condition checks for a win condition in which the computer picks a winning move
        else if(computerChoice == 'P' && userMove == 'R')
        {
           //User Score is automotically decreased by one due to a computer win  
           --pScore;
           
          //The user is informed that the computer won the round/point and the overall score of the game is shown 
          //This is only shown if the user picked option one or two in the starting menu 
           if(computerChoiceVersion == 2 || computerChoiceVersion == 1)
            {
            cout << "   Computer's point. " << "Score: " << pScore << endl;
            }
            
            //If the user picked option 3 it displays a graphical score
           else if(computerChoiceVersion == 3)
            {
                cout << "   Computer's point. " << endl;//Informs the user that the computer won a point
             
                //Since the computer won a round the string line is reduced in size. This is done by .substr which
                //takes the current size of the string with .size and subtracts it by 3 thus moving back the pointer
                line = line.substr(0, line.size() - 3);
                cout << nGraphics << endl;//Displays number line 
                cout << lGraphics << endl;//Displays dash line 
                //Displays a dotted line with pointer that indicates the overall score of the game 
                cout << line << pointer <<endl;
            }
          
            x++; //The game round is incremented by one 
            cout << endl;//Used for a new line
          
            //The continue statement prevents the loop to continue further and instead returns to the beginning of the 
            //loop and checks for the loop condition to be true 
            continue;
        } 
    
        //This condition checks for a win condition in which the user picks a winning move 
        else if(computerChoice == 'S' && userMove == 'R')
        {
           
           //User Score is automotically incremented by one due to a user win  
           ++pScore;
          
          //The user is informed that they won the round/point and the overall score of the game is shown 
          //This is only shown if the user picked option one or two in the starting menu  
          if(computerChoiceVersion == 2 || computerChoiceVersion == 1)
            {
            cout << "   User's point. " << "Score: " << pScore << endl;
            }
          
          //If the user picked option 3 it displays a graphical score  
          else if(computerChoiceVersion == 3)
            {
                cout << "   User's point. " << endl;//Informs the user that they won a point 
            
                //Becuase the user won the string line is incremented by .append which 
                //adds  "..." to the oveall lenght of the string. This is in order to push the pointer to the right score. 
                line = line.append("...");
                cout << nGraphics << endl;//Displays number line 
                cout << lGraphics << endl;//Displays dash line 
                //Displays a dotted line with pointer that indicates the overall score of the game  
                cout << line << pointer <<endl;
            }
            
            x++; //The game round is incremented by one 
            cout << endl;//Used for a new line
          
            //The continue statement prevents the loop to continue further and instead returns to the beginning of the 
            //loop and checks for the loop condition to be true 
            continue;
           }
    
        //This condition checks for a win condition in which the computer picks a winning move
        else if(computerChoice == 'S' && userMove == 'P')
        {
           //User Score is automotically decreased by one due to a computer win  
           --pScore;
           
          //The user is informed that the computer won the round/point and the overall score of the game is shown 
          //This is only shown if the user picked option one or two in the starting menu 
           if(computerChoiceVersion == 2 || computerChoiceVersion == 1)
            {
            cout << "   Computer's point. " << "Score: " << pScore << endl;
            }
            
            //If the user picked option 3 it displays a graphical score
           else if(computerChoiceVersion == 3)
            {
                cout << "   Computer's point. " << endl;//Informs the user that the computer won a point 
             
                //Since the computer won a round the string line is reduced in size. This is done by .substr which
                //takes the current size of the string with .size and subtracts it by 3 thus moving back the pointer
                line = line.substr(0, line.size() - 3);
                cout << nGraphics << endl;//Displays number line 
                cout << lGraphics << endl;//Displays dash line 
                //Displays a dotted line with pointer that indicates the overall score of the game 
                cout << line << pointer <<endl;
            }  
          
            x++; //The game round is incremented by one 
            cout << endl;//Used for a new line
          
            //The continue statement prevents the loop to continue further and instead returns to the beginning of the 
            //loop and checks for the loop condition to be true 
            continue;
        } 
        
   } 
     
    //This section checks for the winner of the game by checking if the score is below or above zero
    //If the score is equal to zero then the game is tied and the user is informed
     if(pScore == 0)
     {
         cout << "Tie game!" << endl;
     }
  
     //If the score is below 0 then the computer wins and the user is informed
     else if(pScore < 0)
     {
         cout << "Computer wins!" << endl;
     }
  
     //If the score is greater than zero then the user wins and the user is informed 
     else if(pScore > 0)
     {
         cout << "User wins!" << endl;
     }
     
     cout << endl;//Used for new space
     
     cout << "Ending program..." << endl;//Tells the user the program is terminating 
    
  return 0; 
  
}//end main()