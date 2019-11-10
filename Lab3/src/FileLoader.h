#pragma once

#ifndef FILELOADER_H
#define FILELOADER_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <tuple>

class FileLoader
{
public:
	FileLoader();
	FileLoader(std::string);
	void Load();
	void updateFile(std::string);
	std::map <int, std::tuple<float, float, float>>& sendData();

private:
	std::string fileName;
	std::map <int, std::tuple<float, float, float>> positions;
};


#endif // !FILELOADER_H
