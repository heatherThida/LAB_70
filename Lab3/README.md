#COEN 70: Formal Specification and Advanced Data Structures
##Winter 2015 
##Lab 3: List ADT with single linked list

We are going to implement the List ADT using the single linked list data structure. The node class will be implemented as an inner class of the List class. Here is the List class interface:

```C++
class List {
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
			node(int, node*); int data;
			node* next;
		}; 

	private:
		node* list;
		int size; 
		node* cursor;
};
```

You are to implement this interface and properly test it.
