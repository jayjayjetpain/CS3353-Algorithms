#include "GeneticAlgo.h"

std::vector<std::vector<float>> GeneticAlgo::distances;

std::vector<float> GeneticAlgo::geneticAlgo(std::vector<std::vector<float>> dist, int selection, int crossover, int mutation)
{
	distances = dist;
	std::vector<float> tempPath = geneticAlgo(dist.size(), 100, 20, 0.01, 500);
	return tempPath;
}

std::vector<float> GeneticAlgo::geneticAlgo(int pathLen, int popSize, int eliteSize, float mutationRate, int generations)
{
	std::vector<std::vector<float>> tempPop = initializePop(popSize, pathLen);
	std::cout << "Initial distance: " << (1 / rankRoutes(tempPop).at(0).second) << std::endl;

	for (int i = 0; i < generations; i++)
	{
		tempPop = nextGeneration(tempPop, eliteSize, mutationRate);
	}

	std::vector<std::pair<int, float>> rankedPop = rankRoutes(tempPop);
	std::cout << "Final distance: " << (1 / rankedPop.at(0).second) << std::endl;
	int bestRouteIndex = rankedPop.at(0).first;
	std::vector<float> bestPath = tempPop.at(bestRouteIndex);
	bestPath.push_back(1 / rankedPop.at(0).second);
	return bestPath;
}

std::vector<float> GeneticAlgo::createRoute(int pathLen)
{
	std::vector<float> route;
	for (int i = 0; i < pathLen; i++)
	{
		route.push_back(i);
	}
	route.push_back(0);

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(route.begin() + 1, route.end() - 1, std::default_random_engine(seed));
	return route;
}

std::vector<std::vector<float>> GeneticAlgo::initializePop(int popSize, int pathLen)
{
	std::vector<std::vector<float>> population;
	for (int i = 0; i < popSize; i++)
	{
		population.push_back(createRoute(pathLen));
	}
	return population;
}

std::vector<std::pair<int, float>> GeneticAlgo::rankRoutes(std::vector<std::vector<float>> population)
{
	std::vector<std::pair<int, float>> fitnessResults;
	for (int i = 0; i < population.size(); i++)
	{
		fitnessResults.push_back(std::make_pair(i, getPathFitness(population.at(i))));
	}
	std::sort(fitnessResults.begin(), fitnessResults.end(), compareFitness);
	return fitnessResults;
}

std::vector<int> GeneticAlgo::selection(std::vector<std::pair<int, float>> popRanked, int eliteSize)
{
	std::vector<int> selectionResults;
	for (int i = 0; i < eliteSize; i++)
	{
		selectionResults.push_back(popRanked.at(i).first);
	}
	for (int j = eliteSize; j < popRanked.size(); j++)
	{
		selectionResults.push_back(popRanked.at(j).first);
	}
	return selectionResults;
}

std::vector<std::vector<float>> GeneticAlgo::matingPool(std::vector<std::vector<float>> population, std::vector<int> selectionResults)
{
	std::vector<std::vector<float>> matingPool;
	for (int i = 0; i < selectionResults.size(); i++)
	{
		int index = selectionResults.at(i);
		matingPool.push_back(population.at(index));
	}
	return matingPool;
}

std::vector<float> GeneticAlgo::breed(std::vector<float> parent1, std::vector<float> parent2)
{
	std::srand(time(NULL));
	std::vector<float> child;
	std::vector<float> childPart1;
	std::vector<float> childPart2;

	int geneA = int(std::rand() % (parent1.size() - 1) + 1);
	int geneB = int(std::rand() % (parent1.size() - 1) + 1);

	int start = std::min(geneA, geneB);
	int end = std::max(geneA, geneB);

	for (int i = start; i < end; i++)
	{
		childPart1.push_back(parent1.at(i));
	}

	for (int j = 0; j < parent2.size(); j++)
	{
		if (std::find(childPart1.begin(), childPart1.end(), parent2.at(j)) == childPart1.end())
		{
			childPart2.push_back(parent2.at(j));
		}
	}

	int inner = 0;
	int outer = 0;
	for (int k = 0; k < parent1.size(); k++)
	{
		if (k >= start && k < end)
		{
			child.push_back(childPart1.at(inner));
			inner++;
		}
		else
		{
			child.push_back(childPart2.at(outer));
			outer++;
		}
	}

	return child;
}

std::vector<std::vector<float>> GeneticAlgo::breedPopulation(std::vector<std::vector<float>> matingPool, int eliteSize)
{

	std::vector<std::vector<float>> children;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::vector<std::vector<float>> pool = matingPool;
	std::shuffle(pool.begin(), pool.end(), std::default_random_engine(seed));

	//int length = matingPool.size() - eliteSize;

	for (int i = 0; i < eliteSize; i++)
	{
		children.push_back(matingPool.at(i));
	}

	for (int j = eliteSize; j < matingPool.size(); j++)
	{
		std::vector<float> child = breed(pool.at(j), pool.at(matingPool.size() - j - 1));
		children.push_back(child);
	}
	return children;
}

std::vector<float> GeneticAlgo::mutate(std::vector<float> individual, float rate)
{
	std::srand(time(NULL));
	for (int i = 0; i < individual.size(); i++)
	{
		if (std::rand() < rate)
		{
			int swapWith = int(std::rand() % individual.size());

			float city1 = individual.at(i);
			float city2 = individual.at(swapWith);

			individual.at(i) = city2;
			individual.at(swapWith) = city1;
		}
	}
	return individual;
}

std::vector<std::vector<float>> GeneticAlgo::mutatePopulation(std::vector<std::vector<float>> population, float rate)
{
	std::vector<std::vector<float>> mutatedPop;

	for (int i = 0; i < population.size(); i++)
	{
		std::vector<float> mutatedInd = mutate(population.at(i), rate);
		mutatedPop.push_back(mutatedInd);
	}
	return mutatedPop;
}

std::vector<std::vector<float>> GeneticAlgo::nextGeneration(static std::vector<std::vector<float>> currentGen, int eliteSize, float rate)
{
	std::vector<std::pair<int, float>> rankedPop = rankRoutes(currentGen);
	std::vector<int> selectionResults = selection(rankedPop, eliteSize);
	std::vector<std::vector<float>> pool = matingPool(currentGen, selectionResults);
	std::vector<std::vector<float>> children = breedPopulation(pool, eliteSize);
	std::vector<std::vector<float>> nextPop = mutatePopulation(children, rate);
	return nextPop;
}

float GeneticAlgo::getPathFitness(std::vector<float> path)
{
	float pathDist = 0;
	for (int i = 0; i < path.size() - 1; i++)
	{
		float fromCity = path.at(i);
		float toCity = path.at(i + 1);
		pathDist += distances.at(fromCity).at(toCity);
	}

	float pathFitness = 1 / (pathDist);
	return pathFitness;
}

bool GeneticAlgo::compareFitness(std::pair<int, float> one, std::pair<int, float> two)
{
	return one.second > two.second;
}