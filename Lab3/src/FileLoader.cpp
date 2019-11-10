#include "FileLoader.h"

FileLoader::FileLoader()
{
}

FileLoader::FileLoader(std::string file)
{
	this->fileName = file;
}

void FileLoader::Load()
{
	if (fileName == "")
	{
		std::cout << "Need to select file to read" << std::endl;
		return;
	}

	std::ifstream reader;
	//std::ifstream size;

	//int verticies = 0;
	//std::string temp;

	//size.open(this->fileName);
	//if (!(size.is_open()))
	//{
	//	throw std::runtime_error("File Never Loaded");	//if file never opens, throw an execption to stop the program
	//}
	//while (!(size.eof()))
	//{
	//	std::getline(size, temp);
	//	verticies++;
	//}
	//size.close();

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

void FileLoader::updateFile(std::string newFile)
{
	this->fileName = newFile;
}

std::map <int, std::tuple<float, float, float>>& FileLoader::sendData()
{
	return positions;
}