#pragma once
#include <iostream>
using namespace std;
#define Posi(T) ListNode<T>*

template<typename T>
struct ListNode
{
	T data;
	Posi(T) pred;
	Posi(T) succ;
	ListNode() {};
	ListNode(T e, Posi(T) p = NULL, Posi(T) s = NULL) : data(e), pred(p), succ(s) {}  // 初始化列表
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