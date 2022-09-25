#include<iostream>
#include<string.h>
#include<cmath>
using namespace std;

#define HASHSIZE 80003  // 40320

struct Map
{
	int* arr;
	int step;
	Map* succ;
	Map() : arr(NULL), step(0), succ(NULL) {};
}bucket[HASHSIZE];

void insert(int addr, int arr[], int step) // 头插法
{
	Map* t = new Map;
	t->arr = arr;  // 使用地址传递，已重载=号，创建新空间
	t->step = step;
	t->succ = bucket[addr].succ;
	bucket[addr].succ = t;
}

int merge(int arr[])
{
	int cnt = 0;
	for (int i = 7; i >= 0; i--)
	{
		cnt += arr[i] * pow(10, i);
	}
	return cnt;
}

int hashcode(int n)
{
	return (13 * n + 7) % HASHSIZE;
}


struct ArrofArr
{
	int* arr;
	int step;
	void func1()
	{
		for (int i = 0; i < 4; i++)
		{
			swap(arr[i], arr[7 - i]);
		}
		step++;
	}
	void func2()
	{
		int i = arr[3], j = arr[4];
		for (int k = 3; k > 0; k--)
		{
			arr[k] = arr[k - 1];
			arr[7 - k] = arr[8 - k];
		}
		arr[0] = i;
		arr[7] = j;
		step++;
	}
	void func3()
	{
		int i = arr[1];
		arr[1] = arr[6];
		arr[6] = arr[5];
		arr[5] = arr[2];
		arr[2] = i;
		step++;
	}
	ArrofArr() : arr(NULL), step(0) {};
	ArrofArr(int arr[], int step) : arr(arr), step(step) {};
	ArrofArr& operator=(const ArrofArr& a)
	{
		step = a.step;
		int* Arr = new int[8];
		for (int i = 0; i < 8; i++)
		{
			Arr[i] = a.arr[i];
		}
		arr = Arr;
		return *this;
	}

}queue[40321];

bool creatMap(int arr[], int step)
{
	int num = hashcode(merge(arr));
	Map* p = bucket[num].succ;
	while (p) // 当p存在
	{
		if (!memcmp(arr, p->arr, 32)) // 相同
		{
			return 1;
		}
		else  // 不相同
		{
			p = p->succ;
		}
	}
	// 不存在即插入
	insert(num, arr, step);
	return 0;
}

int first[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };

void bfs()
{
	int head = 0, tail = 0, step = 0;
	
	queue[tail++] = ArrofArr(first, step);
	creatMap(first, step);

	ArrofArr temp;
	while (head != tail)
	{
		head++;
		
		temp = queue[head-1];
		temp.func1();
		if (!creatMap(temp.arr, temp.step))
		{
			queue[tail++] = temp;
		}

		temp = queue[head - 1];
		temp.func2();
		if (!creatMap(temp.arr, temp.step))
		{
			queue[tail++] = temp;
		}

		temp = queue[head - 1];
		temp.func3();
		if (!creatMap(temp.arr, temp.step))
		{
			queue[tail++] = temp;
		}
	}
}

void printArr(int arr[])
{
	for (int i = 0; i < 8; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main()
{
	bfs();
	
	int arr[8], n;
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			scanf_s("%d", &arr[j]);
		}

		int addr = hashcode(merge(arr));
		Map* p = bucket[addr].succ;
		while (p)
		{
			if (!memcmp(arr, p->arr, 32))
			{
				printf("%d", p->step);
				break;
			}
			else
			{
				p = p->succ;
			}
		}
		if (!p) cout << -1 << endl;
	}

	return 0;
}