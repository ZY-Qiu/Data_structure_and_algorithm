#include <iostream>
#include <cstring>
using namespace std;










#define Posi(T) ListNode<T>*

template<typename T>
struct ListNode
{
	T data;
	Posi(T) pred;
	Posi(T) succ;
	ListNode() {};
	ListNode(T e, Posi(T) p = NULL, Posi(T) s = NULL) : data(e), pred(p), succ(s) {}  // ��ʼ���б�
	Posi(T) insertAsPred(T const& e);
	Posi(T) insertAsSucc(T const& e);
};

template<typename T>
Posi(T) ListNode<T>::insertAsPred(T const& e)
{
	Posi(T) x = new ListNode<T>(e, this->pred, this);
	this->pred->succ = x;
	this->pred = x;
	return x;
}

template<typename T>
Posi(T) ListNode<T>::insertAsSucc(T const& e)
{
	Posi(T) x = new ListNode<T>(e, this, this->succ);
	this->succ->pred = x;
	this->succ = x;
	return x;
}













template<class T>
class List
{
private:
	int _size;
	Posi(T) header;
	Posi(T) trailer;
protected:
	void init();
public:
	List();
	List(Posi(T) p, int n);
	bool is_empty();
	int size();
	Posi(T) first();
	Posi(T) last();
	T operator[](int r) const;  // ���Է���������
	Posi(T) find(T const& e, int n, Posi(T) p) const;
	Posi(T) find(T const& e, Posi(T) p, int n) const;
	Posi(T) insertBefore(T const& e, Posi(T) p);
	Posi(T) insertAfter(T const& e, Posi(T) p);
	Posi(T) insertAsFirst(T const& e);
	Posi(T) insertAsLast(T const& e);
	T remove(Posi(T) p);
	int deduplicate();
	int uniquify();
	Posi(T) search(T const& e, int n, Posi(T) p) const;
	int clear();
	~List();
};

template<class T>
void List<T>::init()  // ��ʼ������
{
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->pred = NULL;
	header->succ = trailer;
	trailer->pred = header;
	trailer->succ = NULL;
	_size = 0;
}

template<class T>
List<T>::List() // ���캯��
{
	this->init();
}

template<class T>
List<T>::List(Posi(T) p, int n)  // �������캯��
{
	this->init();
	while (n--)
	{
		this->insertAsLast(p->data);
		p = p->succ;
	}
}

template<class T>
bool List<T>::is_empty()
{
	return this->_size == 0;
}

template<class T>
int List<T>::size()
{
	return this->_size;
}

template<class T>
Posi(T) List<T>::first()
{
	if (this->is_empty())
	{
		return NULL;
		//cout << "first(): List is empty!" << endl;
		//exit(1);
	}
	return this->header->succ;
}

template<class T>
Posi(T) List<T>::last()
{
	if (this->is_empty())
	{
		cout << "first(): List is empty!" << endl;
		exit(1);
	}
	return this->trailer->pred;
}

template<class T>
T List<T>::operator[](int r) const
{
	if (r > this->size() - 1)
	{
		cout << "operator[](): Index out of range!" << endl;
		exit(1);
	}
	Posi(T) p = this->first();
	while (0 < r--) p = p->succ;
	return p->data;
}

template<class T>
Posi(T) List<T>::find(T const& e, int n, Posi(T) p) const  // ��P��n����ǰ���У��ҵ�ֵ����e�������
{
	while (0 < n--)
	{
		if (e == (p = p->pred)->data) return p;
	}
	return NULL;
}

template<class T>
Posi(T) List<T>::find(T const& e, Posi(T) p, int n) const  // // ��P��n�������У��ҵ�ֵ����e����ǰ��
{
	while (0 < n--)
	{
		if (e == (p = p->succ)->data) return p;
	}
	return NULL;
}

template<class T>
Posi(T) List<T>::insertBefore(T const& e, Posi(T) p)
{
	this->_size++;
	return p->insertAsPred(e);
}

template<class T>
Posi(T) List<T>::insertAfter(T const& e, Posi(T) p)
{
	this->_size++;
	return p->insertAsSucc(e);
}

template<class T>
Posi(T) List<T>::insertAsFirst(T const& e)
{
	return this->insertAfter(e, this->header);
}

template<class T>
Posi(T) List<T>::insertAsLast(T const& e)
{
	return this->insertBefore(e, this->trailer);
}

template<class T>
T List<T>::remove(Posi(T) p)
{
	if (this->size() == 0)
	{
		cout << "remove(): List is empty!" << endl;
		exit(1);
	}
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	this->_size--;
	return e;
}

template<class T>
int List<T>::deduplicate()  // ɾ�������б��е��ظ��ڵ�, ���Ӷ�O(n^2)
{
	if (this->size() < 2) return 0;
	int oldSize = this->size();
	Posi(T) p = this->first();
	int rank = 1;
	while (this->trailer != (p = p->succ))
	{
		Posi(T) q = this->find(p->data, rank, p);
		q ? this->remove(q) : rank++;
	}
	return oldSize - this->size();
}

template<class T>
int List<T>::uniquify()  // ɾ�������б��е��ظ��ڵ�, ���Ӷ�O(n)
{
	if (this->size() < 2) return 0;
	int oldSize = this->size();
	Posi(T) p = this->first();
	Posi(T) q;
	while (this->trailer != (q = p->succ))
	{
		if (p->data == q->data) this->remove(q);
		else p = q;
	}
	return oldSize - this->size();
}

template<class T>
Posi(T) List<T>::search(T const& e, int n, Posi(T) p) const  // �������б���P��n����ǰ���У��ҳ�������e�������
{
	while (0 < n--)
	{
		if (((p = p->pred)->data) <= e) break;
	}
	return p;
}



template<class T>
int List<T>::clear()
{
	int oldSize = this->size();
	while (this->size() > 0)
	{
		this->remove(this->header->succ);
	}
	return oldSize;
}

template<class T>
List<T>::~List()
{
	this->clear();
	delete this->header;
	delete this->trailer;
}













int m, n, u, v;
int* village_value;
int* firstNbr;
int* nextNbr;
bool* visited;
List<int>* list;

//int nextNbr(int i, int j)
//{
//	while (j > 0 && !matrix[i][--j]);  // 1-n�Ŵ�ׯ
//	return j;
//}
//
//int firstNbr(int i)
//{
//	return nextNbr(i, n + 1);
//}

void DFS(int village)
{
	visited[village] = true;
	for(ListNode<int>*l = list[village].first(); l && l->succ; l = l->succ)
	{
		if (!visited[l->data])
		{
			DFS(l->data);
		}
		if (village_value[village] < village_value[l->data] + 1)
		{
			village_value[village] = village_value[l->data] + 1;
		}
	}
}

int main()
{
	cin >> n >> m; // nΪ�ڵ�������mΪ·������

	village_value = new int[n + 1];  // ��ׯ���1-n
	visited = new bool[n + 1];
	list = new List<int>[n + 1];
	memset(village_value, 0, sizeof(int) * (n + 1));
	memset(visited, false, sizeof(bool) * (n + 1));

	for (int i = 0; i < m; i++)
	{
		// �ڽӾ���ռ䳬���ˣ������ڽӱ�ʵ��
		scanf("%d %d", &u, &v);  // ��Ҫ���һ���ṹ��ʹ�ÿ���ͨ��һ��index�ҵ����е��ھ�
		list[u].insertAsLast(v);
	}                                              

	for (int i = 1; i <= n; i++)
	{
		DFS(i);
	}

	int max = 1;
	for (int i = 1; i <= n; i++)
	{
		//cout << village_value[i] << endl;
		if (village_value[max] < village_value[i]) max = i;
	}
	//cout << "-------------------------" << endl;
	cout << village_value[max] + 1;

	return 0;
}