#pragma once
using namespace std;
#include <string>

const int MAX_SIZE = 676;
const int MAX_INTERCHANGES = 2;
typedef string ItemType;
typedef string KeyType;
typedef int PriorityType;

class Graph
{
private:
	struct Node {
		ItemType item;
		KeyType key;
		PriorityType priority;
		Node* next;
		KeyType interchanges[MAX_INTERCHANGES];
	};
	Node *items[MAX_SIZE];
	int size;

public:
	Graph();
	~Graph();
	void generate_graph();
	void readCSV();
	void generateInterchanges();
	void displayStationInfo(string station_name);
	Node* find(KeyType key);
	int hash(KeyType key);
	string priority(KeyType key);
	bool add(KeyType newKey, ItemType newItem);
	bool addWrite(KeyType newKey, ItemType newItem);
	void getLine(KeyType key);
	void print();
	void write();
};

