#COEN 70: Formal Specification and Advanced Data Structures
##Winter 2015 
##Lab 2: Operator Overloading

Write a class for complex numbers. A complex number has the form X=a + b*i, where a and b are real numbers and i is the square root of -1. We refer to a as the real part and b as the imaginary part of the number. The class should have two data members to represent the real and imaginary numbers; the constructor takes two arguments to set these members. Define the following operations, given X=a+b*i and Y=c+d*i:

- Re(X)=a
- Im(X)=b
- X+Y=(a+c)+(b+d)*i
- X*Y=(a*c-b*d)+(a*d+b*c)*i

Additionally, include all necessary methods such as default constructor, accessors, mutators, input/output.
