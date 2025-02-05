#pragma once

#ifndef NODE_H
#define NODE_H

#include <vector>
#include <tuple>

class Node {
public:
	Node();
	Node(int);
	Node(int, float, float, float);
	Node(const Node&);

	int getData();
	int getData() const;
	float getCost();
	float getCost() const;
	int getDepth();
	Node* getParent();
	std::tuple<float, float, float> getPos();
	int getChildrenNum();
	std::vector<Node*> getChildren();
	int getTime();
	int getTime() const;

	void setData(int);
	void setCost(float);
	void setDepth(int);
	void setParent(Node*);
	void setPos(float, float, float);
	void setTime(int);
	void addChild(int);
	void addChild(Node*);
	void addChild(std::vector<Node*>);
	void clearChildren();

	Node& operator=(const Node&);
	Node* operator[](const int);
	bool operator==(const Node*);
	bool operator<(const Node*);
	bool operator>(const Node*);

	void clear();

private:
	float cost = 0;
	int data;
	int depth = 0;
	int time = 0;
	std::tuple<float, float, float> position;
	Node* parent = nullptr;
	std::vector<Node*> children;
};

#endif // !NODE_H
