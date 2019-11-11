#include "AlgoFactory.h"
#include "TSPBrute.h"
#include "TSPDynamic.h"

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