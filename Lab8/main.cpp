/*
 * Gus Boling & Robert Bayer
 * COEN 70 Lab #8 // Tuesday 9:15 - 12:00
 * TA Patrick
 *
 * Filename: main.cpp
 *
 *
 * Expression Tree Lab
 * */

#include <iostream>
#include <stack>
#include <cassert>
#include <cstdlib>
#include <string>

using namespace std;

//node class with separate variables for int and char (operator and operand)
class node {
	public:
		int operandData;
		char operatorData;
		
		node* lc;
		node* rc;

		node(int nD, char cD = '\0', node* left = NULL, node* right = NULL){
			operandData = nD;
			operatorData = cD;

			lc = left;
			rc = right;
		}

};

//Expression class, which contains a stack of pointers to nodes
//at end of build, should just be 1 item in stack
class Expression{
	private:
		stack<node*> tree;

	public:
		Expression();
		~Expression();

		void build(string s);
		int evaluate(node* root);
		
		void print_preorder(node* subtree);
		void print_inorder(node* subtree);
		void print_postorder(node* subtree);

		node* getRoot();
        void pass2build(string input);
};

Expression::Expression(){
	//construct here
}

Expression::~Expression(){
	//destruct here
}

//take line of user input and pass to build function
void Expression::pass2build(string input){
    int start = 0;
    for(int i = 0; i < input.length(); i++){
        if(input[i] == ' '){
            string temp = input.substr(start, i-start);
            this->build(temp);
            start = i+1;
        }
    }
    return;
}

//given a string of user input, build an Expression tree
void Expression::build(string s){
	//set c to be first character in the string, s
	char c = s[0];
	char d = s[1];

	//check and see if the input is an operator, making sure to avoid the case where negative numbers can be misinterpreted as operators
	if((c == '+' || c == '-' || c == '*' || c == '/') && !(c == '-' && isdigit(d))){
		char ch = s[0];
		node* rc = tree.top();
		tree.pop();
		node* lc = tree.top();
		tree.pop();
		//pass a 0 as a placeholder for integer
		node* newTree = new node(0, ch, lc, rc);
		tree.push(newTree);
	}
	//else, it must be a number
	else{
		char* cstr = new char[s.length()+1];
		strcpy(cstr, s.c_str());
		int num = atoi(cstr);
		node* temp = new node(num, '\0', NULL, NULL);
		tree.push(temp);
	}
}

//assume root points to nonempty expression tree to begin
int Expression::evaluate(node* root){
	//base case of recursion
	if((root->lc == NULL) && (root->rc == NULL)){
		return root->operandData;
	}
	
	int leftOperand = evaluate(root->lc);
	int rightOperand = evaluate(root->rc);

	char c = root->operatorData;
	if(c == '+')
		return leftOperand + rightOperand;
	else if(c == '-')
		return leftOperand - rightOperand;
	else if(c == '*')
		return leftOperand * rightOperand;
	else if(c == '/')
		return leftOperand / rightOperand;

	//may reach end of non-void function.. but that'd be an error, so hopefully this will never evaluate
    return -5;
}

//returns root for use in beginning the evaluate function
node* Expression::getRoot(){
	node* temp = tree.top();
	return temp;
}

//Print the expression in order
void Expression::print_inorder(node* subtree){
    if(subtree->rc==NULL && subtree->lc==NULL){
        cout<<subtree->operandData;
        return;
    }
    
    print_inorder(subtree->lc);
    cout<<subtree->operatorData;
    print_inorder(subtree->rc);
}

//Print expression in preorder
void Expression::print_preorder(node* subtree){
    if(subtree->rc==NULL && subtree->lc==NULL){
        cout<<subtree->operandData;
        return;
    }
    
    cout<<subtree->operatorData;
    print_preorder(subtree->lc);
    print_preorder(subtree->rc);
}

//Print expression in postorder
void Expression::print_postorder(node* subtree){
    if(subtree->rc==NULL && subtree->lc == NULL){
        cout<<subtree->operandData;
        return;
    }
    
    print_postorder(subtree->lc);
    print_postorder(subtree->rc);
    cout<<subtree->operatorData;
}

int main(){
    
    cout << "Enter a valid postfix expression with a space after the last character (operator)." << endl;
    //get user input
    string input;
    getline(cin, input);
    //create Expression and pass user input to be built
    Expression e;
    e.pass2build(input);
    
    //print in order, post order, pre order, and evaluate.
	node* top = e.getRoot();
    e.print_inorder(top);
    cout << endl;
    e.print_postorder(top);
    cout << endl;
    e.print_preorder(top);
    cout << endl;
	int answer = e.evaluate(top);
    

	cout << "That tree evaluates to: " << answer << endl;
	
	return 0;
}
