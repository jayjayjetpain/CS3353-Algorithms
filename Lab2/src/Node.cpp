#include "Node.h"

Node::Node() {
	this->data = 0;
}

Node::Node(int newData) {
	this->data = newData;
}

Node::Node(int newData, float x, float y, float z) {
	this->data = newData;
	this->position = std::make_tuple(x, y, z);
}

Node::Node(const Node& source) {
	this->data = source.data;
	this->cost = source.cost;
	this->depth = source.depth;
	this->position = source.position;
	this->children = source.children;
}

int Node::getData() {
	return this->data;
}

float Node::getCost() {
	return this->cost;
}

int Node::getDepth() {
	return this->depth;
}

Node* Node::getParent() {
	return this->parent;
}

std::tuple<float, float, float> Node::getPos() {
	return this->position;
}

int Node::getChildrenNum() {
	return this->children.size();
}

bool Node::isVisited() {
	return this->visited;
}

void Node::setData(int newData) {
	this->data = newData;
}

void Node::setCost(float newCost) {
	this->cost = newCost;
}

void Node::setDepth(int newDepth) {
	this->depth = newDepth;
}
void Node::setParent(Node* newParent) {
	this->parent = newParent;
}

void Node::setPos(float x, float y, float z) {
	this->position = std::make_tuple(x, y, z);
}

void Node::addChild(int newData) {
	Node* newNode = new Node(newData);
	newNode->setDepth(this->depth + 1);
	newNode->setParent(this);
	children.push_back(newNode);
}

void Node::addChild(Node* newNode) {
	newNode->setParent(this);
	children.push_back(newNode);
}

void Node::addChild(std::vector<Node*> childs) {
	for (int i = 0; i < childs.size(); i++)
	{
		childs.at(i)->setParent(this);
		children.push_back(childs.at(i));
	}
}

void Node::clearChildren() {
	this->children.clear();
}

Node& Node::operator=(const Node& source) {
	this->data = source.data;
	this->cost = source.cost;
	this->depth = source.depth;
	this->position = source.position;
	this->children = source.children;
	return *this;
}

Node* Node::operator[](int pos) {
	return(this->children.at(pos));
}

bool Node::operator==(const Node* other) {
	if (this->data == other->data)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Node::operator<(const Node* other)
{
	if (this->getCost() < other->cost)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Node::operator>(const Node* other)
{
	if (this->getCost() > other->cost)
	{
		return true;
	}
	else
	{
		return false;
	}
}