#pragma once
#ifndef PATH_H
#define PATH_H
#include <vector>

class Path {
public:
	Path();
	Path(std::vector<int>, int);
	Path(std::vector<int>, int, float);
	Path(std::vector<int>, int, float, float);
	
	void setPath(std::vector<int>);
	void setPathCost(float);
	void setPathDist(float);
	void setExploredNodes(int);

	std::vector<int> getPath();
	float getCost();
	float getDist();
	int getTotalNodes();
	int getExploredNodes();

private:
	std::vector<int> dataPath;
	float pathCost;
	float pathDist;
	int totalPathNodes;
	int totalExploredNodes;
};

#endif // PATH_H
