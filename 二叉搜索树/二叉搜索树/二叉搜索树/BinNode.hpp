#pragma once
#include <iostream>
#include "visit.hpp"
#include "array.hpp"
#include "Queue.hpp"
using namespace std;

#define BinNodePosi(T) BinNode<T>*

template<class T>
struct BinNode
{
	BinNodePosi(T) parent, lChild, rChild;
	T data;
	int height;

	BinNode() {};
	BinNode(T const& e, BinNodePosi(T) b);
	int size(); // 返回规模，即包括它在内所有后代的总数
	BinNodePosi(T) insertAsLC(T const&);
	BinNodePosi(T) insertAsRC(T const&);
	BinNodePosi(T) succ(); // （中继遍历意义下）当前节点的直接后继
	

	template<typename VST> void travLevel(VST&); // 子树层次遍历
	template<typename VST> void travPre(BinNodePosi(T) x, VST&);  // 子树先序遍历
	template<typename VST> void travIn(BinNodePosi(T) x, VST&);  // 子树中序遍历
	template<typename VST> void travPost(BinNodePosi(T) x, VST&);  // 子树后序遍历
	// 用于先序遍历
	template<typename VST> static void visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, Array<BinNodePosi(T)>& S);
	// 用于中序遍历
	static void goAlongLeftBranch(BinNodePosi(T) x, Array<BinNodePosi(T)>& S);
	// 用于后续遍历
	static void walkAlongLeftBranch(BinNodePosi(T) x, Array<BinNodePosi(T)>& S);
};

template<class T>
BinNode<T>::BinNode(T const& e, BinNodePosi(T) b)
{
	this->data = e;
	this->parent = b;
	this->lChild = NULL;
	this->rChild = NULL;
	this->height = 0;
}

template<class T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const& e)
{
	return this->lChild = new BinNode(e, this);
}

template<class T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const& e)
{
	return this->rChild = new BinNode(e, this);
}

template<class T>
int BinNode<T>::size()
{
	int s = 1;
	if (this->lChild) s += this->lChild->size();
	if (this->rChild) s += this->rChild->size();
	return s;
}


template<class T>
template<typename VST> static void BinNode<T>::visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, Array<BinNodePosi(T)>& S)
{
	while (x)
	{
		visit(x->data);
		S.push_back(x->rChild);
		x = x->lChild;
	}
}

template<class T>
template<typename VST> void BinNode<T>::travPre(BinNodePosi(T) x, VST& visit)
{
	Array<BinNodePosi(T)> S;
	while (true)
	{
		this->visitAlongLeftBranch(x, visit, S);
		if (S.is_empty()) break;
		x = S.pop_back();
	}
}

template<class T>
void BinNode<T>::goAlongLeftBranch(BinNodePosi(T) x, Array<BinNodePosi(T)>& S)
{
	while (x)
	{
		S.push_back(x);
		x = x->lChild;
	}
}

template<class T>
template<typename VST> void BinNode<T>::travIn(BinNodePosi(T) x, VST& visit)
{
	Array<BinNodePosi(T)> S;
	while (true)
	{
		this->goAlongLeftBranch(x, S);
		if (S.is_empty()) break;
		x = S.pop_back();
		visit(x->data);
		x = x->rChild;
	}
}

template<class T>
static void BinNode<T>::walkAlongLeftBranch(BinNodePosi(T) x, Array<BinNodePosi(T)>& S)
{
	while (x)
	{
		S.push_back(x->lChild);  // stack顶端的一定是lChild
		x = x->lChild;
	}
}

template<class T>
template<typename VST> void BinNode<T>::travPost(BinNodePosi(T) x, VST& visit)
{
	Array<BinNodePosi(T)> S;
	BinNodePosi(T) pervisited = NULL;
	while (true)
	{
		this->walkAlongLeftBranch(x, S);  // 此时栈顶端为子树的最左节点，可能为左节点也可能为顶端
		if (S.is_empty()) break;
		x = S.top();
		if (x->rChild == NULL || x->rChild == pervisited)  // 是否为左节点；但需要知道是否被访问过
		{
			visit(x->data);
			pervisited = x;
			S.pop_back();
			x = NULL;  // 不向栈中push入数据
		}
		else x = x->rChild;
	}
}

template<class T>
template<typename VST> void BinNode<T>::travLevel(VST& visit)
{
	Queue<BinNodePosi(T)> Q;
	Q.enqueue(this);
	while (!Q.is_empty())
	{
		BinNodePosi(T) x = Q.dequeue();
		visit(x->data);
		if (x->lChild != NULL) Q.enqueue(x->lChild);
		if (x->rChild != NULL) Q.enqueue(x->rChild);
	}
}