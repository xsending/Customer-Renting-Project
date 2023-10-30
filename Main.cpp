#include <iostream>
#include <string>
#include "Data.h"

using namespace std;

void delay(bool &x)
{ //asks for any character/string before going back to menu
	string delayStr;
	if (!x) {
		cout << "\nInput any character to continue: ";
		cin >> delayStr; //asks for any input
		
	}
	x = false;
	system("CLS"); //clears the console
}

int main(){
	//variable declarations
	int  vidID, custID, vidOption, custOption; 
	string  genre, title, production;
	//class object declarations
	MovieList movieList;
	Customer customerList;
	CustomerRent rentList;	
	//invokes readFromFile functions from all involved classes
	movieList.readFromFile();
	customerList.readFromFile();
	rentList.readFromFile();
	// flag variables
	bool firstOpen = true;
	char rentLoop = 'Y';
	char returnLoop = 'Y';
	mainMenu: // displays the main menu of the program
		delay(firstOpen); // delays the program by asking the user to enter any input before clearing the screen if the firstOpen variable is false
		cout << "VIDEO STORE MENU" << endl;
		cout << "[1] New Video" << endl;
		cout << "[2] Rent a Video" << endl;
		cout << "[3] Return a Video" << endl;
		cout << "[4] Show Video Details" << endl;
		cout << "[5] Display All Videos" << endl;
		cout << "[6] Check Video Availability" << endl;
		cout << "[7] Customer Maintenance" << endl;
		cout << "[8] Exit Program" << endl;
		cout << "Enter Choice: ";
		cin >> vidOption;
		cout << endl << endl;
		if(cin.fail()){ // checks if the input is a valid integer input
			cout << "Please enter a valid input..." << endl;
			//system("pause");
			cin.clear();
			cin.ignore(200, '\n');
			//system("cls");
			goto mainMenu; 
		}
		cin.ignore();
	switch(vidOption){
		case 1: movieList.insertVideo(); // option that invokes the function to add a video into the linked list
				goto mainMenu; // loops back to the main menu
				break;
		case 2: if(customerList.isEmpty()){ // if there are no customers in the queue, the program loops back to the main menu
					cout << "Customer list is empty." << endl;
					goto mainMenu;
				}
				cout << "Please enter the customer ID: "; // if there are customers, prompt the user to enter customer ID
				custID = customerList.intCheck(); // checks if entered ID is an integer
				customerList.showCustomerDetails(custID); // shows customer details of the entered ID
				cout << endl << endl;
				if(customerList.exists(custID)){ // if the customer ID is in the queue, displays all video IDs in the linked list as reference for renting
					movieList.displayAll();
				}
				//loop that lets the user rent multiple videos // checks if the linked list is empty and that the customer is in the queue
				while((rentLoop == 'y' || rentLoop == 'Y') && !(movieList.isEmpty()) && customerList.exists(custID)){
					cout << "Please enter the ID of the video you want to rent" << endl;
					cout << "Video ID: ";
					cin >> vidID;
					if(movieList.checkVideo(vidID)){ // checks if the video's number of copies is not 0
						movieList.rentVideo(vidID); // if not 0, lets the user rent the video
						rentList.rentVideo(custID, vidID);
					}
					cout << "Would you like to rent another video?[Y/N or any key]: ";
					cin >> rentLoop; // if Y is entered, the program loops over the renting process 
				}
				rentLoop = 'Y'; // sets the flag back to Y for the next renting process
				goto mainMenu; // loops back to the main menu
				break;
		case 3: if(customerList.isEmpty()){ // if there are no customers in the queue, the program loops back to the main menu
					cout << "Customer list is empty." << endl;
					goto mainMenu;
				}
				cout << "Please enter the customer ID: ";
				custID = customerList.intCheck(); // checks if entered ID is an integer
				customerList.showCustomerDetails(custID); // shows customer details of the entered ID
				//loop that lets the user return multiple videos // checks if the linked list is empty and that the customer is in the queue
				while((returnLoop == 'Y' || returnLoop == 'y') && !(movieList.isEmpty()) && customerList.exists(custID)){
					cout << "Rented Videos... " << endl;
					rentList.returnVideo(custID, vidID); // returns the video present at the top of stack of the specified customer
														 // sets the vidID variable equal to the popped element
					if(vidID > 0) // checks if the value of vidID is greater than 0 (a video ID was popped in the stack)
						cout << "Video ID: " << vidID << endl;				
					movieList.returnVideo(vidID); // returns the video of the corresponding video ID back to the linked list(number of copies is incremented)
					if(vidID > 0){ //if a video ID was popped, prompts if the user wants to return another video
						cout << "Would you like to return another video?[Y/N or any key]: ";
						cin >> returnLoop;
					}
					else{
						returnLoop = 'N'; // if no video ID was popped, sets flag to N and ends the loop
					}
					vidID = 0; // clears the video ID stored in this variable
				}
				returnLoop = 'Y'; // sets the flag back to Y for the next return process
				goto mainMenu; // loops back to the main menu
				break;
		case 4:	movieList.displayVideo(); // displays video details specified by the user
				goto mainMenu;// loops back to the main menu
				break;
		case 5: movieList.displayAll();	
				goto mainMenu;// loops back to the main menu
				break;
		case 6:	movieList.checkVideo(movieList.displayVideo()); //if number of copies returned by the displayVideo function is not zero, displays that the video is available
				goto mainMenu;// loops back to the main menu
				break;
		case 7:	firstOpen = true; // sets firstOpen to true to make sure the program is not delayed as it goes to the customer menu
				system("CLS"); // clears screen
				goto customerMenu; // goes to the customer menu
				break;
		case 8: //invokes writeToFile functions from all involved classes before closing
				movieList.writeToFile();
				customerList.writeToFile();
				rentList.writeToFile();
				cout << "\t\t\t\t\tThank you for using the program!!\t\t\t\t\t\t\n";
				cout << "\t\t\t\t\t  CS0015L FINALS (SECTION 1 -C) \t\t\t\t\t\t\n";
				cout << "\t\t\t\t\t\t THE TELETUBBIES \t\t\t\t\t\t\n";
				cout << "\t\t\t\t\tGOMEZ, EDRA ABEL (LEAD PROGRAMMER)  \t\t\t\t\t\t\n";
				cout << "\t\t\t\t\tINES, WILLIAM (PROGRAMMER 1) \t\t\t\t\t\t\n";
				cout << "\t\t\t\t\tRAMOS, FRANCO GIAN (PROGRAMMER 2) \t\t\t\t\t\t\n";
				exit(0); // exits out of program
				break;
		default: // if input is invalid, loops back to main menu
				cout <<"Please enter a valid input..." << endl; 
				goto mainMenu;
				break;
	}
	customerMenu: // displays the customer menu
		delay(firstOpen);
		cout << "Customer Maintenance" << endl;
		cout << "[1] Add New Customer" << endl;
		cout << "[2] Show Customer Details" << endl;
		cout << "[3] Display All Customers" << endl;
		cout << "[4] List of Videos Rented by a Customer" << endl;		
		cout << "[5] Return to Main Menu" << endl;
		cout << "Enter choice: ";
		cin >> custOption;
		if(cin.fail()){ // checks if the input is a valid integer input
			cout << "Please enter a valid input..." << endl;
			//system("pause");
			cin.clear();
			cin.ignore(200, '\n');
			//system("cls");
			goto customerMenu;
		}
		switch(custOption){
			case 1:	
				cin.ignore(); // ignores newline 
				customerList.addCustomer(); //invokes addCustomer function to add a customer in the queue stl
				goto customerMenu; // loops back to customer menu
				break;
			case 2:
				cout << "Please enter customer ID: ";
				custID = customerList.intCheck();  // checks if entered ID is an integer
				customerList.showCustomerDetails(custID); // displays a customer detail specified by the user
				goto customerMenu; // loops back to customer menu
				break;
			case 3:
				customerList.printCustomerList(); // displays all customers in the queue stl
				goto customerMenu; // loops back to customer menu
				break;
			case 4: 
				cout << "Please enter customer ID: ";
				custID = customerList.intCheck();  // checks if entered ID is an integer
				customerList.showCustomerDetails(custID); // displays the detail of the customer specified by the user
				rentList.printAllRented(custID); // displays all the rented videos of the customer
				
				goto customerMenu; // loops back to customer menu
				break;
			case 5: // loops back to the main menu
				firstOpen = true;
				goto mainMenu;
				break;
			default: // if input is invalid, loops back to main menu
					cout <<"Please enter a valid input..." << endl;
					goto customerMenu; 
					break;
		}
		
	return 0;
}
