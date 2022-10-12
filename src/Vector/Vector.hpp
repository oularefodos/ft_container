#ifndef vector_HPP
#define vector_HPP


#include <iostream>
#include <string>
#include <vector>
#include "../Iterator/Iterator_traits.hpp"
#include "../Iterator/Vector_iterator.hpp"

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
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;
		public:
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
			vector(inputIterator const & start, inputIterator const & end, \
				const allocator_type& _alloc = allocator_type())
			{
				unsigned int i;
				alloc = _alloc;
				this->sz = end - start;
				this->cap = this->sz;
				this->tab = alloc.allocate(this->sz);
				i = 0;
				while((start != end) && (i < sz))
					alloc.construct(&tab[i++], *start);
			}


			~vector()
			{
				destroy_tab();
			}

			vector &operator=(vector const &rhs)
			{
				this->cap = rhs.cap;
				this->sz = rhs.sz;
				this->tab = new T[this->size];
				for (int i = 0; i < this->size; i++)
					this->tab[i] = rhs.tab[i];
				return *this;
			}

			reference operator[](int index)
			{
				return this->tab[index];
			}

			const_reference operator[](int index) const
			{
				return this->tab[index];
			}

			void push_back(T const elm)
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

			void pop_back()
			{
				this->sz--;
			}

			bool empty() const
			{
				return (this->size == 0);
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

			void reserve(size_t len)
			{
				T *newTab;
				if (this->cap < len)
				{
					this->cap = len;
					this->tab_duplicate(len);
				}
			}
	};

};
#endif /* ********************************************************** vector_H */