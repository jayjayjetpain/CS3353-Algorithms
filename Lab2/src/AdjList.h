#pragma once
#ifndef ADJLIST_H
#define ADJLIST_H

#include "LinkedList.h"
#include "Node.h"
#include "Graph.h"
#include <iostream>

class AdjList : public Graph {
public:
	AdjList();
	virtual void addVertex(int);
	virtual void addEdge(int, int);
	virtual int getVertexNum();
	virtual Node* at(int, int = 0);
	virtual void setWeights(int, int, float);
	virtual void setPositions(int, float, float, float);
	void print();
	virtual Node* findNode(Node*);
	virtual std::vector<Node*> getChildren(int, Node*);
	virtual float getWeight(int, int);

	typename LinkedList<Node>::Iterator getIter();

private:
	LinkedList<Node> dataList;
	std::vector<std::tuple<int, int, float>> weights;
	typename LinkedList<Node>::Iterator frontIter;
	int vertexNum;

	struct compareDatas
	{
		bool operator()(const Node* one, const Node* two)
		{
			return one->getData() < two->getData();
		}
	} myCompare;
};

#endif //ADJLIST_H
