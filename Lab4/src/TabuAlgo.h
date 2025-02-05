#pragma once

#ifndef TABUALGO_H
#define TABUALGO_H

#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <algorithm>
#include <random>
#include <utility>
#include <fstream>

class TabuAlgo {
public:
	static std::vector<float> tabuAlgo(std::vector<std::vector<float>>, int, int, float);

private:
	static std::vector<float> tabuAlgo(std::vector<float>, float, int, int, int, float);
	static std::vector<float> initialSolution(int, int);
	static std::vector<std::vector<float>> find_neighborhood(std::vector<float>, int);

	static std::vector<std::vector<float>> find_neighborhood_swap(std::vector<float>);
	static std::vector<std::vector<float>> find_neighborhood_invert(std::vector<float>);
	static float getPathDistance(std::vector<float>);
	static std::vector<std::vector<float>> distances;
	static std::list<std::pair<float, float>>::const_iterator currBest;
	static bool compareDist(std::vector<float>, std::vector<float>);
};

#endif // !TABUALGO_H
