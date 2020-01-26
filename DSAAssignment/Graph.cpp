#include "pch.h"
#include "Graph.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


Graph::Graph(Node* start, Node* end)
{
	startNode = start;
	endNode = end;
}
Graph::Graph() {

}

Graph::~Graph()
{
}
void Graph::generate_graph() {
	
}
string Graph::readCSV(string file_name) {
	fstream file;
	file.open("Stations.csv", ios::in);
	
	string row;
	getline(file, row);
	std::stringstream s_stream(row);
	string word;
	string output;
	
	while (getline(s_stream, word, ',')) {
		output += word;
	}
	return output;
}