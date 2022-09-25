#include <iostream>
#include "List.hpp"
using namespace std;

void printList(List<int> &l)
{
	Posi(int) p = l.first();
	do
	{
		cout << p->data << " ";
	} 	while ((p = p->succ) != l.last()->succ);

	cout << endl;
}

void test()
{
	List<int> l;
	cout << "0: size = " << l.size() << ", expected 0." << endl;
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			l.insertAsLast(i);
		}
	}
	cout << "1: size = " << l.size() << ", expected 10." << endl;
	printList(l);
	l.deduplicate();
	cout << "2: size = " << l.size() << ", expected 5." << endl;
	printList(l);
	l.clear();
	cout << "3: size = " << l.size() << ", expected 0." << endl;
	//printList(l);
}

int main()
{
	test();

	system("pause");
	return 0;
}