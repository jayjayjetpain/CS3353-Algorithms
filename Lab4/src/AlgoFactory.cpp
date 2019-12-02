#include "AlgoFactory.h"
#include "Tabu.h"
#include "Genetic.h"

//static method that takes a value of the class' enum and creates a type of TSP search algo via Alogrithms pointer
Algorithms* AlgoFactory::Create(AlgoFactory::AlgoClass type)
{
	Algorithms* pAlgo;
	switch (type)
	{
	case AlgoFactory::AlgoClass::TABU:
		pAlgo = new Tabu();
		break;

	case AlgoFactory::AlgoClass::GENETIC:
		pAlgo = new Genetic();
		break;

	default:
		pAlgo = nullptr;
	}

	return pAlgo;
}