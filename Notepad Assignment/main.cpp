#include <iostream>
#include <windows.h>
#include "List.h"
#include "Node.h"
#include "Notepad.h"
#include <fstream>
using namespace std;



void main() { 

    
    Notepad pageOne;
    pageOne.instructionsScreen();
    pageOne.inputCustomPathway();
    pageOne.start();
}