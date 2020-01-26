#pragma once
using namespace std;
#include <string>

typedef string ItemType;
class Graph
{
private:
	struct Node {
		ItemType item;
		Node* next;
		float distance_to_next;
	};
	Node* startNode;
	Node* endNode;
public:
	Graph(Node* start, Node* end);
	Graph();
	~Graph();
	void generate_graph();
	string readCSV(string filename);
	
	


};

