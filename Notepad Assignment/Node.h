#pragma once
#include <iostream> 
#include <Windows.h>
#include <string>
using namespace std;

class Node {
public:
	char data; ///data 
	Node* next; //pointer to next 
	Node* prev; //pointer to the previous 
	Node() { next = NULL; prev = NULL;  } //initializing variables for all Nodes at creation 
};

