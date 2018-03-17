#pragma once

class IntSet
{
public:
	IntSet();
	~IntSet();
	bool insert(const int x);
	bool IsEqual(const IntSet& s);
	IntSet& union2(const IntSet& s1, const IntSet& s2);
	IntSet& incorporate2(const IntSet& s1, const IntSet& s2);
	void print() const;
private:
	int* set;
	int _size;
	int _capacity;
	bool find(const int x) const;
};
