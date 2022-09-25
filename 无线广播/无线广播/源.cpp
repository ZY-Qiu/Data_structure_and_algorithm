#include<iostream>
#include<cstring>

using namespace std;

#define maxArrSize 10001
typedef enum { NONE, FM1, FM2 } VStatus;

struct List
{
	List* succ;
	int index;
	List() : succ(NULL), index(0) {};
};

struct adjList
{
	List* fst;
	VStatus status;
	adjList() : fst(NULL), status(NONE) {};

}adj[maxArrSize];

void add(int t1, int t2)
{
	List* temp = new List;
	temp->index = t1;
	temp->succ = adj[t2].fst;
	adj[t2].fst = temp;
}

int queue[maxArrSize];

void BFS(int v)
{
	int head = 0, tail = 0;
	adj[v].status = FM1;
	queue[tail++] = v;

	while (head != tail)
	{
		v = queue[head++];
		for (List* i = adj[v].fst; i != NULL; i = i->succ)
		{
			if (adj[i->index].status == NONE)
			{
				if (adj[v].status == FM1)
				{
					adj[i->index].status = FM2;
				}
				else
				{
					adj[i->index].status = FM1;
				}
				queue[tail++] = i->index;
			}
			else if (adj[i->index].status == adj[v].status)
			{
				cout << -1;
				return;
			}
		}
	}
	cout << 1;
	return;
}

int main()
{
	int n, m;
	cin >> n >> m;

	int *arr = new int[n+1];
	memset(arr, 0, sizeof(int)*(n+1));

	int t1, t2;
	for (int i = 0; i < m; i++)
	{
		cin >> t1 >> t2;

		add(t1, t2);
		add(t2, t1);

	}

	BFS(1);

	return 0;
}