#include "TSPDynamic.h"

//Using a passed-in file, get the positions and calculate the distances between each pair of nodes
void TSPDynamic::Load(std::string file)
{
	handler.updateFile(file);	//sets the file to be read and loads the map
	positions = handler.sendData();	//gets the map data from the FileLoader
	size = positions.size();	//sets local variable of the size for easy access in algos
	FINISHED_STATE = (1 << size) - 1;	//sets a finish state based on the size

	//creates enough rows of vectors based on the size of the map
	distances.reserve(size);
	distances.resize(size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j)
			{
				distances.at(i).push_back(0);	//cost from a node to itself is 0
			}
			else if (distances.at(i).size() < j + 1)
			{
				float dist = distFormula(i, j);	//else find the Euclidean distance between the nodes
				distances.at(i).push_back(dist);	//and add them to the distance vector for easy access
				distances.at(j).push_back(dist);
			}
		}
	}

}

//calls the TSP Dynamic Programming method and times its execution
void TSPDynamic::Execute()
{
	//implementation syntax of high_resolution_clock:time_point and calculation below pulled from cplusplus.net
	//url to model used -> http://www.cplusplus.com/reference/chrono/high_resolution_clock/now/
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	tempPath = *(tspDynamic());	//executes the appropriate loaded sort algorithm
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

	//using the time points found above, find the time elapsed; also derived from the above link
	time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
}

//Displays the name, min cost, and shortest path of the algo
void TSPDynamic::Display()
{
	std::cout << "Minimum Cost of Hamiltonian Circuit: " << tempPath.back() << std::endl;
	std::cout << "Path of Minimum Cost: ";
	for (int i = 0; i < tempPath.size() - 1; i++)
	{
		std::cout << tempPath.at(i);

		if (i != tempPath.size() - 2)
		{
			std::cout << ", ";
		}
	}
	std::cout << std::endl;
}

//Displays the name, nodes, min cost, shortest path, and timing of the algo
void TSPDynamic::Stats()
{
	std::cout << "Travelling Salesman Problem - Dynamic Programming Method" << std::endl;
	std::cout << "Number of Nodes in Circuit: " << size << std::endl;
	std::cout << "Minimum Cost of Hamiltonian Circuit: " << tempPath.back() << std::endl;
	std::cout << "Path of Minimum Cost: ";
	for (int i = 0; i < tempPath.size() - 1; i++)
	{
		std::cout << tempPath.at(i);

		if (i != tempPath.size() - 2)
		{
			std::cout << ", ";
		}
	}
	std::cout << std::endl;
	std::cout << "Time Taken to Search: " << time_span.count() << " seconds" << std::endl;
}

//Using the FileHandler of the class and an output file PATH, then send the data and file to the handler to save
void TSPDynamic::Save(std::string outFile)
{
	std::string ext = outFile + "Dynamic.txt";
	tempPath.push_back(time_span.count());	//adds the timing for stats in the file
	handler.Save(ext, "Dynamic Programming", tempPath);
}

void TSPDynamic::Configure()
{}

//returns the shortest distance of a Hamiltonian circuit of the current graph (using memo and bitmask state)
float TSPDynamic::getMinTour(int i, int state, std::vector<std::vector<float>>& memo, std::vector<std::vector<float>>& prev)
{

	// Done this tour. Return cost of going back to start node.
	if (state == FINISHED_STATE)
		return distances.at(i).at(0);	//state will be all 111111... meaning all nodes were visited

	// Return cached answer if already computed.
	if (memo[i][state] != -1)
		return memo[i][state];	//return already calucated distance instead of recursing again

	float minCost = FLT_MAX;	//set the intial path cost to max so we get a min path
	int index = -1;
	for (int next = 0; next < size; next++)
	{

		// Skip if the next node has already been visited.
		if ((state & (1 << next)) != 0) continue; //0010 & 0010 = 0010 != 0000 so we've already visited node 2

		int nextState = state | (1 << next);	//update the state to show we've visited the next node when we recur
		//find the distance from this node to the next and add the shortest path from the rest of the nodes
		float newCost = distances.at(i).at(next) + getMinTour(next, nextState, memo, prev);
		if (newCost < minCost)	//if this path cost is the least, then update the minCost and the index
		{
			minCost = newCost;
			index = next;
		}
	}

	prev[i][state] = index;		//stores the node where the minCost occured for memoization later
	return memo[i][state] = minCost;	//returns the min cost of this path/subpath
}

//gets the path of shortest cost (with cost appened on the end)
std::vector<float>* TSPDynamic::tspDynamic()
{
	// Run the solver
	std::vector<float>* tour = new std::vector<float>;	//vector of shortest path
	int state = 1 << 0;	//bitmask to show which nodes have been visited
	std::vector<std::vector<float>> memo;	//creates a memo table to later get the path
	memo.reserve(size);
	memo.resize(size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < (1 << size); j++)
		{
			memo.at(i).push_back(-1);	//fills it with default values of -1
		}
	}
	std::vector<std::vector<float>> prev;	//makes a concurrent table to memo that holds the order of the nodes
	prev.reserve(size);
	prev.resize(size);
	for (int k = 0; k < size; k++)
	{
		for (int l = 0; l < (1 << size); l++)
		{
			prev.at(k).push_back(-1);	//fills it with default values of -1
		}
	}
	float minTourCost = getMinTour(0, state, memo, prev);	//gets the min cost and updates memo/prev

	// Regenerate path
	int index = 0;
	while (true && state < (1 << size))		//while the state doesnt go too high
	{
		tour->push_back(index);		//add the next node
		int nextIndex = prev[index][state];		//use the prev table to get the next node (of least cost)
		if (nextIndex == -1) break;	//if its -1 then we found the full path
		int nextState = state | (1 << nextIndex);	//else update the state to show we've "visited" that city
		state = nextState;	//update state and index
		index = nextIndex;
	}
	tour->push_back(0);	//add the first node again to make a circuit
	tour->push_back(minTourCost);	//append the cost to the end for easy future access
	return tour;
}

//returns the Euclidean distance between two nodes based on the positions in the map
float TSPDynamic::distFormula(int one, int two)
{
	std::tuple<float, float, float> tempPos1 = positions.at(one+1);
	std::tuple<float, float, float> tempPos2 = positions.at(two+1);
	float temp = sqrt(pow(std::get<0>(tempPos2) - std::get<0>(tempPos1), 2) +
		pow(std::get<1>(tempPos2) - std::get<1>(tempPos1), 2) +
		pow(std::get<2>(tempPos2) - std::get<2>(tempPos1), 2));

	return temp;
}