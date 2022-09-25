#pragma once
#include"PQ.hpp"
#include"array.hpp"

#define Parent(i)				((i - 1) >> 1)
#define ParentValid(i)			((i == 0) ? false : true)
#define LChild(i)				((i << 1) + 1)
#define RChild(i)				((i + 1) << 1)
#define InHeap(n, i)			(i > -1) && (i < n)
#define LChildValid(n, i)		InHeap(n, LChild(i))
#define RChildValid(n, i)		InHeap(n, RChild(i))
#define Bigger(PQ, i, j)		(PQ[i] < PQ[j]) ? j: i
#define PorperParent(PQ, n, i)  /*父子（至多）三者中的大者*/ \
								(RChildValid(n, i) ? Bigger(PQ, Bigger(PQ, i, LChild(i)), RChild(i)) : \
								(LChildValid(n, i) ? Bigger(PQ, i, LChild(i)) : i))
#define LastInternal(i)			(i / 2 - 1)

template<class T>
class PQ_ComplHeap : public PQ<T>, public Array<T>
{
protected:
	Rank percolateDown(Rank n, Rank i);
	Rank percolateUp(Rank i);
	void heapify(Rank n);

public:
	PQ_ComplHeap(T* A, Rank n)
	{
		Array<T>::copyFrom(A, 0, n);
		this->heapify(n);
	}
	void insert(T);
	T getMax() { return this->pArray[0]; }
	T delMax();
};

template<typename T>
void PQ_ComplHeap<T>::insert(T e)
{
	Array<T>::push_back(e);
	this->percolateUp(this->m_size - 1);
}

template<typename T>
Rank PQ_ComplHeap<T>::percolateUp(Rank i)
{
	while (ParentValid(i))
	{
		Rank j = Parent(i);
		if (this->pArray[i] < this->pArray[j]) break;
		swap(this->pArray[i], this->pArray[j]);
		i = j;
	}
	return i;
}

template<typename T>
T PQ_ComplHeap<T>::delMax()
{
	T maxElem = this->pArray[0];
	this->pArray[0] = this->pArray[--this->m_size];
	this->percolateDown(this->m_size, 0);
	return maxElem;
}

template<typename T>
Rank PQ_ComplHeap<T>::percolateDown(Rank n, Rank i)
{
	Rank j;
	while (i != (j = PorperParent(this->pArray, n, i)))
	{
		swap(this->pArray[i], this->pArray[j]);
		i = j;
	}
	return i;
}

//template<typename T>
//void PQ_ComplHeap<T>::heapify(Rank n) // 蛮力，自上而下的上滤，O(logn)，已经过copyFrom
//{
//	for (int i = 1; i < n; i++) // 忽略i = 0，即只有根的上滤
//	{
//		this->percolateUp(i);
//	}
//}

template<typename T>
void PQ_ComplHeap<T>::heapify(Rank n) // 自下而上的下滤，O(n)
{
	for (int i = LastInternal(n); i >= 0; i--) // 自最后一个内部节点至根节点
	{
		this->percolateDown(n, i);
	}
}





template<class T>
static Array<T>* heapsort(Array<T>* S, Rank lo, Rank hi)
{
	PQ_ComplHeap<T> H(S->pArray + lo, hi - lo); // 建堆
	while (!H.is_empty())
	{
		S->pArray[--hi] = H.delMax();
	}
	return S;
}