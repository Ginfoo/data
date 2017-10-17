#pragma once
#include <stddef.h>
#include <ostream>

template <class T>
class queue
{
public:
	queue(int maxSize);
	queue(const queue& q);
	queue(queue&&) = delete;
	queue& operator=(const queue& q);
	queue& operator=(const queue&&) = delete;

	~queue();

	bool enQueue(const T x);//入队
	bool deQueue(T& x);//出队

	bool getFront(T& x) const;
	void makeEmpty();
	bool isEmpty() const;
	bool isFull() const;
	int getNumElems() const;
	template <class TT>
	friend std::ostream& operator<<(std::ostream& os, const queue<TT>& q);
private:
	int front, rear;
	T* elems;
	int maxSize;
};
