#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;

#define HashSize 2000003

char str[600001][41];

struct Slot
{
	char* data;
	bool repeat;
	Slot() : data(NULL), repeat(false) {};
}bucket[HashSize];

bool trial(int addr, char* str) // 开放定址，双平方试探
{
	int cnt = 1, index = addr;
	
	while (bucket[index].data != NULL)
	{
		if (!strcmp(str, bucket[index].data)) // 找到重复
		{
			if (!bucket[index].repeat)
			{
				bucket[index].repeat = true;
				return 0;
			}
			else return 1;
		}
		else
		{
			index = int(addr + pow(ceil(cnt / 2), 2) * pow(-1, cnt) + HashSize) % HashSize;
		}
		cnt++;
	}
	// 插入
	bucket[index].data = str;
	return 1;
}

int HashCode(char* str)
{
	int h = 0;
	size_t n = strlen(str);
	for (int i = 0; i < n; i++)
	{
		h = abs((h << 5) | (h >> 27));
		h += (int)str[i];
	}
	return h;

	//int sum = 0, len = strlen(str);
	//for (int i = 0; i < len; i++)//多项式求和 
	//	sum += (i + 1) * (str[i] - 'a' + 1);
	//return sum;

}

int main()
{
	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		scanf("%s", str[i]);
		//cin >> str[i];

		int addr = HashCode(str[i]) % HashSize;

		if (!trial(addr, str[i]))
		{
			cout << str[i] << endl;
		}

	}

	return 0;
}