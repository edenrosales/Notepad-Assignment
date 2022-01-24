#include "Notepad.h"
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <cstring> 
#include <iomanip>
#include <time.h>
using namespace std;
string outName = "C:/Users/eden/source/repos/Module 5 Assignment/input.txt";//standard input file location
string saveName = "C:/Users/eden/source/repos/Module 5 Assignment/output.txt";//standard output file location 
void Notepad::start()
{
	int screenColor = 15;	//variable that sets the screen color 
	srand(time(NULL));		//initialization for random number generator 
	int random = 0;			//variable for random numbers 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), screenColor);	//sets the screen color for the first iteration (run only once)
	system("cls");			//clears screen from past methods 
	int downArrow=0;		//counter for how many lines ive created in the Notepad (useful for dwnArrow)
	
	List rows[20];			//initializes the amount of rows in the editor (20, cannot be changed)
	int xMod = 0;	//variable to modify the x position without having to change a lot of code
	int yMod = -3;	//variable to modify the y position without having to chnage a lot of code
	int z = 0;		//variable for which row is being edited (used in rows[z] array)
	int x = 10 + xMod;		//standard, starting x position
	int y = 10 + yMod;		//standard, starting y position 
	int xloc = 10 +xMod;	//x location for printing 
	int yloc = 10 + yMod;	//y location for printing
	char ch = NULL;			//variable for user input throughout the main interface 
	printingBorders();		//prints the borders for the first iteraton 
	gotoxy(xloc, yloc);		//setting cursor location inside the borders
	while (1) {
		if (_kbhit()) {		//looking for user input 
			ch = _getch();	//grabbing user input 
			if (ch == 27) { //when user presses escape key, they will be instructed to either press escape again to exit program, or press any other key to continue 
				gotoxy(73, 28);		//setting location to print message (bottom right of screen)
				random = (rand() % 10) + 1;	//random number generator (from 1-10)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), random);	//sets color to random color (just for the following printed text)
				cout << "Press esc key again to end the program";					//instructions printed after escape is pressed
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), screenColor); //sets color to screenColor (after the instructions for this section have been printed)
				char exitProgram = NULL; //variable for user input 
				exitProgram = _getch();	//grabbing user input
				if (exitProgram == 27) {	//when escape is pressed here, will exit the program
					break;
				}

			}
			else if (ch == 13) { //enter key will move to the next line in the Notepad if it exists. When pressed, will move the cursor to the start of the next line 
				if (y < 29+yMod) {
					downArrow++;	//sets how many lines of text were initialized (for use with the down arrow)
					z++;
					x = 10 + xMod;
					y++;
					gotoxy(x, y);
					rows[z].setCurr();
				}
			}
			else if (ch == 8) { //backspace will delete the node (character) that is currently being pointed to
								//special cases are accounted for. if the node that is being pointed to is NULL (the start of a line), does nothing.
				if (rows[z].atBeginning()) { //takes care of the case where curr is pointing to NULL 
					gotoxy(x, y); 
				}
				else {			//if the character passes the first if statement, we know that it is pointing to a valid Node 
					rows[z].deleteIndex();	//deletes the node 
					system("cls");			//updates the screen by clearing it and reprinting it to visually show the Node has been deleted 
					x--;					//decrements the variable for the cursor (horizonal movement)
					printingBorders();		
					for (int w = 0; w <= 19; w++) {
						gotoxy(xloc,yloc + w);	//sets the location for printing the text 
						rows[w].DisplayRows();	//prints the text
						cout << endl;
					}
					gotoxy(x, y);	//sets the cursor location 
				}
			}
			else if (ch == -32) { //Arrow keys: UP, DOWN, LEFT, AND RIGHT keys have been coded in
				char c = NULL;		//variable for user input 
				c = _getch();		//collects user input 
				if (c == 72) {	//arrow key UP
								//if a line exists above the cursor, will move it up 
								//will set it to the start of the above line of text
					if (z > 0) {	//tests that there is a line of text above 
						z--;	//changes the line of text to be one higher
						y--;	//updates cursor variable (sets to be one line of text higher) 
						x = 10 + xMod;	//updates cursor variable (setting to start of the line of text)
						gotoxy(x, y);	//moves cusor
						rows[z].setCurr();	//moves the curr Node to point to NULL (start of the line of text)
					}
				}
				if (c == 80) { //arrow key DOWN 
							   //will check if a line of text has been created below the cusor, if so, will move to the start of the line below the cursor 
							   //**NOTE** lines of text cannot be un-created, after they have been visited, the down arrow can move there **NOTE**
					if (y < downArrow+ 10 + yMod) { //tests to see if the next line of text has been created 
						z++;						//moves the line of text 
						y++;						//changes variable for the cursor (moves down) 
						x = 10 + xMod;				//changes the variable for the cursor (moves to the start of the line of text)
						gotoxy(x, y);				//sets the cursor (start of the next line of text downward)
						rows[z].setCurr();			//sets curr Node to point to NULL (start of the line of text)
					}
				}
				if (c == 75)//arrow key LEFT 
							//if there is a character to the left of the current character, will move to the next character
							//will move to NULL, which is the value right before the first character (the start of the line of text) 
				{
					if (rows[z].inBoundsLeft()) {	//checks bounds to the left of the current Node
						rows[z].moveLeft();			//sets curr to the next Node to the left 
						x--;						//changes variable for the cursor (to the left) 
						gotoxy(x, y);				//sets the cusor (one to the left of the prevoius location)
					}
					else {}
				}
				else if (c == 77) { //arrow key RIGHT 
									//will check the bounds to the right of the cursor, if it is open, will move to the next node to the right
									//also moves the cursor there. If curr is pointing to NULL, will still move to the right 
					if (rows[z].inBoundsNULL() && !rows[z].IsEmpty()) {	//checks if curr is pointing to NULL 
						rows[z].currAtNull();	//moves curr to the right
						x++;					//changes variable for the cursor (to the right)
						gotoxy(x, y);			//sets the cursor (one to the right of the previous locaton)
					}
					else if ((!rows[z].IsEmpty()) && (rows[z].inBoundsRight())) {//checks if a Node exists to the left of curr
						rows[z].moveRight();	//moves the Node to the right 
						x++;					//changes the variable for the cursor (to the right)
						gotoxy(x, y);			//sets the cursor (one to the right of the previous location) 
					}
					else {}
				}
			}
			else if (ch == 0) { //FUNCTION KEYS: f1, f2, and f3 are coded 
				char d = NULL;	//initializes variable for user input 
				d = _getch();	//grabs user input 

				if (d == 60) { //F2 
					for (int w = 0; w <= 19; w++) {	//THIS IS THE SAVE FUNCTION 
													//when f2 is pressed, it will save to either the default pathway (which is custom for Eden's pc only. or a custom one
													//that was entered at the beginning of the program
						rows[w].copyListToOutput(saveName);	//function copies the text to the output file (saving it)
					}	
					//will send a messgae to the bottom right of screen notifiyng the user that the text has been saved. will print in a random color between 10 values 
					gotoxy(75, 28);					//sets cursor location 
					random = (rand() % 10) + 1;		// creates random number for setting color 
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), random);	//sets color to a random color 
					cout << "Saved!";													//prints the notificatoin 
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), screenColor);	//resets the screen color to the screenColor variable that can be customized 
					Sleep(250);	//sleeps the program for a brief amount of time so the notificatoin can be seen 
					//clears screen and reprints all the text 
					system("cls");	//clears the screen
					printingBorders();	//reprints the border 
					for (int w = 0; w <= 19; w++) {	//loop prints out the text onto the screen 
						gotoxy(xloc, yloc + w);
						rows[w].DisplayRows();
						cout << endl;
					}
					
				}
				if (d == 61) { //F3
							   //is the function to open a file into the NotePad. will add the file wherever the cursor is, and will continue to add the text
								//even if the document being opened in the Notepad exceedes the amount of lines that the Notepad allows, it will continue to enter the text without the 
								//new lines, and it will just add it all onto the same line at 20
					char c;		//variable for user input 
					ifstream file(outName);	//opens the file that will be opened into the Notepad 
					while (file.get(c)) {	//while loop will run while values are being returned from the get() function, until there are no more values to be read in the file 
						gotoxy(75, 28);		//sets cursor location to bottom right of screen  
						random = (rand() % 10) + 1; //get a random number (between 1 and 10) 
						
						//will change the color to a random color between 1 and 10, prints the notification that the file is being imported, then changes the color back to screenColor 
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), random);
						cout << "Importing file...";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), screenColor);
						if (c == '\n') { //checks if the character read is Enter, which is equivalent to \n in the text file, if so, it will act like enter does when normally pressed 
							if (y < 29 + yMod) {//makes sure that enter wont sent the code to a line that does not exist, stops it if it tries to 
								z++;			//increments variable to the next line of text 
								x = 10 +xMod;	//changes variable of x coordinate to point to the start of the line 
								y++;			//increments the variable for the y value of cursor to be one lower than it was before
								gotoxy(x, y);	//sets cursor position to updated variables 
								downArrow++;	//increments the amount of lines that have been created (used with down arrow)
							}
							if (y >= 29 + yMod) {//does nothing if there are more than 20 lines of text 
							}
						}
						else {				
							//if the character that is read is not enter, reads it like a normal character
							//this is the same code that is used for when i input values outside of a document 
							system("cls");		//clears screen 
							rows[z].addToEnd(c);	//adds the character to the line of text 
							x++;				//increments cursor variable for the x coordinate 
							printingBorders();		//prints out the borders of the notepad 
							for (int w = 0; w <= 19; w++) {	//prints out the text of the file 
								gotoxy(xloc, yloc + w);	//sets location of the cursor to print 
								rows[w].DisplayRows();
								cout << endl;
							}
							gotoxy(x , y); //sets cursor to where the end of the text is 
						}
					}
				}
				if (d == 59) {//F1 
					//will make a color menu
					//it will prompt the user to input numbers according to colors that will be displayed on the screen
					//when the input is pressed, it will exit out of the menu and change the color of the borders, instructions at the bottom of the border and the text to the color 
					//selected. The menu name for the menu will flash random colors 
					screenColor= colorMenu();	//calls the function for the menu
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), screenColor);	//changes the color of the screen to the color selected 
					system("cls");	//clears the screen to reprint in the color selected
					printingBorders(); //prints borders in new color  
					for (int w = 0; w <= 19; w++) {	//prints text in new color 
						gotoxy(xloc, yloc + w);
						rows[w].DisplayRows();
						cout << endl;
					}
					gotoxy(x, y);
				}
			}
				else { //code that gets characters to place it into the List (rows)
					system("cls");		//clears screen
					rows[z].addToEnd(ch);	//adds characters to List
					x++;					//increments variable for the x coodintate of the cursor 
					printingBorders();		//printsthe borders 
					for (int w = 0; w <= 19; w++) {	//prints the characers up to and including the new one that user inputs 
						gotoxy(xloc, yloc + w);
						rows[w].DisplayRows();
						cout << endl;
					}
					gotoxy(x, y);
				}
			}
		}

	}

void Notepad::gotoxy(int x, int y) {//relocates the cursor to the x, y values given as parameters 

	COORD pos = { x, y };

	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(output, pos);

}




void Notepad::printPageTwo() { //prints page two of the instructions 
	gotoxy(50, 4);				//sets cursor to the spot where the page will be printed
	//prints page 2 of the insctructions 
	cout << R"( 
	        +--------------------------------------------------------------------------+
		|                              Other notes:                                |
		|          Press space to return to Page 1. Or enter to proceed            |
		+--------------------------------------------------------------------------+
		|                                                                          |
		|       There are only 20 lines that you can type in the notepad           |
		|      any more will not go to the next line, and will stay                |
		|      on the 20th line                                                    |
		|                                                                          |
		|      This notepad is capable of saving the text to an external file      |
		|      or write text from an external file into the notepad.               |
		|      When opening a file in the Notepad, it will paste it after the      |
		|      current location of the cursor, and will not delete the current     |
		|      text on screen. This is done on purpose.                            |
		|                                                                Page 2/2  |
		+--------------------------------------------------------------------------+


)";

}
void Notepad::printingBorders() //prints the borders for the main Notepad function 
{
	//prints out the header for Notepad, which says "Notepad" in ascii 
	cout << R"(
					  /\ \ \___ | |_ ___ _ __   __ _  __| |
					 /  \/ / _ \| __/ _ \ '_ \ / _` |/ _` |
					/ /\  / (_) | ||  __/ |_) | (_| | (_| |
					\_\ \/ \___/ \__\___| .__/ \__,_|\__,_|
					                    |_|                )";
	gotoxy(100, 5);	//sets the cursor location for printing the borders
	//prints out the borders, with some instructions on the botto showing the user how to use the program
	cout << R"(
	.-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-.
	|                                                                       				|
	|                                                                      					|
	|                                                                       				|
	|                                                                       				|
	|                                                                       				|
	|                                                                       				|
	!                                                                       				!
	:                                                                       				:
	:                                                                       				:
	.                                                                       				.
	.                                                                       				.
	:                                                                      					:
	:                                                                       				:
	!                                                                       				!
	|                                                                       				|
	|                                                                       				|
	|                                                                       				|
	|                                                                       				|
	|                                                                       				|
	|                                                                       				|
	`-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=by-eden'
	Esc- exit	f2- Save   f3- Import file	f1- Color menu	
)";
}
void Notepad::inputCustomPathway()	//gives the user the option to type in their own custom pathways for the input and output files 
//the user is given the option to opt out of inputting their own pathway, and if done with result in the program using the default pathway (works on Eden's computer only)
//at the end of the method, displays a timer which counts down to 0, then the Notepad function is run, and it is displayed in random numbers every second till the Notepad program officially starts 
{
	srand(time(NULL));	//random number generator 
	int random = 0;		//variable for the random number to be stored 
		char determinant = NULL;	//variable for user input 
		system("cls");		//clears the screen
		gotoxy(15, 6);		//sets location of the cursor 
		cout << "Do you want to input custom pathways? Press Enter again if no, Space if yes" << endl;		
		determinant= _getch();	//gets user input 
		if (determinant == 32) {	//if the user input is spacebar, it will allow the user to input their own pathway for the input and output files 
			gotoxy(17, 8);	
			cout << "Input the pathway for the input: ";
			getline(cin, outName);	//gets the user input for the input file 
			Sleep(100);
			gotoxy(17, 9);
			cout << "Input the pathway for the output: ";
			getline(cin, saveName);	//gets the user input for the output file 
			for (int i = 4; i > 0; i--) {	//this is the counter for when the code counts down to when the method ends and the Notepad opens up 
				random = (rand() % 10) + 1;	//randon number generator gets random numbers here 
				system("cls");				//clears the screen 
				gotoxy(33, 12);				//sets the cursor at the middle of the screen 
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), random);	//sets color to a random value between 1 and 10 
				cout << "Thank you. The Notepad will start in: " << i << "..."; //prints countdown 
				Sleep(1000);	//waits a second befoer printing again 
			}
			return;
		}
		else if (determinant == 13) {	//if enter was pressed, it just does the countdown the same was as before and exits the function
			for (int i = 4; i > 0; i--) {
				random = (rand() % 10)+1; 
				system("cls");
				gotoxy(33, 12);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), random);
				cout << "Thank you. The Notepad will start in: " << i << "...";
				Sleep(1000);
			}
			return;
		}
}
int Notepad::colorMenu()	//when f1 is pressed, opens this function. gives the user the option to select differnet colors according to their preference
//changes all the text on the Notepad except for notificatons (like escape key, and the other function keys)
{
	while (1) {
		int random = 0;
		random = (rand() % 10) + 1;
		char ch = NULL;
		system("cls");
		//shows "color menu!" with randomizing colors 
		gotoxy(45, 5);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), random);
		cout << "Color menu!!" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//displays option 1 
		gotoxy(45, 6);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
		cout << "1. This one?" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//displays option 2
		gotoxy(45, 7);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		cout << "2. This one!" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//displays option 3
		gotoxy(45, 8);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		cout << "3. This one?!" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//displays option 4
		gotoxy(45, 9);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		cout << "4. THIS ONE?" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//displays option 5
		gotoxy(45, 10);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
		cout << "5. this one?" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//displays option 6
		gotoxy(45, 11);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		cout << "6. thisone?" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//displays option 7
		gotoxy(45, 12);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		cout << "7. ThiS oNe?" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//displays option 8
		gotoxy(45, 13);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		cout << "8. eno siht?" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//displays option 9
		gotoxy(45, 14);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		cout << "9. th1s on3?" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//displays option 10, which is the default option
		gotoxy(45, 15);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "Enter. Default?" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		if (_kbhit()) {
			ch = _getch();
			if (ch == 49) {//when number 1 is pressed, cooresponding with option 1, will return 1, which can be stored in a variable 
				return 1;
				break;
			}
			else if (ch == 50) { //when number 2 is pressed, cooresponding with option 2, will return 2, which caan be stored in a variable 
				return 2;
				break;
			}
			else if (ch == 51) {//when number 3 is pressed, cooresponding with option 3, will return 3, which can be stored in a variable
				return 3;
				break;
			}
			else if (ch == 52) {//when number 4 is pressed, cooresponding with option 4, will return 4, which can be stored in a variable
				return 4;
				break;
			}
			else if (ch == 53) {//when number 5 is pressed, cooresponding with option 5, will return 5, which can be stored in a variable
				return 5;
				break;
			}
			else if (ch == 54) {//when number 6 is pressed, cooresponding with option 6, will return 6, which can be stored in a variable
				return 6;
				break;
			}
			else if (ch == 55) {//when number 7 is pressed, cooresponding with option 7, will return 7, which can be stored in a variable
				return 7;
				break;
			}
			else if (ch == 56) {//when number 8 is pressed, cooresponding with option 8, will return 8, which can be stored in a variable

				return 8;
				break;
			}
			else if (ch == 57) {//when number 9 is pressed, cooresponding with option 9, will return 9, which can be stored in a variable
				return 9;
				break;
			}
			else if (ch == 13) {//when enter is pressed, cooresponding with the enter option, will return 15 as its value (default color), which can be stored in a variable 
				return 15;
				break;
			}
		}
		
	}

}
void Notepad::printPageOne()//this function prints page one of the instructions
{
	gotoxy(50, 3);		//sets the cursor at the point i am going to print 
	cout << "INSTRUCTIONS:";//prints the header 
	gotoxy(25, 4);//sets location of the instructions under the header 
	cout << "Press spaceabar to continue to page 2. And enter to proceed";//prints instructions under the header 
	gotoxy(50, 5);//sets cursor location for printing the table of information 
	//prints the table 
	cout << R"( 
		  +--------------+--------+--------------------------------------------------+
		  | Keystroke    | ASCII  |                   Function                       |
		  |              |        |                                                  |
		  +--------------------------------------------------------------------------+
		  |  ESCAPE      |   27   |  When pressed twice will exit the program        |
		  |              |        |                                                  |
		  |  Enter       |   13   |  Generates a new line to type on                 |
		  |              |        |                                                  |
		  |  Backspace   |    8   |  Deletes the previous character                  |
		  |              |        |                                                  |
		  |  Arrow keys  | -32    |                                                  |
		  |    up        |   72   |  Mo^es one line up if it exists                  |
		  |    down      |   80   |  Moves one line down if it extists               |
		  |    left      |   75   |  Moves current index to the left if it exists    |
		  |    right     |   77   |  Moves current index to the right if it exists   |
		  |              |        |                                                  |
		  | Function keys|   0    |                                                  |
	   	  |    f2        |   60   |  Saves text to given output                      |
		  |    f3        |   61   |  Enters text from given input                    |
		  |    f1        |   59   |  Opens color menu                       Page 1/2 |
		  +--------------+--------+----^---------------------------------------------+

  )";
}
void Notepad::instructionsScreen()//this is the function that controls the switch between the two pages of instructions using spacebar
//will also leave the method and continue to other parts of the program if the user presses enter 
{
	printPageOne(); //prints page one as default 
	bool pageSwap = false;	//sets variable for the switch of the page 
	while (1) {
		if (_kbhit()) {	//if the keyboard was pressed 
			char c = _getch();//initializes the variable and sets it to the users input 
			if (c == 32) {	//if spacebar was pressed 
				pageSwap = !pageSwap;//switch the variable for switching between page one and two 
				if (!pageSwap) {//if variable has been switched to false, switch the page to page one 
					system("cls");
					printPageOne();
				}
				if (pageSwap) {//if varaible has been switched to true, switch the page to page two 
					system("cls");
					printPageTwo();
				}
			}
			else if (c == 13) {//if enter was pressed exit the method
				return;
			}
		}
	}
	system("cls"); //clears the screen of the instruction menus 
}
