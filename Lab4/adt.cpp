#include "stack.h"
#include <assert.h>

//Constructor
Stack::Stack()
{
	size=0;
	top = NULL;
}

//Constructors for the node
Stack::Node::Node(double d)
{
	number=d;
	next=NULL;
}
//Node constructor with next pointer
Stack::Node::Node(double d, Node *n)
{
	number=d;
	next=n;
}

//destructor
Stack::~Stack()
{
    //deallocate memory by popping each node, which deletes the nodes (top to bottom)
	while(size>0)
	{
		pop();
	}
}

//Copy Constructor
Stack::Stack(const Stack& og)
{
	size=0;
	top = NULL;
	//overrides the = operator
	*this = og;
}

//push
void Stack::push(double d)
{
    //create a new node with the next pointer to the current top, move top to new node, increment size
	Node *n = new Node(d,top);
	top = n;
	size++;
}

//pop
double Stack::pop()
{
    //assume there are nodes on the stack
    assert(size>0);
    double d;
    
    //set new node to the next of top (2nd node), save top data in temp double, move top to next (2nd node), decrement size, and return data stored from prev. top
	Node *n=top->next;
    d=top->number;
	delete top;
	top=n;
	size--;
    return d;
}

//top
double Stack::getTop() const
{
    //return the data from the top node
	assert(size>0);
	return top->number;
}

//overrides the =
const Stack& Stack::operator=(const Stack& right)
{
    //self-check
	if(this == &right) // checks if you set a=a
	{
		return *this;
	}
    //clear
	while(size>0) // deletes the left hand side if there was stuff in it
	{
		pop();
	}

    //asignment
	size=0;
	top = NULL;

	Node *ptr1 = right.top;
	Node *ptr2 = NULL;

	while(ptr1!=NULL)
	{
		if(ptr2==NULL)
		{
			ptr2 = new Node(ptr1->number);
			top=ptr2;
		}
		else
		{
			ptr2->next = new Node(ptr1->number);
			ptr2=ptr2->next;
		}
		ptr1=ptr1->next;
		size++;
	}
	return *this;
}

//overrides the outstream
ostream& operator<<(ostream &out, const Stack& s)
{
    //set temp var to top and traverse stack, outputting each node's data
	Stack::Node *n = s.top;
	while(n != NULL)
	{
		out<<n->number<<" ";
		n=n->next;
	}

	return out;
}

//return the size of the stack
int Stack::getSize()
{
    return size;
}




