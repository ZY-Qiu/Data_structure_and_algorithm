#pragma once
#include <iostream>
#include "BinNode.hpp"

using namespace std;

#define stature(p) ((p) ? (p->height) : -1)

template<class T>
class BinTree
{
protected:
	int _size;
	BinNodePosi(T) _root;
	virtual int updateHeight(BinNodePosi(T) x);
	void updateHeightAbove(BinNodePosi(T) x);
public:
	BinTree();
	int size() const { return this->_size; }
	bool is_empty() const { return !this->_root; }
	BinNodePosi(T) root() const { return this->_root; }
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);

	
};

template<class T>
BinTree<T>::BinTree()
{
	this->_root = new BinNode<T>(0, NULL);
	this->_size = 1;
}

template<class T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height = 1 + max(stature(x->lChild), stature(x->rChild));
}

template<class T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while (x)  // ÖÁrootµÄparentÎªNULL
	{
		int h = x->height;
		if(this->updateHeight(x) == h) return;
		x = x->parent;
	}
}

template<class T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e)
{
	if (x->lChild != NULL)
	{
		cout << "insertAsLC(): Left child already exists!" << endl;
		exit(1);
	}
	this->_size++;
	x->insertAsLC(e);
	this->updateHeightAbove();
	return x->lChild;
}

template<class T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e)
{
	if (x->rChild != NULL)
	{
		cout << "insertAsLC(): Left child already exists!" << endl;
		exit(1);
	}
	this->_size++;
	x->insertAsRC(e);
	this->updateHeightAbove();
	return x->rChild;
}


