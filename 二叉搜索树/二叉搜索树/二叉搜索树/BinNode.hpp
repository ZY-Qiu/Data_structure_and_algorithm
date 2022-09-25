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
	int size(); // ���ع�ģ�����������������к��������
	BinNodePosi(T) insertAsLC(T const&);
	BinNodePosi(T) insertAsRC(T const&);
	BinNodePosi(T) succ(); // ���м̱��������£���ǰ�ڵ��ֱ�Ӻ��
	

	template<typename VST> void travLevel(VST&); // ������α���
	template<typename VST> void travPre(BinNodePosi(T) x, VST&);  // �����������
	template<typename VST> void travIn(BinNodePosi(T) x, VST&);  // �����������
	template<typename VST> void travPost(BinNodePosi(T) x, VST&);  // �����������
	// �����������
	template<typename VST> static void visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, Array<BinNodePosi(T)>& S);
	// �����������
	static void goAlongLeftBranch(BinNodePosi(T) x, Array<BinNodePosi(T)>& S);
	// ���ں�������
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
		S.push_back(x->lChild);  // stack���˵�һ����lChild
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
		this->walkAlongLeftBranch(x, S);  // ��ʱջ����Ϊ����������ڵ㣬����Ϊ��ڵ�Ҳ����Ϊ����
		if (S.is_empty()) break;
		x = S.top();
		if (x->rChild == NULL || x->rChild == pervisited)  // �Ƿ�Ϊ��ڵ㣻����Ҫ֪���Ƿ񱻷��ʹ�
		{
			visit(x->data);
			pervisited = x;
			S.pop_back();
			x = NULL;  // ����ջ��push������
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