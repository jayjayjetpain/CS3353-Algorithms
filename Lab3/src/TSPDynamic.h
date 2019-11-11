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
	std::chrono::duration<double> time_span;
	std::vector<float> tempPath;
	int FINISHED_STATE;
	int size;
};

#endif // !TSPDYNAMIC_H
