#include "TSPBrute.h"

//Using a passed-in file, get the positions and calculate the distances between each pair of nodes
void TSPBrute::Load(std::string file)
{
	handler.updateFile(file);	//sets the file to be read and loads the map
	positions = handler.sendData();	//gets the map data from the FileLoader
	size = positions.size();	//sets local variable of the size for easy access in algos
	FINISHED_STATE = (1 << size) - 1;	//sets a finish state based on the size

	//creates enough rows of vectors based on the size of the map
	distances.reserve(size);
	distances.resize(size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j)
			{
				distances.at(i).push_back(0);	//cost from a node to itself is 0
			}
			else if (distances.at(i).size() < j + 1)
			{
				float dist = distFormula(i, j);	//else find the Euclidean distance between the nodes
				distances.at(i).push_back(dist);	//and add them to the distance vector for easy access
				distances.at(j).push_back(dist);
			}
		}
	}
}

//calls the TSP Brute Force method and times its execution
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

//Displays the name, min cost, and shortest path of the algo
void TSPBrute::Display()
{
	std::cout << "Travelling Salesman Problem - Brute Force Method" << std::endl;
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
}

//Displays the name, nodes, min cost, shortest path, and timing of the algo
void TSPBrute::Stats()
{
	std::cout << "Travelling Salesman Problem - Brute Force Method" << std::endl;
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

//Using the FileHandler of the class and an output file PATH, then send the data and file to the handler to save
void TSPBrute::Save(std::string outFile)
{
	std::string ext = outFile + "Brute.txt";
	tempPath.push_back(time_span.count());	//adds the timing for stats in the file
	handler.Save(ext, "Brute Force", tempPath);
}

void TSPBrute::Configure()
{}

//Brute Force method of solving the TSP
std::vector<float> TSPBrute::tspBrute()
{
	//creates the vectors for the path and the verticies
	std::vector<float> minPath;
	std::vector<float> vertex;
	//adds all the vertecies but the start so we can get all the permuations
	for (int i = 1; i < size; i++)
		vertex.push_back(i);

	//set the min weight to INF so we always get a min path 
	float min_path = FLT_MAX;
	do {

		float current_pathweight = 0;

		//get the weight of the current path based on the orientation of the vector
		int k = 0;
		for (int i = 0; i < vertex.size(); i++)
		{
			current_pathweight += distances.at(k).at(vertex[i]);
			k = vertex[i];
		}
		current_pathweight += distances.at(k).at(0); //add the distance back to the start to complete the circuit

		//if this iteration of min is the absolute min, then update the min_cost and min_path 
		if (current_pathweight < min_path)
		{
			min_path = std::min(min_path, current_pathweight);
			minPath = vertex;
			minPath.insert(minPath.begin(), 0);
			minPath.push_back(0);
		}

	} while (next_permutation(vertex.begin(), vertex.end()));	//reorders the vector until all permutaions have been tested

	minPath.push_back(min_path);
	return minPath;
}

//returns the Euclidean distance between two nodes based on the positions in the map
float TSPBrute::distFormula(int one, int two)
{
	std::tuple<float, float, float> tempPos1 = positions.at(one+1);
	std::tuple<float, float, float> tempPos2 = positions.at(two+1);
	float temp = sqrt(pow(std::get<0>(tempPos2) - std::get<0>(tempPos1), 2) +
		pow(std::get<1>(tempPos2) - std::get<1>(tempPos1), 2) +
		pow(std::get<2>(tempPos2) - std::get<2>(tempPos1), 2));

	return temp;
}