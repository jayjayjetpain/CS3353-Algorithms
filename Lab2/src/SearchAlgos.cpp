#include "SearchAlgos.h"

Path SearchAlgos::DFSIter(int start, int end, Graph* g)
{
	Tree* t = new Tree();
	DFSIterUtil(start, end, g, t);

	t->setPath();
	std::vector<Node*> tempPath = t->getPath();
	std::vector<int> path;
	if (tempPath.size() > 1 || start == end)
	{
		for (int i = tempPath.size() - 1; i >= 0; i--)
		{
			path.push_back(tempPath.at(i)->getData());
		}
	}
	Path p(path, t->getExploredNum());
	delete t;
	return p;
}

void SearchAlgos::DFSIterUtil(int start, int end, Graph* g, Tree* t)
{
	std::vector<bool> visited(g->getVertexNum() + 1, false);
	std::stack<Node*> stack;
	Node* startNode = g->at(start, start);
	t->insert(start, startNode);
	if (start < 1 || start > g->getVertexNum() || end < 1 || end > g->getVertexNum())
	{
		return;
	}

	stack.push(startNode);
	visited[start] = true;

	while (!stack.empty())
	{
		Node* tempNode = g->findNode(stack.top());
		int tempInt = tempNode->getData();
		std::vector<Node*> children = g->getChildren(tempInt, stack.top());

		if (tempInt != start && !visited[tempInt])
		{
			t->insert(stack.top()->getParent()->getData(), tempNode);
			visited[tempInt] = true;	
		}
		stack.pop();

		if (tempInt == end)
		{
			visited[0] = true;
			break;
		}

		int added = false;
		for (int i = 0; i < children.size(); i++)
		{
			if (!visited[children.at(i)->getData()])
			{
				stack.push(children.at(i));
				added = true;
			}
		}

		if (!added)
		{
			if (!stack.empty())
			{
				int top = stack.top()->getData();
				t->move(top);
			}
			else
			{
				t->move();
			}
		}
	}
	if (!visited[0])
	{
		t->findNode(start);
	}
	int totalExplored = 0;
	for (int p = 1; p < visited.size(); p++)
	{
		if (visited[p])
		{
			totalExplored++;
		}
	}
	t->setExplored(totalExplored);
	return;
}

Path SearchAlgos::BFSIter(int start, int end, Graph* g)
{
	Tree* t = new Tree();
	BFSIterUtil(start, end, g, t);

	t->setPath();
	std::vector<Node*> tempPath = t->getPath();
	std::vector<int> path;
	if (tempPath.size() > 1 || start == end)
	{
		for (int i = tempPath.size() - 1; i >= 0; i--)
		{
			path.push_back(tempPath.at(i)->getData());
		}
	}
	Path p(path, t->getExploredNum());
	delete t;
	return p;
}

void SearchAlgos::BFSIterUtil(int start, int end, Graph* g, Tree* t)
{
	std::vector<bool> visited(g->getVertexNum() + 1, false);
	std::vector<bool> onTree(g->getVertexNum() + 1, false);
	std::queue<Node*> queue;
	Node* startNode = g->at(start, start);
	t->insert(start, startNode);
	if (start < 1 || start > g->getVertexNum() || end < 1 || end > g->getVertexNum())
	{
		return;
	}

	queue.push(startNode);
	visited[start] = true;

	while (!queue.empty())
	{
		Node* tempNode = g->findNode(queue.front());
		int tempInt = tempNode->getData();
		std::vector<Node*> children = g->getChildren(tempInt, queue.front());
		
		if (tempInt != start && !onTree[tempInt])
		{
			t->insert(queue.front()->getParent()->getData(), tempNode);
			onTree[tempInt] = true;
		}
		queue.pop();

		if (tempInt == end)
		{
			visited[0] = true;
			break;
		}

		int added = false;
		for (int i = 0; i < children.size(); i++)
		{
			if (!visited[children.at(i)->getData()])
			{
				visited[children.at(i)->getData()] = true;
				queue.push(children.at(i));
				added = true;
			}
		}

		if (!added)
		{
			if (!queue.empty())
			{
				int top = queue.front()->getData();
				t->move(top);
			}
			else
			{
				t->move();
			}
		}
	}
	if (!visited[0])
	{
		t->findNode(start);
	}
	int totalExplored = 0;
	for (int p = 1; p < visited.size(); p++)
	{
		if (visited[p])
		{
			totalExplored++;
		}
	}
	t->setExplored(totalExplored);
	return;
}

Path SearchAlgos::DFSRecur(int start, int end, Graph* g)
{
	std::vector<bool> visited(g->getVertexNum() + 1, false);
	std::vector<bool> onTree(g->getVertexNum() + 1, false);
	std::vector<int> finalPath;
	std::stack<Node*> stack;
	Path p;
	if (start < 1 || start > g->getVertexNum() || end < 1 || end > g->getVertexNum())
	{
		return p;
	}
	Node* startNode = g->at(start, start);
	Tree* t = new Tree();
	visited[start] = true;
	t->insert(start, startNode);

	DFSRecurUtil(start, end, g, startNode, visited, onTree, t);

	t->setPath();
	std::vector<Node*> tempPath = t->getPath();
	if ((tempPath.size() > 1 || start == end) && visited[0])
	{
		for (int i = tempPath.size() - 1; i >= 0; i--)
		{
			finalPath.push_back(tempPath.at(i)->getData());
		}
	}

	int totalExplored = 0;
	for (int j = 1; j < visited.size(); j++)
	{
		if (visited[j])
		{
			totalExplored++;
		}
	}
	p.setPath(finalPath);
	p.setExploredNodes(totalExplored);
	delete t;
	return p;
}

void SearchAlgos::DFSRecurUtil(int start, int end, Graph* g, Node* tempNode, std::vector<bool>& visited, std::vector<bool>& onTree, Tree* t)
{
	int tempInt = tempNode->getData();
	if (tempInt == start && t->getTotalNodes() > 1)
	{
		return;
	}
	
	if (tempInt != start && !onTree[tempInt])
	{
		onTree[tempInt] = true;
		t->insert(tempNode->getParent()->getData(), tempNode);
	}
	std::vector<Node*> children = g->getChildren(tempInt, tempNode);

	if (tempInt == end)
	{
		visited[0] = true;
		return;
	}

	for (int i = children.size()-1; i >= 0; i--)
	{
		if (!visited[children.at(i)->getData()])
		{
			visited[children.at(i)->getData()] = true;
			children.at(i)->setParent(tempNode);
			DFSRecurUtil(start, end, g, children.at(i), visited, onTree, t);
			if (visited[0])
			{
				return;
			}		
		}
	}

	t->move();
	return;

}

Path SearchAlgos::BFSRecur(int start, int end, Graph* g)
{
	std::vector<bool> visited(g->getVertexNum() + 1, false);
	std::vector<bool> onTree(g->getVertexNum() + 1, false);
	std::vector<int> finalPath;
	std::queue<Node*> queue;
	Path p;
	if (start < 1 || start > g->getVertexNum() || end < 1 || end > g->getVertexNum())
	{
		return p;
	}
	Node* startNode = g->at(start, start);
	Tree* t = new Tree();
	queue.push(startNode);
	visited[start] = true;
	t->insert(start, startNode);

	BFSRecurUtil(start, end, g, queue, visited, onTree, t);

	t->setPath();
	std::vector<Node*> tempPath = t->getPath();
	
	if ((tempPath.size() > 1 || start == end) && visited[0])
	{
		for (int i = tempPath.size() - 1; i >= 0; i--)
		{
			finalPath.push_back(tempPath.at(i)->getData());
		}
	}

	int totalExplored = 0;
	for (int j = 1; j < visited.size(); j++)
	{
		if (visited[j])
		{
			totalExplored++;
		}
	}
	p.setPath(finalPath);
	p.setExploredNodes(totalExplored);
	delete t;
	return p;
}

void SearchAlgos::BFSRecurUtil(int start, int end, Graph* g, std::queue<Node*>& queue, std::vector<bool>& visited, std::vector<bool>& onTree,
								Tree* t)
{
	if (queue.empty())
	{
		return;
	}
	Node* tempNode = g->findNode(queue.front());
	int tempInt = tempNode->getData();

	if (tempInt == start && t->getTotalNodes() > 1)
	{
		return;
	}

	if (tempInt != start && !onTree[tempInt])
	{
		t->insert(queue.front()->getParent()->getData(), tempNode);
		onTree[tempInt] = true;
	}
	std::vector<Node*> children = g->getChildren(tempInt, tempNode);
	queue.pop();

	if (tempInt == end)
	{
		visited[0] = true;
		return;
	}

	for (int i = 0; i < children.size(); i++)
	{
		if (!visited[children.at(i)->getData()])
		{
			visited[children.at(i)->getData()] = true;
			queue.push(children.at(i));
		}
	}

	BFSRecurUtil(start, end, g, queue, visited, onTree, t);
	if (visited[0])
	{
		return;
	}
}

Path SearchAlgos::Dijkstra(int start, int end, Graph* g)
{
	Tree* t = new Tree();
	DijkstraUtil(start, end, g, t);

	t->setPath();
	std::vector<Node*> tempPath = t->getPath();
	std::vector<int> path;
	float totalCost = tempPath.at(0)->getCost();
	if (tempPath.size() > 1 || start == end)
	{
		for (int i = tempPath.size() - 1; i >= 0; i--)
		{
			path.push_back(tempPath.at(i)->getData());
		}
	}
	Path p(path, t->getExploredNum(), totalCost);
	delete t;
	return p;
}

void SearchAlgos::DijkstraUtil(int start, int end, Graph* g, Tree* t)
{
	std::priority_queue<Node*, std::vector<Node*>, compareCosts> pq;
	Node* startNode = g->at(start, start);
	std::vector<int> dist(g->getVertexNum() + 1, INT32_MAX);
	std::vector<bool> visited(g->getVertexNum() + 1, false);
	int time = 1;
	startNode->setTime(0);
	startNode->setCost(0);
	dist[start] = 0;
	visited[start] = true;

	t->insert(start, startNode);
	if (start < 1 || start > g->getVertexNum() || end < 1 || end > g->getVertexNum())
	{
		return;
	}
	pq.push(startNode);

	while (!pq.empty())
	{
		Node* tempNode = g->findNode(pq.top());
		int tempInt = tempNode->getData();
		std::vector<Node*> children = g->getChildren(tempInt, pq.top());

		if (tempInt != start) //&& !visited[tempInt])
		{
			float tempWeight = g->getWeight(tempInt, pq.top()->getParent()->getData());
			tempNode->setCost(pq.top()->getParent()->getCost() + tempWeight);
			t->insert(pq.top()->getParent()->getData(), tempNode);
			visited[tempInt] = true;
		}
		pq.pop();

		if (tempInt == end)
		{
			visited[0] = true;
			break;
		}

		int added = false;
		for (int i = 0; i < children.size(); i++)
		{
			float weight = g->getWeight(tempNode->getData(), children.at(i)->getData());
			
			if (dist[children.at(i)->getData()] > dist[tempInt] + weight)
			{
				dist[children.at(i)->getData()] = dist[tempInt] + weight;
				weight += dist[tempInt];
				children.at(i)->setCost(weight);
				children.at(i)->setTime(time);
				pq.push(children.at(i));
				added = true;
			}	
		}

		if (!added)
		{
			if (!pq.empty())
			{
				int top = pq.top()->getData();
				t->findNode(top);
			}
			else
			{
				t->move();
			}
		}
		time++;
	}

	if (!visited[0])
	{
		t->findNode(start);
	}
	int totalExplored = 0;
	for (int p = 1; p < visited.size(); p++)
	{
		if (visited[p])
		{
			totalExplored++;
		}
	}
	t->setExplored(totalExplored);
	return;
}

Path SearchAlgos::AStar(int start, int end, Graph* g)
{
	Tree* t = new Tree();
	AStarUtil(start, end, g, t);

	t->setPath();
	std::vector<Node*> tempPath = t->getPath();
	std::vector<int> path;
	float totalCost = tempPath.at(0)->getCost();
	float totalDist = sqrt(distFormula(tempPath.at(tempPath.size() - 1), tempPath.at(0)));
	if (tempPath.size() > 1 || start == end)
	{
		for (int i = tempPath.size() - 1; i >= 0; i--)
		{
			path.push_back(tempPath.at(i)->getData());
		}
	}
	Path p(path, t->getExploredNum(), totalCost, totalDist);
	delete t;
	return p;
}

void SearchAlgos::AStarUtil(int start, int end, Graph* g, Tree* t)
{
	std::priority_queue<Node*, std::vector<Node*>, compareCosts> pq;
	Node* startNode = g->at(start, start);
	std::vector<float> dist(g->getVertexNum() + 1, INT32_MAX);
	std::vector<bool> visited(g->getVertexNum() + 1, false);
	int time = 1;
	startNode->setCost(0);
	startNode->setTime(0);
	dist[start] = 0;
	visited[start] = 0;
	

	t->insert(start, startNode);
	if (start < 1 || start > g->getVertexNum() || end < 1 || end > g->getVertexNum())
	{
		return;
	}
	pq.push(startNode);

	while (!pq.empty())
	{
		Node* tempNode = g->findNode(pq.top());
		int tempInt = tempNode->getData();
		std::vector<Node*> children = g->getChildren(tempInt, pq.top());

		if (tempInt != start) //&& !visited[tempInt])
		{
			float tempWeight = g->getWeight(tempInt, pq.top()->getParent()->getData());
			float tempDist = distFormula(tempNode, pq.top()->getParent());
			tempNode->setCost(pq.top()->getParent()->getCost() + tempWeight + tempDist);
			t->insert(pq.top()->getParent()->getData(), tempNode);
			visited[tempInt] = true;
		}
		pq.pop();

		if (tempInt == end)
		{
			visited[0] = true;
			break;
		}

		int added = false;
		for (int i = 0; i < children.size(); i++)
		{
			float weight = g->getWeight(tempNode->getData(), children.at(i)->getData());
			float distance = distFormula(tempNode, children.at(i));
			float totalCost = distance + weight;

			if (dist[children.at(i)->getData()] > dist[tempInt] + totalCost)
			{
				dist[children.at(i)->getData()] = dist[tempInt] + totalCost;
				totalCost += dist[tempInt];
				children.at(i)->setCost(totalCost);
				children.at(i)->setTime(time);
				pq.push(children.at(i));
				added = true;
			}
		}

		if (!added)
		{
			if (!pq.empty())
			{
				int top = pq.top()->getData();
				t->findNode(top);
			}
			else
			{
				t->move();
			}
		}
		time++;
	}

	if (!visited[0])
	{
		t->findNode(start);
	}
	int totalExplored = 0;
	for (int p = 1; p < visited.size(); p++)
	{
		if (visited[p])
		{
			totalExplored++;
		}
	}
	t->setExplored(totalExplored);
	return;
}

float SearchAlgos::distFormula(Node* one, Node* two)
{
	std::tuple<float, float, float> tempPos1 = one->getPos();
	std::tuple<float, float, float> tempPos2 = two->getPos();
	float temp = pow(std::get<0>(tempPos2) - std::get<0>(tempPos1), 2) +
				 pow(std::get<1>(tempPos2) - std::get<1>(tempPos1), 2) +
				 pow(std::get<2>(tempPos2) - std::get<2>(tempPos1), 2);

	return temp;
}