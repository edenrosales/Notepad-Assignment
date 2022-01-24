#pragma once
#include "Notepad.h"
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;


class List {
public:
	List() { head = NULL; end = NULL; curr = NULL; }
	~List();
	bool IsEmpty() { return head == NULL; }//returns if the List is empty by checking the head variables state 
	void DisplayRows(); //prints data that is being held at all the Nodes in the list 
	void addToEnd(char x);//adds the character to the end of the list 
	void deleteIndex();//deletes the index that is being pointed to by curr 
	//deletes the index that is being pointed to 
	void moveLeft();//moves curr to the left if it exists 
	void moveRight();//moves curr to the right if it exists
	bool atBeginning();//checks if curr is pointing to the beggining (NULL) of the List 
	bool inBoundsLeft(); //checks for the left arrow key functionalty, if the left bound has been exceeded or not 
	bool inBoundsRight();	//checks for the right arrow key functionality, if the right bound has been exceeded or not 
	bool inBoundsNULL();	//checks if curr it pointing to NULL (the start of the List 
	void currAtNull();	//sets curr to head, used when curr is pointing to NULL, and needs to step one to the right 
	void setCurr(); //this sets ccurr to NULL, or the start of the List, for placing curr to the begining of the List 
	void copyListToOutput(string fileName);//function is used for saving the document to another file 
	void copyListToInput(string fileName);//funtion is used for opening the file to the Notepad 

	void gotoxy(int x, int y);//used to set the cursor at different places 
private:
	Node* head;//points to the first Node in the List 
	Node* end;//points to the last Node in the List
	Node* curr; //points to the current Node int he List 
};
