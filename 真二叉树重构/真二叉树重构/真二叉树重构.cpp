#include <iostream>

using namespace std;






#define default_capacity 30
typedef int Rank;

template<class T>
class Array
{
public:
	Array();

	Array(int cap);

	int size();

	T& operator[](int index);

	int find(T val);

	int find(T val, int posi);

	int find(T val, int start, int end);

	void push_back(const T& val);

	bool is_empty();

	bool is_full();

	T pop_back();

	T top();

	T remove(int i);

	void expand();

	void arrayCopy(T* newArray);

	void mergeSort(Rank lo, Rank hi);

	void merge(Rank lo, Rank mi, Rank hi);

	void insert(const T& val, int posi);

	~Array();

private:
	int m_size;
	int m_capacity;
	T* pArray;
};

// 模板类实现
template<class T>
void Array<T>::mergeSort(Rank lo, Rank hi)
{
	if (hi - lo < 2) return;
	int mi = (lo + hi) >> 1;
	mergeSort(lo, mi);
	mergeSort(mi, hi);
	merge(lo, mi, hi);
}

template<class T>
void Array<T>::merge(Rank lo, Rank mi, Rank hi)
{
	T* A = this->pArray + lo;
	int lb = mi - lo;
	T* B = new T[lb];
	for (Rank i = 0; i < lb; B[i] = A[i], i++);
	int lc = hi - mi;
	T* C = this->pArray + mi;
	for (Rank i = 0, j = 0, k = 0; j < lb;)
	{
		if (k < lc && C[k] < B[j]) A[i++] = C[k++];
		if (k >= lc || C[k] >= B[j]) A[i++] = B[j++]; // 当||前一个为真即停止判断
	}
	delete[] B;
}

template<class T>
Array<T>::Array()
{
	this->m_capacity = default_capacity;
	this->m_size = 0;
	this->pArray = new T[this->m_capacity];
}

template<class T>
Array<T>::Array(int cap)
{
	this->m_capacity = cap;
	this->m_size = 0;
	this->pArray = new T[this->m_capacity];
}

template<class T>
int Array<T>::size()
{
	return this->m_size;
}

template<class T>
T& Array<T>::operator[](int index)
{
	if (index >= this->m_size)
	{
		printf("operator[](): Index out of range!\n");
		exit(1);
	}
	else
	{
		return this->pArray[index];
	}
}

template<class T>
int Array<T>::find(T val)
{
	for (int i = this->size() - 1; i >= 0; i--)
	{
		if (this->pArray[i] == val) return i;
	}
	return -1;
}

template<class T>
int Array<T>::find(T val, int posi)  // 不包括posi，向前查找
{
	if (posi > this->size())
	{
		cout << "find(): Index out of range!" << endl;
		exit(1);
	}
	for (int i = posi - 1; i >= 0; i--)
	{
		if (this->pArray[i] == val) return i;
	}
	return -1;
}

template<class T>
int Array<T>::find(T val, int start, int end)
{
	if (end > this->size())
	{
		cout << "find(): Index out of range!" << endl;
		exit(1);
	}
	for (int i = end - 1; i >= start; i--)
	{
		if (this->pArray[i] == val) return i;
	}
	return -1;
}

template<class T>
void Array<T>::push_back(const T& val)
{
	if (this->m_size != this->m_capacity)
	{
		this->pArray[this->m_size] = val;
		this->m_size++;
	}
	else
	{
		this->expand();
		this->push_back(val);
	}
}

template<class T>
bool Array<T>::is_empty()
{
	return (this->m_size == 0);
}

template<class T>
bool Array<T>::is_full()
{
	return (this->m_size == this->m_capacity);
}

template<class T>
T Array<T>::pop_back()
{
	if (this->is_empty())
	{
		printf("pop_back(): Index out of range!\n");
		exit(1);
	}
	this->m_size--;
	return this->pArray[this->m_size];
}

template<class T>
T Array<T>::top()
{
	if (this->is_empty())
	{
		printf("top(): Array is empty!\n");
		exit(1);
	}
	return this->pArray[this->m_size - 1];
}

template<class T>
void Array<T>::expand()
{
	this->m_capacity <<= 1;
	T* newArray = new T[this->m_capacity];
	arrayCopy(newArray);
	delete[] this->pArray;
	this->pArray = newArray;
}

template<class T>
void Array<T>::arrayCopy(T* newArray)
{
	for (int i = 0; i < this->m_size; i++)
	{
		newArray[i] = this->pArray[i];
	}
}

template<class T>
T Array<T>::remove(int i)
{
	if (i >= this->size())
	{
		cout << "remove(): Index out of range!" << endl;
		exit(1);
	}
	T ret = this->pArray[i];
	for (int j = i; j < this->size() - 1; j++)
	{
		this->pArray[j] = this->pArray[j + 1];
	}
	return ret;
}

template<class T>
void Array<T>::insert(const T& val, int posi)
{
	if (this->size() < this->m_capacity)
	{
		for (int i = this->m_size; i > posi; i--)
		{
			this->pArray[i] = this->pArray[i - 1];
		}
		this->pArray[posi] = val;
		this->m_size++;
	}
	else
	{
		cout << "insert(): Array is full!" << endl;
		exit(1);
	}
}

template<class T>
Array<T>::~Array()
{
	if (this->pArray != NULL)
	{
		delete[] this->pArray;
		this->pArray = NULL;
	}
}









void print(int* c, int len)
{
	for (int i = 0; i < len; i++)
	{
		printf("%d ", c[i]);
	}
}

void reconstruct(int d, int prel, int prer, int postl, int postr, int* c, Array<int>& a, Array<int>& b)
{
	d++;
	//cout << "---------------------" << endl;
	//cout << "prel = " << prel << ", prer = " << prer << ", d = " << d << endl;
	//cout << "postl = " << postl << ", postr = " << postr << endl;
	if (prel == (a.size() - 1))
	{
		c[prel] = a[prel];
		//print(c, 9);
		return;
	}
	int posi = b.find(a[prel + 1], postl, postr);
	if (posi != -1)
	{
		c[posi + d] = a[prel];
		//print(c, 9);
		reconstruct(d - 1, prel + 1, prel + 1 + posi - postl + 1, postl, posi, c, a, b);  // 左子树
		reconstruct(d, prel + 1 + posi - postl + 1, prer, posi + 1, postr, c, a, b);  // 右子树
	}
	else  // 叶子节点
	{
		posi = b.find(a[prel], postl, postr + 1);
		c[posi + d - 1] = a[prel];
		//print(c, 9);
	}
}

int main()
{
	int n;
	cin >> n;  // 节点个数
	Array<int> a(n), b(n);
	int* c = new int[n];
	int depth = 0;
	int j;
	
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &j);  // 先序遍历序列
		a.push_back(j);
	}
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &j);  // 后序遍历序列
		b.push_back(j);
	}

	reconstruct(depth, 0, n, 0, n, c, a, b);

	print(c, n);

	return 0;
}