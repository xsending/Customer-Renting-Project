#include <iostream>
#include <string>
#include <queue>
#include <cmath> //rounding numbers
#include <iomanip>
#include <stdlib.h>
#include <stack>
#include <cstdio>
#include <time.h>
#include "Data.h"
using namespace std;
	
Customer::Customer(){ // class constructor // sets randomizer values
	srand(time(NULL));
}

int Customer::intCheck() // evaluates if an input is an integer 
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

void Customer::readFromFile(){ // reads information from a file to be stored in the linked as the program starts
	string get, custID, tempName, tempAddress;
	customerList.open("CUSTOMER.txt", ios::in); // opens file and customerList file stream for reading
	int flag = 1; // flag that lets the function know when an empty line is present in the file
							 
	if(!customerList.fail() && customerList.is_open()){ // checks if file opened successfully
		while(getline(customerList, get)){ // sets value of variables to be stored in the structure and into the queue stl
			switch(flag){
				case 1: custID = get;
						break;
				case 2: tempName = get;
						break;
				case 3: tempAddress = get;
						break;
			}
			if(flag == 4){ //if an empty line is encountered, invokes add customer function and reset flag to 1

				Customer::addCustomer(stoi(custID), tempName, tempAddress);

				flag = 1;			
			}
			else{
				flag++;
			}
		}
	}
	else{
		cout << "Customer List currently empty" << endl;
	}
	
	customerList.close(); // closes file and customerList file stream
}

void Customer::writeToFile(){ // stores customer details structure into a file as the program ends

	customerList.open("CUSTOMER2.txt", ios::out | ios::app); // opens file and customerList file stream for writing
	int queueSize = customers.size(); // used as a for loop condition

	if(customerList.is_open()){ // checks if file opened successfully
		if(customers.empty()){ // checks if the queue stl is empty
			cout << "There are no customers in the list" << endl;
		}
		else{ // if not empty, writes information of the front element of the queue stl and then pops it
			for(int i = 0; i < queueSize; i++){
				customerList << customers.front().customer_ID << endl;
				customerList << customers.front().name << endl;
				customerList << customers.front().address << endl;
				customerList << endl;
				customers.pop();
			}
		}
	}
	
	customerList.close(); // closes the file and customerList file stream
	remove("CUSTOMER.txt"); // removes old file
	rename("CUSTOMER2.txt", "CUSTOMER.txt"); //renames new file name into the old file name
	
}

void Customer:: addCustomer() //adds customer details structure into the stl queue
{
	string nameTemp;
	string addressTemp;
	// prompts the user to enter details of the customer to be added
	cout << "Please input Customer Name: ";
	getline(cin, nameTemp);
	cout << "Please input Customer Address: ";
	getline(cin, addressTemp);

	CustomerDetails x;
	x.customer_ID = rand() % 10000 + 20000; //randomizes customer ID from 20000 and up
	x.name = nameTemp;
	x.address = addressTemp;
	customers.push(x); // pushes the structure into the queue stl

	cout << "Customer added to queue." << endl;
}

void Customer:: addCustomer(int num, string name, string addr) { // utility function that helps adding customer details from a file into the queue
	// sets structure variables equal to values passed to the function parameter
	CustomerDetails x;
	x.customer_ID = num;
	x.name = name;
	x.address = addr;
	customers.push(x); // pushes the structure into the queue stl

}

void Customer:: showCustomerDetails(int input) // displays a customer's details specified by the user
{
	int found = 0; // flag to indicate that the specified customer ID is found
	queue<CustomerDetails> temp; // queue used to display and pop elements of the queue // makes sure that the elements in the main queue is not affected
	temp = customers; // sets value of temp queue equal to the main queue
	for (int i = 0; i < customers.size(); i++) { //loop to find the specified customer ID in the front of the queue
		if (input == temp.front().customer_ID) { // checks if the current element in the front of the queue is equal to the ID passed on the parameter
			cout << "================================================" << endl;
			cout << "Customer Details" << endl;
			cout << "------------------------------------------------" << endl;
			cout << "ID:      " << temp.front().customer_ID << endl;
			cout << "Name:    " << temp.front().name << endl;
			cout << "Address: " << temp.front().address << endl;
			cout << "================================================" << endl;
			found = 1;
			break;
		}
		else { // if not equal, pop the element
			temp.pop();
		}
	}
	if(found == 0){ //displays a message if no customer with equal ID is found
		cout << "The customer is not in the list!" << endl;
	}
}

void Customer::printCustomerList() { // displays all customers' details
	// sets width of every column
	int firstCol = 15;
	int secondCol = 35;
	int thirdCol = 50;
	int fullCol = firstCol + secondCol + thirdCol;
	queue<CustomerDetails> temp;
	temp = customers; // sets value of temp queue equal to the main queue
	//displays all the video details with formatted output 
	cout << setfill('=') << setw(fullCol) << "" << endl;
	cout << setfill(' ') << setw(firstCol) << left << "ID";
	cout << setfill(' ') << setw(secondCol) << left << "Name";
	cout << setfill(' ') << setw(thirdCol) << left << "Address";
	cout << endl << setfill('=') << setw(fullCol) << "" << endl;
			
		
	for (int i = 0; i < customers.size(); i++){ // loops enough times to display the front element of the queue and then pop to access the next element
		cout << setfill(' ') << setw(firstCol) << left << temp.front().customer_ID;
		cout << setfill(' ') << setw(secondCol) << left << temp.front().name;
		cout << setfill(' ') << setw(thirdCol) << left << temp.front().address;
		cout << endl << setfill('=') << setw(fullCol) << "" << endl;
		temp.pop();
	}
}

bool Customer::isEmpty(){ // checks whether the queue stl is empty
	bool status; // flag that indicates if queue is empty
	if(customers.empty()){
		status = true;
	}
	else{
		status = false;
	}
	return status;
}

bool Customer::exists(int input){ // checks whether the customer exists in the queue or not
	bool found = false; // flag that indicates if the customer is found in the queue or not
	queue<CustomerDetails> temp;
	temp = customers; // sets value of temp queue equal to the main queue
	for (int i = 0; i < customers.size(); i++) { // loops over the the temporary queue and pops front element if ID is not equal to the value in the parameter
		if (input == temp.front().customer_ID) {
			found = true;
		}
		else {
			temp.pop();
		}
	}
	return found; // returns found value to be used in the main function
}

