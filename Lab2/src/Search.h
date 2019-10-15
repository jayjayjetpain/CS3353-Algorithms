#pragma once

#ifndef SEARCH_H
#define SEARCH_H

#include "Algorithms.h"
#include "Graph.h"
#include "AdjList.h"
#include "AdjMatrix.h"
#include "SearchAlgos.h"
#include "Path.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

class Search : public Algorithms {
public:
	virtual void Load(std::string, std::string, std::string);
	virtual void Execute(int, int);
	virtual void Display();
	virtual void Stats();
	virtual void Select(int, int);
	virtual void Save(std::string);
	virtual void Configure();

	enum SearchingAlgos
	{
		IDFS = 0,
		RDFS,
		IBFS,
		RBFS,
		DIJKSTRA,
		ASTAR,
		LAST1
	};

	enum GraphType
	{
		ADJLIST = 0,
		ADJMATRIX,
		LAST2
	};


private:
	Path(*algo)(int, int, Graph*) = nullptr;
	std::chrono::duration<double> time_span;
	std::string currAlgo;
	std::string graphType;
	int totElements;

	Graph* currGraph;
	AdjList list;
	AdjMatrix matrix;
	Path tempPath;
};

#endif // SEARCH_H
