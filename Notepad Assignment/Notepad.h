#pragma once
#include "Node.h"
#include "List.h"
#include <Windows.h>
#include <string>
#include <stdio.h>
using namespace std; 
#define CHARACTER_INLINE 60; 
#define NEWLINE '\n';


class Notepad {
public:
	void start(); //is the driving method for the program Notepad 
	void instructionsScreen();//displays the instruction screens for the program
	void gotoxy(int x, int y);//used to control cursor location
	void printPageOne();//prints page one of the instructions
	void printPageTwo();//prints page two of the instructions 
	void printingBorders(); //prints the borders of the Notepad
	void inputCustomPathway();//allows the user to input a custom pathway for externam file access 
	int colorMenu();//opens the menu for the user to select the color the for Notepad 
};