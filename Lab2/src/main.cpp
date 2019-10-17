#include <iostream>
#include <fstream>
#include <chrono>
#include "Search.h"

int main(int argc, char* argv[])
{
	int start = 1;
	int end = 2;
	if (argc >= 3)
	{
		start = std::stoi(argv[1]);
		end = std::stoi(argv[2]);
	}

	//Code used for creating files of random start/end nodes

	//std::ofstream out("OutputData/randomData3.csv");
	//out << "AlgoName, Graph Type, Nodes in Path, Nodes Explored, Execution Time, Total Distance, Heuristic Cost" << std::endl;
	//std::ofstream out("Data/randoms3.txt");
	//int one = 0;
	//int two = 0;
	//for (int i = 0; i < 100; i++)
	//{
	//	one = rand() % 16 + 1;
	//	two = rand() % 16 + 1;
	//	out << one << ", " << two;
	//	if (i != 99)
	//	{
	//		out << std::endl;
	//	}
	//}

	
	//Code used to load the files of random star/end nodes for testing

	//std::vector<int> one;
	//std::vector<int> two;
	//std::string temp;
	//int temp1, temp2;
	//std::ifstream in("Data/randoms.txt");

	//while (!in.eof())
	//{
	//	std::getline(in, temp, ',');
	//	temp1 = std::stoi(temp);

	//	std::getline(in, temp);
	//	temp2 = std::stoi(temp);

	//	one.push_back(temp1);
	//	two.push_back(temp2);
	//}

	Algorithms* ptr = new Search;
	ptr->Load("Data/graph2.txt", "Data/weights.txt", "Data/positions.txt");
	for (int i = Search::IDFS; i <= Search::ASTAR; i++)
	{
		for (int j = Search::ADJLIST; j <= Search::ADJMATRIX; j++)
		{
			ptr->Select(i, j);	//calls Sort's version of Select, which tell the Sort class which sorting method will later be executed

			//calls Sort's Execute and Stats functions which runs the sort method, timing it, and then print data afterwards
			ptr->Execute(start, end);
			ptr->Stats();

			//calls Sort's Save method which prints the sorted vector and associated stats to an output file usin the original file name
			ptr->Save(".txt");
		}
	}
}