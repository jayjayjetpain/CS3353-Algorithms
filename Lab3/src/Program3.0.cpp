// Program3.0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm> 
#include <vector>
#include <iostream>
#include <math.h>
using namespace std;
#define V 5
#define INT_MAX 999999

int n = 5;
int dist[10][10] = {
		{ 0, 10, 15, 20, 25 },
					   { 10, 0, 35, 25, 15 },
					   { 15, 35, 0, 30, 25 },
					   { 20, 25, 30, 0, 15 },
					   { 25, 15, 25, 15, 0 }
};
int VISITED_ALL = (1 << n) - 1;

int dp[32][5];

int dist2[][V] = { { 0, 10, 15, 20, 25 },
					   { 10, 0, 35, 25, 15 },
					   { 15, 35, 0, 30, 25 },
					   { 20, 25, 30, 0, 15 },
					   { 25, 15, 25, 15, 0 } };

const int N = 5;
const int FINISHED_STATE = (1 << N) - 1;



//// implementation of traveling Salesman Problem 
vector<int> travllingSalesmanProblem(int graph[][V], int s)
{
	// store all vertex apart from source vertex 
	vector<int> minPath;
	vector<int> vertex;
	for (int i = 0; i < V; i++)
		if (i != s)
			vertex.push_back(i);

	// store minimum weight Hamiltonian Cycle. 
	int min_path = INT_MAX;
	do {

		// store current Path weight(cost) 
		int current_pathweight = 0;

		// compute current path weight 
		int k = s;
		for (int i = 0; i < vertex.size(); i++) {
			current_pathweight += graph[k][vertex[i]];
			k = vertex[i];
		}
		current_pathweight += graph[k][s];

		// update minimum 
		if (current_pathweight < min_path)
		{
			min_path = min(min_path, current_pathweight);
			minPath = vertex;
			minPath.insert(minPath.begin(), s);
			minPath.push_back(s);
		}

	} while (next_permutation(vertex.begin(), vertex.end()));

	return minPath;
}

float tsp(int i, int state, float memo[][1 << N], int prev[][1 << N]) {

	// Done this tour. Return cost of going back to start node.
	if (state == FINISHED_STATE) return dist2[i][0];

	// Return cached answer if already computed.
	if (memo[i][state] != -1) return memo[i][state];

	float minCost = FLT_MAX;
	int index = -1;
	for (int next = 0; next < N; next++) {

		// Skip if the next node has already been visited.
		if ((state & (1 << next)) != 0) continue;

		int nextState = state | (1 << next);
		float newCost = dist2[i][next] + tsp(next, nextState, memo, prev);
		if (newCost < minCost) {
			minCost = newCost;
			index = next;
		}
	}

	prev[i][state] = index;
	return memo[i][state] = minCost;
}

vector<float>* solve()
{
	// Run the solver
	vector<float>* tour = new vector<float>;
	int state = 1 << 0;
	float memo[N][1 << N];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (1 << n); j++) {
			memo[i][j] = -1;
		}
	}
	int prev[N][1 << N];
	float minTourCost = tsp(0, state, memo, prev);

	// Regenerate path
	int index = 0;
	while (true && state < (1 << N)) {
		tour->push_back(index);
		int nextIndex = prev[index][state];
		if (nextIndex == -1) break;
		int nextState = state | (1 << nextIndex);
		state = nextState;
		index = nextIndex;
	}
	tour->push_back(0);
	tour->push_back(minTourCost);
	return tour;
}



int main() {

	cout << "Naive Brute Force Approach: ";
	vector<int> temps = travllingSalesmanProblem(dist2, 0);
	for (int i = 0; i < temps.size(); i++)
	{
		cout << temps.at(i) << " ";
	}
	cout << endl << endl;

	cout << "Dynamic Programming Method: " << endl;
	vector<float>* path = solve();
	cout << "Minimum Cost of Path: " << path->back() << endl;
	for (int j = path->size() - 2; j >= 0; j--)
	{
		cout << path->at(j) << " ";
	}
	return 0;
}
