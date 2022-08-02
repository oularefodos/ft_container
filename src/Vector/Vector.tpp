/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
template <typename T>
Vector<T>::Vector()
{
	this->size = 0;
	this->tab = new T[0];
}

template <typename T>
Vector<T>::Vector(int _size)
{
	this->size = _size;
	this->tab = new T[this->size];
}

template <typename T>
Vector<T>::Vector(int _size, T const init)
{
	this->size = _size;
	this->tab = new T[this->size];
	for (int i = 0; i < _size; i++)
		this->tab[i] = init;
}

template <typename T>
Vector<T>::Vector( const Vector & src )
{
	this->size = src.size;
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
Vector<T> &Vector<T>::operator=( Vector<T> const & rhs )
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

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */