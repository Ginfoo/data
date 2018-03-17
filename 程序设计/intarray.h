#pragma once
class IntArray
{
public:
	IntArray(int size);//初始化数组，长度为 size,且赋初值为 0
	~IntArray();
	int size() const;//返回数组长度
	int& Item(int i);//返回 i 下标的引用
	bool equal(IntArray& a);//长度和数据相等返回 True，否则 False
	void assign(IntArray& a);//将 a 中的数组赋值到 this 中，如果 a 长度大于 this 长度，这终止程序！
	void enlarge(int delta);//将 this 中的数组延长 Delta 个单位，并将这 Delta 个单位的数组	赋初值为 0
	void sort();//this 中的数组排序，从小到大
	void display();//打印数组
};
