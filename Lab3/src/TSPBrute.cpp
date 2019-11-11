#include "TSPBrute.h"

void TSPBrute::Load(std::string file)
{
	handler.updateFile(file);
	positions = loader.sendData();
	size = positions.size();
	FINISHED_STATE = 1 << size;
}

void TSPBrute::Execute()
{
	//implementation syntax of high_resolution_clock:time_point and calculation below pulled from cplusplus.net
	//url to model used -> http://www.cplusplus.com/reference/chrono/high_resolution_clock/now/
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	tempPath = tspBrute();	//executes the appropriate loaded sort algorithm
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

	//using the time points found above, find the time elapsed; also derived from the above link
	time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
}

void TSPBrute::Display()
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

void TSPBrute::Stats()
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

void TSPBrute::Save(std::string outFile)
{
	tempPath.push_back(time_span.count());
	handler.Save(outFile, tempPath);
}

void TSPBrute::Configure()
{}

std::vector<float> TSPBrute::tspBrute()
{
	// store all vertex apart from source vertex 
	std::vector<float> minPath;
	std::vector<float> vertex;
	for (int i = 1; i < size; i++)
		vertex.push_back(i);

	// store minimum weight Hamiltonian Cycle. 
	int min_path = INT_MAX;
	do {

		// store current Path weight(cost) 
		int current_pathweight = 0;

		// compute current path weight 
		int k = 0;
		for (int i = 0; i < vertex.size(); i++) {
			current_pathweight += distFormula(k, vertex[i]);
			k = vertex[i];
		}
		current_pathweight += distFormula(k, 0);

		// update minimum 
		if (current_pathweight < min_path)
		{
			min_path = std::min(min_path, current_pathweight);
			minPath = vertex;
			minPath.insert(minPath.begin(), 0);
			minPath.push_back(0);
		}

	} while (next_permutation(vertex.begin(), vertex.end()));

	minPath.push_back(min_path);
	return minPath;
}

float TSPBrute::distFormula(int one, int two)
{
	std::tuple<float, float, float> tempPos1 = positions.at(one);
	std::tuple<float, float, float> tempPos2 = positions.at(two);
	float temp = pow(std::get<0>(tempPos2) - std::get<0>(tempPos1), 2) +
		pow(std::get<1>(tempPos2) - std::get<1>(tempPos1), 2) +
		pow(std::get<2>(tempPos2) - std::get<2>(tempPos1), 2);

	return temp;
}