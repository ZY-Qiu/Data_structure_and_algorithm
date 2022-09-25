#pragma once
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

	void push_back(const T& val);

	bool is_empty();

	T pop_back();

	T top();

	void expand();

	void arrayCopy(T* newArray);

	void mergeSort(Rank lo, Rank hi);

	void merge(Rank lo, Rank mi, Rank hi);

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
		printf("[]: Index out of range!\n");
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
T Array<T>::pop_back()
{
	if (this->is_empty())
	{
		printf("pop_back: Index out of range!\n");
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
		printf("top: Array is empty!\n");
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
Array<T>::~Array()
{
	if (this->pArray != NULL)
	{
		delete[] this->pArray;
		this->pArray = NULL;
	}
}