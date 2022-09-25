#pragma once
#include <iostream>
#include "Queue.hpp"
using namespace std;

template<class Tv, class Te>  // 顶点类型，边类型
class Graph
{
private:
	
protected:
	void reset();
};


template<class Tv, class Te>
void Graph<Tv, Te>::reset()
{
	for (int i = 0; i < n; i++)
	{
		status(i) = UNDISCOVERED;
		dTime(i) = fTime(i) = -1;
		parent(i) = -1;
		//priority(i) = INT_MAX;
		for (int j = 0; j < n; j++) status(i, j) = UNDETERMINED;
	}
}




