#pragma once
#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

template <class T>
class vector
{
public:
	explicit vector(int size);
	vector(const vector<T>& v);
	vector(vector<T>&&) = delete;
	vector(int size, T vlaue);
	vector(T* es, int len);
	vector& operator=(const vector<T>& v);
	vector& operator=(vector<T>&&) = delete;

	int size() const;
	int capacity() const;
	void reserve(int min_capacity);
	void push_back(T e);
	void pop_back();
	void erase(int pos);
	void insert(T e, int pos);

	const T& operator[](int) const;
	T& operator[](int);
	template <class Ty>
	friend ostream& operator<<(ostream& os, const vector<Ty>& v);
private:
	T* vec;
	int _size;
	int _capacity;
};

template <class T>
inline ostream& operator<<(ostream& os, const vector<T>& v)
{
	os << endl << "输出： " << endl;
	for (int i = 0; i < v._size; i++)
	{
		os << v.vec[i] << "  ";
	}
	return os;
}

template <class T>
inline vector<T>::vector(int size) : _size(size)
{
	_capacity = size + size / 3;
	this->vec = new T[_capacity];
	memset(this->vec, 0x00, sizeof(T) * _capacity);
}

template <class T>
inline vector<T>::vector(int size, T vlaue)
{
	this->_capacity = size + size / 3;
	this->_size = size;
	this->vec = new T[_capacity];
	for (int i = 0; i < _size; i++)
	{
		this->vec[i] = vlaue;
	}
}

template <class T>
inline vector<T>::vector(T* es, int len)
{
	this->_size = len;
	this->_capacity = len + len / 3;
	this->vec = new T[_capacity];
	memcpy_s(this->vec, len * sizeof(T), es, len * sizeof(T));
}

template <class T>
inline vector<T>::vector(const vector& v)
{
	this->_capacity = v._capacity;
	this->_size = v._size;
	this->vec = new T[_capacity];
	memcpy_s(this->vec, sizeof(T) * _capacity, v.vec, sizeof(T) * _capacity);
}

template <class T>
inline int vector<T>::size() const
{
	return this->_size;
}

template <class T>
inline int vector<T>::capacity() const
{
	return this->_capacity;
}

template <class T>
inline vector<T>& vector<T>::operator=(const vector<T>& v)
{
	if (this == &v)return *this;
	if (this->vec != nullptr)delete[] this->vec;
	this->_capacity = v._capacity;
	this->_size = v._size;
	this->vec = new T[_capacity];
	memcpy_s(this->vec, _capacity * sizeof(T), v.vec, v._capacity * sizeof(T));
	return *this;
}

template <class T>
inline void vector<T>::reserve(const int min_capacity)
{
	if (min_capacity < this->_capacity) return;
	else
	{
		int* n_vec = new T[min_capacity];
		for (int i = 0; i < _size; i++)
		{
			n_vec[i] = vec[i];
		}
		delete[] vec;
		this->vec = n_vec;
		this->_capacity = min_capacity;
	}
}

template <class T>
inline void vector<T>::push_back(T e)
{
	if (this->_size >= this->_capacity)
	{
		this->reserve(this->_size + this->_size / 3);
	}
	this->vec[_size++] = e;
}

template <class T>
inline void vector<T>::pop_back()
{
	if (this->_size != 0)
		this->_size -= 1;
}

template <class T>
inline void vector<T>::erase(int pos)
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

template <class T>
inline void vector<T>::insert(T e, int pos)
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

template <class T>
inline const T& vector<T>::operator[](int i) const
{
	if (i < 0 || i >= this->_size)
	{
		cout << "下标 i=" << i << " 越界 退出";
		exit(1);
	};
	return this->vec[i];
}

template <class T>
T& vector<T>::operator[](int pos)
{
	//这个写法的意思是 将指针this 转成 const 型指针 再对其*解引 
	//return const_cast<T&>((*static_cast<const vector<T>*>(this))[pos]);

	//这个是先对this 指针解引  再转成const 而且&直接引用该对象 
	return const_cast<T&>(static_cast<const vector<T>&>(*this)[pos]);

	//这个写法不不可取；先对this指针 解引，再转成const时 并不是&，所以会重新创建一个新对象
	//return const_cast<T&>(static_cast<const vector<T>>(*this)[pos]);
}
