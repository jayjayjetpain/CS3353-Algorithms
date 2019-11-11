#include "FileHandler.h"

FileHandler::FileHandler()
{
}

FileHandler::FileHandler(std::string file)
{
	this->fileName = file;
}

void FileHandler::Load()
{
	if (fileName == "")
	{
		std::cout << "Need to select file to read" << std::endl;
		return;
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

		positions.emplace(vertex, std::make_tuple(tempFloat1, tempFloat2, tempFloat3));
	}

	reader.close();
}

void FileHandler::updateFile(std::string newFile)
{
	this->fileName = newFile;
}

std::map <int, std::tuple<float, float, float>>& FileHandler::sendData()
{
	return positions;
}

void FileHandler::Save(std::string outFile, std::vector<float> data)
{
	out.open(outFile);
	if (!out.is_open())
	{
		throw std::runtime_error("Output file not loaded");
	}

	out << "Travelling Salesman Problem - Dynamic Programming Method" << std::endl;
	out << "Number of Nodes in Circuit: " << (data.size() - 2) << std::endl;
	out << "Minimum Cost of Hamiltonian Circuit: " << data.at(data.size() - 2) << std::endl;
	out << "Path of Minimum Cost: ";
	for (int i = 0; i < data.size() - 2; i++)
	{
		std::cout << data.at(i);

		if (i != data.size() - 3)
		{
			out << ", ";
		}
	}
	out << std::endl;
	out << "Time Taken to Search: " << data.back() << " seconds" << std::endl;
}