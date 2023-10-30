#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <cmath>
#include <stdlib.h>
#include <cstdio>
#include <time.h>
#include "Data.h"

using namespace std;

MovieList::MovieList(){ //class constructor // initializes value of head node and the randomizer
	head = NULL;
	srand(time(NULL));
}

int MovieList::intCheck()
{ //checks if number inputted is an int
	double num;
	cin >> num;
	while (cin.fail() || num != round(num))
	{ //if input does not fit the 'double' data type, or if the input is not a whole number (not fit for int)
		cout << "Please enter a valid input: ";
		cin.clear();
		cin.ignore(200, '\n');
		cin >> num;
	}
	return num;
}

void MovieList::readFromFile(){ // reads information from a file to be stored in the linked as the program starts
	string get, title, genre, production, ID, numCopies;
	
	movieList.open("VIDEO.txt", ios::in); // opens file and movieList file stream for reading
	int flag = 1; // flag that lets the function know when an empty line is present in the file
	if(!movieList.fail() && movieList.is_open()){ // checks if file opened successfully
		while(getline(movieList, get)){ // sets value of variables to be stored in the linked list
			switch(flag){
				case 1: ID = get;
						break;
				case 2: title = get;
						break;
				case 3: genre = get;
						break;
				case 4: production = get;
						break;
				case 5: numCopies = get;
						break;
			}
			if(flag == 6){
				MovieList::addMovieNode(stoi(ID), title, genre, production, stoi(numCopies));
				flag = 1; //if an empty line is encountered, invokes addMovieNode and reset flag to 1
			}
			else{
				flag++;
			}
		}
	}
	
	movieList.close(); // closes movieList file stream
}

void MovieList::writeToFile(){ // stores nodes into a file as the program ends
	movieNode *nodePtr;
	
	movieList.open("VIDEO2.txt", ios::out | ios::app); // opens file and movieList file stream for writing
	
	if(movieList.is_open()){ //checks if file opened successfully
		if(MovieList::isEmpty()){ // checks if linked list is empty
			cout << "There are no available movies!" << endl;
		}
		else{
			nodePtr = head; // sets nodePtr to head
			while(nodePtr != NULL){ // while pointer is not in the end of list, writes information of each node into the file
				movieList << nodePtr->movieID << endl;
				movieList << nodePtr->movieTitle << endl;
				movieList << nodePtr->movieGenre << endl;
				movieList << nodePtr->movieProduction << endl;
				movieList << nodePtr->numOfCopies << endl;
				movieList << endl;
	
				nodePtr = nodePtr->next;
			}
		}
	}
	
	movieList.close(); // closes file and movieList file stream 
	remove("VIDEO.txt"); // removes old file
	rename("VIDEO2.txt", "VIDEO.txt"); // renames new file name into the old file name
}

void MovieList::addMovieNode(int ID, string title, string genre, string production, int numCopies){// utility function for storing videos in linked list
	//sets new Node variables equal to the values stored in the function parameters 
	movieNode *newNode, *nodePtr;
	nodePtr = NULL;
	newNode = new movieNode;
	newNode->movieID = ID;
	newNode->movieTitle = title;
	newNode->movieGenre = genre;
	newNode->movieProduction = production;
	newNode->numOfCopies = numCopies;
	newNode->next = NULL;
	
	if(MovieList::isEmpty()){ // checks if linked list is empty
		head = newNode; // sets head to new Node
	}
	else{
		nodePtr = head;
		while(nodePtr->next){ // if list is not empty, traverse the list till the last node is reached
			nodePtr = nodePtr->next;
		}
		nodePtr->next = newNode; //sets the next node of the last node equal to the new node
	}
}

void MovieList::insertVideo(){ // main function for storing videos in linked list
	int ID, numCopies; 
	string title, production;
	char genre[20]; 
	// prompts the user to enter details of the desired video to be added
	cout << "Please enter the movie title: ";
	getline(cin, title);
	cout << "Please enter the movie genre: ";
	cin.getline(genre, 20);
	cout << "Please enter the movie production: ";
	getline(cin, production);
	cout << "Please enter the number of copies: ";
	numCopies = MovieList::intCheck(); // checks if the input is an integer
	ID = MovieList::generateID(MovieList::capitalize(genre)); // invokes random number generator function based on the capitalized genre and set as value of the ID
	MovieList::addMovieNode(ID, title, genre, production, numCopies); // invokes the utility function addMovieNode

}

void MovieList::rentVideo(int searchID){ // function that lets a customer rent a video // decrements a video's number of copies
	movieNode *nodePtr;
	int found = 0; // flag to indicate that the specified movie is found
	if(MovieList::isEmpty()){ // checks if the linked list is empty
		cout << "There are no available movies!" << endl;
	}
	else{
		if(head->movieID == searchID){ // checks if head node contains the specified ID 
			head->numOfCopies--; // decrements number of copies of the movie
			cout << "Video successfully rented!" << endl;
			found = 1;
		}
		else{
			nodePtr = head; // if not head, traverse the linked list to find the node with ID equal to the value passed to the parameter
			while(nodePtr != NULL && nodePtr->movieID != searchID){
				nodePtr = nodePtr->next;
			}
			if(nodePtr != NULL){ // if nodePtr found the ID, run the block of code below
				nodePtr->numOfCopies--;
				cout << "Video successfully rented!" << endl;
				found = 1;
			}
			
		}
	}
	
	if(found == 0){ //displays a message if no movie with equal ID is found
		cout << "Movie is not in the list!" << endl;
	}
	
}

void MovieList::returnVideo(int searchID){ // function that lets a customer return a video // increments a video's number of copies
	movieNode *nodePtr;
	int found = 0; // flag to indicate that the specified movie is found
	if(MovieList::isEmpty()){ // checks if the linked list is empty
		cout << "There are no available movies!" << endl;
	}
	else{
		if(head->movieID == searchID){ // checks if head node contains the specified ID 
			head->numOfCopies++; // increments number of copies of the movie
			cout << "Video successfully returned!" << endl;
			found = 1;
		}
		else{
			nodePtr = head; // if not head, traverse the linked list to find the node with ID equal to the value passed to the parameter
			while(nodePtr != NULL && nodePtr->movieID != searchID){
				nodePtr = nodePtr->next;
			}
			if(nodePtr != NULL){ // if nodePtr found the ID, run the block of code below
				nodePtr->numOfCopies++;
				cout << "Video successfully returned!" << endl;
				found = 1;
			}
			
		}
	}
	
	if(found == 0 && !(MovieList::isEmpty())){ //displays a message if no movie with equal ID is found
		cout << "No more rented videos left!" << endl;
	}
}

int MovieList::displayVideo(){ // function to display a video specified by the user
	movieNode *nodePtr;
	int found = 0, ID; 
	nodePtr = NULL;
	
	MovieList::displayID(); // displays all the video IDs within the list as reference
	cout << "Please enter the ID of the video to be displayed" << endl;
	cout << "Video ID: ";
	cin >> ID;
	
	if(MovieList::isEmpty()){  // checks if the linked list is empty
		cout << "There are no available movies!" << endl;
	}
	if(head->movieID == ID){ //checks if the head node contains the specified ID
		cout << "================================================" << endl;
		cout << "Movie Details" << endl;
		cout << "------------------------------------------------" << endl;
		cout << "Movie Title:      " << head->movieTitle << endl;
		cout << "Genre:            " << head->movieGenre << endl;
		cout << "Production:       " << head->movieProduction << endl;
		cout << "Number of Copies: " << head->numOfCopies << endl;
		cout << "================================================" << endl;
		found = 1;
	}
	else{
		nodePtr = head;// if not head, traverse the linked list to find the node with ID equal to the value passed to the parameter
		while(nodePtr != NULL && nodePtr->movieID != ID){
			nodePtr = nodePtr->next;
		}
		
		if(nodePtr != NULL){ // if nodePtr found the ID, run the block of code below
			cout << "================================================" << endl;
			cout << "Movie Details" << endl;
			cout << "------------------------------------------------" << endl;
			cout << "Movie Title:      " << nodePtr->movieTitle << endl;
			cout << "Genre:            " << nodePtr->movieGenre << endl;
			cout << "Production:       " << nodePtr->movieProduction << endl;
			cout << "Number of Copies: " << nodePtr->numOfCopies << endl;
			cout << "================================================" << endl;
			found = 1;
		}
	}
	
	if(found == 0){ //displays a message if no movie with equal ID is found
		cout << "Movie is not in the list!" << endl;
	}
	
	return ID; // return the ID specified by the user to be used in the main function
	
}

void MovieList::displayAll(){ // displays all videos in the store
	// sets width of every column
	int firstCol = 15;
	int secondCol = 40;
	int thirdCol = 15;
	int fourthCol = 35;
	int fifthCol = 10;
	int fullCol = firstCol + secondCol + thirdCol + fourthCol + fifthCol;
	movieNode *nodePtr;
	nodePtr = NULL;
	
	if(MovieList::isEmpty()){ // checks if the linked list is empty
		cout << "There are no available movies!" << endl;
	}
	else{ //if not empty, displays all the video details with formatted output 
		cout << setfill('=') << setw(fullCol) << "" << endl;
		cout << setfill(' ') << setw(firstCol) << left << "ID";
		cout << setfill(' ') << setw(secondCol) << left << "Movie";
		cout << setfill(' ') << setw(thirdCol) << left << "Genre";
		cout << setfill(' ') << setw(fourthCol) << left << "Production";
		cout << setfill(' ') << setw(fifthCol) << left << "Copies";
		cout << endl << setfill('=') << setw(fullCol) << "" << endl;
		
		nodePtr = head;
		while(nodePtr != NULL){ // traverses through the linked list to display information of each video node

			cout << setfill(' ') << setw(firstCol) << left << nodePtr->movieID;
			cout << setfill(' ') << setw(secondCol) << left << nodePtr->movieTitle;
			cout << setfill(' ') << setw(thirdCol) << left << nodePtr->movieGenre;
			cout << setfill(' ') << setw(fourthCol) << left << nodePtr->movieProduction;
			cout << setfill(' ') << setw(fifthCol) << left << nodePtr->numOfCopies;
			cout << endl << setfill('=') << setw(fullCol) << "" << endl;

			nodePtr = nodePtr->next;

		}
	}
	cout << endl;
}

bool MovieList::checkVideo(int ID){ // checks video availability
	movieNode *nodePtr;
	nodePtr = NULL;
	bool status = false; // flag that indicates video availability
	int found = 0; // flag to indicate that the specified movie is found
	
	if(MovieList::isEmpty()){ // checks if the linked list is empty
		cout << "There are no available movies!" << endl;
	}
	else{
		nodePtr = head; // if not head, traverse the linked list to find the node with ID equal to the value passed to the parameter
		while(nodePtr != NULL && nodePtr->movieID != ID){
			nodePtr = nodePtr->next;
		}
		if(nodePtr != NULL && nodePtr->numOfCopies > 0){ // if nodePtr found the ID, run the block of code below
			cout << "Movie is available!" << endl;
			cout << "================================================" << endl;
			found = 1;
			status = true;
		}
		else if(nodePtr != NULL && nodePtr->numOfCopies == 0){ // if nodePtr found the ID and the number of Copies is 0, run the block of code below
			cout << "Movie is not available!" << endl;
			found = 1;
		}
	}
	if(found == 0){ //displays a message if no movie with equal ID is found
		cout << "Movie is not in the list!" << endl;
	}
	return status; // returns status to be used in the main function
}

string MovieList::capitalize(char* str){ // function to capitalize letters
	string output;
	for(int i = 0; i < strlen(str); i++){ // iterates over the characters of the passed cstring and capitalizes each
		str[i] = toupper(str[i]);
	}
	output = str; // set the value of the string equal to the cstring
	return output;
}

int MovieList::generateID(string genre){ // generates random ID based on movie genre
	int ID;
	srand(time(NULL)); // sets randomizer values
	if(genre.compare("HORROR") == 0){ // if genre is equal to HORROR, randomly set the value of ID equal to values from 1000-2000
		ID = rand() % 1000 + 1000;
	}
	else if(genre.compare("ROMANCE") == 0){ // if genre is equal to ROMANCE, randomly set the value of ID equal to values from 2000-3000
		ID = rand() % 1000 + 2000;
	}
	else if(genre.compare("SCI-FI") == 0){ // if genre is equal to SCI-FI, randomly set the value of ID equal to values from 3000-4000
		ID = rand() % 1000 + 3000;
	}
	else if(genre.compare("ACTION") == 0){ // if genre is equal to ACTION, randomly set the value of ID equal to values from 4000-5000
		ID = rand() % 1000 + 4000; 
	}
	else if(genre.compare("COMEDY") == 0){ // if genre is equal to COMEDY, randomly set the value of ID equal to values from 5000-6000
		ID = rand() % 1000 + 5000;
	}
	else{ // if genre is equal to other genres, randomly set the value of ID equal to values from 6000 above
		ID = rand() % 3000 + 6000;
	}
	return ID;
}

bool MovieList::isEmpty(){ // checks whether the linked list is empty
	bool status; // flag that indicates if linked list is empty
	
	if(!head){
		status = true;
	}
	else{
		status = false;
	}
	return status;
}

void MovieList::displayID(){ // displays all video IDs stored in the linked list
	movieNode *nodePtr;
	nodePtr = NULL;
	
	if(MovieList::isEmpty()){ // checks whether the linked list is empty
		cout << "There are no available movies!" << endl;
	}
	else{
		nodePtr = head;
		while(nodePtr != NULL){ // if not empty, traverse the linked list and displays ID of each video node
			cout << "Video ID: " << nodePtr->movieID << endl;
			nodePtr = nodePtr->next;
		}
	}
}
