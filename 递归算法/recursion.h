#pragma once
#include <iostream>
using std::cout;
using std::endl;
/*
 * ����һ��
 *       �ƶ����� 0��ʾ���� 1��ʾ����
 *       00001111  �ƶ���  01010101
 *       Ҫ�����Ӹ���>=2N (N=4)
 *             ��ʼ״̬��������������������λ
 *             �ƶ�������������ͬʱ�ƶ����ƶ�����λ��
 */
inline void move(int n)// 2nΪ���ӵĸ���
{
	if(n==4)//�ݹ���ֹ����
	{
		cout << "4,5-->9,10\n";
		cout << "8,9-->4,5\n";
		cout << "2,3-->8,9\n";
		cout << "7,8-->2,3\n";
		cout << "1,2-->7,8\n";
	}else
	{
		//�ݹ�ǰ��
		cout << n << "," << n + 1 << "-->" << 2 * n + 1 << "," << 2 * n + 2 << endl;
		cout << 2 * n - 1 << "," << 2 * n << "-->" << n << "," << n + 1 << endl;
		//�ݹ�
		move(n - 1);
	}
}

/*
 * ��������
 *       ���̻���
 */
inline int z(int a,int b)//aΪ�� b Ϊ��
{
	if (a == b) return 1;//�ݹ���ֹ����
	else if(a<b)
	{
		b = b - a;//�ݹ�ǰ��
		return z(a, b) + 1;
	}else
	{
		a = a - b;//�ݹ�ǰ��
		return z(a, b) + 1;
	}
}
inline int z2(const int width,const int height)
{
	//�ݹ���ֹ����
	if (width == height)return 1;
	else
	{
		
		const int max = width > height ? width : height;
		const int min = width > height ? height : width;
		const int rem = max % min;
		if (rem == 0)return max / min;//�ݹ���ֹ����
		else
		{
			return z(min, rem) + max / min;
		}
	}
}
/*
 * ������
 *      �����Ȼ��
 *      2=1+1��
 *      3=1+1+1��
 *      3=1+2��
 *      4=1+1+1+1��
 *      4=1+1+2��
 *      4=1+3��
 *      4=2+2��
 *      
 */