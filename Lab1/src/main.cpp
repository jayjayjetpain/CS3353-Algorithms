#include "Sort.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdio>
#include <filesystem>

// namespace fs = std::filesystem;

// int main()
// {
//     std::string path = "/Data";
//     for (const auto & entry : fs::directory_iterator(path))
//         std::cout << entry.path() << std::endl;
// }

int main()
{
	try {


		Algorithms* ptr = new Sort;

		ptr->Load("Data/100030rando.txt");
		ptr->Select(2);
		ptr->Display();
		ptr->Stats();

	}
	catch (...)
	{
		std::cout << "Error";
	}
    return 0;
}