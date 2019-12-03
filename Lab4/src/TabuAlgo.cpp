#include "TabuAlgo.h"

std::vector<std::vector<float>> TabuAlgo::distances;
std::list<std::pair<float, float>>::const_iterator TabuAlgo::currBest;

std::vector<float> TabuAlgo::tabuAlgo(std::vector<std::vector<float>> dist, int neighborhoodSearch, int tabuSize)
{
	distances = dist;
	std::vector<float> bestPath;
	std::vector<float> tempPath;
	for (int i = 0; i < 5; i++)
	{
		std::vector<float> firstPath = initialSolution(dist.size());
		float firstDist = getPathDistance(firstPath);
		tempPath = tabuAlgo(firstPath, firstDist, 3000, tabuSize, neighborhoodSearch);
		if (bestPath.size() == 0)
		{
			bestPath = tempPath;
		}
		if (tempPath.back() < bestPath.back())
		{
			bestPath = tempPath;
		}
	}
	return bestPath;
}

std::vector<float> TabuAlgo::tabuAlgo(std::vector<float> firstPath, float firstDist, int iterations, int tabuSize, int neighborhoodSearch)
{
	int count = 1;
	int change_count = 1;
	std::vector<float> solution = firstPath;
	std::list<std::pair<float, float>> tabu_list;
	currBest = tabu_list.begin();
	float bestDist = firstDist;
	std::vector<float> bestSolutionEver = solution;

	while (count <= iterations)
	{
		std::vector<std::vector<float>> neighborhood = find_neighborhood(solution, neighborhoodSearch);
		int indexOfBest = 0;
		std::vector<float> best_solution = neighborhood.at(indexOfBest);

		bool found = false;
		while (!found)
		{
			int i = 0;
			float firstChange = -1;
			float secondChange = -1;
			while (i < best_solution.size()-1)
			{
				if (best_solution.at(i) != solution.at(i))
				{
					firstChange = best_solution.at(i);
					secondChange = solution.at(i);
					break;
				}
				i++;
			}

			if (firstChange > 0 && secondChange > 0 &&
				std::find(tabu_list.begin(), tabu_list.end(), std::make_pair(firstChange, secondChange)) == tabu_list.end() &&
				std::find(tabu_list.begin(), tabu_list.end(), std::make_pair(secondChange, firstChange)) == tabu_list.end())
			{
				tabu_list.push_back(std::make_pair(firstChange, secondChange));
				found = true;
				solution = best_solution;
				float distance = solution.back();
				solution.pop_back();
				if (distance < bestDist)
				{
					bestDist = distance;
					bestSolutionEver = solution;
					change_count = 1;
				}
			}
			else
			{
				indexOfBest += 1;
				change_count++;
				if (indexOfBest >= neighborhood.size())
				{
					break;
				}
				best_solution = neighborhood.at(indexOfBest);

				if (change_count > 500)
				{
					bestSolutionEver.push_back(bestDist);
					return bestSolutionEver;
				}
			}
		}

		if (tabu_list.size() >= tabuSize)
		{
			tabu_list.pop_front();
		}

		count++;
	}
	bestSolutionEver.push_back(bestDist);
	return bestSolutionEver;
}

std::vector<float> TabuAlgo::initialSolution(int pathSize)
{
	std::vector<float> route;
	for (int i = 0; i < pathSize; i++)
	{
		route.push_back(i);
	}
	route.push_back(0);

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(route.begin() + 1, route.end() - 1, std::default_random_engine(seed));
	return route;
}

std::vector<std::vector<float>> TabuAlgo::find_neighborhood(std::vector<float> solution, int neighborhoodSearch)
{
	std::vector<std::vector<float>> neighborhood;
	if (neighborhoodSearch == 1)
	{
		neighborhood = find_neighborhood_swap(solution);
	}
	else if (neighborhoodSearch == 2)
	{
		neighborhood = find_neighborhood_invert(solution);
	}
	return neighborhood;
}

std::vector<std::vector<float>> TabuAlgo::find_neighborhood_swap(std::vector<float> solution)
{
	std::vector<std::vector<float>> neighborhood;
	for (int i = 1; i < solution.size() - 1; i++)
	{
		int index1 = i;
		for (int j = 1; j < solution.size() - 1; j++)
		{
			int index2 = j;
			if (solution.at(index1) == solution.at(index2))
				continue;

			std::vector<float> tempPath;
			tempPath = solution;
			tempPath.at(index1) = solution.at(j);
			tempPath.at(index2) = solution.at(i);

			float distance = 0;
			distance = getPathDistance(tempPath);
			tempPath.push_back(distance);

			if (std::find(neighborhood.begin(), neighborhood.end(), tempPath) == neighborhood.end())
			{
				neighborhood.push_back(tempPath);
			}
		}
	}
	std::sort(neighborhood.begin(), neighborhood.end(), compareDist);
	return neighborhood;
}

std::vector<std::vector<float>> TabuAlgo::find_neighborhood_invert(std::vector<float> solution)
{
	std::vector<std::vector<float>> neighborhood;
	for (int i = 1; i < solution.size() - 1; i++)
	{
		int index1 = i;
		for (int j = 1; j < solution.size() - 1; j++)
		{
			int index2 = j;
			if (solution.at(index1) == solution.at(index2))
				continue;

			std::vector<float> tempPath;
			tempPath = solution;

			int start = std::min(i, j);
			int end = std::max(i, j);
			std::reverse(tempPath.begin() + start, tempPath.begin() + end);

			float distance = 0;
			distance = getPathDistance(tempPath);
			tempPath.push_back(distance);

			if (std::find(neighborhood.begin(), neighborhood.end(), tempPath) == neighborhood.end())
			{
				neighborhood.push_back(tempPath);
			}
		}
	}
	std::sort(neighborhood.begin(), neighborhood.end(), compareDist);
	return neighborhood;
}

float TabuAlgo::getPathDistance(std::vector<float> path)
{
	float pathDist = 0;
	for (int i = 0; i < path.size() - 1; i++)
	{
		float fromCity = path.at(i);
		float toCity = path.at(i + 1);
		pathDist += distances.at(fromCity).at(toCity);
	}

	return pathDist;
}

bool TabuAlgo::compareDist(std::vector<float> one, std::vector<float> two)
{
	return one.back() < two.back();
}