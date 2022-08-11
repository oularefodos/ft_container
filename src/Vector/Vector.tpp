/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
template <typename T>
Vector<T>::Vector()
{
	this->sz = 0;
	this->cap = 0;
}

template <typename T>
Vector<T>::Vector(size_t _size)
{
	this->cap = _size;
	this->sz = _size;
	this->tab = new T[this->sz];
	bzero(this->tab, _size);
}

template <typename T>
Vector<T>::Vector(size_t _size, T const init)
{
	this->sz = _size;
	this->cap = this->sz;
	this->tab = new T[this->sz];
	for (int i = 0; i < _size; i++)
		this->tab[i] = init;
}

template <typename T>
Vector<T>::Vector(const Vector &src)
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
Vector<T>::~Vector()
{
	delete[] tab;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/
template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> const &rhs)
{
	this->cap = rhs.cap;
	this->sz = rhs.sz;
	this->tab = new T[this->size];
	for (int i = 0; i < this->size; i++)
		this->tab[i] = rhs.tab[i];
	return *this;
}

template <typename T>
T &Vector<T>::operator[](int const index)
{
	return this->tab[index];
}

/*
** --------------------------------- METHODS ----------------------------------
*/

template <typename T>
void Vector<T>::push_back(T const elm)
{
	if (this->sz < this->max_size())
	{
		if (this->cap == this->sz)
			this->tab_duplicate();
		this->tab[this->sz++] = elm;
	}
}

template <typename T>
void Vector<T>::pop_back(void)
{
	this->sz--;
}

template <typename T>
void Vector<T>::tab_duplicate()
{
	T *newTab;
	this->cap ? this->cap *= 2 : this->cap = 1;
	newTab = new T[this->sz];
	for (int i(0); i < this->sz / 2; i++)
		newTab[i] = this->tab[i];
	delete[] this->tab;
	this->tab = newTab;
}

template <typename T>
size_t Vector<T>::max_size() const
{
	std::allocator<T> m;
	return m.max_size();
}

template <typename T>
size_t Vector<T>::capacity() const
{
	return this->cap;
}

template <typename T>
size_t Vector<T>::size() const
{
	return this->sz;
}

template <typename T>
bool Vector<T>::empty() const
{
	return (this->size == 0);
}

template <typename T>
void Vector<T>::resize(int n, T const val)
{
	if (n > this->sz)
	{
		for (int i = n - this->sz; i > 0; i--)
			this->push_back(val);
	}
}

template <typename T>
T const Vector<T>::front(void) const
{
	return (tab[0]);
}

template <typename T>
T const Vector<T>::back(void) const
{
	return (tab[this->sz - 1]);
}

template <typename T>
void Vector<T>::shrink_to_fit(void)
{
	this->cap -= (this->cap - this->sz);
}

template <typename T>
T &Vector<T>::at(size_t index)
{
	return (this->tab[index]);
}

template <typename T>
T *Vector<T>::data(void) const
{
	return this->tab;
}

template <typename T>
void Vector<T>::reserve(size_t len)
{
	T *newTab;
	if (this->cap < len)
	{
		this->cap = len;
		newTab = new T[len];
		for (int i(0); i < this->sz; i++)
			newTab[i] = this->tab[i];
		delete[] this->tab;
		this->tab = newTab;
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */