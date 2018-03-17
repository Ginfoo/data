#pragma once
#include <iostream>
using std::cout;
using std::endl;
/*
 * 案例一：
 *       移动棋子 0表示白子 1表示黑子
 *       00001111  移动成  01010101
 *       要求：棋子个数>=2N (N=4)
 *             初始状态在棋子最后面紧跟两个空位
 *             移动方法：两个子同时移动，移动到空位上
 */
inline void move(int n)// 2n为棋子的个数
{
	if(n==4)//递归终止条件
	{
		cout << "4,5-->9,10\n";
		cout << "8,9-->4,5\n";
		cout << "2,3-->8,9\n";
		cout << "7,8-->2,3\n";
		cout << "1,2-->7,8\n";
	}else
	{
		//递归前件
		cout << n << "," << n + 1 << "-->" << 2 * n + 1 << "," << 2 * n + 2 << endl;
		cout << 2 * n - 1 << "," << 2 * n << "-->" << n << "," << n + 1 << endl;
		//递归
		move(n - 1);
	}
}

/*
 * 案例二：
 *       地盘划分
 */
inline int z(int a,int b)//a为长 b 为宽
{
	if (a == b) return 1;//递归终止条件
	else if(a<b)
	{
		b = b - a;//递归前件
		return z(a, b) + 1;
	}else
	{
		a = a - b;//递归前件
		return z(a, b) + 1;
	}
}
inline int z2(const int width,const int height)
{
	//递归终止条件
	if (width == height)return 1;
	else
	{
		
		const int max = width > height ? width : height;
		const int min = width > height ? height : width;
		const int rem = max % min;
		if (rem == 0)return max / min;//递归终止条件
		else
		{
			return z(min, rem) + max / min;
		}
	}
}
/*
 * 案例二
 *      拆分自然数
 *      2=1+1；
 *      3=1+1+1；
 *      3=1+2；
 *      4=1+1+1+1；
 *      4=1+1+2；
 *      4=1+3；
 *      4=2+2；
 *      
 */