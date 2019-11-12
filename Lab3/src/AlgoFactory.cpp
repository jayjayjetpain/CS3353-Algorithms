#include "AlgoFactory.h"
#include "TSPBrute.h"
#include "TSPDynamic.h"

//static method that takes a value of the class' enum and creates a type of TSP search algo via Alogrithms pointer
Algorithms* AlgoFactory::Create(AlgoFactory::AlgoClass type)
{
	Algorithms* pAlgo;
	switch (type)
	{
		case AlgoFactory::AlgoClass::BRUTE:
			pAlgo = new TSPBrute();
			break;

		case AlgoFactory::AlgoClass::DYNAMIC:
			pAlgo = new TSPDynamic();
			break;

		default:
			pAlgo = nullptr;
	}

	return pAlgo;
}