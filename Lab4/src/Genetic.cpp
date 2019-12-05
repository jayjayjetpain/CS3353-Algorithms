#include "Genetic.h"

//Using a passed-in file, get the positions and calculate the distances between each pair of nodes
void Genetic::Load(std::string file)
{
	handler.updateFile(file);	//sets the file to be read and loads the map
	positions = handler.sendData();	//gets the map data from the FileLoader
	size = positions.size();	//sets local variable of the size for easy access in algos
	selectionType = Genetic::SelectionMethods::ELITISM;
	mutationType = Genetic::MutationMethods::SWAP;
	crossoverType = Genetic::CrossoverMethods::ORDERED;

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

//calls the TSP Dynamic Programming method and times its execution
void Genetic::Execute()
{
	//implementation syntax of high_resolution_clock:time_point and calculation below pulled from cplusplus.net
	//url to model used -> http://www.cplusplus.com/reference/chrono/high_resolution_clock/now/
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	tempPath = (*algo)(distances, selectionType, mutationType, crossoverType, 0);	//executes the appropriate loaded sort algorithm
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

	//using the time points found above, find the time elapsed; also derived from the above link
	time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
}

void Genetic::Execute(float stop)
{
	//implementation syntax of high_resolution_clock:time_point and calculation below pulled from cplusplus.net
	//url to model used -> http://www.cplusplus.com/reference/chrono/high_resolution_clock/now/
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	tempPath = (*algo)(distances, selectionType, mutationType, crossoverType, stop);	//executes the appropriate loaded sort algorithm
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

	//using the time points found above, find the time elapsed; also derived from the above link
	time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
}

//Displays the name, min cost, and shortest path of the algo
void Genetic::Display()
{
	std::cout << "Generated Path Distance: " << tempPath.back() << std::endl;
	std::cout << "Generated Best Path: ";
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
void Genetic::Stats()
{
	std::cout << "Travelling Salesman Problem - Genetic Algorithm Method" << std::endl;
	std::cout << "Number of Nodes in Circuit: " << size << std::endl;
	std::cout << "Type of Selection: ";
	if (selectionType == 1)
		std::cout << "Elitism Selection";
	else if (selectionType == 2)
		std::cout << "Roulette Wheel Selection";
	else if (selectionType == 3)
		std::cout << "Tournament Selection";
	std::cout << std::endl;

	std::cout << "Type of Mutation: ";
	if (mutationType == 1)
		std::cout << "Swap Mutation";
	else if (mutationType == 2)
		std::cout << "Inversion Mutation";
	std::cout << std::endl;

	std::cout << "Type of Crossover: ";
	if (crossoverType == 1)
		std::cout << "Ordered Crossover";
	else if (crossoverType == 2)
		std::cout << "PMX Crossover";
	std::cout << std::endl;

	std::cout << "Generated Path Distance: " << tempPath.back() << std::endl;
	std::cout << "Generated Best Path: ";
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
void Genetic::Save(std::string outFile)
{
	std::string ext = outFile + "Genetic.txt";
	tempPath.push_back(time_span.count());	//adds the timing for stats in the file
	handler.Save(ext, "Genetic Algorithm", tempPath);
	//out << time_span.count() << ", ";
}

void Genetic::Select()
{
	algo = &GeneticAlgo::geneticAlgo;
}

void Genetic::Configure(int select, int mut, int cross)
{
	if (select > 0 && select < 4)
	{
		selectionType = select;
	}

	if (mut > 0 && mut < 3)
	{
		mutationType = mut;
	}

	if (cross > 0 && cross < 3)
	{
		crossoverType = cross;
	}
}

//returns the Euclidean distance between two nodes based on the positions in the map
float Genetic::distFormula(int one, int two)
{
	std::tuple<float, float, float> tempPos1 = positions.at(one + 1);
	std::tuple<float, float, float> tempPos2 = positions.at(two + 1);
	float temp = sqrt(pow(std::get<0>(tempPos2) - std::get<0>(tempPos1), 2) +
		pow(std::get<1>(tempPos2) - std::get<1>(tempPos1), 2) +
		pow(std::get<2>(tempPos2) - std::get<2>(tempPos1), 2));

	return temp;
}