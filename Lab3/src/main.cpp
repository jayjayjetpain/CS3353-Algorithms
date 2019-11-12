#include <algorithm> 
#include <vector>
#include <iostream>
#include <math.h>
#include "AlgoFactory.h"
#include "Algorithms.h"


int main() {

	//Creates an instance of the Algorithm Factory to create each algorithm
	AlgoFactory fact;
	
	//File for input and path to output file for Load and Save respectively
	std::string inFile = "Data/positions4.txt";
	std::string outPath = "OutputData/";

	//handles the creatation of a TSP Brute Force Algo object via AlgoFactory and excutes the search
	Algorithms* pAlgoBrute = fact.Create(AlgoFactory::AlgoClass::BRUTE);
	pAlgoBrute->Load(inFile);
	pAlgoBrute->Execute();
	pAlgoBrute->Stats();
	std::cout << std::endl;
	pAlgoBrute->Save(outPath);

	//handles the creatation of a TSP Dynamic Programming Algo object via AlgoFactory and excutes the search
	Algorithms* pAlgoDynamic = fact.Create(AlgoFactory::AlgoClass::DYNAMIC);
	pAlgoDynamic->Load(inFile);
	pAlgoDynamic->Execute();
	pAlgoDynamic->Stats();
	std::cout << std::endl;
	pAlgoDynamic->Save(outPath);

	return 0;
}
