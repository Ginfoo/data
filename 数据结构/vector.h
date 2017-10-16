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
	void push_back(int e);
	void pop_back();
	void erase(int pos);
	void insert(int e, int pos);
	friend ostream& operator<<(ostream& os, const vector& v);
private:
	int* vec;
	int _size;
	int _capacity;
};

inline ostream& operator<<(ostream& os, const vector& v)
{
	os << endl << "Êä³ö£º " << endl;
	for (int i = 0; i < v._size; i++)
	{
		os << v.vec[i] << "  ";
	}
	return os;
}

vector::vector(int size) : _size(size)
{
	_capacity = size + size / 3;
	this->vec = new int[_capacity];
	memset(this->vec, 0x00, 4 * _capacity);
}

vector::vector(int size, int vlaue)
{
	this->_capacity = size + size / 3;
	this->_size = size;
	this->vec = new int[_capacity];
	for (int i = 0; i < _size; i++)
	{
		this->vec[i] = vlaue;
	}
}

vector::vector(const vector& v)
{
	this->_capacity = v._capacity;
	this->_size = v._size;
	this->vec = new int[_capacity];
	memcpy_s(this->vec, 4 * _capacity, v.vec, 4 * _capacity);
}

int vector::size() const
{
	return this->_size;
}

int vector::capacity() const
{
	return this->_capacity;
}

vector& vector::operator=(const vector& v)
{
	if (this == &v)return *this;
	if (this->vec != nullptr)delete[] this->vec;
	this->_capacity = v._capacity;
	this->_size = v._size;
	this->vec = new int[_capacity];
	memcpy_s(this->vec, _capacity * 4, v.vec, v._capacity * 4);
	return *this;
}

void vector::reserve(const int min_capacity)
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

void vector::push_back(int e)
{
	if (this->_size >= this->_capacity)
	{
		this->reserve(this->_size + this->_size / 3);
	}
	this->vec[_size++] = e;
}

void vector::pop_back()
{
	if (this->_size != 0)
		this->_size -= 1;
}

inline void vector::erase(int pos)
{
	if (pos < 0 || pos >= _size)return;
	else
	{
		for (int i = pos; i < _size - 1; i++)
		{
			this->vec[i] = this->vec[i + 1];
		}
		_size -= 1;
	}
}

inline void vector::insert(int e, int pos)
{
	if (pos < 0 || pos > _size - 1)return;
	if (this->_size >= this->_capacity)
	{
		this->reserve(this->_size + this->_size / 3);
	}
	for (int i = _size; i > pos; i++)
	{
		this->vec[i] = this->vec[i - 1];
	}
	this->vec[pos] = e;
}
