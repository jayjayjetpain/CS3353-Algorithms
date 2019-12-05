// Project4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "AlgoFactory.h"
#include "Algorithms.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

int main()
{
	//Creates an instance of the Algorithm Factory to create each algorithm
	AlgoFactory fact;

	//File for input and path to output file for Load and Save respectively
	std::string inFile = "Data/positions8.txt";
	std::string outPath = "OutputData/";
	//std::vector<float> stops = { 23.10, 28.41, 29.08, 40.17, 48.93, 52.77, 73.19, 84.44, 85.25, 85.83, 88.76, 95.11, 97.00, 101.07, 104.10,
	//							109.71, 125.51, 127.72, 131.07, 135.66, 142, 148.05 };

	//handles the creatation of a TSP Brute Force Algo object via AlgoFactory and excutes the search
	/*Configure:	1: Type of Selection -> 1) Elitism  2) Roulette Wheel  3) Tournament
	 *				2: Type of Mutation -> 1) Swap  2) Inversion
	 *				3: Type of Crossover -> 1) Ordered  2) PMX (Partially-Mapped)
	 */
	Algorithms* pAlgoGenetic = fact.Create(AlgoFactory::AlgoClass::GENETIC);
	pAlgoGenetic->Load(inFile);
	pAlgoGenetic->Select();
	pAlgoGenetic->Configure(1,1,1);
	pAlgoGenetic->Execute();
	pAlgoGenetic->Stats();
	std::cout << std::endl;
	pAlgoGenetic->Save(outPath);

	//handles the creatation of a TSP Dynamic Programming Algo object via AlgoFactory and excutes the search
	/*Configure:	1: Type of Neighborhood Selection -> 1) Swap  2) Inversion
	 *				2: Maximum Size of Tabu List
	 */
	Algorithms* pAlgoTabu = fact.Create(AlgoFactory::AlgoClass::TABU);
	pAlgoTabu->Load(inFile);
	pAlgoTabu->Select();
	pAlgoTabu->Configure(1,20);
	pAlgoTabu->Execute();
	pAlgoTabu->Stats();
	std::cout << std::endl;
	pAlgoTabu->Save(outPath);

	return 0;

}

