#include "TSPDynamic.h"

void TSPDynamic::Load(std::string file)
{
	handler.updateFile(file);
	positions = loader.sendData();
	size = positions.size();
	FINISHED_STATE = 1 << size;
}

void TSPDynamic::Execute()
{
	//implementation syntax of high_resolution_clock:time_point and calculation below pulled from cplusplus.net
	//url to model used -> http://www.cplusplus.com/reference/chrono/high_resolution_clock/now/
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	tempPath = *(tspDynamic());	//executes the appropriate loaded sort algorithm
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

	//using the time points found above, find the time elapsed; also derived from the above link
	time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
}

void TSPDynamic::Display()
{
	std::cout << "Minimum Cost of Hamiltonian Circuit: " << tempPath.back() << std::endl;
	std::cout << "Number of Nodes in Circuit: " << size << std::endl;
	std::cout << "Path of Minimum Cost: ";
	for (int i = 0; i < tempPath.size() - 1; i++)
	{
		std::cout << tempPath.at(i);

		if (i != tempPath.size() - 2)
		{
			std::cout << ", ";
		}
	}
	std::cout << std::endl;
	std::cout << "Time Taken to Search: " << time_span.count() << " seconds" << std::endl;
}

void TSPDynamic::Stats()
{
	std::cout << "Travelling Salesman Problem - Dynamic Programming Method" << std::endl;
	std::cout << "Number of Nodes in Circuit: " << size << std::endl;
	std::cout << "Minimum Cost of Hamiltonian Circuit: " << tempPath.back() << std::endl;
	std::cout << "Path of Minimum Cost: ";
	for (int i = 0; i < tempPath.size() - 1; i++)
	{
		std::cout << tempPath.at(i);

		if (i != tempPath.size() - 2)
		{
			std::cout << ", ";
		}
	}
	std::cout << std::endl;
	std::cout << "Time Taken to Search: " << time_span.count() << " seconds" << std::endl;
}

void TSPDynamic::Save(std::string outFile)
{
	tempPath.push_back(time_span.count());
	handler.Save(outFile, tempPath);
}

void TSPDynamic::Configure()
{}

float TSPDynamic::getMinTour(int i, int state, std::vector<std::vector<float>>& memo, std::vector<std::vector<int>>& prev)
{

	// Done this tour. Return cost of going back to start node.
	if (state == FINISHED_STATE) return distFormula(i, 0);

	// Return cached answer if already computed.
	if (memo[i][state] != -1) return memo[i][state];

	float minCost = FLT_MAX;
	int index = -1;
	for (int next = 0; next < size; next++) {

		// Skip if the next node has already been visited.
		if ((state & (1 << next)) != 0) continue;

		int nextState = state | (1 << next);
		float newCost = distFormula(i, next) + getMinTour(next, nextState, memo, prev);
		if (newCost < minCost) {
			minCost = newCost;
			index = next;
		}
	}

	prev[i][state] = index;
	return memo[i][state] = minCost;
}

std::vector<float>* TSPDynamic::tspDynamic()
{
	// Run the solver
	std::vector<float>* tour = new std::vector<float>;
	int state = 1 << 0;
	std::vector<std::vector<float>> memo;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < (1 << size); j++) {
			memo.at(i).at(j) = -1;
		}
	}
	std::vector<std::vector<int>> prev;
	for (int k = 0; k < size; k++)
		for (int l = 0; l < (1 << size); l++)
			prev.at(k).at(l) = -1;
	float minTourCost = getMinTour(0, state, memo, prev);

	// Regenerate path
	int index = 0;
	while (true && state < (1 << size)) {
		tour->push_back(index);
		int nextIndex = prev[index][state];
		if (nextIndex == -1) break;
		int nextState = state | (1 << nextIndex);
		state = nextState;
		index = nextIndex;
	}
	tour->push_back(0);
	tour->push_back(minTourCost);
	return tour;
}


float TSPDynamic::distFormula(int one, int two)
{
	std::tuple<float, float, float> tempPos1 = positions.at(one);
	std::tuple<float, float, float> tempPos2 = positions.at(two);
	float temp = pow(std::get<0>(tempPos2) - std::get<0>(tempPos1), 2) +
		pow(std::get<1>(tempPos2) - std::get<1>(tempPos1), 2) +
		pow(std::get<2>(tempPos2) - std::get<2>(tempPos1), 2);

	return temp;
}