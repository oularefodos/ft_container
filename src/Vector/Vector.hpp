#ifndef vector_HPP
#define vector_HPP

#include <iostream>
#include <string>

namespace ft
{
	template <typename T>
	class vector
	{
		private:
			T *tab;
			unsigned int sz;
			unsigned int cap;
			void tab_duplicate(size_t _size)
			{
				T *newTab;
				newTab = new T[_size];
				for (int i(0); i < this->sz; i++)
					newTab[i] = this->tab[i];
				delete[] this->tab;
				this->tab = newTab;
			}

		public:
			typedef T & reference;
			typedef T const & const_reference;
			typedef T * pointer;
			typedef T const * const_pointer;

			vector()
			{
				this->sz = 0;
				this->cap = 0;
			}

			vector(vector const &src)
			{
				this->sz = src.sz;
				this->cap = this->sz;
				this->tab = new T[this->sz];
				for (int i = 0; i < this->sz; i++)
					this->tab[i] = src.tab[i];
			}

			~vector()
			{
				delete[] tab;
			}

			vector(int _size)
			{
				this->cap = _size;
				this->sz = _size;
				this->tab = new T[this->sz];
				bzero(this->tab, _size);
			}

			vector(int _size, T const init)
			{
				this->sz = _size;
				this->cap = this->sz;
				this->tab = new T[this->sz];
				for (int i = 0; i < _size; i++)
					this->tab[i] = init;
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
				std::allocator<T> m;
				return m.max_size();
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

			pinter data(void)
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
			
			T *begin() const;
			T *end() const;
			void clear() const;
	};
};
#endif /* ********************************************************** vector_H */