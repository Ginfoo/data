#pragma once
#include <iostream>

template <class T>
class stack
{
	template <class Ty>
	friend std::ostream& operator<<(std::ostream& os, const stack<Ty>& s);
public:
	explicit stack<T>(int maxSize);
	stack<T>(const stack<T>& s);
	stack<T>(stack<T>&&) = delete;
	stack<T>& operator=(const stack& s);
	stack<T>& operator=(stack<T>&&) = delete;
	~stack<T>();

	void push(T e);
	bool pop(T& e);
	bool getTop(T& e) const;

	bool isEmpty() const;
	int getNumElems() const;

private:
	T* elems;
	int top;
	int maxSize;
	void overflowProcess();
};

template <class T>
std::ostream& operator<<(std::ostream& os,const stack<T>& s)
{
	for (int i = 0; i <= s.top; i++)
	{
		std::cout << s.elems[i] << " ";
	}
	return os;
}

template <class T>
stack<T>::stack(int maxSize_): top(-1), maxSize(maxSize_)
{
	this->elems = new T[this->maxSize];
}

template <class T>
stack<T>::stack(const stack<T>& s)
{
	this->top = s.top;
	this->maxSize = s.maxSize;
	this->elems = new T[this->maxSize];
	memcpy_s(this->elems, sizeof(T) * maxSize, s.elems, sizeof(T) * maxSize);
}

template <class T>
stack<T>& stack<T>::operator=(const stack& s)
{
	if (this == &s) return *this;
	if (this->elems != nullptr)delete[] elems;
	this->top = s.top;
	this->maxSize = s.maxSize;
	this->elems = new T[maxSize];
	memcpy_s(this->elems, sizeof(T) * maxSize, s.elems, sizeof(T) * maxSize);
	return *this;
}

template <class T>
stack<T>::~stack()
{
	if (this->elems != nullptr)
		delete[] elems;
}

template <class T>
void stack<T>::push(T e)
{
	if (this->top == maxSize - 1)
	{
		overflowProcess();
	}
	this->elems[++top] = e;
}

template <class T>
bool stack<T>::pop(T& e)
{
	if (!isEmpty())
	{
		e = this->elems[top--];
		return true;
	}
	return false;
}

template <class T>
bool stack<T>::getTop(T& e) const
{
	if (!isEmpty())
	{
		e = elems[top];
		return true;
	}
	return false;
}

template <class T>
bool stack<T>::isEmpty() const
{
	return top == -1 ? true : false;
}

template <class T>
int stack<T>::getNumElems() const
{
	return top + 1;
}

template <class T>
void stack<T>::overflowProcess()
{
	T* new_elems = new T[maxSize + maxSize / 3];
	memcpy_s(new_elems, sizeof(T) * maxSize, this->elems, sizeof(T) * maxSize);
	delete[] elems;
	this->elems = new_elems;
}
