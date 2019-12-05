#include "GeneticAlgo.h"

std::vector<std::vector<float>> GeneticAlgo::distances;

std::vector<float> GeneticAlgo::geneticAlgo(std::vector<std::vector<float>> dist, int selection, int mutation, int crossover, float stop)
{
	distances = dist;
	std::srand(time(0));
	//std::ofstream out;
	//out.open("OutputData/Genetic.csv");
	std::vector<float> tempPath = geneticAlgo(dist.size(), 100, 0.04, 500, selection, mutation, crossover, stop);
	return tempPath;
}

std::vector<float> GeneticAlgo::geneticAlgo(int pathLen, int popSize, float mutationRate, int generations,
											int selectionType, int mutationType, int crossoverType, float stop)
{
	std::vector<std::vector<float>> tempPop = initializePop(popSize, pathLen);
	std::cout << "Initial distance: " << (1 / rankRoutes(tempPop).at(0).second) << std::endl;
	//out << 1 << ", " << (1 / rankRoutes(tempPop).at(0).second) << std::endl;
	bool iter = false;
	if (stop == 0)
	{
		iter = true;
	}

	std::vector<std::pair<int, float>> rankedPop;
	if (!iter)
	{
		do
		{
			tempPop = nextGeneration(tempPop, selectionType, mutationType, crossoverType, mutationRate);
			rankedPop = rankRoutes(tempPop);
			//std::cout << (1 / rankedPop.at(0).second) << std::endl;
		} while ((1 / rankedPop.at(0).second) > stop);
	}
	else
	{
		for (int i = 2; i < generations; i++)
		{
			tempPop = nextGeneration(tempPop, selectionType, mutationType, crossoverType, mutationRate);
			rankedPop = rankRoutes(tempPop);
			//out << i << ", " << (1 / rankRoutes(tempPop).at(0).second) << std::endl;
		}
		/*rankedPop = rankRoutes(tempPop);*/
	}

	std::cout << "Final distance: " << (1 / rankedPop.at(0).second) << std::endl;
	int bestRouteIndex = rankedPop.at(0).first;
	std::vector<float> bestPath = tempPop.at(bestRouteIndex);
	bestPath.push_back(1 / rankedPop.at(0).second);
	return bestPath;
}

std::vector<float> GeneticAlgo::createRoute(int pathLen, int j)
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
		population.push_back(createRoute(pathLen, i));
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

std::vector<int> GeneticAlgo::selection(std::vector<std::pair<int, float>> popRanked, int selectionType)
{
	std::vector<int> selectionResults;

	if (selectionType == 1)
	{
		selectionResults = selectionElitism(popRanked, popRanked.size() / 5);
	}
	else if (selectionType == 2)
	{
		selectionResults = selectionRoulette(popRanked, popRanked.size() / 5);
	}
	else if (selectionType == 3)
	{
		selectionResults = selectionTournament(popRanked, popRanked.size() / 5);
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

std::vector<float> GeneticAlgo::breed(std::vector<float> parent1, std::vector<float> parent2, int crossoverType)
{
	std::vector<float> child;
	if (crossoverType == 1)
	{
		child = breedOrdered(parent1, parent2);
	}
	else if (crossoverType == 2)
	{
		child = breedPMX(parent1, parent2);
	}

	return child;
}

std::vector<std::vector<float>> GeneticAlgo::breedPopulation(std::vector<std::vector<float>> matingPool, int eliteSize, int crossoverType)
{

	std::vector<std::vector<float>> children;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::vector<std::vector<float>> pool = matingPool;
	std::shuffle(pool.begin(), pool.end(), std::default_random_engine(seed));

	for (int i = 0; i < eliteSize; i++)
	{
		children.push_back(matingPool.at(i));
	}

	for (int j = eliteSize; j < matingPool.size(); j++)
	{
		std::vector<float> child = breed(pool.at(j), pool.at(matingPool.size() - j - 1), crossoverType);
		children.push_back(child);
	}
	return children;
}

std::vector<float> GeneticAlgo::mutate(std::vector<float> individual, float rate, int mutationType)
{
	std::vector<float> newIndividual;
	if (mutationType == 1)
	{
		newIndividual = mutateSwap(individual, rate);
	}
	else if (mutationType == 2)
	{
		newIndividual = mutateInvert(individual, rate);
	}

	return newIndividual;
}

std::vector<std::vector<float>> GeneticAlgo::mutatePopulation(std::vector<std::vector<float>> population, float rate, int mutationType)
{
	std::vector<std::vector<float>> mutatedPop;

	for (int i = 0; i < population.size(); i++)
	{
		std::vector<float> mutatedInd = mutate(population.at(i), rate, mutationType);
		mutatedPop.push_back(mutatedInd);
	}
	return mutatedPop;
}

std::vector<std::vector<float>> GeneticAlgo::nextGeneration(std::vector<std::vector<float>> currentGen, 
															int selectionType, int mutationType, int crossoverType, float rate)
{
	std::vector<std::pair<int, float>> rankedPop = rankRoutes(currentGen);
	std::vector<int> selectionResults = selection(rankedPop, selectionType);
	std::vector<std::vector<float>> pool = matingPool(currentGen, selectionResults);
	std::vector<std::vector<float>> children = breedPopulation(pool, 20, crossoverType);
	std::vector<std::vector<float>> nextPop = mutatePopulation(children, rate, mutationType);
	return nextPop;
}

std::vector<int> GeneticAlgo::selectionElitism(std::vector<std::pair<int, float>> popRanked, int eliteSize)
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

std::vector<int> GeneticAlgo::selectionRoulette(std::vector<std::pair<int, float>> popRanked, int eliteSize)
{
	float totalFitness = 0;
	for (int k = 0; k < popRanked.size(); k++)
	{
		totalFitness += popRanked.at(k).second;
	}

	std::vector<int> selectionResults;
	while(selectionResults.size() < eliteSize)
	{
		float pick = std::rand() % 100;
		for (int j = 0; j < popRanked.size(); j++)
		{
			if (pick <= (popRanked.at(j).second/totalFitness)*100)
			{
				selectionResults.push_back(popRanked.at(j).first);
				break;
			}
		}
	}
	for (int i = eliteSize; i < popRanked.size(); i++)
	{
		selectionResults.push_back(popRanked.at(i).first);
	}
	return selectionResults;
}

std::vector<int> GeneticAlgo::selectionTournament(std::vector<std::pair<int, float>> popRanked, int eliteSize)
{
	std::vector<int> selectionResults;
	while (selectionResults.size() < eliteSize)
	{
		std::vector<int> indexList;
		for (int k = 0; k < 20; k++)
		{
			int temp = std::rand() % popRanked.size();
			indexList.push_back(temp);
		}

		int bestIndex = indexList.at(0);
		for (int i = 0; i < indexList.size(); i++)
		{
			if (popRanked.at(indexList.at(i)).second > popRanked.at(bestIndex).second)
			{
				bestIndex = indexList.at(i);
			}
		}
		selectionResults.push_back(popRanked.at(bestIndex).first);
	}
	for (int j = eliteSize; j < popRanked.size(); j++)
	{
		selectionResults.push_back(popRanked.at(j).first);
	}
	return selectionResults;
}

std::vector<float> GeneticAlgo::mutateSwap(std::vector<float> individual, float rate)
{
	for (int i = 1; i < individual.size() - 1; i++)
	{
		float num = ((float)(std::rand()) / (RAND_MAX));
		if (num < rate)
		{
			int swapWith = int(std::rand() % (individual.size() - 2) + 1);

			float city1 = individual.at(i);
			float city2 = individual.at(swapWith);

			individual.at(i) = city2;
			individual.at(swapWith) = city1;
			//std::cout << "mutate swap!" << std::endl;
		}
	}
	return individual;
}

std::vector<float> GeneticAlgo::mutateInvert(std::vector<float> individual, float rate)
{
	for (int i = 1; i < individual.size() - 1; i++)
	{
		float num = ((float)(std::rand()) / (RAND_MAX));
		if (num < rate)
		{
			int swapWith = int(std::rand() % (individual.size() - 2) + 1);

			int start = std::min(i, swapWith);
			int end = std::max(i, swapWith);

			std::reverse(individual.begin() + start, individual.begin() + end);

			//std::cout << "mutate invert!" << std::endl;
		}
	}
	return individual;
}

std::vector<float> GeneticAlgo::breedOrdered(std::vector<float> parent1, std::vector<float> parent2)
{
	std::vector<float> child;
	std::vector<float> childPart1;
	std::vector<float> childPart2;

	int geneA = int(std::rand() % (parent1.size() - 2) + 1);
	int geneB = int(std::rand() % (parent1.size() - 2) + 1);

	int start = std::min(geneA, geneB);
	int end = std::max(geneA, geneB);

	for (int i = start; i < end; i++)
	{
		childPart1.push_back(parent1.at(i));
	}

	for (int j = 1; j < parent2.size() - 1; j++)
	{
		if (std::find(childPart1.begin(), childPart1.end(), parent2.at(j)) == childPart1.end())
		{
			childPart2.push_back(parent2.at(j));
		}
	}

	int inner = 0;
	int outer = 0;
	child.push_back(0);
	for (int k = 1; k < parent1.size() - 1; k++)
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
	child.push_back(0);

	return child;
}

std::vector<float> GeneticAlgo::breedPMX(std::vector<float> parent1, std::vector<float> parent2)
{
	std::vector<float> child;

	int geneA = int(std::rand() % (parent1.size() - 2) + 1);
	int geneB = int(std::rand() % (parent1.size() - 2) + 1);

	int start = std::min(geneA, geneB);
	int end = std::max(geneA, geneB);

	child.resize(parent1.size());
	for (int i = start; i < end; i++)
	{
		child.at(i) = parent1.at(i);
	}

	for (int j = start; j < end; j++)
	{
		float firstVal = parent2.at(j);
		float currVal = parent2.at(j);
		if (std::find(child.begin(), child.end(), currVal) == child.end())
		{
			bool added = false;
			float parallelVal = parent1.at(j);
			while (!added)
			{
				float searchIndex = 0;
				std::vector<float>::iterator temp = std::find(parent2.begin(), parent2.end(), parallelVal);
				searchIndex = std::distance(parent2.begin(), temp);

				if (searchIndex < start || searchIndex >= end)
				{
					child.at(searchIndex) = firstVal;
					added = true;
				}
				else
				{
					currVal = parallelVal;
					std::vector<float>::iterator temp = std::find(parent2.begin(), parent2.end(), parallelVal);
					int index = std::distance(parent2.begin(), temp);
					parallelVal = parent1.at(index);
				}
			}
		}
	}

	for (int l = 1; l < parent2.size() - 1 ; l++)
	{
		if (child.at(l) == 0)
		{
			child.at(l) = parent2.at(l);
		}
	}

	return child;
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