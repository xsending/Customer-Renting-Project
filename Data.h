#pragma once
#include <stack>
#include <queue>
#include <fstream>
#include <list>


class MovieList{ //Linked List class used for storing video details 
	private:
		struct movieNode{//movie node
			int movieID;
			std::string movieTitle;
			std::string movieGenre;
			std::string movieProduction;
			int numOfCopies;
			movieNode *next;
		};
		std::fstream movieList; // for file manipulation
		movieNode *head;
		void addMovieNode(int ID, std::string title, std::string genre, std::string production, int numCopies); // utility function for storing videos in linked list
		std::string capitalize(char* str); // function to capitalize letters
		int generateID(std::string genre);	// generates random ID based on movie genre
	public:
		MovieList(); // class constructor			
		void insertVideo(); // main function for storing videos in linked list
		void rentVideo(int searchID); // function that lets a customer rent a video // decrements a video's number of copies
		void returnVideo(int searchID); // function that lets a customer return a video // increments a video's number of copies
		int displayVideo(); // function to display a video specified by the user
		void displayAll(); // displays all videos in the store
		bool checkVideo(int ID); // checks video availability
		void displayID(); // displays all video IDs stored in the linked list
		bool isEmpty();	// checks whether the linked list is empty
		int intCheck();	// evaluates if an input is an integer 
		void readFromFile(); // reads information from a file to be stored in the linked as the program starts
		void writeToFile(); // stores nodes into a file as the program ends
};

class Customer{ // class that uses queue stl for storing customer details
	protected:
		struct CustomerDetails { //customer structure containing customer details
			int customer_ID;
			std::string name;
			std::string address;
		};
		std::fstream customerList; // for file manipulation
		std::queue<CustomerDetails> customers; // stl queue to store customer details
	public:
		Customer(); // class constructor
		int intCheck(); // evaluates if an input is an integer 
		void addCustomer(); //adds customer details structure into the stl queue
		void addCustomer(int num, std::string name, std::string addr); // utility function that helps adding customer details from a file into the queue
		void showCustomerDetails(int input); // displays a customer's details specified by the user
		void printCustomerList(); // displays all customers' details
		bool isEmpty(); // checks whether the queue is empty or not in the main function
		bool exists(int input); // checks whether the customer exists in the queue or not
		void readFromFile(); // reads information from a file to be stored in the stl queue as the program starts
		void writeToFile(); // stores customer details structure into a file as the program ends
		
};

class CustomerRent{ // class that uses list and stack stl for storing customer ID and rented video IDs
	private:
		struct customerRent{ //customer structure containing customer ID and rented video IDs
			int customerID; 
			std::stack<int> rentedVideos;
		};
		std::fstream customerRentList; // for file manipulation
		std::list<customerRent> custRent; // list stl to store structure containing customer ID and rented video IDs
		std::list<customerRent>::iterator iter; // iterator for list stl
	public:
		CustomerRent(); // class constructor
		void rentVideo(int custID, int vidID); // function that lets a customer rent a video // creates a customer structure to be stored in the list
		void returnVideo(int custID, int& vidID); // function that lets a customer return a video // pops video IDs stored in stack within the customer structure
		void printAllRented(int custID); // displays all customer IDs and rented video IDs of the corresponding customers
		void readFromFile();// reads information from a file to be stored in the list and stack stl as the program starts
		void writeToFile();// stores customer-rent structure into a file as the program ends
		void addToList(int ID, std::stack<int> videos); //utility function that helps in adding a customer structure into the list
};


