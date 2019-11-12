#pragma once

#ifndef TSPDYNAMIC_H
#define TSPDYNAMIC_H

#include "Algorithms.h"
#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <math.h>
#include <cfloat>

/*	This class defines the TSP Search Algorithm using a Dynamic Programming Method of coding. This specific implementation
 *	is a recursive, memoization (top-down) Dynamic Programming Method. This class also encompasses the Strategy pattern
 *	as it inherits from the abstract Algorithms class so that we can use a Algorithms pointer in main. This class also
 *	uses the FileHandler class which is an interface that separates the loading and saving and files from the class.
 *	Contains functionality to Load a positions file, execute a TSP Search, Display the min cost and path, display stats
 *	of the algo, and save the stats to file (the loading and saving done via filehandler).
 *	Reference for DP Algo:
 *	GitHub: https://github.com/williamfiset/Algorithms/blob/master/com/williamfiset/algorithms/graphtheory/TspDynamicProgrammingRecursive.java
 *	Video: https://www.youtube.com/watch?v=cY4HiiFHO1o&t=30s
 */

class TSPDynamic : public Algorithms {
public:
	virtual void Load(std::string);
	virtual void Execute();
	virtual void Display();
	virtual void Stats();
	virtual void Save(std::string);
	virtual void Configure();

private:
	std::vector<float>* tspDynamic();
	float getMinTour(int i, int state, std::vector<std::vector<float>>& memo, std::vector<std::vector<float>>& prev);
	float distFormula(int one, int two);

	FileHandler handler;
	std::map<int, std::tuple<float, float, float>> positions;
	std::vector<std::vector<float>> distances;
	std::chrono::duration<double> time_span;
	std::vector<float> tempPath;
	int FINISHED_STATE;
	int size;
};

#endif // !TSPDYNAMIC_H
