#include <iostream>
#include <string>

using namespace std;

bool erase(string& s)
{
	char ch = s[0];
	int cnt = 1;
	for (int i = 1; i < s.size(); i++)
	{
		if (ch == s[i])
		{
			cnt++;
		}
		else
		{
			if (cnt >= 3)
			{
				s.erase(i - cnt, cnt);
				return true;
			}
			else
			{
				ch = s[i];
				cnt = 1;
			}
		}
	}
	if (cnt >= 3)
	{
		s.erase(s.size() - cnt, cnt);
	}
	return false;
}

int main()
{
	string str;
	getline(cin, str);  // 使用getline处理输入为空的状况
	int n;
	scanf("%d", &n);

	char a;
	int pos;
	
	for (int i = 0; i < n; i++)
	{
		scanf("%d %c", &pos, &a);
		str.insert(pos, 1, a);
		while (erase(str));
		if (str.size() == 0)
		{
			cout << "-" << endl;
		}
		else
		{
			cout << str << endl;
		}
	}

	//system("pause");
	return 0;
}