#COEN 70: Formal Specification and Advanced Data Structures
##Winter 2015 
##Lab 5: Ordered List ADT

Using the class List as the base class, we are going to derive the OrderedList class. Similar to the List ADT, the Ordered List ADT is a list that is always in order. For this lab, we will assume an ascending order and that the data are integers.

Starting with the implemented List class (of Lab 3):

- Add a replace(int index, int element) function, that replaces the element at the specified position in this list with the specified element, and
- change the access level of the private methods, so that members of the OrderedList class can access their member variables.

The OrderedList class will inherit from the modified List class. Add any needed functions and redefine the following functions: insert() and replace().

Include appropriate tests and submit both the super class List (modified) and the subclass OrderedList.
