#include "AdjList.h"
#include "LinkedList.h"

AdjList::AdjList() 
{
	vertexNum = 0;
}

void AdjList::addVertex(int data)
{
	Node* temp = new Node(data);
	dataList.push_back(*temp);
	vertexNum++;

	if (vertexNum == 1)
	{
		frontIter = dataList.begin();
	}
}

void AdjList::addEdge(int vertex, int data)
{
	for (typename LinkedList<Node>::Iterator i(dataList.begin()); i.getNode() != nullptr; i++)
	{
		if ((*i).getData() == vertex)
		{
			(*i).addChild(data);
			return;
		}
	}
}

int AdjList::getEdgeNum(int vertex)
{
	for (typename LinkedList<Node>::Iterator i(dataList.begin()); i.getNode() != nullptr; i++)
	{
		if ((*i).getData() == vertex)
		{
			return (*i).getChildrenNum();
		}
	}
}

int AdjList::getVertexNum()
{
	return dataList.getLength();
}

Node* AdjList::at(int vertex, int edge)
{
	for (typename LinkedList<Node>::Iterator i(dataList.begin()); i.getNode() != nullptr; i++)
	{
		if ((*i).getData() == vertex)
		{
			return &(*i);
		}
	}
}

void AdjList::setWeights(int vertex, int edge, int cost)
{
	std::tuple<int, int, int> temp = std::make_tuple(vertex, edge, cost);
	weights.push_back(temp);
}

void AdjList::setPositions(int vertex, float x, float y, float z)
{
	for (typename LinkedList<Node>::Iterator i(dataList.begin()); i.getNode() != nullptr; i++)
	{
		if ((*i).getData() == vertex)
		{
			(*i).setPos(x,y,z);
			return;
		}
	}
}

typename LinkedList<Node>::Iterator AdjList::getIter()
{
	return frontIter;
}

void AdjList::print()
{
	for (typename LinkedList<Node>::Iterator i(dataList.begin()); i.getNode() != nullptr; i++)
	{
		std::cout << (*i).getData() << " ";
		for (int j = 0; j < (*i).getChildrenNum(); j++)
		{
			std::cout << (*i).operator[](j)->getData() << " ";
		}
		std::cout << std::endl;
	}
}

Node* AdjList::findNode(Node* source)
{
	for (typename LinkedList<Node>::Iterator i(dataList.begin()); i.getNode() != nullptr; i++)
	{
		if ((*i).getData() == source->getData())
		{
			return &(*i);
		}
	}
}

std::vector<Node*> AdjList::getChildren(int source, Node* child)
{
	std::vector<Node*> children;
	for (typename LinkedList<Node>::Iterator i(dataList.begin()); i.getNode() != nullptr; i++)
	{
		if ((*i).getData() == child->getData())
		{
			for (int j = 0; j < (*i).getChildrenNum(); j++)
			{
				children.push_back((*i).operator[](j));
			}
		}
	}
	return children;
}
