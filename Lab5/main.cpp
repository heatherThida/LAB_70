#include "orderedlist.h"

int main(){
	List x;
	OrderedList y;

	x.insert(5);
	x.insert(1);
	x.insert(3);

	cout << x << endl; //should print 5, 1, 3,
	x.replace(2, 6);
	cout << x << endl; //should print 5, 6, 3,
	x.insert(2);
	cout << x << endl; //should print 5, 6, 3, 2,

	y.insert(5);
	y.insert(1);
	y.insert(3);
	cout << y << endl; //should print 1, 3, 5,

	y.replace(2, 6);
	cout << y << endl; //should print 1, 5, 6,
	y.insert(2);
	cout << y << endl; //should print 1, 2, 5, 6,

	return 1;
}
