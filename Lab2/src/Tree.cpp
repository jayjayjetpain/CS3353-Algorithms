#include "Tree.h"
#include <algorithm>
#include <iostream>

Tree::Tree()
{
	this->root = nullptr;
	this->currNode = nullptr;
	this->depth = 0;
	this->totalNodes = 0;
}

Tree::Tree(Node* data)
{
	this->root = new Node(*data);
	this->currNode = this->root;
	this->depth = 1;
	this->totalNodes = 1;
}

Tree::~Tree()
{
	this->makeEmpty(root);
}

void Tree::insert(int parent, Node* data)
{
	if (this->root == nullptr)
	{
		this->root = new Node(*data);
		this->root->clearChildren();
		this->currNode = this->root;
		this->totalNodes++;
		this->depth++;
	}
	else if (this->currNode == data)
	{
	}
	else if (this->currNode->getData() == parent)
	{
		Node* tempNode = new Node(*data);
		tempNode->clearChildren();
		tempNode->setDepth(this->currNode->getDepth() + 1);
		this->currNode->addChild(tempNode);
		this->currNode = tempNode;
		if (tempNode->getDepth() > this->depth)
		{
			this->depth++;
		}
		this->totalNodes++;

	}
	else
	{
		for (int i = 0; i < this->currNode->getChildrenNum(); i++)
		{
			Node* temp = this->currNode->operator[](i);
			if (temp->getData() == parent)
			{
				this->currNode = currNode->operator[](i);
				insert(parent, data);
			}
		}
		if (this->currNode->getData() != root->getData())
		{
			findNode(parent);
			insert(parent, data);
		}

	}
}

void Tree::move(int data)
{
	if (data == 0)
	{
		this->currNode = this->currNode->getParent();
		return;
	}

	for (int i = 0; i < this->currNode->getChildrenNum(); i++)
	{
		Node* temp = this->currNode->operator[](i);
		if (temp->getData() == data)
		{
			this->currNode = this->currNode->operator[](i);
			return;
		}
	}

	if (this->currNode->getParent() != this->root)
	{
		this->currNode = this->currNode->getParent();
		return move(data);
	}
	else
	{
		std::cout << "No path available" << std::endl;
	}
}

void Tree::setPathCost(int cost)
{
	int tempCost = this->currNode->getCost();
	this->currNode->setCost(tempCost + cost);
}

void Tree::setWeights(std::vector<std::tuple<int, int, int>> temp)
{
	std::copy(temp.begin(), temp.end(), this->weights.begin());
}

int Tree::getTotalNodes()
{
	return this->totalNodes;
}

void Tree::setPath()
{
	if (currNode == nullptr)
	{
		return; ///////idk is this breaks things**********************
	}
	while (currNode->getData() != root->getData())
	{
		Node* tempNode = this->currNode;
		this->path.push_back(tempNode);
		this->currNode = this->currNode->getParent();
	}
	this->path.push_back(currNode);
}

std::vector<Node*> Tree::getPath()
{
	return this->path;
}

void Tree::makeEmpty(Node* t)
{
	if (t != nullptr)
	{
		for (int i = 0; i < t->getChildrenNum(); i++)
		{
			this->makeEmpty(t->operator[](i));
		}
		delete t;   //then deletes the root node
	}
	t = nullptr;    //sets the root to nullptr for future deletions
}

void Tree::findNode(int parent)
{
	this->findNode(this->root, parent);
}

void Tree::findNode(Node* curr, int data)
{
	if (curr->getData() == data)
	{
		this->currNode = curr;
		return;
	}
	else
	{
		for (int i = 0; i < curr->getChildrenNum(); i++)
		{
			Node* temp1 = curr->operator[](i);
			this->findNode(temp1, data);
			if (currNode->getData() == data)
			{
				return;
			}
		}
	}
}

void Tree::setExplored(int nodes)
{
	this->numExplored = nodes;
}

int Tree::getExploredNum()
{
	return this->numExplored;
}