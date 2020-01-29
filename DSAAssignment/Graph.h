#pragma once
using namespace std;
#include <string>

const int MAX_SIZE = 11;
const int MAX_INTERCHANGES = 2;
typedef string ItemType;
typedef string KeyType;

class Graph
{
private:
	struct Node {
		ItemType item;
		KeyType key;
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
	bool add(KeyType newKey, ItemType newItem);
	string getLine(KeyType key);
	void print();
};

