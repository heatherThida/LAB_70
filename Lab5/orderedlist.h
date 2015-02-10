/*
 * Jason Chen & Robert Bayer
 * COEN 70 Lab #5 // Tuesday 9:15 - 12:00
 * TA Patrick
 *
 * Filename: orderedlist.h
 * (Also need main.cpp to run)
 *
 * This file includes the List class and the OrderedList class, which is a derived class from the List class.
 * We created a new function, replace in the List class, and we overwrote the insert and replace functions in the OrderedList function.
 *
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
 		void replace(int, int);
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
	protected:
		node* list;
		int size;
		node* cursor;
};

class OrderedList: public List {
	public:
		OrderedList();
		~OrderedList();
		//re-implement the replace and insert function
		void replace(int, int);
		void insert(const int&);

		//add remove function
		void remove(node*);
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

OrderedList::OrderedList():List(){}
OrderedList::~OrderedList(){}

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

//replace function: replace the element at the specified position in the list with the specified element
//index value starts at 1 (NOT 0)
void List::replace(int index, int element){
	int i = 1;
	node* temp;
	//check to make sure specified index exists
	if(index <= size){
		temp = list;
		//move temp to index position (using i to count index of list)
		while(i != index){
			temp = temp->next;
			i++;
		}//at end of loop, temp is at position for replacement
		
		//over-write old data in List
		temp->data = element;
	}	
	else{
		//index doesn't exist, print error message and return
		cout << "The indicated index doesn't exist in the List." << endl;
		return;
	}
}

/* ORDERED LIST IMPLEMENTATION */

void OrderedList::insert(const int& num) {
	//temp pointer at head
	node* temp = list;

	//if list is empty
	if(size == 0){
		//create a new node
		node* x = new node(num, NULL);
		//update head and tail
		list = cursor = x;
		size++;
		return;
	}

	//loop until temp is either at the last node or the correct insertion point
	while((temp->next != NULL) && (temp->next->data < num)){
		temp = temp->next;	
	}

	if((temp == list) && (num <= temp->data)){
		//num goes before head and head resets if num is less than head->data
			
		//create a node with data and next is head
		node* x = new node(num, temp);
		//update head
		list = x;
		//increment size
		size++;
		return;
	}
	
	else if(temp == cursor){
		//create new node and put it after tail and update tail
		node* x = new node(num, NULL);
		//update temp->next
		temp->next = x;
		//update tail
		cursor = x;
		//increment size
		size++;
		return;
	}
	else{
		//create new node with next = temp->next
		node* x = new node(num, temp->next);
		//update temp->next
		temp->next = x;
		//increment size
		size++;
		return;

	}
}

void OrderedList::replace(int index, int element){
	int i = 1;
	node* temp;
	//check to make sure specified index exists
	if(index <= size){
		temp = list;
		//move temp to index position (using i to count index of list)
		while(i != index){
			temp = temp->next;
			i++;
		}//at end of loop, temp is at position for replacement

		//remove the current node
		remove(temp);

		//insert new element
		insert(element);
		
	}	
	else{
		//index doesn't exist, print error message and return
		cout << "The indicated index doesn't exist in the List." << endl;
		return;
	}

}	

void OrderedList::remove(node* temp){
	if(size == 0){
		cout << "There's nothing in the list to remove." << endl;
		return;
	}
	
	if(temp == list){
		list = temp->next;
		size--;
		delete temp;
	}
	else{
		node* pre = list;
		//pre is at the node before the temp at end of loop
		while(pre->next != temp)
			pre = pre->next;
		//update pre->next
		pre->next = temp->next;

		//update tail if necessary
		if(temp == cursor){
			cursor = pre;
		}

		//decrement size
		size--;
		//delete temp
		delete temp;
	}
}

