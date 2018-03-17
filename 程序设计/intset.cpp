#include "intset.h"
#include <cstring>
#include <iostream>

IntSet::IntSet(): _size(0), _capacity(30)
{
	this->set = new int[_capacity];
	memset(this->set, 0x00, sizeof(int) * _capacity);
};

IntSet::~IntSet()
{
	if (this->set != nullptr)
		delete[] this->set;
}

bool IntSet::insert(const int x)
{
	if (this->find(x))return false;
	if (this->_size < this->_capacity)
	{
		this->set[_size++] = x;
	}
	else//空间不够用 重新分配
	{
		this->_capacity = _capacity * 2;
		int* tempSet = new int[_capacity];
		memcpy_s(tempSet, sizeof(int) * _size, this->set, sizeof(int) * _size);
		delete[] this->set;
		this->set = tempSet;
		this->set[_size++] = x;
	}
	return true;
}

bool IntSet::IsEqual(const IntSet& s)
{
	if (this->_size != s._size)return false;
	bool result = false;
	for (int i = 0; i < _size; i++)
	{
		result = this->find(s.set[i]);
		if (result == false)return false;
	}
	return true;
}

IntSet& IntSet::incorporate2(const IntSet& s1, const IntSet& s2)
{
	const int n_capacity = s1._size + s2._size;
	if (this->_capacity < n_capacity)
	{
		this->_capacity = n_capacity + n_capacity / 2;
		int* tempSet = new int[_capacity];
		delete[] this->set;
		this->set = tempSet;
	}
	memcpy_s(this->set, sizeof(int) * s1._size, s1.set, sizeof(int) * s1._size);
	this->_size = s1._size;
	for (int i = 0; i < s2._size; i++)
	{
		if (!this->find(s2.set[i]))
		{
			this->insert(s2.set[i]);
		}
	}

	return *this;
}

/*求交集*/
IntSet& IntSet::union2(const IntSet& s1, const IntSet& s2)
{
	if (this->_capacity < s1._capacity && this->_capacity < s2._capacity)
	{
		const int n_capacity = (s1._size > s2._size ? s1._size : s2._size);
		this->_capacity = n_capacity;
		delete[] this->set;
		int* tempSet = new int[_capacity];
		this->set = tempSet;
	}
	for (int i = 0; i < s1._size; i++)
	{
		if (s2.find(s1.set[i]))
		{
			this->insert(s1.set[i]);
		}
	}
	return *this;
}

void IntSet::print() const
{
	for (int i = 0; i < this->_size; i++)
	{
		std::cout << this->set[i] << " ";
	}
	std::cout << std::endl;
}

bool IntSet::find(const int x) const
{
	bool result = false;
	for (int i = 0; i < _size; i++)
	{
		if (this->set[i] == x)
		{
			result = true;
			return result;
		}
	}
	return result;
}
