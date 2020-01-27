#pragma once
using namespace std;
#include <string>

const int MAX_SIZE = 11;
typedef string ItemType;
typedef string KeyType;

class Graph
{
private:
	struct Node {
		ItemType item;
		KeyType key;
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
	string getLine(KeyType key);
	void print();
};

