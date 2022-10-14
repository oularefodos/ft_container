#ifndef vector_HPP
#define vector_HPP


#include <iostream>
#include <string>
#include <vector>
#include "../Iterator/Iterator_traits.hpp"
#include "../Iterator/Vector_iterator.hpp"
#include "../Iterator/reverse_iterator.hpp"

namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class vector
	{
		private:
			T *tab;
			Alloc alloc;
			size_t sz;
			unsigned int cap;
			void destroy_tab()
			{
				for (unsigned int i(0); i < sz; i++)
					alloc.destroy(&tab[i]);
				alloc.destroy(tab);
				alloc.deallocate(tab, sz);
			}
			void tab_duplicate(size_t _size)
			{
				T *newTab;
				newTab = alloc.allocate(_size);
				for (unsigned int i(0); i < this->sz; i++)
					alloc.construct(&newTab[i], tab[i]);
				destroy_tab();
				this->tab = newTab;
			}
		protected:
			typedef T value_type;
			typedef typename std::allocator<value_type> allocator_type;
			typedef typename allocator_type::reference reference;
			typedef Vector_iterator<value_type> iterator;
			typedef Vector_iterator<const value_type> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;
		public:

			// CONSTRUCTOR ---------------> DONE
			vector(const allocator_type& _alloc = allocator_type())
			{
				alloc = _alloc;
				this->sz = 0;
				this->cap = 0;
			}

			vector(vector const &src)
			{
				alloc = src.alloc;
				this->sz = src.sz;
				this->cap = this->sz;
				this->tab = alloc.allocate(sz);
				for (unsigned int i = 0; i < this->sz; i++)
					alloc.construct(&tab[i], src.tab[i]);
			}

			vector(size_type _size, const value_type& val = value_type(),
				 const allocator_type& _alloc = allocator_type())
			{
				alloc = _alloc;
				this->cap = _size;
				this->sz = _size;
				this->tab = alloc.allocate(sz);
				for (unsigned int i = 0; i < this->sz; i++)
					alloc.construct(&tab[i], val);
			}

			template <class inputIterator>
			vector(inputIterator& start, inputIterator const & end, \
				const allocator_type& _alloc = allocator_type())
			{
				unsigned int i;
				alloc = _alloc;
				this->sz = end - start;
				this->cap = this->sz;
				this->tab = alloc.allocate(this->sz);
				i = 0;
				while((start++ != end) && (i < sz))
					alloc.construct(&tab[i++], *start);
			}


			~vector()
			{
				destroy_tab();
			}

			vector &operator=(vector const &rhs)
			{
				this->alloc = rhs.alloc;
				this->cap = rhs.cap;
				this->sz = rhs.sz;
				this->tab = alloc.allocate(this->sz);
				for (unsigned int i = 0; i < this->size; i++)
					alloc.construct(&tab[i], rhs.tab[i]);
				return *this;
			}
			// MODIFIERS METHODS ------------> ! DONE
			void push_back(value_type elm)
			{
				if (this->sz < this->max_size())
				{
					if (this->cap == this->sz)
					{
						this->cap ? this->cap *= 2 : this->cap = 1;
						this->tab_duplicate(this->cap);
					}
					this->tab[this->sz++] = elm;
				}
			}

			void pop_back()
			{
				this->sz--;
			}

			template <class InputIterator>
  			void assign (InputIterator first, InputIterator last) {
				this->sz = last - first;
				int i;
				i = 0;
				if (this->sz > this->cap)
				{
					T *newTab;
					this->cap = this->sz;
					newTab = alloc.allocate(this->cap);
					while(first++ != last)
						alloc.construct(&newTab[i++], *first);
					destroy_tab();
					this->tab = newTab;
				}
				else {
					while(first++ != last)
						tab[i++] = *first;
				}
			}

			void assign (size_type n, const value_type& val) {
				this->sz = n;
				int i;
				i = 0;
				if (this->sz > this->cap)
				{
					T *newTab;
					this->cap = this->sz;
					newTab = alloc.allocate(this->cap);
					while(i < n)
						alloc.construct(&newTab[i++], val);
					destroy_tab();
					this->tab = newTab;
				}
				else {
					while(i < n)
						tab[i++] = val;
				}
			}

			iterator insert (iterator position, const value_type& val) {
				this->sz++;
				unsigned int y;
				y = 0;
				if (this->sz >= this->cap)
				{
					this->cap ? this->cap *= 2 : this->cap = 1;
					T *newTab;
					newTab = alloc.allocate(this->cap);
					for (unsigned int i(0); i < this->sz; i++)
					{
						if (iterator(tab + i) == position)
							alloc.construct(&newTab[i], val);
						else
							alloc.construct(&newTab[i], tab[y++]);
					}
					destroy_tab();
					this->tab = newTab;
				}
				else {
					y = position - iterator(tab);
					for(unsigned int i = sz - 1 - 1; i != y; i--)
						tab[i] = tab[i - 1];
					tab[y] = val;
				}
				return iterator(tab);
			}

			void insert (iterator position, size_type n, const value_type& val) {
				this->sz += n;
				unsigned int y;
				y = 0;
				if (this->sz >= this->cap)
				{
					while (this->sz >= this->cap)
						this->cap ? this->cap *= 2 : this->cap = 1;
					T *newTab;
					newTab = alloc.allocate(this->cap);
					for (unsigned int i(0); i < this->sz; i++)
					{
						if (iterator(tab + i) == position)
							while (i <= n)
								alloc.construct(&newTab[i++], val);
						alloc.construct(&newTab[i], tab[y++]);
					}
					destroy_tab();
					this->tab = newTab;
				}
				else {
					y = position - iterator(tab);
					for (unsigned int i = this->sz - n - 1; i >= y; i--)
						tab[i + n] = tab[i];
					while (n--)
						tab[y++] = val;
				}
			}

			template <class InputIterator>
    		void insert (iterator position, InputIterator& first, InputIterator last)
			{
				difference_type n = (last - first);
				this->sz += n;
				unsigned int y;
				y = 0;
				if (this->sz >= this->cap)
				{
					while (this->sz >= this->cap)
						this->cap ? this->cap *= 2 : this->cap = 1;
					T *newTab;
					newTab = alloc.allocate(this->cap);
					for (unsigned int i(0); i < this->sz; i++)
					{
						if (iterator(tab + i) == position)
						{
							while (i <= n) {
								alloc.construct(&newTab[i++], *first);
								first++;
							}
						}
						alloc.construct(&newTab[i], tab[y++]);
					}
					destroy_tab();
					this->tab = newTab;
				}
				else {
					y = position - iterator(tab);
					for (unsigned int i = this->sz - n - 1; i >= y; i--)
						tab[i + n] = tab[i];
					while (n--) {
						tab[y++] = *first;
						first++;
					}
				}
			}

			iterator erase (iterator position) {
				unsigned int index = position - begin();
				this->sz--;
				for (unsigned int i = index; i < sz; i++)
				{
					alloc.destroy(&tab[i]);
					alloc.construct(&tab[i], tab[i + 1]);
				}
			}

			iterator erase (iterator first, iterator last) {
				while (first != last)
					erase(first++);
			}

			void swap (vecteur& x) {
				vector n = x;
				x = *this;
				*this = n;
			}

			void clear() {
				for (unsigned int i = 0; i < this->sz; i++)
					alloc.destroy(&tab[i]);
				this->sz = 0;
			}

			// CAPACITY METHODS
			size_t max_size()
			{
				return alloc.max_size();
			}

			size_t capacity()
			{
				return this->cap;
			}

			size_t size() const
			{
				return this->sz;
			}

			bool empty() const
			{
				return (this->size == 0);
			}

			void reserve(size_t len)
			{
				T *newTab;
				if (this->cap < len)
				{
					this->cap = len;
					this->tab_duplicate(len);
				}
			}

			void shrink_to_fit(void)
			{
				this->cap -= (this->cap - this->sz);
				this->tab_duplicate(this->cap);
			}

			void resize(size_t n, T const val)
			{
				if (n > this->sz)
				{
					for (int i = n - this->sz; i > 0; i--)
						this->push_back(val);
				}
				else
					this->sz = n;
			}
			// ELEMENT ACCESS -------------> done
			const_reference back(void) const
			{
				return (tab[this->sz - 1]);
			}

			reference back(void)
			{
				return (tab[this->sz - 1]);
			}

			const_reference front(void) const
			{
				return (tab[0]);
			}

			reference front(void)
			{
				return (tab[0]);
			}

			reference at(size_t index)
			{
				if (this->sz <= index)
					throw std::out_of_range("out of range");
				return (this->tab[index]);
			}

			const_reference at(size_t index) const
			{
				if (this->sz <= index)
					throw std::out_of_range("out of range");
				return (this->tab[index]);
			}

			const_pointer data(void) const
			{
				return this->tab;
			}

			pointer data(void)
			{
				return this->tab;
			}

			reference operator[](int index)
			{
				return this->tab[index];
			}

			const_reference operator[](int index) const
			{
				return this->tab[index];
			}

			// ALLOCATOR ACCESS METHODS --------> DONE
			allocator_type get_allocator() const {
				return alloc;
			}

			// Iterators methods

			iterator begin() {
				return iterator(this->tab);
			}

			const_iterator begin() const {
				return const_iterator(this->tab);
			}

			iterator end() {
				return iterator(this->tab + this->sz);
			}

			const_iterator end() const {
				return const_iterator(this->tab + this->sz);
			}

			reverse_iterator rbegin() {
				return reverse_iterator(end() - 1);
			}

			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(end() - 1);
			}

			reverse_iterator rend() {
				return reverse_iterator(begin() - 1);
			}

			const_reverse_iterator rend() const {
				return const_reverse_iterator(begin() - 1);
			}

			// const_iterator cbegin() const noexcept {
			// 	return const_iterator(this->tab);
			// }

			// const_iterator cend() const noexcept {
			// 	return const_iterator(this->tab + this->sz);
			// }

			// const_reverse_iterator crbegin() const noexcept {
			// 	return const_reverse_iterator(cend() - 1);
			// }

			// const_reverse_iterator crend() const noexcept {
			// 	return const_reverse_iterator(cbegin() - 1);
			// }

	};

};
#endif /* ********************************************************** vector_H */