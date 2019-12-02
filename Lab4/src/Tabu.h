#pragma once

#ifndef TABU_H
#define TABU_H

#include "Algorithms.h"
#include "FileHandler.h"
#include "TabuAlgo.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <math.h>
#include <cfloat>

/*	This class defines the TSP Search Algorithm using a Brute Force/Naive Method of coding. This class also encompasses
 *	the Strategy pattern as it inherits from the abstract Algorithms class so that we can use a Algorithms pointer in
 *	main. This class also uses the FileHandler class which is an interface that separates the loading and saving and
 *	files from the class. Contains functionality to Load a positions file, execute a TSP Search, Display the min cost
 *	and path, display stats of the algo, and save the stats to file (the loading and saving done via filehandler).
 */

class Tabu : public Algorithms {
public:
	virtual void Load(std::string);
	virtual void Execute();
	virtual void Display();
	virtual void Stats();
	virtual void Save(std::string);
	virtual void Select();
	virtual void Configure();

private:
	FileHandler handler;
	float distFormula(int one, int two);
	std::vector<float>(*algo)(std::vector<std::vector<float>>, int, int) = nullptr;
	std::map<int, std::tuple<float, float, float>> positions;
	std::vector<std::vector<float>> distances;
	std::chrono::duration<double> time_span;
	std::vector<float> tempPath;
	int size;

};

#endif // !TABU_H