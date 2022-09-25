#pragma once
#include <iostream>
using namespace std;
typedef int Rank;

// 二分查找
template<typename T>
int search_in(T& v, int val)
{
	Rank hi = v.size(), lo = 0;
	//cout << "hi = " << hi << ", lo = " << lo << endl;
	while (hi > lo)
	{
		Rank mi = (hi + lo) >> 1;
		(val < v[mi]) ? hi = mi : lo = mi + 1;
		//cout << "hi = " << hi << ", lo = " << lo << endl;
	}
	//cout << "-------------" << endl;
	return --lo;      // 注意！lo可能小于零！
}

template<typename T1, typename T2>
void find_in(T1& v, T2& r)
{
	int l_ind, r_ind;
	for (int i = 0; i < r.size(); i++)
	{
		//cout << "进入查找" << endl;
		if (v[v.size() - 1] < r[i].left || r[i].right < v[0])
		{
			printf("0\n");
		}
		else
		{
			l_ind = search_in(v, r[i].left);
			r_ind = search_in(v, r[i].right);
			//cout << "l_ind = " << l_ind << endl;
			//cout << "r_ind = " << r_ind << endl;
			if (v[l_ind] == r[i].left && l_ind >=0)  // 重要条件：l_ind >=0，否则l_ind可能为-1，发生越界
			{
				l_ind--;
			}
			printf("%d\n", r_ind - l_ind);
		}
		
	}
}