/*
 * Jason Chen & Robert Bayer
 * COEN 70 Lab #3 // Tuesday 9:15 - 12:00
 * TA Patrick
 *
 * Filename: list.h
 * (Also need main2.cpp to run)
 *
 * Operator Overloading:
 * This file includes all our work for the lab: A class for a singly linked list including constructor, destructor, assignment operator, copy constructor, an insert function, an overload of the output, and a constructor for the node class.
 * */

#include <iostream>

using namespace std;

class List{
	public:
		// Function: Constructors 
		List();
		// Function: Destructor 
		~List();
		// Function: Copy constructor
		List(const List&);
		// Function: Assignment operator
 		const List& operator=(const List&);
 		// Function: output operator
		friend ostream& operator<<(ostream&, const List&); 
		// Function: Insert an item to the list
	 	// Postcondition: insert after the pointer and
 		// move the pointer to the new item
 		void insert(const int&);
 		class node {
			public:
				node(int n, node* p){
					//set variables in class equal to parameters
					data = n;
					next = p;
				}	
				int data;
  				node* next;
		};
	private:
		node* list;
		int size;
		node* cursor;
};

//Constructor
List::List(){
	//set pointers to NULL and size to 0
	list = NULL;
	size = 0;
	cursor = NULL;
}

//Destructor
List::~List(){
	//Using a temp node, traverse the list and deallocate individual pointers and decrement size.
	node* temp;
	while(list != NULL){
		temp = list;
		list = list->next;
		size--;
		delete[] temp;
	}
}

//Assignment operator
const List& List::operator=(const List& other){
	//self-check
	if(this == &other){
		return *this;
	}

	//declare temp var to use for deletion
	node* temp;
	
	//clear
	while(this->list != NULL)
	{
		//basically the destructor
		temp = this->list;
		this->list = this->list->next;
		this->size--;
		delete[] temp;
	}

	//set pointers to NULL and size to 0
	this->list = NULL;
	this->cursor = NULL;
	this->size = 0;

	//copy from other to this using "temp" as temporary pointer
	temp = other.list;
	while(temp != NULL)
	{
		this->insert(temp->data);
		temp = temp->next;
	}

	return *this;
}

//Copy Constructor
List::List(const List& other){
	this->list = NULL;
	this->cursor = NULL;
	//using assignment operator
	*this = other;
}

//Ostream Overload
ostream& operator <<(ostream& out, const List& l){
	//traverse list and output data from each node using temp node
	List::node* temp = l.list;
	while(temp != NULL){
		out << temp->data << ", ";
		temp = temp->next;
	}
	return out;
}

//insert function
void List::insert(const int& num){
	//Create a new node with data and next equal to NULL
	node* x = new node(num, NULL);
	
	//If first elem, head and tail point to x, increment size
	if(size == 0){
		this->list = this->cursor = x;
		this->size++;
	}
	//otherwise, place x in next position, move the tail pointer, and increment size
	else{
		this->cursor->next = x;
		this->cursor = this->cursor->next;
	   	this->size++;	
	}
	return;

}
