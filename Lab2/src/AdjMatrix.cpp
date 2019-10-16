#include "AdjMatrix.h"

AdjMatrix::AdjMatrix()
{
}

AdjMatrix::~AdjMatrix()
{
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data.at(i).size(); j++)
		{
			if (data.at(i).at(j) != nullptr)
			{
				delete data.at(i).at(j);
			}
		}
	}
}

void AdjMatrix::addEdge(int vertex, int edge)
{
	if (data.at(vertex - 1).at(edge - 1) == nullptr)
	{
		Node* tempNode1 = new Node(edge);
		Node* tempNode2 = new Node(vertex);
		data.at(vertex - 1).at(edge - 1) = tempNode1;
		data.at(edge - 1).at(vertex - 1) = tempNode2;
	}
}

void AdjMatrix::addVertex(int vertex)
{
	Node* tempNode = new Node(vertex);
	data.at(vertex - 1).at(vertex - 1) = tempNode;
}

int AdjMatrix::getVertexNum()
{
	return data.size();
}

Node* AdjMatrix::at(int vertex, int edge)
{
	if (vertex > 0 && edge > 0 && vertex <= data.size() && edge <= data.size())
	{
		Node* tempNode = data.at(vertex - 1).at(edge - 1);
		return tempNode;
	}
}

void AdjMatrix::setWeights(int vertex, int edge, float cost)
{
	std::tuple<int, int, float> temp = std::make_tuple(vertex, edge, cost);
	weights.push_back(temp);
}

void AdjMatrix::setPositions(int vertex, float x, float y, float z)
{
	for (int i = 0; i < data.size(); i++)
	{
		if (data.at(i).at(vertex-1) != nullptr)
		{
			data.at(i).at(vertex-1)->setPos(x, y, z);
		}
	}
}

void AdjMatrix::makeMatrix(int num)
{
	data.reserve(num);
	data.resize(num);
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data.size(); j++)
		{
			data.at(i).push_back(nullptr);
		}
		//data.at(i).reserve(num);
		//data.at(i).resize(num);
	}
}

void AdjMatrix::print()
{
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data.at(i).size(); j++)
		{
			std::cout << data.at(i).at(j)->getData() << " ";
		}
		std::cout << std::endl;
	}
}

Node* AdjMatrix::findNode(Node* source)
{
	Node* tempNode = source;
	for (int i = 0; i < data.size(); i++)
	{
		if (i + 1 == source->getData())
		{
			for (int j = 0; j < data.at(i).size(); j++)
			{
				if (data.at(i).at(j) != nullptr && data.at(i).at(j)->getData() != source->getData())
				{
					tempNode->addChild(data.at(i).at(j));
				}
			}
		}
	}
	return tempNode;
}

std::vector<Node*> AdjMatrix::getChildren(int source, Node* child)
{
	std::vector<Node*> children;
	for (int i = 0; i < data.size(); i++)
	{
		if (i + 1 == child->getData())
		{
			for (int j = 0; j < data.at(i).size(); j++)
			{
				if (data.at(i).at(j) != nullptr && data.at(i).at(j)->getData() != source)
				{
					children.push_back(data.at(i).at(j));
				}
			}
		}
	}
	return children;
}

float AdjMatrix::getWeight(int one, int two)
{
	for (int i = 0; i < weights.size(); i++)
	{
		if (std::get<0>(weights.at(i)) == one)
		{
			if (std::get<1>(weights.at(i)) == two)
			{
				return std::get<2>(weights.at(i));
			}
		}
	}
}