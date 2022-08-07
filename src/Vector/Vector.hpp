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
		Vector (size_t _size);
		Vector (size_t _size, T const init);
		Vector &	operator=( Vector const & rhs ); //done
		T const operator[](int const index) const; // done
		void push_back(T const elm); // done
		size_t max_size() const;
		size_t capacity() const; //done
		size_t size() const; // done
		void pop_back(); // on yet
		bool empty() const; // done
		void resize(int n, T const val); // done
		T const back(void) const;
		T const front(void) const;
	private:
		T *tab;
		unsigned int sz;
		unsigned int cap;
		void tab_duplicate();
		
};

#include "Vector.tpp"
#endif /* ********************************************************** VECTOR_H */