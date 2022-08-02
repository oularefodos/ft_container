#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <string>

template <typename T>
class Vector
{
	public:
		Vector();
		Vector( Vector const & src );
		~Vector();
		Vector (int _size);
		Vector (int _size, T const init);
		Vector &	operator=( Vector const & rhs );
		void push_back(T const elm);
	private:
		T *tab;
		unsigned int size;
		unsigned int capacity;
		void tab_duplicate();
		int max_size;
};

#include "Vector.tpp"
#endif /* ********************************************************** VECTOR_H */