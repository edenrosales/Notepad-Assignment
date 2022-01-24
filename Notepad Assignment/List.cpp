#include "List.h"
#include <windows.h>
#include <iostream>
#include <string> 
#include "Node.h"
#include <fstream>
#include <cstring> 
#include "Notepad.h"
using namespace std;



void List::moveLeft() {//moves current to previous Node
	curr = curr->prev; 

}

void List::moveRight() //moves current to the next Node
{
	curr = curr->next; 
}

bool List::atBeginning()//returns if the curr Node is at the beginning of the line or not (NULL)
{
	if (curr == NULL)
		return true; 
	return false;
}

bool List::inBoundsLeft()//checks and returns if the curr is withing the bounds for moving left or not.
//since cannot go left when curr is pointed at NULL (the beginning of the line) it will return false in that case 
{
	if (curr==NULL) {
		return false;
	}
	return true; 
}

bool List::inBoundsRight()//checks and returns if curr is within the bounds for moving to the right or not 
//will make sure the curr is not pointing to the very right of the line (NULL), because it would not make sense to allow for the right arrow to work in that case 
{
	if (curr->next == NULL)
		return false; 
	if (curr == end)
		return false;
	return true;
}

bool List::inBoundsNULL() {//checks if the curr is pointed at NULL (the beginning of the line) 
	if (curr == NULL)
		return true;
	return false;
}

void List::currAtNull()//sets current to head, is used when current is pointing to NULL, as a way to iterate to the right 
//this is because NULL cant hold a next value 
{
	curr = head; 
}

void List::setCurr()//sets current to NULL, used when using enter and arrow keys for going up and down lines 
{
	curr = NULL; 
}

void List::copyListToOutput(string fileName)//this is the function that saves the contents of Notepad to the output file that is designated 
//this is to be called using a loop that will iterate through each List in the Notepad.
//will append the next of the output to the end of the file, so that it can print it all 
{
	ofstream file(fileName,ofstream::app);//opens the file 
	Node* T;//creates a node 
	T = head; //points the node to head 
	while (T != NULL) {//while the node is not NULL
		file << T->data;//will print the data from the node into the file
		T = T->next;//will iterate to the next Node
	}
	file << endl;//will press enter at the end of each line 
	file.close();//at the end of printing the line, closes the file
}

void List::copyListToInput(string fileName)//will take the input and open it in the Notepad
//will start to copy the contents of the file where the cursor is in the program 
//we need to put this in a for loop because this will only print out one line from the input file 
{
	char c; //creates char variable 
	ifstream file(fileName);//opens the input file
	//will not contiue to enter in characters if it runs into an enter, or a new line, will break and then the for loop will iterate to the next line in the input file 
	while ((file.get(c)) && (c != '\n')) {//runs a while loop while the function is reading more values in the file (while there is more contents in the file) 

		addToEnd(c); //adds the characters  to the end of the file 
	}
	return; 
}


void List::DisplayRows()//prints out the List, this translates to only one line of Notepad, so we need to use a for loop to iterate through all the lines 
{
	Node* currNode = head;//points a new node to the head 
	while (currNode != NULL) {//starts printing while the node is not poining to NULL 
		cout << currNode->data;//prints out the data of the node 
		currNode = currNode->next;//iterates to the next Node 
	}
}
List::~List() {//destructor for List
	Node* currNode = head, * nextNode = NULL;//makes a new node that points to head, and another that poines to NULL 
	while (currNode != NULL)//while the currentNode is not NULL 
	{
		nextNode = currNode->next;
		// destroy the current node
		delete currNode;//deletes currentNode
		currNode = nextNode;//iterates to the next node 
	}
}

void List::addToEnd(char x) {//adds a character that it input to the List
	//despite the name of the method, it will place the character to any point in the List 
	//makes a new node and makes this new node the head, end and current 
	if (IsEmpty() == true) {//acounts for when the list is empty 
		Node* newNode = new Node;
		newNode->data = x;//sets the data of the node that is input 
		head = newNode;//sets the new node to head
		end = newNode;//sets  new node to end 
		newNode->next = NULL;//sets next node to NULL 
		curr = newNode; //sets  node to curr
	}
	//makes the new node the new head, and makes all the connections valid and correct 
	else if (curr ==NULL) {//for when curr is at the beginning of the List 
		Node* newNode = new Node;//makes new node 
		newNode->data = x; //sets the data for the new node 
		curr = newNode;//sets curr to be the new node 
		newNode->next = head;//sets next pointer to point to the current head of the List 
		newNode->prev = NULL;//sets the previous node to be NULL, or the beginning of the List 
		head->prev = newNode;//sets the old heads prev pointer to point to the current node 
		head = newNode;//makes the new node the head of the List 

	}
	//	makes a new node and makes the new node the end node, make the connections work 
	else if (curr == end) {//when curr is set to end 
		
			Node* newNode = new Node;//makes a new node
			newNode->data = x;//sets the new nodes data 
			end->next = newNode;//makes the current ends next pointer point to the new node 
			newNode->prev = end;//set new nodes previous pointer to point to the old head 
			end = newNode;//makes the new pointer head 
			newNode->next = NULL;//makes the new node's next pointer point to NULL
			curr = newNode;//sets curr to new node 
		}
	//is going to place the new node after the head node, making this the current node 
	else if (curr == head) {//if curr is pointing to head 
			Node* newNode = new Node;//make a new node 
			newNode->data = x;//set new nodes data to x 
			newNode->next = head->next;//make the next pointer of the new node point to the current heads next 
			head->next->prev = newNode; //make the current heads next's previous pointer point to the new node 
			head->next = newNode;//make the next pointer of head point to the new node 
			newNode->prev = head;//make the new nodes previous ponter point to head
			curr = newNode;//make the current node point to the new node 
		}
	//when curr is pointoing to a node in the middle 
	//makes a new node and sets the nodes pointers (current and the one right after current) to the new node to insert it in the middle 
	else if (curr->next != NULL && curr->prev != NULL) {
			Node* newNode = new Node; //makes a new node 
			newNode->data = x; //set new nodes data to x 
			newNode->next = curr->next;//new nodes next poniter to pont to the current nexts 
			curr->next->prev = newNode;//sets the current nodes next previous pointer to the new node 
			newNode->prev = curr;//set the new nodes previous pointer to point to curr
			curr->next = newNode;//make the curr's next pointer point to the new node 
			curr = newNode;//set curr to new node 
		}
	else {}
}

void List::deleteIndex()//deletes the index that curr points to 
{

	if (curr == NULL) {//does nothing if curr is at the beginning of the List 
		return; 
	}
	
	if ((curr == head) && (curr == end)) {//if curr is pointing to both head and end, so when there is only one node left in the List 
		delete curr;//delete current, which is the rest of the list 
		//sets head, end and curr to NULL because there is not any nodes left in the list 
		head = NULL;
		end = NULL;
		curr = NULL; 
	}
	//makes the node right before end the new end, and deletes the old end 
	else if (curr == end) {//when curr points to end 
		//Node* newNode = new Node; //makes a new node 
		//newNode = curr;//set the new node to current 
		//curr = newNode->prev; //set current to be the previous of new node 
		//end = newNode->prev;//make the end point to the prevoius of new node  
		//curr->next = NULL; //set currents next to be NULL 
		//delete newNode;//delete new node 
		
		/// <summary>
		/// below is test code that i made for the final, can be replaced with the code above and will work the same(?)
		/// </summary>
		curr = curr->prev; //set current to be the previous of new node 
		end = curr;//make the end point to the prevoius of new node  
		curr->next = NULL; //set currents next to be NULL 
		delete curr->next;//delete new node 
	}

	//deletes the current head and makes the node to the right of head the new head 
	else if (head == curr) {//when curr points to head  
		Node* newNode = new Node;//make new node 
		newNode = curr;//sets new node equal to curr
		curr = NULL;//make curr point to NULL 
		head = head->next;//make the head equal to the node to the right of head 
		head->prev = NULL;//making the prevoius of head point to null 
		delete newNode; //delete new node, which holds the old head

	}
	else if ((curr->next != NULL) && (curr->prev != NULL)) {//when current is pointing to a node in the middle 
		Node* newNode = new Node; //make a new node 
		newNode = curr; //make new node equal to curr
		//makes the nodes of nodes to the left and the right of current go around curr, so it is no longer attached to them 
		curr->next->prev = curr->prev;
		curr->prev->next = curr->next;
		curr = curr->prev; 
		//deletes what the contents of curr were, so the node mentioned in the previous comment 
		delete newNode;
	}

}
void List::gotoxy(int x, int y) {//sets the cursor location to x,y coordinates 

	COORD pos = { x, y };

	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(output, pos);

}