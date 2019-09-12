#include "Sort.h"
#include <iostream>
#include <fstream>
#include <string>

//Load takes the name of a file as input, opens the file and moves all the data (on separate lines) into a local vector
//and obtains some info for later such as the type and size of the data set
void Sort::Load(std::string file)
{
    std::ifstream in;
    in.open(file);
	if (!(in.is_open()))
	{
		throw std::runtime_error("File Never Loaded");	//if file never opens, throw an execption to stop the program
	}
    numList.clear();	//clears the vector from the previous load/iteration

    std::string line;
    int tempInt;
    while(!in.eof())
    {
        std::getline(in, line);			//gets line by line as a string using getline
        tempInt = std::stoi(line);		//converts the string to an int to put in the vector
        numList.push_back(tempInt);		//and stores it into the vector
    }
    totElements = numList.size();	//size of vector for stats later

	//file name structure: dataSize-dataType.txt
	std::string temp = file.substr(file.find_last_of("-")+1);	//gets the dataType.txt part of the file name
	dataType = temp.erase(temp.find_last_of("."), 4);			//isolates the dataType from the name for later stats
}

//using the sorting algorithm pointed to by the fuction pointer, sorts the vector and gets the execution time for the stats
void Sort::Execute()
{
	//implementation syntax of high_resolution_clock:time_point and calculation below pulled from cplusplus.net
	//url to model used -> http://www.cplusplus.com/reference/chrono/high_resolution_clock/now/
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    (*algo)(numList);	//executes the appropriate loaded sort algorithm
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

	//using the time points found above, find the time elapsed; also derived from the above link
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
}

//prints the contents of the sorted/unsorted vector in form {n, n, n, n, n, n, ...}
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

//prints the stats found from the other methods for the current data set type/size and current algorithm
void Sort::Stats()
{
    std::cout << "Name of Sorting Algorithm: " << currAlgo << std::endl;		//from Select
    std::cout << "Size of Current Data Set: " << totElements << std::endl;		//both from Load
	std::cout << "Type of Current Data Set: " << dataType << std::endl;
	std::cout << "Time Taken to Sort: " << time_span.count() << " seconds" << std::endl << std::endl;	//from Execute
}

//using the enum of the class, the int passed-in determines the sorting algorithm to point to with the function pointer
void Sort::Select(int num)
{
    if(num == BUBBLE)
    {
        algo = &SortAlgos<int>::BubbleSort;		//points the function pointer to the memory location of SortAlgos' Bubble Sort
        currAlgo = "BubbleSort";		//stores the name of the algorithm for the stats
    }
    else if(num == MERGE)
    {
        algo = &SortAlgos<int>::MergeSort;		//points the function pointer to the memory location of SortAlgos' Merge Sort
        currAlgo = "MergeSort";			//stores the name of the algorithm for the stats
    }
    else if(num == INSERTION)
    {
        algo = &SortAlgos<int>::InsertionSort;	//points the function pointer to the memory location of SortAlgos' Insertion Sort
        currAlgo = "InsertionSort";		//stores the name of the algorithm for the stats
    }
}

//using the name of the file in the Data folder, construct the new output file name and print the sorted vector and its stats to that file
void Sort::Save(std::string fileNames)
{
	//adds the new folder path and then algorithm for identificaion between algorithms -> BubbleSort-1000-random.txt
	std::string temp = "OutputData/" + currAlgo + "-" + fileNames;
	out.open(temp);
    if(!out.is_open())
    {
        throw std::runtime_error("No file opened");	//if file never opens, throw an execption to stop the program
    }
    
	//prints the sorted vector line by line
    out << "Sorted list:" << std::endl;
    for(int i = 0; i < numList.size(); i++)
    {
		out << numList.at(i) << std::endl;
    }

	//prints the exact same data as in the Stats function but this time to an output stream
    out << "Name of Sorting Algorithm: " << currAlgo << std::endl;
    out << "Size of Current Data Set: " << totElements << std::endl;
	out << "Type of Current Data Set: " << dataType << std::endl;
    out << "Time Taken to Sort: " << time_span.count() << " seconds" << std::endl;

	out.close();	//closes the file after fully printing everything
}

//Configure not used for this lab
void Sort::Configure()
{
}