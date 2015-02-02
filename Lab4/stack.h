#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

class Stack
{
public:
	class Node
	{
		public:
			double number;
			Node *next;

			//constructors for the nodes
			Node(double);
			Node(double, Node*);
	};

	Stack(); //constructor
	~Stack(); //destructor
	Stack(const Stack& og); //copy constructor
    int getSize();
	void push(double);
	double pop();
	double getTop() const;
	const Stack& operator=(const Stack& right);
    friend std::ostream& operator<<(std::ostream&, const Stack&);

	int size;
	Node *top;
};

#endif