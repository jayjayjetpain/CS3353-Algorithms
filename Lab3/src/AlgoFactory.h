#pragma once
#ifndef ALGOFACTORY_H
#define ALGOFACTORY_H

#include "Algorithms.h"

class Algorithms;

class AlgoFactory {
public:
	enum AlgoClass
	{
		BRUTE = 0,
		DYNAMIC,
		LAST
	};

	static Algorithms* Create(AlgoFactory::AlgoClass type);

};

#endif // !ALGOFACTORY_H
