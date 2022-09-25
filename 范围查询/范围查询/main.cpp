#include <iostream>
#include "array.hpp"
#include "binsearch.h"

using namespace std;

struct Range
{
	Range() {};
	Range(int l, int r)
	{
		left = l;
		right = r;
	}
	int left;
	int right;
};

void Print(Array<int>& p)
{
	for (int i = 0; i < p.size(); i++)
	{
		cout << p[i] << " ";
	}
	cout << endl;
}

void test()
{
	Array<int> arr(5);
	for (int i = 0; i < 5; i++)
	{
		arr.push_back(i+1);
	}
	Print(arr);
	while (1)
	{
		int a = 0;
		cin >> a;
		cout << search_in(arr, a) << endl;
	}
}

int main()
{
	//test();


	int n, m, cod, left, right;

	//cout << "输入点的总数n，查询的次数m\n" << endl;
	scanf_s("%d %d", &n, &m);
	//printf("n = %d, m = %d\n", n, m);

	Array<int> point(n);
	Array<Range> range(m);
	//cout << range.size();

	//cout << "输入各点的坐标\n" << endl;
	for(int i = 0; i < n; i++)
	{
		scanf_s("%d", &cod);
		point.push_back(cod);
	}
	for (int j = 0; j < m; j++)
	{
		//cout << "查询区间的左、右边界\n" << endl;
		scanf_s("%d %d", &left, &right);
		range.push_back(Range(left, right));
	}
	//cout << range.size();

	point.mergeSort(0, point.size());

	//Print(point);

	find_in(point, range);

	//system("pause");
	return 0;
}