#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP
#include "Iterator_node.hpp"
#include "Iterator_traits.hpp"
#include <vector>

#include <iterator>
namespace ft
{
    template <class Iterator>
    class reverse_iterator :
        public Iterator <typename ft::iterator_traits<Iterator>::iterator_category,
        typename ft::iterator_traits<Iterator>::value_type,
        typename ft::iterator_traits<Iterator>::difference_type,
        typename ft::iterator_traits<Iterator>::pointer,
        typename ft::iterator_traits<Iterator>::reference>
    {
    protected:
        Iterator iter;
    public:
        typedef typename Iterator                                           iterator_type;
        typedef typename ft::iterator_traits<Iterator>::iterator_category   iterator_category;
        typedef typename ft::iterator_traits<Iterator>::value_type          value_type;
        typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
        typedef typename ft::iterator_traits<Iterator>::pointer             pointer;
        typedef typename ft::iterator_traits<Iterator>::reference           reference;
        reverse_iterator() {};
        reverse_iterator (iterator_type it)
        {
            this->iter = it;
        }

        template <class Iter>  
        reverse_iterator (const reverse_iterator<Iter>& rev_it)
        {
            *this = rev_it;
            return (*this);
        }

        iterator_type base() const {
            return iter;
        }

        reverse_iterator operator- (difference_type n) const 
        {
            return reverse_iterator(iter + n);
        }

        reverse_iterator operator+ (difference_type n) const 
        {
            return reverse_iterator(iter - n);
        }

        reverse_iterator& operator--() {
            ++iter;
            return *this;
        }

        reverse_iterator  operator--(int)
        {
            reverse_iterator temp = *this;
            --(*this)
            return temp;
        }

        reverse_iterator& operator++() {
            --iter;
            return (*this);
        }

        reverse_iterator  operator++(int) {
            reverse_iterator temp = *this;
            ++(*this);
            return temp;
        }

        reverse_iterator& operator-= (difference_type n)
        {
            iter = iter + n;
            return (*this)
        }

        reverse_iterator& operator+= (difference_type n)
        {
            iter = iter - n;
            return (*this);
        }

        pointer operator->() const
        {
            return &(operator*());
        }

        reference operator[] (difference_type n) const
        {
            return base()[-n-1];
        }

        reference operator*() const {
            iterator_type temp(iter);
            return *(--temp);
        }

        template <class Iter>  
        reverse_iterator& operator= (const reverse_iterator<Iter>& rev_it)
        {
            iter = rev_it.iter;
            return (*this);
        }
    }

	template <class Iterator>  
    typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() - rhs.base());
    }

    template <class Iterator>  
    reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, 
        const reverse_iterator<Iterator>& rev_it)
    {
        return (rev_it + n);
    }

    template <class Iterator>  
    bool operator== (const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <class Iterator>  
    bool operator!= (const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <class Iterator>  
    bool operator< (const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <class Iterator>  
    bool operator<= (const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <class Iterator>  
    bool operator> (const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <class Iterator>  
    bool operator>= (const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() >= rhs.base());
    }
};

#endif