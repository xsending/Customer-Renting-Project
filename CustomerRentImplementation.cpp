#include <iostream>
#include <cstdio>
#include <string>
#include "Data.h"

using namespace std;

CustomerRent::CustomerRent(){ // empty class constructor

}

void CustomerRent::readFromFile(){ // function that lets a customer rent a video // creates a customer structure to be stored in the list
	string get;
	int ID;
	stack<int> videos; // stack stl to store rented videos inside a structure
	stack<int> empty; // stack stl to empty out the main stack
	customerRent x;
	customerRentList.open("CUSTOMER-RENT.txt", ios::in); // opens customerRentList file and file stream for reading
	if(!customerRentList.fail() && customerRentList.is_open()){ // checks whether the file opened successfully
		while(customerRentList >> get){
			if(get == "-"){ // serves as a separator in the file for each customer IDs and their video IDs// signals function to add the information into the list
				CustomerRent::addToList(ID, videos); 
				videos = empty; // assigns the video stack to the empty stack
			}
			else if(stoi(get) < 20000){
				videos.push(stoi(get)); // if value is less than 20000, lets the program know that the ID is a video ID and is pushed into the stack
			}
			else if(stoi(get) > 19999){ // if value is greater than 19999, lets the program know that the ID is a customer ID and is set as ID to be stored in list
				ID = stoi(get);	
			}
		}
	}
	
	customerRentList.close(); // closes file and file stream

}

void CustomerRent::addToList(int ID, stack<int> videos){ //utility function that helps in adding a customer structure into the list
	customerRent x;
	x.customerID = ID;
	x.rentedVideos = videos; // sets the structure stack equal to the stack passed in the function parameter
	custRent.push_front(x); //pushes customerRent structure x into the list
}

void CustomerRent::writeToFile(){// stores customer-rent structure into a file as the program ends

	customerRentList.open("CUSTOMER-RENT2.txt", ios::out | ios::app); // opens customerRentList file and file stream for writing
	
	if(customerRentList.is_open()){ //checks whether the file opened successfully
		for(iter = custRent.begin(); iter != custRent.end(); iter++){ // sets list iterator into the beginning of the list stl 
			if(!((*iter).rentedVideos.empty())){ // checks if the current element the iterator is pointing to is not an empty rentedVideos stack
				customerRentList << (*iter).customerID << endl; // if not empty, writes the current element's customer ID into the file
				while(!((*iter).rentedVideos.empty())){ // loops over the non-empty rentedVideos stack until its empty
					customerRentList << (*iter).rentedVideos.top() << endl; // writes the element at the top of the stack into the file
					(*iter).rentedVideos.pop(); // pops top element
				}
				customerRentList << "-" << endl; // writes a separator in the file once the rentedVideos stack is emptied 
			}	
		}
	}
	customerRentList.close(); // closes file and file stream
	remove("CUSTOMER-RENT.txt"); // removes old file
	rename("CUSTOMER-RENT2.txt", "CUSTOMER-RENT.txt"); // renames the new file name into the old file name
}

void CustomerRent::rentVideo(int custID, int vidID){ // function that lets a customer rent a video // creates a customer structure to be stored in the list
	customerRent x; // creates customerRent structure x
	x.customerID = custID;
	x.rentedVideos.push(vidID); // pushes video ID passed on the function parameter into the structure stack
	if(custRent.empty()){ //if list is empty, pushes the structure in the beginning of the list
		custRent.push_front(x);
	}
	else{ // if not empty, set iterator to the beginning of the list
		for(iter = custRent.begin(); iter != custRent.end(); iter++){
			if((*iter).customerID == custID){ // checks if the element the iterator is currently pointing to has a customer ID equal to the ID passed in the function parameter
				(*iter).rentedVideos.push(vidID); // if customer ID is equal, push the video ID into the stack of the pointed element
				break;
			}
		}
		if(iter == custRent.end()){ // if iterator reaches the end of the list, push the structure in the beginning of the list
				custRent.push_front(x);
			}	
	}
}

void CustomerRent::returnVideo(int custID, int& vidID){	// function that lets a customer return a video // pops video IDs stored in stack within the customer structure	
	if(custRent.empty()){ // checks if the list is empty
		cout << "The customer have not rented yet" << endl;
	}	
	else{ // if not empty, set iterator to the beginning of the list
		for(iter = custRent.begin(); iter != custRent.end(); iter++){
			if((*iter).customerID == custID){ // checks if the current element the iterator is pointing to is equal to the ID passed on the parameter
				if(!((*iter).rentedVideos.empty())){ // checks if the rentedVideos stack is empty
					vidID = (*iter).rentedVideos.top(); // if not empty, sets value of vidID parameter equal to the element at the top of the stack
					(*iter).rentedVideos.pop();	// pops the top of the stack
				}
			}
		}
	}
}

void CustomerRent::printAllRented(int custID){ // displays all customer IDs and rented video IDs of the corresponding customers
	stack<int> temp; // stack used to display and pop elements of the stack // makes sure that the elements in the main stack is not affected
	if(custRent.empty()){ //checks if the list is empty
		cout << "The customer have not rented any yet" << endl;
	}
	else{ //if not empty, sets the iterator equal to the beginning of the list
		for(iter = custRent.begin(); iter != custRent.end(); iter++){
			if((*iter).customerID == custID){ // checks if the current element the iterator is pointing to is equal to the ID passed on the parameter
				temp = (*iter).rentedVideos; // assigns the temporary stack to the values of the rentedVideos stack of the pointed element
				cout << "Rented Videos" << endl;
				cout << "------------------------------------------------" << endl;
				while(!(temp.empty())){ // loops over the temporary stack until stack is empty
					cout << "VideoID: " << temp.top() << endl; // displays the video ID at the top of the stack
					temp.pop(); // pops the top of the element 
				}
				cout << "================================================" << endl;
			}
		}
	}
	
	
}
