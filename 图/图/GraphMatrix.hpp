#pragma once
#include <iostream>
//#include "graph.hpp"
#include "VertexAndEdge.hpp"
#include "array.hpp"

using namespace std;


template<class Tv, class Te>
class GraphMatrix: public Graph<Tv, Te>
{
private:
	Array<Vertex<Tv> > V;  // ���㼯
	Array<Array<Edge<Te>* > > E;  //  �߼���Ҳ�����ڽӾ�������[]��E[i][j]���ɷ���i, j���һ����
	int n;  // ������
	int e;  // ����
public:
	GraphMatrix() { n = e = 0; }

	Tv& vertex(int i) { return V[i].data; }
	int inDegree(int i) { return V[i].inDegree; }
	int outDegree(int i) { return V[i].outDegree; }
	VStatus& status(int i) { return V[i].status; }
	int& dTime(int i) { return V[i].dTime; }
	int& fTime(int i) { return V[i].fTime; }
	int& parent(int i) { return V[i].parent; }
	int& priority(int i) { return V[i].priority; }

	int nextNbr(int i, int j);
	int firstNbr(int i);
	bool exists(int i, int j);
	Te edge(int i, int j);
	EStatus & status(int i, int j);
	int & weight(int i, int j);
	void insert(Te const& edge, int w, int i, int j);
	Te remove(int i, int j);

	int insert(Tv const& vertex);
	Tv remove(int i);

	void BFS(int v, int& clock);  // �����������
	void bfs(int s);  // ��������ͨ���ͼ��sΪ��ʼ���㣬�ں����л����BFS

	void DFS(int v, int& clock);  // �����������
	void dfs(int s);  // �������ɴ���sΪ��ʼ���㣬�ں����л����DFS

	~GraphMatrix();
};

template<class Tv, class Te>
int GraphMatrix<Tv, Te>::nextNbr(int i, int j)
{
	while (j > -1 && !this->exists(i, --j));
	return j;
}


template<class Tv, class Te>
int GraphMatrix<Tv, Te>::firstNbr(int i)
{
	return this->nextNbr(i, this->n);
}

template<class Tv, class Te>
bool GraphMatrix<Tv, Te>::exists(int i, int j)
{
	return (i >= 0) && (i < n) && (j >= 0) && (j < n) && E[i][j] != NULL;
}

template<class Tv, class Te>
Te GraphMatrix<Tv, Te>::edge(int i, int j)
{
	if (this->exists(i, j)) return E[i][j]->data;
	else
	{
		cout << "edge(): Edge does not exist!" << endl;
		exit(1);
	}
}

template<class Tv, class Te>
EStatus& GraphMatrix<Tv, Te>::status(int i, int j)
{
	if (this->exists(i, j)) return E[i][j]->status;
	else
	{
		cout << "edge(): Edge does not exist!" << endl;
		exit(1);
	}
}

template<class Tv, class Te>
int& GraphMatrix<Tv, Te>::weight(int i, int j)
{
	if (this->exists(i, j)) return E[i][j]->weight;
	else
	{
		cout << "edge(): Edge does not exist!" << endl;
		exit(1);
	}
}

template<class Tv, class Te>
void GraphMatrix<Tv, Te>::insert(Te const& edge, int w, int i, int j)
{
	if (this->exists(i, j)) return;
	E[i][j] = new Edge(edge, w);
	e++;
	V[i].outDegree++;
	V[j].inDegree++;
}

template<class Tv, class Te>
Te GraphMatrix<Tv, Te>::remove(int i, int j)
{
	if (!this->exists(i, j)) return;
	Te eBak = this->edge(i, j);
	delete this->E[i][j];
	this->E[i][j] = NULL;
	this->e--;
	this->V[i].outDegree--;
	this->V[j].inDegree--;
	return eBak
}


template<class Tv, class Te>
int GraphMatrix<Tv, Te>::insert(Tv const& vertex)
{
	for (int j = 0; j < this->n; j++)
	{
		this->E[j].insert(NULL);  // ��ÿһ�е�ĩβ����һ����λ��
	}
	this->n++;
	this->E.insert(vector<Edge<Te>* >(n, n, NULL));  // ���ڽӾ�����������µ�һ��
	return this->V.insert(Vertex<Tv>(vertex));  // �ڶ��㼯�����һ���¶���
}

template<class Tv, class Te>
Tv GraphMatrix<Tv, Te>::remove(int i)
{
	for (int j = 0; j < n; j++)
	{
		if (this->exists(i, j))
		{
			delete this->E[i][j];
			this->V[j].inDegree--;
		}
	}
	this->E.remove(i)  // ɾ��E�ĵ�i��
	this->n--;
	for (int j = 0; j < n; j++)
	{
		if (this->exists(j, i))
		{
			delete this->E[j].remove(i);
			this->V[j].outDegree--;
		}
	}
	Tv vBak = this->vertex(i);
	V.remove(i);
	return vBak;
}


template<class Tv, class Te>
void GraphMatrix<Tv, Te>::BFS(int v, int& clock)  // �ɶ���v��ʼ����
{
	Queue<int> Q;
	this->status(v) = DISCOVERED;
	Q.enqueue(v);
	while (!Q.is_empty())
	{
		v = Q.dequeue();
		this->dTime(v) = ++clock;
		for (int u = this->firstNbr(v); u > -1; u = this->nextNbr(v, u))
		{
			// ������Դ�����u
			if (this->status(u) == UNDISCOVERED)  // ����δ����
			{
				this->status(u) = DISCOVERED;  // ���ָö���
				Q.enqueue(u);
				this->status(v, u) = TREE;  // ��������
				this->parent(u) = v;
			}
			else  // ���Ѿ����ֻ��ѱ�����
			{
				this->status(v, u) = CROSS;  // ��(v, u)����Ϊ���
			}
		}
		this->status(v) = VISITED;
	}
}

template<class Tv, class Te>
void GraphMatrix<Tv, Te>::bfs(int s)  // �����ж����ͨ�򣬼�������ͨ
{
	this->reset();  // ��ʼ�� theta(n + e)
	int clock = 0, v = s;
	do
		if (this->status(v) == UNDISCOVERED)
		{
			this->BFS(v, clock);
		}
	while (s != (v = ++v % this->n));  // v��һ���ٶ�����ȡģ�����ж���s�Ƿ���ȣ���ȼ������������
}

template<class Tv, class Te>
void GraphMatrix<Tv, Te>::DFS(int v, int& clock)
{
	this->status(v) = DISCOVERED;
	this->dTime(v) = ++clock;
	for (int u = this->firstNbr(v); u > -1; u = this->nextNbr(v, u))  // ö��v���е��ھ�u
	{
		switch (this->status(u))
		{
		case UNDISCOVERED:
			this->status(v, u) = TREE;
			this->parent(u) = v;
			this->DFS(u, clock);  // �ݹ���������ھ�
			break;
		case DISCOVERED:  // �ѱ����֣�����δ������ϣ��Ǳ����ָ�������
			this->status(v, u) = BACKWORD;
			break;
		default:  // VISITED
			this->status(v, u) = ((this->dTime(v) < this->dTime(u)) ? FORWARD : CROSS);
			break;
		}
	}
	this->status(v) = VISITED;
	this->fTime(v) = ++clock;
}

template<class Tv, class Te>
void GraphMatrix<Tv, Te>::dfs(int s)
{
	this->reset();  // ��ʼ�� theta(n + e)
	int clock = 0, v = s;
	do
		if (this->status(v) == UNDISCOVERED)
		{
			this->DFS(v, clock);
		}
	while (s != (v = ++v % this->n));  // v��һ���ٶ�����ȡģ�����ж���s�Ƿ���ȣ���ȼ������������
}





template<class Tv, class Te>
GraphMatrix<Tv, Te>::~GraphMatrix()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			delete this->E[i][j];
		}
	}
}