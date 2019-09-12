#pragma once
#ifndef SORT_H
#define SORT_H

#include "Algorithms.h"
#include "SortAlgos.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <ratio>

/* Derived Class of Base class Algorithms - Fully implements all pure virtual functions found in Algorithms class. Specifically,
 * this Sort class loads files into a vector to be sorted and timed using the standard library high resolution clock, displays
 * stats of the name of the algorithm, size and type of data set, and execution time, selects the type of sort from a included
 * (but not base class) SortAlgos using a function pointer to the memory locations of that class's sorts, and saving the sorted
 * vector and its stats listed above to an output file. Configure is not set up to do anything for this class.
 */

class Sort : public Algorithms  {
public:
    virtual void Load(std::string);
    virtual void Execute();
    virtual void Display();
    virtual void Stats();
    virtual void Select(int);
    virtual void Save(std::string);
    virtual void Configure();

	//enumeration of sorting algorithms' names to make iterating/chosing which sort easier
	enum SortingAlgos {
		BUBBLE = 0,
		MERGE,
		INSERTION,
		LAST
	};

private:
	//function pointer used to access the memory locations in SortAlgos.h to dynamically select and execute each sorting algorithm
    void(*algo)(std::vector<int>&) = nullptr;
	//local vector containing the list of numbers from the input files
    std::vector<int> numList;

	//storage variables for printing statistics; time to sort, name of algorithm, type of data set, and total elements sorted
    std::chrono::duration<double> time_span;
    std::string currAlgo;
	std::string dataType;
    int totElements;

	//class's own ofstream used to open the output files and print the sorted vectors and their stats
    std::ofstream out;
};

#endif // Sort_H