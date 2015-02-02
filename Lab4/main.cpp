/*
 Jimmy Patel & Robert Bayer
 COEN 70 Lab - T 9:15 - 12:00
 TA Patrick
 
 Stack ADT with postfix test program (10 test cases in separate text file)
 
 */

#include "stack.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int main()
{
    //create stack
    Stack stack;
    
    //create a c++ string to read from input, a c str to store individual numbers, and pointer to a cstr (used to traverse converted c++ string)
    string line;
    char str[20];
    char *cstr;
    
    //operands and result of/for operations
    double operand1, operand2, result;
    //flag is used to designate when temp array's contents are not current
    bool flag = false;
    
    //ask user to input equation and read into c++ string
    cout<<"Enter the postfix eqn:"<<endl;
    getline(cin,line);
    
    //make a c string from the c++ string
    cstr = new char[line.length()+1];
    std::strcpy(cstr,line.c_str());
    
    //j variable tracks place in new array (str), i variable traverses input string (cstr)
    int j=0;
    for(int i=0;i<line.length();i++)
    {
        /*
         For following functions, basic form is to pop two doubles from the stack to use as operands, perform the operation, and push the result back to the stack
         */
        
        //if it's a minus sign and not supposed to be read as negative sign, do the operation
        if(cstr[i]=='-' && (cstr[i+1]==' ' || cstr[i+1]=='\0'))
        {
            operand1=stack.pop();
            operand2=stack.pop();
            result = operand2 - operand1;
            stack.push(result);
        }
        else if(cstr[i]=='+')
        {
            operand1=stack.pop();
            operand2=stack.pop();
            result = operand1+operand2;
            stack.push(result);
        }
        else if(cstr[i]=='*')
        {
            operand1=stack.pop();
            operand2=stack.pop();
            result = operand1*operand2;
            stack.push(result);
        }
        else if(cstr[i]=='/')
        {
            operand1=stack.pop();
            operand2=stack.pop();
            result = operand2/operand1;
            stack.push(result);
        }
        //while not empty space, copy character to temp array to separate numbers and set flag to true b/c we are inputting good data to temp array
        else if(cstr[i]!=' ')
        {
            str[j]=cstr[i];
            j++;
            flag=true;
        }
        //if there's a space and the array's data is good (flag), add the null after good data, push number to stack, reset j and flag
        else if(cstr[i]==' ' && flag==true)
        {
            str[j]='\0';
            stack.push(strtod(str,NULL));
            j=0;
            flag=false;
        }
    }
    
    //output the top of the stack, which is the result of the postfix equation
    cout<< stack.getTop() << endl;
    
	return 0;
}