#include <list>
#include <iostream>
#include "pair.h"
#include <assert.h>

using namespace std;

template<typename K, typename V>
class map
{
	public:
		/**
		 * Inserts a value into the map.
		 * @param key the key to insert @param value the value to insert
		 * */
		void insert(K key, V value); 
		/**
		Determines whether the map contains a given key.
		@param key the key to check for
		*/
		bool contains_key(K key);
		/**
		Retrieves the value of a given key. @param key the key to find
		@return the value
		*/
		V value_of(K key);
		/**
		 * Removes the key and value. @param key the key to find
		 * */
		void remove_key(K key);
		void print();
	private:
			list< Pair<K, V> > data;
};


template <typename K, typename V>
void map<K, V>::insert (K key, V value){
	//if the map already has a value with the same key, print error
	if (contains_key(key)){
		cout << "already contains." << endl;
		return;
	}
	//else, create a new pair and push the pair to the map's list
	else{
		Pair<K, V> p(key, value);
		data.push_back(p);
	}
}

template <typename K, typename V>
bool map<K, V>::contains_key(K key){
	typename::list<Pair<K, V> >::iterator it;
	//iterate through the list and if the key given matches, return true
	for (it = data.begin(); it != data.end(); it++){
		if (it->get_first() == key)
			return true;
	}
	return false;
}

template <typename K, typename V>
V map<K, V>::value_of(K key){
	
	assert(contains_key(key));

	typename::list<Pair <K, V> >::iterator it;
	
	//iterate through the list and if the key given matches, return the value of the key
	for (it = data.begin(); it != data.end(); it++){
		if (it->get_first() == key)
			return it->get_second();
	}
	//if it hasn't returned, the key isn't in the map
	cout << "not in map." << endl;
	return it->get_second();
}

template <typename K, typename V>
void map<K, V>::remove_key(K key){
	if (!contains_key(key))
		return;
	else{
		typename::list<Pair<K, V> >::iterator it;
		//iterate through the list and if the key matches, remove the key and value
		for (it = data.begin(); it != data.end(); it++){
			if (it->get_first() == key){
				it = data.erase(it);
				return;
			}
		}
	}
	return;
}

template <typename K, typename V>
void map<K, V>::print(){
	typename::list<Pair<K, V> >::iterator it;
	//print out all the keys and values in the list
	for (it = data.begin(); it != data.end(); it++){
		cout << it->get_first() << ", " << it->get_second() << endl;
	}
	return;
}
