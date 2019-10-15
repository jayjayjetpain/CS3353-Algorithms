#pragma once

#ifndef ADJMATRIX_H
#define ADJMATRIX_H

#include "Graph.h"
#include "Node.h"
#include <vector>
#include <iostream>

class AdjMatrix : public Graph {
public:
	AdjMatrix();
	virtual void addEdge(int, int);
	virtual void addVertex(int);
	virtual int getEdgeNum(int);
	virtual int getVertexNum();
	virtual Node* at(int, int);
	virtual void setWeights(int, int, int);
	virtual void setPositions(int, float, float, float);
	void makeMatrix(int);
	void print();
	virtual Node* findNode(Node*);
	virtual std::vector<Node*> getChildren(int, Node*);

private:
	std::vector<std::vector<Node>> data;
	std::vector<std::tuple<int, int, int>> weights;
};
#endif // ADJMATRIX_H
