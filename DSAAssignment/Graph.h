#pragma once
using namespace std;
#include <string>

const int MAX_SIZE = 676;
typedef string ItemType;
typedef string KeyType;
typedef int PriorityType;

class Graph
{
private:
	struct Node {
		ItemType item;
		KeyType key;
		PriorityType Priority;
		Node* next;
	};
	Node *items[MAX_SIZE];
	int size;

public:
	Graph();
	~Graph();
	void generate_graph();
	void readCSV(string filename);
	int hash(KeyType key);
	bool add(KeyType newKey, ItemType newItem);
	string FindStation(KeyType key);
	void getLine(KeyType key);
	void print();
};

