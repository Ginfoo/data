#include <iostream>
#include "intset.h"
using namespace std;

void main2009();

int main()
{
	main2009();
	system("pause");
};
/*2009年上机题 实现下面功能*/
void main2009()
{
	IntSet s1, s2, s3, s4;
	int x;
	for (cin >> x; x != 0; cin >> x)
		s1.insert(x);//在 s1 中插入元素
	for (cin >> x; x != 0; cin >> x)
		s2.insert(x);//在 s2 中插入元素
	if (s1.IsEqual(s2))//比较 s1 与 s2 是否相等
		cout << " s1 is equal s2 ";
	s3 = s3.union2(s1, s2);//求 s1 与 s2 的交
	s4 = s4.incorporate2(s1, s2);//求 s1 与 s2 的并
	cout << "\ns1:";
	s1.print();//输出 s1 中的元素
	cout << "\ns2:";
	s2.print();
	cout << "\ns3:";
	s3.print();
	cout << "\ns4:";
	s4.print();
}
