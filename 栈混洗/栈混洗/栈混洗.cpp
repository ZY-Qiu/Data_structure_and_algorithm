#include <iostream>
#include <vector>
#include "array.hpp"
using namespace std;

void print(Array<int>& a)
{
	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}

bool stackPermutarion(Array<int>& a1, Array<int>& a2)
{
	Array<int> arr1, arr2;
	int index1, index2;

	for (int i = 0; i < a2.size(); i++)
	{
		index1 = a1.find(a2[i]);
		index2 = arr1.find(a2[i]);

		//cout << "a2[" << i << "] = " << a2[i] << endl;
		//cout << "index1 = " << index1 << ", a1.size() = " << a1.size() << endl;

		if (index1 != -1)
		{
			int s = a1.size();
			for (int j = 0; j < s - index1; j++)
			{
				arr1.push_back(a1.pop_back());
			}
			arr2.push_back(arr1.pop_back());
		}
		else if (index2 != -1)
		{
			if (index2 != arr1.size() - 1)
			{
				return false;
			}
			else
			{
				arr2.push_back(arr1.pop_back());
			}
		}
	}
	return true;
}


int main()
{
	Array<int> arr1;
	Array<int> arr2;
	
	cout << "输入个数" << endl;
	int n;
	cin >> n;

	int m;
	cout << "输入原栈， 底至顶" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> m;
		arr1.push_back(m);
	}
	cout << "输入后栈" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> m;
		arr2.push_back(m);
	}

	cout << stackPermutarion(arr1, arr2) << endl;

	system("pause");
	return 0;
}