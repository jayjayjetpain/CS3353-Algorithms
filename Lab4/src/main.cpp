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
	std::string inFile = "Data/positions9.txt";
	std::string outPath = "OutputData/";

	//handles the creatation of a TSP Brute Force Algo object via AlgoFactory and excutes the search
	//Algorithms* pAlgoGenetic = fact.Create(AlgoFactory::AlgoClass::GENETIC);
	//pAlgoGenetic->Load(inFile);
	//pAlgoGenetic->Select();
	//pAlgoGenetic->Configure(1,1,1);
	//pAlgoGenetic->Execute();
	//pAlgoGenetic->Stats();
	//std::cout << std::endl;
	//pAlgoGenetic->Save(outPath);

	////handles the creatation of a TSP Dynamic Programming Algo object via AlgoFactory and excutes the search
	Algorithms* pAlgoTabu = fact.Create(AlgoFactory::AlgoClass::TABU);
	pAlgoTabu->Load(inFile);
	pAlgoTabu->Select();
	pAlgoTabu->Configure(2, 20);
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
