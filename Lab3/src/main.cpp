// Program3.0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm> 
#include <vector>
#include <iostream>
#include <math.h>
#include "AlgoFactory.h"
#include "Algorithms.h"


int main() {

	AlgoFactory fact;
	
	for (int i = AlgoFactory::AlgoClass::BRUTE; i < AlgoFactory::AlgoClass::LAST; i++)
	{
		Algorithms* pAlgo = fact.Create(i);
		pAlgo->Load("Data/positions4.txt");
		pAlgo->Execute();
		pAlgo->Stats();
		pAlgo->Save("OutputData/pos4");
	}

	return 0;
}
