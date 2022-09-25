#pragma once
#include <iostream>

using namespace std;

typedef enum{UNDISCOVERED, DISCOVERED, VISITED} VStatus;
typedef enum{UNDETERMINED,TREE, CROSS, FORWARD, BACKWORD } EStatus;

template<typename Tv>
struct Vertex
{
	Tv data;
	int inDegree, outDegree;
	VStatus status;
	int dTime, fTime;
	int parent;
	int priority;

	Vertex(Tv const& d) :
		data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
};


template<typename Te>
struct Edge
{
	Te data;
	int weight;
	EStatus status;
	Edge(Te const & d, int w): data(d), weight(w), status(UNDETERMINED) {}
};