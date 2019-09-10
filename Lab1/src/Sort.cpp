#include "Sort.h"
#include <iostream>
#include <fstream>
#include <string>

Sort::Sort()
{
}

void Sort::Load(std::string file)
{
    std::ifstream in;
    in.open(file);
	if (!(in.is_open()))
	{
		throw std::runtime_error("File Never Loaded");
	}
    numList.clear();

    std::string line;
    int tempInt;
    while(!in.eof())
    {
        std::getline(in, line);
        tempInt = std::stoi(line);
        numList.push_back(tempInt);
    }
    totElements = numList.size();
}

void Sort::Execute()
{
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    (*algo)(numList);
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
}

void Sort::Display()
{
    std::cout << "Sorted list: {";
    for(int i = 0; i < numList.size(); i++)
    {
        std::cout << numList.at(i);
        if(i != numList.size()-1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
}

void Sort::Stats()
{
    std::cout << "Name of Sorting Algorithm: " << currAlgo << std::endl;
    std::cout << "Size of Current Data Set: " << totElements << std::endl;
    std::cout << "Time Taken to Sort: " << time_span.count() << " seconds" << std::endl;
}

void Sort::Select(int num)
{
    if(num == 0)
    {
        algo = &SortAlgos<int>::BubbleSort;
        currAlgo = "Bubble Sort";
        Execute();
    }
    else if(num == 1)
    {
        algo = &SortAlgos<int>::MergeSort;
        currAlgo = "Merge Sort";
        Execute();
    }
    else if(num == 2)
    {
        algo = &SortAlgos<int>::InsertionSort;
        currAlgo = "Insertion Sort";
        Execute();
    }
}

void Sort::Save(std::string fileName)
{
    if(!out.is_open())
    {
        out.open(fileName);
    }
    
    out << "Sorted list: {";
    for(int i = 0; i < numList.size(); i++)
    {
        out << numList.at(i);
        if(i != numList.size()-1)
        {
            out << ", ";
        }
    }
    out << "}" << std::endl;

    out << "Name of Sorting Algorithm: " << currAlgo << std::endl;
    out << "Size of Current Data Set: " << totElements << std::endl;
    out << "Time Taken to Sort: " << time_span.count() << " seconds" << std::endl;
}

void Sort::Configure()
{
}