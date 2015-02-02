/*
 * Jackson Beadle & Robert Bayer
 * COEN 70 Lab #2 // Tuesday 9:15 - 12:00
 * TA Patrick
 *
 * Filename: complex.h
 * (Also need main2.cpp to run)
 *
 * Operator Overloading:
 * This file includes all our work for the lab: A class for complex numbers including operator functions, constructor, mutators, accessors, and i/o.
 * */
#include <iostream>

using namespace std;

class Complex {
	private:
		double a;
		double b;

	public:
		//constructor with default to 0
		Complex(double=0, double=0);

		//accessors
		double getA() const;
		double getB() const;

		//mutators
		void Re(double); 	//set a
		void Im(double);	//set b
};

//operator declarations
Complex operator+(const Complex& left, const Complex& right);
Complex operator*(const Complex& left, const Complex& right);

//input/output declarations
ostream& operator<<(ostream& out, const Complex& c);
istream& operator>>(istream& in, Complex& c);

/*
 * Constructor puts parameters into private variables a & b
 * Works with 0, 1, and 2 variable inputs
*/
Complex::Complex(double a, double b) {
	this->a = a;
	this->b = b;
}

/*
 * Accessor functions both return respective private variable, a or b
*/
double Complex::getA() const{
	return a;
}
double Complex::getB() const{
	return b;
}

/*
 * Mutator functions set respective private variables, a or b 
 * a and b AKA Real(Re) or Imaginary(Im)
 * */
void Complex::Re(double a) {
	this->a = a;
}
void Complex::Im(double b) {
	this->b = b;
}

/*
 * Plus sign operator overload allows addition of two Complex numbers
 * */
Complex operator+(const Complex& left, const Complex& right) {
	Complex x;
	x.Re(left.getA() + right.getA());
	x.Im(left.getB() + right.getB());
	
	return x;
}

/*
 * Star operator overload allows multiplication of two Complex numbers
 * */
Complex operator*(const Complex& left, const Complex& right) {
	Complex x;
	x.Re((left.getA() * right.getA()) - (left.getB() * right.getB()));
	x.Im((left.getA() * right.getB()) + (left.getB() * right.getA()));

	return x;
}

/*
 * Istream/Ostream overload operators take input and give output in imaginary form
 * Does not check for specific characters in input, just looks for form: double/char/double/char
 * */
ostream& operator<<(ostream& out, const Complex& c) {
	out << c.getA() << "+" << c.getB() << "i";
	return out;
}
istream& operator>>(istream& in, Complex& c) {
	double a, b;
	char s,t;

	in >> a >> s >> b >> t;
	c.Re(a);
	c.Im(b);

	return in;
}	
