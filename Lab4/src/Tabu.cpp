#include "Tabu.h"

//Using a passed-in file, get the positions and calculate the distances between each pair of nodes
void Tabu::Load(std::string file)
{
	handler.updateFile(file);	//sets the file to be read and loads the map
	positions = handler.sendData();	//gets the map data from the FileLoader
	size = positions.size();	//sets local variable of the size for easy access in algos
	FINISHED_STATE = (1 << size) - 1;	//sets a finish state based on the size
}

//calls the TSP Dynamic Programming method and times its execution
void Tabu::Execute()
{
	//implementation syntax of high_resolution_clock:time_point and calculation below pulled from cplusplus.net
	//url to model used -> http://www.cplusplus.com/reference/chrono/high_resolution_clock/now/
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	tempPath = (*algo)();	//executes the appropriate loaded sort algorithm
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

	//using the time points found above, find the time elapsed; also derived from the above link
	time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
}

//Displays the name, min cost, and shortest path of the algo
void Tabu::Display()
{
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
void Tabu::Stats()
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

//Using the FileHandler of the class and an output file PATH, then send the data and file to the handler to save
void Tabu::Save(std::string outFile)
{
	std::string ext = outFile + "Dynamic.txt";
	tempPath.push_back(time_span.count());	//adds the timing for stats in the file
	handler.Save(ext, "Dynamic Programming", tempPath);
}

void Tabu::Select()
{}

void Tabu::Configure()
{}