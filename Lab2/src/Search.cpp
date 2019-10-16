#include "Search.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Search::Load(std::string graph, std::string weights, std::string position)
{
	std::ifstream one;
	std::ifstream two;
	std::ifstream three;
	std::ifstream size;

	int verticies = 0;
	int tempInt1, tempInt2, tempInt3;
	std::string temp;

	size.open(graph);
	if (!(size.is_open()))
	{
		throw std::runtime_error("File Never Loaded");	//if file never opens, throw an execption to stop the program
	}
	while (!(size.eof()))
	{
		std::getline(size, temp);
		verticies++;
	}
	matrix.makeMatrix(verticies);
	size.close();

	one.open(graph);
	if (!(one.is_open()))
	{
		throw std::runtime_error("File Never Loaded");	//if file never opens, throw an execption to stop the program
	}
	while (!(one.eof()))
	{
		std::getline(one, temp);
		std::istringstream ss(temp);

		std::getline(ss, temp, ',');
		tempInt1 = std::stoi(temp);
		list.addVertex(tempInt1);
		matrix.addVertex(tempInt1);

		while (std::getline(ss, temp, ','))
		{
			tempInt2 = std::stoi(temp);
			list.addEdge(tempInt1, tempInt2);
			matrix.addEdge(tempInt1, tempInt2);
		}
	}

	two.open(weights);
	float tempFloat1, tempFloat2, tempFloat3;
	if (!(two.is_open()))
	{
		throw std::runtime_error("File Never Loaded");	//if file never opens, throw an execption to stop the program
	}
	while (!(two.eof()))
	{
		std::getline(two, temp, ',');
		tempInt1 = std::stoi(temp);
		
		std::getline(two, temp, ',');
		tempInt2 = std::stoi(temp);

		std::getline(two, temp);
		tempFloat1 = std::stof(temp);

		list.setWeights(tempInt1, tempInt2, tempFloat1);
		matrix.setWeights(tempInt1, tempInt2, tempFloat1);
	}

	int vertex;
	three.open(position);
	if (!((three.is_open())))
	{
		throw std::runtime_error("File Never Loaded");	//if file never opens, throw an execption to stop the program
	}
	while (!(three.eof()))
	{
		std::getline(three, temp, ',');
		vertex = std::stoi(temp);

		std::getline(three, temp, ',');
		tempFloat1 = std::stof(temp);

		std::getline(three, temp, ',');
		tempFloat2 = std::stof(temp);

		std::getline(three, temp);
		tempFloat3 = std::stof(temp);

		list.setPositions(vertex, tempFloat1, tempFloat2, tempFloat3);
		matrix.setPositions(vertex, tempFloat1, tempFloat2, tempFloat3);
	}

	one.close();
	two.close();
	three.close();
}

void Search::Execute(int source, int target)
{
	//implementation syntax of high_resolution_clock:time_point and calculation below pulled from cplusplus.net
	//url to model used -> http://www.cplusplus.com/reference/chrono/high_resolution_clock/now/
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	tempPath = (*algo)(source, target, currGraph);	//executes the appropriate loaded sort algorithm
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

	//using the time points found above, find the time elapsed; also derived from the above link
	time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
}

void Search::Display()
{
	std::vector<int> temp = tempPath.getPath();
	std::cout << "Algorithm Name: " << currAlgo << std::endl;
	std::cout << "Path: ";
	for (int i = 0; i < temp.size(); i++)
	{
		std::cout << temp.at(i) << " ";
	}
	if (temp.size() == 0)
	{
		std::cout << "No path found";
	}
	std::cout << std::endl;
	std::cout << "Number of Nodes: " << tempPath.getTotalNodes() << std::endl;
	std::cout << "Total Nodes Explored: " << tempPath.getExploredNodes() << std::endl;
	std::cout << "Cost of Path: " << tempPath.getCost() << std::endl;
	std::cout << "Distance of Path: " << tempPath.getDist() << std::endl;
	std::cout << "Time Taken to Search: " << time_span.count() << " seconds" << std::endl << std::endl;
}

void Search::Stats()
{
	std::vector<int> temp = tempPath.getPath();
	std::cout << "Algorithm Name: " << currAlgo << std::endl;
	std::cout << "Graph Name: " << graphType << std::endl;
	std::cout << "Path: ";
	for (int i = 0; i < temp.size(); i++)
	{
		std::cout << temp.at(i) << " ";
	}
	if (temp.size() == 0)
	{
		std::cout << "No path found";
	}
	std::cout << std::endl;
	std::cout << "Number of Nodes: " << tempPath.getTotalNodes() << std::endl;
	std::cout << "Total Nodes Explored: " << tempPath.getExploredNodes() << std::endl;
	std::cout << "Cost of Path: " << tempPath.getCost() << std::endl;
	std::cout << "Distance of Path: " << tempPath.getDist() << std::endl;
	std::cout << "Time Taken to Search: " << time_span.count() << " seconds" << std::endl << std::endl;
}

void Search::Select(int searchNum, int graphNum)
{
	if (searchNum == IDFS)
	{
		algo = &SearchAlgos::DFSIter;
		currAlgo = "Iterative_DFS";
	}
	else if (searchNum == RDFS)
	{
		algo = &SearchAlgos::DFSRecur;
		currAlgo = "Recursive_DFS";
	}
	else if (searchNum == IBFS)
	{
		algo = &SearchAlgos::BFSIter;
		currAlgo = "Iterative_BFS";
	}
	else if (searchNum == RBFS)
	{
		algo = &SearchAlgos::BFSRecur;
		currAlgo = "Recursive_BFS";
	}
	else if (searchNum == DIJKSTRA)
	{
		algo = &SearchAlgos::Dijkstra;
		currAlgo = "Dijkstra";
	}
	else if (searchNum == ASTAR)
	{
		algo = &SearchAlgos::AStar;
		currAlgo = "A_Star";
	}

	if (graphNum == ADJLIST)
	{
		currGraph = &list;
		graphType = "Adjacency_List";
	}
	else if (graphNum == ADJMATRIX)
	{
		currGraph = &matrix;
		graphType = "Adjacency_Matrix";
	}
}

void Search::Save(std::string fileExtension)
{
	//adds the new folder path and then algorithm for identificaion between algorithms -> BubbleSort-1000-random.txt
	std::string file = "OutputData/" + currAlgo + "-" + graphType + fileExtension;
	out.open(file);
	if (!out.is_open())
	{
		throw std::runtime_error("No file opened");	//if file never opens, throw an execption to stop the program
	}

	std::vector<int> temp = tempPath.getPath();
	out << "Algorithm Name: " << currAlgo << std::endl;
	out << "Graph Name: " << graphType << std::endl;
	out << "Path: ";
	for (int i = 0; i < temp.size(); i++)
	{
		out << temp.at(i) << " ";
	}
	if (temp.size() == 0)
	{
		out << "No path found";
	}
	out << std::endl;
	out << "Number of Nodes: " << tempPath.getTotalNodes() << std::endl;
	out << "Total Nodes Explored: " << tempPath.getExploredNodes() << std::endl;
	out << "Cost of Path: " << tempPath.getCost() << std::endl;
	out << "Distance of Path: " << tempPath.getDist() << std::endl;
	out << "Time Taken to Search: " << time_span.count() << " seconds" << std::endl << std::endl;

	out.close();	//closes the file after fully printing everything
}

void Search::Configure()
{
}