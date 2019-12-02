#pragma once
#ifndef ALGOFACTORY_H
#define ALGOFACTORY_H

#include "Algorithms.h"

/*	This class serves as the single interface for building TSP Algorithms, which extend the abstract class,
 *	Algorithms. The only method is a Create method that takes in a value of its enum and creates the appropriate
 *	TSP algo via Algorithms pointer so the user doesn't have to mess with creation via a poitner
 */

class Algorithms;

class AlgoFactory {
public:
	enum AlgoClass
	{
		TABU = 0,
		GENETIC,
		LAST
	};

	static Algorithms* Create(AlgoFactory::AlgoClass type);

};

#endif // !ALGOFACTORY_H