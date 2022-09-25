#pragma once
#include <iostream>
#include "ListNode.hpp"
using namespace std;

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
	T operator[](int r) const;  // 可以返回引用吗
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
void List<T>::init()  // 初始化函数
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
List<T>::List() // 构造函数
{
	this->init();
}

template<class T>
List<T>::List(Posi(T) p, int n)  // 拷贝构造函数
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
Posi(T) List<T>::find(T const& e, int n, Posi(T) p) const  // 在P的n个真前驱中，找到值等于e的最后者
{
	while (0 < n--)
	{
		if (e == (p = p->pred)->data) return p;
	}
	return NULL;
}

template<class T>
Posi(T) List<T>::find(T const& e, Posi(T) p, int n) const  // // 在P的n个真后继中，找到值等于e的最前者
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
int List<T>::deduplicate()  // 删除无序列表中的重复节点, 复杂度O(n^2)
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
int List<T>::uniquify()  // 删除有序列表中的重复节点, 复杂度O(n)
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
Posi(T) List<T>::search(T const& e, int n, Posi(T) p) const  // 在有序列表内P的n个真前驱中，找出不大于e的最后者
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