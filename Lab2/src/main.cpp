// Project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <chrono>
#include "Search.h"

int main(int argc, char* argv[])
{
	if (argc >= 3)
	{
		int start = std::stoi(argv[1]);
		int end = std::stoi(argv[2]);
	}

	Algorithms* ptr = new Search;

	//std::ofstream out("Data/randoms.txt");
	//int one = 0;
	//int two = 0;

	//for (int i = 0; i < 100; i++)
	//{
	//	one = rand() % 10000 + 1;
	//	two = rand() % 10000 + 1;
	//	out << one << ", " << two;
	//	if (i != 99)
	//	{
	//		out << std::endl;
	//	}
	//}

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	ptr->Load("Data/largeGraph100.txt", "Data/largeWeights100.txt", "Data/largePositions100.txt");
	for (int i = Search::IDFS; i <= Search::ASTAR; i++)
	{
		for (int j = Search::ADJLIST; j <= Search::ADJMATRIX; j++)
		{
			ptr->Select(i, j);	//calls Sort's version of Select, which tell the Sort class which sorting method will later be executed

			//calls Sort's Execute and Stats functions which runs the sort method, timing it, and then print data afterwards
			ptr->Execute(1, 7);

			//calls Sort's Save method which prints the sorted vector and associated stats to an output file usin the original file name
			ptr->Save(".txt");
		}
	}
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	std::cout << "Time Taken to Run: " << time_span.count() << " seconds" << std::endl << std::endl;
}