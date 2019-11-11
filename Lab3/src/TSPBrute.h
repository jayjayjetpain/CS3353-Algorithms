#pragma once

#ifndef TSPBRUTE_H
#define TSPBRUTE_H

#include "Algorithms.h"
#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <math.h>
#include <cfloat>

class TSPBrute : public Algorithms {
public: 
	virtual void Load(std::string);
	virtual void Execute();
	virtual void Display();
	virtual void Stats();
	virtual void Save(std::string);
	virtual void Configure();

private:
	std::vector<float> tspBrute();
	float distFormula(int one, int two);

	FileHandler handler;
	std::ofstream out;
	std::map<int, std::tuple<float, float, float>> positions;
	std::chrono::duration<double> time_span;
	std::vector<float> tempPath;
	int FINISHED_STATE;
	int size;

};

#endif // !TSPBRUTE_H
