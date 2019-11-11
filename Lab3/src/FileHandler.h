#pragma once

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

class FileHandler {
public:
	FileHandler();
	FileHandler(std::string);
	void Load();
	void updateFile(std::string);
	std::map <int, std::tuple<float, float, float>>& sendData();
	void Save(std::string, std::vector<float>);

private:
	std::string fileName;
	std::map <int, std::tuple<float, float, float>> positions;
	std::ofstream out;
};


#endif // !FILELOADER_H
