/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
template <typename T>
ft::vector<T>::vector()
{
	this->sz = 0;
	this->cap = 0;
}

template <typename T>
ft::vector<T>::vector(size_t _size)
{
	this->cap = _size;
	this->sz = _size;
	this->tab = new T[this->sz];
	bzero(this->tab, _size);
}

template <typename T>
ft::vector<T>::vector(size_t _size, T const init)
{
	this->sz = _size;
	this->cap = this->sz;
	this->tab = new T[this->sz];
	for (int i = 0; i < _size; i++)
		this->tab[i] = init;
}

template <typename T>
ft::vector<T>::vector(const vector &src)
{
	this->sz = src.sz;
	this->cap = this->sz;
	this->tab = new T[this->sz];
	for (int i = 0; i < this->sz; i++)
		this->tab[i] = src.tab[i];
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/
template <typename T>
ft::vector<T>::~vector()
{
	delete[] tab;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/
template <typename T>
ft::vector<T> &ft::vector<T>::operator=(vector<T> const &rhs)
{
	this->cap = rhs.cap;
	this->sz = rhs.sz;
	this->tab = new T[this->size];
	for (int i = 0; i < this->size; i++)
		this->tab[i] = rhs.tab[i];
	return *this;
}

template <typename T>
T &ft::vector<T>::operator[](int const index)
{
	return this->tab[index];
}

template <typename T>
T &ft::vector<T>::operator[](int const index) const
{
	return this->tab[index];
}

/*
** --------------------------------- METHODS ----------------------------------
*/



template <typename T>
void ft::vector<T>::push_back(T const elm)
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

template <typename T>
void ft::vector<T>::pop_back(void)
{
	this->sz--;
}

template <typename T>
void ft::vector<T>::tab_duplicate(size_t _size)
{
	T *newTab;
	newTab = new T[_size];
	for (int i(0); i < this->sz; i++)
		newTab[i] = this->tab[i];
	delete[] this->tab;
	this->tab = newTab;
}

template <typename T>
size_t ft::vector<T>::max_size() const
{
	std::allocator<T> m;
	return m.max_size();
}

template <typename T>
size_t ft::vector<T>::capacity() const
{
	return this->cap;
}

template <typename T>
size_t ft::vector<T>::size() const
{
	return this->sz;
}

template <typename T>
bool ft::vector<T>::empty() const
{
	return (this->size == 0);
}

template <typename T>
void ft::vector<T>::resize(size_t n, T const val)
{
	if (n > this->sz)
	{
		for (int i = n - this->sz; i > 0; i--)
			this->push_back(val);
	}
	else 
		this->sz = n;
}

template <typename T>
T& ft::vector<T>::front(void) const
{
	return (tab[0]);
}

template <typename T>
T& ft::vector<T>::front(void)
{
	return (tab[0]);
}

template <typename T>
T& ft::vector<T>::back(void) const
{
	return (tab[this->sz - 1]);
}

template <typename T>
T& ft::vector<T>::back(void)
{
	return (tab[this->sz - 1]);
}

template <typename T>
void ft::vector<T>::shrink_to_fit(void)
{
	this->cap -= (this->cap - this->sz);
	this->tab_duplicate(this->cap);
}

template <typename T>
T &ft::vector<T>::at(size_t index)
{
	if (this->sz <= index)
		throw std::out_of_range("out of range");
	return (this->tab[index]);
}

template <typename T>
T &ft::vector<T>::at(size_t index) const
{
	if (this->sz <= index)
		throw std::out_of_range("out of range");
	return (this->tab[index]);
}

template <typename T>
T *ft::vector<T>::data(void) const
{
	return this->tab;
}

template <typename T>
void ft::vector<T>::reserve(size_t len)
{
	T *newTab;
	if (this->cap < len)
	{
		this->cap = len;
		this->tab_duplicate(len);
	}
}

template <typename T>
T* ft::vector<T>::begin() const
{
	return &tab[0];
}

template <typename T>
T* ft::vector<T>::end() const
{
	return &tab[this->sz - 1];
}

template <typename T>
void ft::vector<T>::clear(void) const {
	this->sz = 0;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */

/**** capacities methods done ****/