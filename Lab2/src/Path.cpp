#include "Path.h"

Path::Path()
{
	pathCost = 0;
	pathDist = 0;
	totalPathNodes = 0;
	totalExploredNodes = 0;
}

Path::Path(std::vector<int> path, int nodes)
{
	for (int i = 0; i < path.size(); i++)
	{
		dataPath.push_back(path.at(i));
	}
	pathCost = 0;
	pathDist = 0;
	totalPathNodes = dataPath.size();
	totalExploredNodes = nodes;
}

Path::Path(std::vector<int> path, int nodes, float cost)
{
	for (int i = 0; i < path.size(); i++)
	{
		dataPath.push_back(path.at(i));
	}
	pathCost = cost;
	pathDist = 0;
	totalPathNodes = dataPath.size();
	totalExploredNodes = nodes;
}

Path::Path(std::vector<int> path, int nodes, float cost, float dist)
{
	for (int i = 0; i < path.size(); i++)
	{
		dataPath.push_back(path.at(i));
	}
	pathCost = cost;
	pathDist = dist;
	totalPathNodes = dataPath.size();
	totalExploredNodes = nodes;
}

void Path::setPath(std::vector<int> path)
{
	for (int i = 0; i < path.size(); i++)
	{
		dataPath.push_back(path.at(i));
	}
	totalPathNodes = dataPath.size();
}

void Path::setPathCost(float cost)
{
	pathCost = cost;
}

void Path::setPathDist(float dist)
{
	pathDist = dist;
}

void Path::setExploredNodes(int nodes)
{
	totalExploredNodes = nodes;
}

std::vector<int> Path::getPath()
{
	return dataPath;
}

float Path::getCost()
{
	return pathCost;
}

float Path::getDist()
{
	return pathDist;
}

int Path::getTotalNodes()
{
	return totalPathNodes;
}

int Path::getExploredNodes()
{
	return totalExploredNodes;
}