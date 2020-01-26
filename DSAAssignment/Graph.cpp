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
	ifstream file;
	file.open("Stations.csv");
	if (file.is_open()) {
		string word;
		string stations;
		string names;
		string output;

		while (!file.eof()) {
			string row;
			getline(file, row);
			std::stringstream s_stream(row);
			int count = 0;
			while (getline(s_stream, word, ',')) {
				if (count == 0) {
					stations += word + "\n";
					count++;
				}
				else {
					names += word + "\n";
				}
			}
		}
		stations += "\n";
		names += "\n";
		output = stations + names;
		return output;
	}
	return "";
}