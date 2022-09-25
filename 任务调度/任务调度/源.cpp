#include<iostream>
#include<cstring>

using namespace std;

#define taskNum 4000000
#define printNum 2000000
#define maxn 4294967295
#define Rank int
#define Parent(i)				((i - 1) >> 1)
#define ParentValid(i)			((i == 0) ? false : true)
#define LChild(i)				((i << 1) + 1)
#define RChild(i)				((i + 1) << 1)
#define InHeap(n, i)			(i > -1) && (i < n)
#define LChildValid(n, i)		InHeap(n, LChild(i))
#define RChildValid(n, i)		InHeap(n, RChild(i))
#define Bigger(PQ, i, j)		(PQ[i] > PQ[j]) ? j: i
#define PorperParent(PQ, n, i)  /*父子（至多）三者中的大者*/ \
								(RChildValid(n, i) ? Bigger(PQ, Bigger(PQ, i, LChild(i)), RChild(i)) : \
								(LChildValid(n, i) ? Bigger(PQ, i, LChild(i)) : i))
#define LastInternal(i)			((i >> 1) - 1)

int n, m;
struct Task
{
	long long int priority;
	char name[9];
	bool operator>(const Task& t) // 判断优先级更高，即数字更小，或ASCII顺序更小
	{
		if (priority == t.priority)
		{
			if (strcmp(name, t.name) < 0)
			{
				return false;
			}
			return true;
		}
		return priority > t.priority;
	}

}task[taskNum];

Rank percolateDown(Rank n, Rank i)
{
	Rank j;
	while (i != (j = PorperParent(task, n, i)))
	{
		swap(task[i], task[j]);
		i = j;
	}
	return i;
}

void heapify(Task* task, int n)
{
	for (int i = LastInternal(n); i >= 0; i--) // 自最后一个内部节点至根节点
	{
		percolateDown(n, i);
	}
}

Task delMax()
{
	Task maxElem = task[0];
	task[0] = task[n - 1];
	percolateDown(n - 1, 0);
	return maxElem;
}

Rank percolateUp(Rank i)
{
	while (ParentValid(i))
	{
		Rank j = Parent(i);
		if (task[i] > task[j]) break;
		swap(task[i], task[j]);
		i = j;
	}
	return i;
}

void insert(Task e)
{
	task[n - 1] = e;
	percolateUp(n - 1);
}







int main()
{

	scanf("%d %d", &n, &m);
	//cin >> n >> m;

	for (int i = 0; i < n; i++)
	{
		scanf("%lld %s", &(task[i].priority), &(task[i].name));
		//cin >> task[i].priority >> task[i].name;
	}

	heapify(task, n);

	for (int i = 0; (i < m) && (n > 0); i++)
	{
		Task max = delMax();
		printf("%s\n", max.name);
		//cout << max.name << endl;
		max.priority *= 2;
		if (max.priority > maxn)
		{
			n--;
			continue;
		}
		insert(max);
	}

	return 0;
}