#include <iostream>
#include "Data.h"
using namespace std;

RentStack::RentStack(){
	top = NULL;
}

void RentStack::push(int ID, string title, string genre, string production, int numCopies){
	rentMovieNode *newNode, *nodePtr;
	newNode = new rentMovieNode;
	newNode->movieID = ID;
	newNode->movieTitle = title;
	newNode->movieGenre = genre;
	newNode->movieProduction = production;
	newNode->numOfCopies = numCopies;
	newNode->next = NULL;
	
	if(RentStack::isEmpty()){
		cout << "There are no rented movies!" << endl;
	}
	else{
		newNode->next = top;
		top = newNode;
	}
}

void RentStack::pop(int& ID, string& title, string& genre, string& production, int& numCopies){
	rentMovieNode *temp;
	if(RentStack::isEmpty()){
		cout << "There are no rented movies!" << endl;
	}
	else{
		ID = top->movieID;
		title = top->movieTitle;
		genre = top->movieGenre;
		production = top->movieProduction;
		numCopies = top->numOfCopies;
		
		temp = top->next;
		delete top;
		top = temp;
	}
}

void RentStack::returnVideo(int ID, string title, string genre, string production, int numCopies){
	RentStack::showCustomerDetails();
	RentStack::pop(int& ID, string& title, string& genre, string& production, int& numCopies); 
	
}
bool RentStack::isEmpty(){
	bool status;
	
	if(!top)
		status = true;
	else
		status = false;
	
	return status;
}
