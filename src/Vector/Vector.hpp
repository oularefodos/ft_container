#ifndef vector_HPP
#define vector_HPP

#include <iostream>
#include <string>

namespace ft
{
	template <typename T>
	class vector
	{
	public:
		vector();
		vector(vector const &src);
		~vector();
		vector(size_t _size);
		vector(size_t _size, T const init);
		vector &operator=(vector const &rhs); // done
		T &operator[](int index);		  // done
		T &operator[](int index) const;		  // done
		void push_back(T const elm);		  // done
		size_t max_size() const;			  //....
		size_t capacity() const;			  // done
		size_t size() const;				  // done
		void pop_back();					  // .....
		bool empty() const;					  // done
		void shrink_to_fit(void);			  // done;
		void resize(size_t n, T const val);	  // done
		T &back(void) const;			  // done
		T &back(void);			  // done
		T &front(void) const;			  // done
		T &front(void);
		T &at(size_t index);				  // done
		T &at(size_t index) const;				  // done
		T *data(void) const;				  // done
		T *data(void) const;				  // done
		void reserve(size_t len);			  // done
		T *begin() const;
		T *end() const;
		void clear() const;

	private:
		T *tab;
		unsigned int sz;
		unsigned int cap;
		void tab_duplicate(size_t _size);
	};
};

#include "Vector.tpp"
#endif /* ********************************************************** vector_H */