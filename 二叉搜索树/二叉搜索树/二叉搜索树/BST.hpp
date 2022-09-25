#pragma once
#include "BinTree.hpp"

template<class T>
class BST : public BinTree<T>
{
public:
	virtual BinNodePosi(T)& search(const T&);
	virtual BinNodePosi(T) insert(const T&);
	virtual bool remove(const T&);
protected:
	BinNodePosi(T) _hot;
	BinNodePosi(T) connect34();
	BinNodePosi(T) rotateAt(BinNodePosi(T));
	static BinNodePosi(T)& searchIn(BinNodePosi(T) & v, const T & e, BinNodePosi(T) & hot);
	static BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot);
};


template<class T>
BinNodePosi(T)& BST<T>::search(const T& e)
{
	return this->searchIn(this->_root, e, this->_hot = NULL);
}


template<class T>
BinNodePosi(T)& BST<T>::searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot)
{
	if (!v || v->data == e) return v;
	hot = v;
	return this->searchIn(((e < v->data) ? v->lChild : v->rChild), e, hot);
}


template<class T>
BinNodePosi(T) BST<T>::insert(const T& e)
{
	BinNodePosi(T)& x = this->search(e);
	if (!x) // ��ֹ��ͬԪ��
	{
		x = new BinNode<T>(e, this->_hot);
		this->_size++;
		this->updateHeightAbove(x);
	}
	return x;
}


template<class T>
bool BST<T>::remove(const T& e)
{
	BinNodePosi(T)& x = this->search(e);
	if (!x) return false;
	this->removeAt(e, this->_hot);
	this->_size--;
	this->updateHeightAbove(this->_hot);
	return true;
}


template<class T>
BinNodePosi(T) BST<T>::removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot)
{
	BinNodePosi(T) w = x; // ��¼��ɾ���Ľڵ�
	BinNodePosi(T) succ = NULL; // ��ɾ���ڵ�Ľ�����
	if (x->lChild == NULL) succ = x = x->rChild;
	else if (x->rChild == NULL) succ = x = x->lChild;
	else
	{
		w = w->succ(); // ���������ֱ�Ӻ��
		swap(x->data, w->data);
		BinNodePosi(T) u = w->parent;
		(u == x ? u->rChild : u->lChild) = succ = w->rChild; // �ڵ�wֻ�����Һ���
	}
	hot = w->parent;
	if (succ) succ->parent = hot;
	// �����ͷŵ���ɾ���Ľڵ�
	return succ;
}