// 12:53 PM/09/22/2017

#pragma warning(disable:4996)
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <Windows.h>
#include "heap.h"
#include <ctime>
using namespace std;
const int maxSize = 12;

void print(int* heap, int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << heap[i] << " ";
	}
	cout << endl;
}

int main()
{
	int heap[maxSize] = {0};
	srand(20);
	for (int i = 1; i < maxSize; i++)
	{
		heap[i] = (rand() % 100);
	}
	cout << "�������===========" << endl;
	print(heap, maxSize);

	make_heap(heap, 1, maxSize);
	cout << "����========" << endl;
	print(heap, maxSize);

	cout << "��������===" << endl;
	partial_sort(heap, 1, 6, maxSize);
	print(heap, maxSize);

	//���µ����ɶ�,�ٵ�������
	make_heap(heap, 1, maxSize);
	cout << "����Ϊ��===" << endl;
	print(heap, maxSize);
	sort_heap(heap, 1, maxSize);
	cout << "������====" << endl;
	print(heap, maxSize);
}
