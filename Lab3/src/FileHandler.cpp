#include "FileHandler.h"

FileHandler::FileHandler()
{
}

FileHandler::FileHandler(std::string file)
{
	this->fileName = file;
	this->Load();
}

//Using the file used to create/updated with, read the positions file and make a map with node # and positions
void FileHandler::Load()
{
	//checks to ensure a file was provided
	if (fileName == "")
	{
		std::cout << "Need to select file to read" << std::endl;
		return;
	}

	//if re-loading, then clear the old data from the map
	if (positions.size() > 0)
	{
		positions.clear();
	}

	std::ifstream reader;

	int vertex;
	std::string temp;
	float tempFloat1, tempFloat2, tempFloat3;
	reader.open(this->fileName);
	if (!((reader.is_open())))
	{
		throw std::runtime_error("File Never Loaded");	//if file never opens, throw an execption to stop the program
	}
	while (!(reader.eof()))
	{
		std::getline(reader, temp, ',');
		vertex = std::stoi(temp);

		std::getline(reader, temp, ',');
		tempFloat1 = std::stof(temp);

		std::getline(reader, temp, ',');
		tempFloat2 = std::stof(temp);

		std::getline(reader, temp);
		tempFloat3 = std::stof(temp);

		//reads the node number and gets its positions and then puts it in the map
		positions.emplace(vertex, std::make_tuple(tempFloat1, tempFloat2, tempFloat3));
	}

	reader.close();
}

//updates the file to read in and then re-load the map
void FileHandler::updateFile(std::string newFile)
{
	this->fileName = newFile;
	this->Load();
}

//sends the mpa of positions to the algo classes
std::map <int, std::tuple<float, float, float>>& FileHandler::sendData()
{
	return positions;
}

//using a passed in file and the data from the tsp algos, print the stats to that file
void FileHandler::Save(std::string outFile, std::string algoName, std::vector<float> data)
{
	//opens the output file of the class
	out.open(outFile);
	if (!out.is_open())
	{
		throw std::runtime_error("Output file not loaded");	//ensures a file was actually opened
	}

	//prints which algo, the number of nodes in the circuit, the min cost, the path, and the timing of the algo
	out << "Travelling Salesman Problem - " << algoName << " Method" << std::endl;
	out << "Number of Nodes in Circuit: " << (data.size() - 2) << std::endl;
	out << "Minimum Cost of Hamiltonian Circuit: " << data.at(data.size() - 2) << std::endl;
	out << "Path of Minimum Cost: ";
	for (int i = 0; i < data.size() - 2; i++)
	{
		out << data.at(i);

		if (i != data.size() - 3)
		{
			out << ", ";
		}
	}
	out << std::endl;
	out << "Time Taken to Search: " << data.back() << " seconds" << std::endl;
}