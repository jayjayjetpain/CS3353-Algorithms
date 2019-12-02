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
	//std::vector<float> route;
	//for (int i = 0; i < 12; i++)
	//{
	//	route.push_back(i);
	//}
	//route.push_back(0);

	//unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	//std::shuffle(route.begin() + 1, route.end() - 1, std::default_random_engine(seed));

	//for (int j = 0; j < route.size(); j++)
	//{
	//	std::cout << route.at(j) << " ";
	//}
	//std::srand(time(NULL));

	//std::vector<float> parent1 = { 0,1,2,3,4,5,6,7,8,9,0 };
	//std::vector<float> parent2 = { 0,9,8,7,6,5,4,3,2,1,0 };

	//std::vector<float> child;
	//std::vector<float> childPart1;
	//std::vector<float> childPart2;

	//int geneA = int(std::rand() % (parent1.size()-1) + 1);
	//int geneB = int(std::rand() % (parent1.size()-1) + 1);

	//int start = std::min(geneA, geneB);
	//int end = std::max(geneA, geneB);

	//for (int i = start; i < end; i++)
	//{
	//	childPart1.push_back(parent1.at(i));
	//}

	//for (int j = 0; j < parent2.size(); j++)
	//{
	//	if (std::find(childPart1.begin(), childPart1.end(), parent2.at(j)) == childPart1.end())
	//	{
	//		childPart2.push_back(parent2.at(j));
	//	}
	//}

	//int inner = 0;
	//int outer = 0;
	//for (int k = 0; k < parent1.size(); k++)
	//{
	//	if (k >= start && k < end)
	//	{
	//		child.push_back(childPart1.at(inner));
	//		inner++;
	//	}
	//	else
	//	{
	//		child.push_back(childPart2.at(outer));
	//		outer++;
	//	}
	//}


	//for (int l = 0; l < child.size(); l++)
	//{
	//	std::cout << child.at(l) << " ";
	//}



	//Creates an instance of the Algorithm Factory to create each algorithm
	AlgoFactory fact;

	//File for input and path to output file for Load and Save respectively
	std::string inFile = "Data/positions5.txt";
	std::string outPath = "OutputData/";

	//handles the creatation of a TSP Brute Force Algo object via AlgoFactory and excutes the search
	//Algorithms* pAlgoGenetic = fact.Create(AlgoFactory::AlgoClass::GENETIC);
	//pAlgoGenetic->Load(inFile);
	//pAlgoGenetic->Select();
	//pAlgoGenetic->Execute();
	//pAlgoGenetic->Stats();
	//std::cout << std::endl;
	//pAlgoGenetic->Save(outPath);

	////handles the creatation of a TSP Dynamic Programming Algo object via AlgoFactory and excutes the search
	Algorithms* pAlgoTabu = fact.Create(AlgoFactory::AlgoClass::TABU);
	pAlgoTabu->Load(inFile);
	pAlgoTabu->Select();
	pAlgoTabu->Execute();
	pAlgoTabu->Stats();
	std::cout << std::endl;
	pAlgoTabu->Save(outPath);

	return 0;







}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
