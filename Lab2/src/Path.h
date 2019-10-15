#pragma once
#ifndef PATH_H
#define PATH_H
#include <vector>

class Path {
public:
	Path();
	Path(std::vector<int>, int);
	Path(std::vector<int>, int, int, int);
	
	void setPath(std::vector<int>);
	void setPathCost(int);
	void setPathDist(int);
	void setExploredNodes(int);

	std::vector<int> getPath();
	int getCost();
	int getDist();
	int getTotalNodes();
	int getExploredNodes();

private:
	std::vector<int> dataPath;
	int pathCost;
	int pathDist;
	int totalPathNodes;
	int totalExploredNodes;
};

#endif // PATH_H
