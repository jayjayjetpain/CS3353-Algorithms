#pragma once

#ifndef SEARCHALGOS_H
#define SEARCHALGOS_H
#include "AdjList.h"
#include "AdjMatrix.h"
#include "Tree.h"
#include "Path.h"
#include <vector>
#include <stack>
#include <queue>
#include <math.h>

class SearchAlgos {
public:
	 static Path DFSIter(int, int, Graph*);
	 static Path BFSIter(int, int, Graph*);
	 static Path DFSRecur(int, int, Graph*);
	 static Path BFSRecur(int, int, Graph*);
	 static Path Dijkstra(int, int, Graph*);
	 static Path AStar(int, int, Graph*);

private:
	static void DFSIterUtil(int, int, Graph*, Tree*);
	static void BFSIterUtil(int, int, Graph*, Tree*);
	static void DFSRecurUtil(int, int, Graph*, Node*, std::vector<bool>&, std::vector<bool>&, Tree*);
	static void BFSRecurUtil(int, int, Graph*, std::queue<Node*>&, std::vector<bool>&, std::vector<bool>&, Tree*);
	static void DijkstraUtil(int, int, Graph*, Tree*);
	static void AStarUtil(int, int, Graph*, Tree*);

	static float distFormula(Node*, Node*);

	struct compareCosts 
	{
		bool operator()(const Node* one, const Node* two)
		{
			if (one->getCost() == two->getCost())
			{
				return one->getTime() > two->getTime();
			}
			else
			{
				return one->getCost() > two->getCost();
			}
			
		}
	};
};





#endif //SEARCHALGOS_H