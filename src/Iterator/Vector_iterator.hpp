#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP
#include "Iterator_node.hpp"
#include "Iterator_traits.hpp"

template <class T>
class Vector_iterator : public Iterator<ft::random_access_iterator_tag, T>
{
    private:
        T *ptr;
    
    public:
        typedef T & reference;
        typedef ptrdiff_t difference_type;
		typedef T const & const_reference;
		typedef T * pointer;
		typedef T const * const_pointer;

    public:
        // constructor 

        Vector_iterator() : ptr(0) {}
        Vector_iterator(T * x)
        {
            ptr = x;
        }

        Vector_iterator(Vector_iterator const& rhs)
        {
            ptr = rhs.ptr;
        }

        // affectation
        
        Vector_iterator& operator=(T * rhs)
        {
            ptr = rhs;
            return *this;
        }

        Vector_iterator& operator=(const Vector_iterator& rhs)
        {
            ptr = rhs.ptr;
            return *this;
        }

        //Pointer like operators
        reference operator*() const {
            return *ptr;
        }

        pointer operator->() const
        {
            return ptr;
        }

        reference operator[](const int& rhs) const {
            return ptr[rhs];
        }

        // increment and decrement
        Vector_iterator& operator++()
        {
            return ++ptr, *this;
        }

        Vector_iterator& operator++(int)
        {
            Vector_iterator tmp(*this);
            ++ptr;
            return tmp;
        }

        Vector_iterator& operator--()
        {
            return --ptr, *this;
        }

        Vector_iterator& operator--(int)
        {
            Vector_iterator temp(*this);
            --ptr;
            return *this;
        }

        // Arthimetic

        Vector_iterator& operator+=(difference_type rhs)
        {
            ptr += rhs;
            return *this;
        }

        Vector_iterator& operator+(difference_type rhs)
        {
            return Vector_iterator(ptr + rhs);
        }

        // Vector_iterator& operator+(difference_type rhs, const Vector_iterator& lhs)
        // {
        //     return Vector_iterator(rhs + lhs.ptr);
        // }

        Vector_iterator& operator-=(const int& rhs)
        {
            ptr = ptr - rhs;
            return *this;
        }

        Vector_iterator& operator-(difference_type rhs) const
        {
            return Vector_iterator(ptr - rhs);
        }

        difference_type operator-(const Vector_iterator& rhs)
        {
            return ptr - rhs.ptr;
        }

        // Comparaison

        bool operator==(const Vector_iterator rhs) const {
            return ptr == rhs.ptr;
        }

        bool operator!=(const Vector_iterator rhs) const {
            return ptr != rhs.ptr;
        }

        bool operator>=(const Vector_iterator rhs) const {
            return ptr >= rhs.ptr;
        }

        bool operator<=(const Vector_iterator rhs) const {
            return ptr <= rhs.ptr;
        }

        bool operator<(const Vector_iterator rhs) const {
            return ptr < rhs.ptr;
        }

        bool operator>(const Vector_iterator rhs) const {
            return ptr > rhs.ptr;
        }
};

#endif