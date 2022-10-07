#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP
#include "Iterator_node.hpp"
#include "Iterator_traits.hpp"

template <class T>
class Vector_iterator : public Iterator<ft::random_access_iterator_tag, T>
{
    protected:
        T *ptr;
        typedef T & reference;
		typedef T const & const_reference;
		typedef T * pointer;
		typedef T const * const_pointer;

    public:
        Vector_iterator() {};
        Vector_iterator(T * x)
        {
            ptr = x;
        };

        Vector_iterator(Vector_iterator const& rhs)
        {
            ptr = rhs.ptr;
        };

        Vector_iterator& operator=(T * rhs)
        {
            ptr = rhs;
            return *this;
        };

        Vector_iterator& operator=(const Vector_iterator& rhs)
        {
            ptr = rhs.ptr;
            return *this;
        };

        Vector_iterator& operator+=(const int& rhs)
        {
            ptr = ptr + rhs;
            return *this;
        };

        Vector_iterator& operator-=(const int& rhs)
        {
            ptr = ptr - rhs;
            return *this;
        };

        reference operator*() {
            return *ptr;
        };

        pointer operator->()
        {
            return ptr;
        };

        reference operator[](const int& rhs) {
            return ptr[rhs];
        };

        Vector_iterator& operator++()
        {
            return ++ptr, *this;
        };

        Vector_iterator& operator++(int)
        {
            Vector_iterator tmp(*this);
            ++ptr;
            return tmp;
        };

        Vector_iterator& operator--()
        {
            return --ptr, *this;
        };

        Vector_iterator& operator--(int)
        {
            Vector_iterator temp(*this);
            --ptr;
            return *this;
        };

        difference_type operator-(const Vector_iterator& rhs)
        {
            return ptr - rhs.ptr;
        };
};

#endif