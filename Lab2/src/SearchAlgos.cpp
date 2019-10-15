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
				added = true;;
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
	return p;
}

void SearchAlgos::BFSIterUtil(int start, int end, Graph* g, Tree* t)
{
	std::vector<bool> visited(g->getVertexNum() + 1, false);
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
		
		if (tempInt != start && !visited[tempInt])
		{
			t->insert(queue.front()->getParent()->getData(), tempNode);
			visited[tempInt] = true;
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
	std::vector<int> finalPath;
	std::stack<Node*> stack;
	Path p;
	if (start < 1 || start > g->getVertexNum() || end < 1 || end > g->getVertexNum())
	{
		return p;
	}
	Node* startNode = g->at(start, start);
	Tree* t = new Tree(startNode);
	visited[start] = true;

	DFSRecurUtil(start, end, g, startNode, visited, t);

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
	return p;
}

void SearchAlgos::DFSRecurUtil(int start, int end, Graph* g, Node* tempNode,
							   std::vector<bool>& visited, Tree* t)
{
	int tempInt = tempNode->getData();
	if (tempInt == start && t->getTotalNodes() > 1)
	{
		return;
	}
	
	if (tempInt != start && !visited[tempInt])
	{
		visited[tempInt] = true;
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
			DFSRecurUtil(start, end, g, children.at(i), visited, t);
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
	std::vector<int> finalPath;
	std::queue<Node*> queue;
	Path p;
	if (start < 1 || start > g->getVertexNum() || end < 1 || end > g->getVertexNum())
	{
		return p;
	}
	Node* startNode = g->at(start, start);
	Tree* t = new Tree(startNode);
	queue.push(startNode);
	visited[start] = true;

	BFSRecurUtil(start, end, g, queue, visited, t);

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
	return p;
}

void SearchAlgos::BFSRecurUtil(int start, int end, Graph* g, std::queue<Node*>& queue,
							   std::vector<bool>& visited, Tree* t)
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

	if (tempInt != start && !visited[tempInt])
	{
		t->insert(queue.front()->getParent()->getData(), tempNode);
		visited[tempInt] = true;
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
			queue.push(children.at(i));
		}
	}

	BFSRecurUtil(start, end, g, queue, visited, t);
	if (visited[0])
	{
		return;
	}
}

Path SearchAlgos::Dijkstra(int start, int end, Graph* g)
{
	
}