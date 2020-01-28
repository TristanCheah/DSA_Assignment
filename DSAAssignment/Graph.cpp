#include "pch.h"
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int charvalue(char c)
{
	if (isalpha(c))
	{
		return (int)toupper(c) - (int) 'A';
	}
	else
		return 0;
}

Graph::Graph() {
	for (int i = 0; i < MAX_SIZE; i++) {
		items[i] = NULL;
	}
	size = 0;
}

Graph::~Graph()
{
}
void Graph::generate_graph() {
	
}

int Graph::hash(KeyType key) {
	int hash = 0;
	for (int i = 0; i < key.length(); i++) {
		hash += charvalue(key[i]);
	}
	hash = hash % MAX_SIZE;
	return hash;
}

bool Graph::add(KeyType newKey, ItemType newItem) {
	int hash = this->hash(newKey);
	Node *n = new Node;
	n->key = newKey;
	n->item = newItem;
	n->next = NULL;
	if (items[hash] == NULL) {
		items[hash] = n;
		size += 1;
		return true;
	}
	else {
		Node *current = items[hash];
		if (current->key == n->key) {
			//cout << "duplicate found" << endl;
			return false;
		}
		while (current->next != NULL) {
			if (current->key == n->key) {
				//cout << "duplicate found" << endl;
				return false;
			}
			current = current->next;
		}
		current->next = n;
		size += 1;
		//cout << "entered after traversing" << endl;
		//cout << to_string(hash) << endl;
		return true;
	}
}

string Graph::getLine(KeyType key) {
	string upperkey;
	for (int i = 0; i < key.length(); i++) {
		upperkey += toupper(key[i]);
	}
	//cout << "uppercase key: " + upperkey<< endl;
	string no;
	string name;
	string output;
	int hash = this->hash(key);
	string linelet;
	string upperll;
	if (items[hash] != NULL) {
		Node* current = items[hash];
		linelet = current->key;
		
		for (int i = 0; i < linelet.length(); i++) {
			if (isalpha(linelet[i])) {
				upperll += toupper(linelet[i]);
			}
		}
		//cout << "uppercase line letters: " + upperll << endl;
		while (current != NULL && upperll == upperkey) {
			no += current->key + "\n";
			name += current->item + "\n";
			linelet = current->key;
			current = current->next;
			upperll = "";
			for (int i = 0; i < linelet.length(); i++) {
				if (isalpha(linelet[i])) {
					upperll += toupper(linelet[i]);
				}
			}
			//cout << "uppercase ll: " + upperll << endl;
		}
		no += "\n";
		output = no + name;
	}
	return output;
}


void Graph::readCSV(string file_name) {
	ifstream file;
	file.open("Stations.csv");
	if (file.is_open()) {
		string word;
		while (!file.eof()) {
			string no;
			string Name;
			string row;
			getline(file, row);
			std::stringstream s_stream(row);
			int count = 0;
			while (getline(s_stream, word, ',')) {
				if (count == 0) {
					no = word;
					count++;
				}
				else {
					Name = word;
					this->add(no, Name);
				}
			}
		}
	}
}

void Graph::print() {
	for (int i = 0; i < MAX_SIZE; i++) {
		Node* current = new Node;
		if (items[i] != NULL) {
			current = items[i];
			while (current != NULL) {
				cout << "Number : " << current->key << endl;
				cout << "Name : " << current->item << endl;
				current = current->next;
			}
		}
	}
}