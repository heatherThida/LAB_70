#ifndef PAIR_H
#define PAIR_H

//stores heterogenous pairs, first field is of type T1 and second is of type T2, e.g. in (COEN70, 2014) the first is a string the second an int
template <class T1, class T2>
class Pair
{
	public: 
		//default constructor 
		Pair();
		//constructor with two parameters
		Pair(const T1& first_value, const T2& second_value);
		//mutator for first field
		void set_first(const T1& value);
		//mutator for second field
		void set_second(const T2& value);
		//accessor for first field
	    T1 get_first() const;
		//accessor for second field
		T2 get_second() const;
	private:
	//The value of the first field
	T1 first;   
	//The value of the second field
	T2 second;
};

template<class T1, class T2>
Pair<T1, T2>::Pair()
{
	//No body needed due to initialization above
}


template<class T1, class T2>
Pair<T1, T2>::Pair(const T1& first_value, const T2& second_value):first(first_value), second(second_value) 
{
	//No body needed due to initialization above
}

template<class T1, class T2>
void Pair<T1, T2>::set_first(const T1& value)
{
	first = value;
}

template<class T1, class T2>
void Pair<T1, T2>::set_second(const T2& value)
{
	second = value;
}

template<class T1, class T2>
T1 Pair<T1, T2>::get_first() const
{
	return first;
}

template<class T1, class T2>
T2 Pair<T1, T2>::get_second() const
{
	return second;
}

#endif
