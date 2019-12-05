#pragma once

#ifndef GENETICALGO_H
#define GENETICALGO_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <math.h>
#include <random>       
#include <chrono>  
#include <tuple>
#include <fstream>

class GeneticAlgo {
public:
	static std::vector<float> geneticAlgo(std::vector<std::vector<float>>, int, int, int, float);
	 

private:
	static std::vector<float> geneticAlgo(int, int, float, int, int, int, int, float);

	static std::vector<float> createRoute(int, int);
	static std::vector<std::vector<float>> initializePop(int, int);
	static std::vector<std::pair<int, float>> rankRoutes(std::vector<std::vector<float>>);
	static std::vector<int> selection(std::vector<std::pair<int, float>>, int);
	static std::vector<std::vector<float>> matingPool(std::vector<std::vector<float>>, std::vector<int>);
	static std::vector<float> breed(std::vector<float>, std::vector<float>, int);
	static std::vector<std::vector<float>> breedPopulation(std::vector<std::vector<float>>, int, int);
	static std::vector<float> mutate(std::vector<float>, float, int);
	static std::vector<std::vector<float>> mutatePopulation(std::vector<std::vector<float>>, float, int);
	static std::vector<std::vector<float>> nextGeneration( std::vector<std::vector<float>>, int, int, int, float);

	static std::vector<int> selectionElitism(std::vector<std::pair<int, float>>, int);
	static std::vector<int> selectionRoulette(std::vector<std::pair<int, float>>, int);
	static std::vector<int> selectionTournament(std::vector<std::pair<int, float>>, int);
	static std::vector<float> mutateSwap(std::vector<float>, float);
	static std::vector<float> mutateInvert(std::vector<float>, float);
	static std::vector<float> breedOrdered(std::vector<float>, std::vector<float>);
	static std::vector<float> breedPMX(std::vector<float>, std::vector<float>);
	static float getPathFitness(std::vector<float>);
	static bool compareFitness(std::pair<int, float>, std::pair<int, float>);
	static std::vector<std::vector<float>> distances;
	
};

#endif // !GENETICALGO_H
