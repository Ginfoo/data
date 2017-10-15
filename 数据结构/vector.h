#pragma once
#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

class vector
{
public:
	explicit vector(int size);
	vector(const vector& v);
	vector(vector&&) = delete;
	vector(int size, int vlaue);
	vector& operator=(const vector& v);
	vector& operator=(vector&&) = delete;

	int size() const;
	int capacity() const;
	void reserve(int min_capacity);
	friend ostream& operator<<(ostream&os, const vector& v);
private:
	int* vec;
	int _size;
	int _capacity;
};

inline ostream& operator<<(ostream& os, const vector& v)
{
	os<< endl << "Êä³ö£º " << endl;
	for (int i=0;i<v._size;i++)
	{
		os << v.vec[i] << "  ";
	}
	return os;
}

inline vector::vector(int size): _size(size)
{
	_capacity = size + size / 3;
	this->vec = new int[_capacity];
	memset(this->vec, 0x00, 4 * _capacity);
}

inline vector::vector(const vector& v)
{
	this->_capacity = v._capacity;
	this->_size = v._size;
	this->vec = new int[_capacity];
	memcpy_s(this->vec, 4 * _capacity, v.vec, 4 * _capacity);
}

inline vector::vector(int size, int vlaue)
{
	this->_capacity = size + size / 3;
	this->_size = size;
	this->vec = new int[_capacity];
	for(int i=0;i<_size;i++)
	{
		this->vec[i] = vlaue;
	}
}

inline vector& vector::operator=(const vector& v)
{
	if (this == &v)return *this;
	if (this->vec != nullptr)delete[] this->vec;
	this->_capacity = v._capacity;
	this->_size = v._size;
	memcpy_s(this->vec, _capacity * 4, v.vec, v._capacity * 4);
}

inline int vector::size() const
{
	return this->_size;
}

inline int vector::capacity() const
{
	return this->_capacity;
}

inline void vector::reserve(const int min_capacity)
{
	if (min_capacity < this->_capacity) return;
	else
	{
		int* n_vec = new int[min_capacity];
		for (int i = 0; i < _size; i++)
		{
			n_vec[i] = vec[i];
		}
		delete[] vec;
		this->_capacity = min_capacity;
	}
}
