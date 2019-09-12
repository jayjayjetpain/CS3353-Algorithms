#include "Sort.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdio>

int main()
{
		//creates a vector of all the file names to be parsed by each sorting algorithm
		std::vector<std::string> files = { "10-random.txt", "1000-random.txt", "10000-random.txt", "100000-random.txt",
										  "10-reverse.txt", "1000-reverse.txt", "10000-reverse.txt", "100000-reverse.txt",
										  "10-2080.txt", "1000-2080.txt", "10000-2080.txt", "100000-2080.txt",
										  "10-30rando.txt", "1000-30rando.txt", "10000-30rando.txt", "100000-30rando.txt"};

		
		std::string prefix = "Data/";	//adds the prefix tag that will precede each file name

		//creates a Sort object using a base class Algorithm pointer to call virual, overloaded methods in Sort class
		Algorithms* ptr = new Sort;

		//using the enum from the Sort class, run through the algorithms from Bubble to Insertion
		for (int i = Sort::BUBBLE; i <= Sort::INSERTION; i++)
		{
			
			ptr->Select(i);	//calls Sort's version of Select, which tell the Sort class which sorting method will later be executed
			//for each sorting method, loop through each file and sort them
			for (int j = 0; j < files.size(); j++)
			{
				std::string fileNames = prefix + files.at(j);	//creates the full folder/file path for the input stream
				ptr->Load(fileNames);	//calls Sort's Load function to read all the integers from a file into a local vector

				//calls Sort's Execute and Stats functions which runs the sort method, timing it, and then print data afterwards
				ptr->Execute();
				ptr->Stats();

				//calls Sort's Save method which prints the sorted vector and associated stats to an output file usin the original file name
				ptr->Save(files.at(j));
			}
		}


    return 0;
}