#pragma once

#ifndef GRAPH_H
#define GRAPH_H


#include "Node.h"

class Graph {
public:
	virtual void addVertex(int) = 0;
	virtual void addEdge(int, int) = 0;
	virtual int getEdgeNum(int) = 0;
	virtual Node* at(int, int) = 0;
	virtual void setWeights(int, int, float) = 0;
	virtual void setPositions(int, float, float, float) = 0;
	virtual int getVertexNum() = 0;
	virtual Node* findNode(Node*) = 0;
	virtual std::vector<Node*> getChildren(int, Node*) = 0;
	virtual float getWeight(int, int) = 0;

};



#endif // GRAPH_H
