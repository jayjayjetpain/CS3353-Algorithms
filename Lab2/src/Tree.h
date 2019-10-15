#pragma once
#ifndef TREE_H
#define TREE_H
#include "Node.h"
#include <vector>

class Tree {
public:
	Tree();
	Tree(Node*);
	~Tree();
	void insert(int, Node*);
	void move(int = 0);
	void setPathCost(int);
	void setWeights(std::vector<std::tuple<int, int, int>>);
	int getTotalNodes();
	void setPath();
	std::vector<Node*> getPath();
	void findNode(int);
	void setExplored(int);
	int getExploredNum();

private:
	Node* root;
	Node* currNode;
	int depth;
	int totalNodes;
	int numExplored;
	std::vector<Node*> path;

	std::vector<std::tuple<int, int, int>> weights;
	void makeEmpty(Node*);
	
	void findNode(Node*, int);
};

#endif // TREE_H
