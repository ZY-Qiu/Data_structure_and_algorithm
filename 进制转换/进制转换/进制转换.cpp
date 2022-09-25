#include <iostream>
#include <vector>

using namespace std;

template<class T>
class stack: public vector<T>
{
public:
	T& top()
	{
		return (*this)[this->size() - 1];
	}
};

void convert(stack<char>& s, int n, int base)
{
	static char digit[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	while (n > 0)
	{
		s.push_back(digit[n % base]);
		n /= base;
	}
}

int main()
{
	stack<char> s;

	convert(s, 15, 2);

	while (s.size() > 0)
	{
		cout << s[s.size() - 1];
		s.pop_back();
	}
	cout << endl;

	system("pause");
	return 0;
}