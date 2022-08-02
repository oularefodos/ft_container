/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
template <typename T>
Vector<T>::Vector()
{
	this->max_size = 1000000;
	this->size = 1;
	this->capacity = this->size;
	this->tab = new T[1];
}

template <typename T>
Vector<T>::Vector(int _size)
{
	this->max_size = 1000000;
	this->size = _size;
	this->capacity = this->size;
	this->tab = new T[this->size];
}

template <typename T>
Vector<T>::Vector(int _size, T const init)
{
	this->max_size = 1000000;
	this->size = _size;
	this->capacity = this->size;
	this->tab = new T[this->size];
	for (int i = 0; i < _size; i++)
		this->tab[i] = init;
}

template <typename T>
Vector<T>::Vector(const Vector &src)
{
	this->max_size = 1000000;
	this->size = src.size;
	this->capacity = this->size;
	this->tab = new T[this->size];
	for (int i = 0; i < this->size; i++)
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
	this->size = rhs.size;
	this->tab = new T[this->size];
	for (int i = 0; i < this->size; i++)
		this->tab[i] = rhs.tab[i];
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

template <typename T>
void Vector<T>::push_back(T const elm)
{
	if (this->size < this->max_size)
	{
		if (this->capacity == size)
			this->tab_duplicate();
		this->tab[this->capacity++] = elm;
	}
}

template <typename T>
void Vector<T>::tab_duplicate()
{
	T *newTab;
	this->size *= 2;
	newTab = new T[this->size];
	for (int i(0); i < this->size / 2; i++)
		newTab[i] = this->tab[i];
	delete[] this->tab;
	this->tab = newTab;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */