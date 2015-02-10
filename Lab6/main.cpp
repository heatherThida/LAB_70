#include <iostream>
#include "pair.h"
#include "map.h"
#include <list>

int main(){
	map<int, int> m;
	m.insert(1, 2);
	m.insert(3, 4);
	m.insert(5, 6);
	m.insert(1, 3);	//list already contains this key

	int i = m.value_of(3);
	cout << i << endl;

	m.remove_key(3);

	m.print();

	return 0;
}
