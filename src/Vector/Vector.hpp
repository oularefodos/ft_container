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

	private:
		T *tab;
		int size;
};

#include "Vector.tpp"
#endif /* ********************************************************** VECTOR_H */