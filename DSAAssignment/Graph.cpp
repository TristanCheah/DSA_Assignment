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

void Graph::displayStationInfo(string station_name) {
	KeyType key;
	int indexes_to_iterate[MAX_SIZE] = {};
	int counter = 0;
	for (int i = 0; i < MAX_SIZE; i++) {
		if (items[i] != NULL) {
			indexes_to_iterate[counter] = i;
			counter++;
		}
	}//to find 

	for (int i = 0; i < counter; i++) {
		if (items[indexes_to_iterate[i]]->item == station_name) {
			key = items[indexes_to_iterate[i]]->key;
			break;
		}
		else {
			Node* current = items[indexes_to_iterate[i]];
			while (current->next != NULL) {
				if (current->item == station_name) {
					key = current->key;
					break;
				}
				else {
					current = current->next;
				}
			}
			if (current->item == station_name) {
				key = current->key;
				break;
			}
			else {
				key = "";
			}
		}
	}


	//ifstream file;
	//file.open("Stations.csv");
	//if (file.is_open()) {
	//	string word;
	//	while (!file.eof()) {
	//		string no;
	//		string Name;
	//		string row;
	//		getline(file, row);
	//		std::stringstream s_stream(row);
	//		int count = 0;
	//		while (getline(s_stream, word, ',')) {
	//			if (count == 0) {
	//				no = word;
	//				count++;
	//			}
	//			else {
	//				Name = word;
	//				if (Name == station_name) {
	//					key = no; //if name is equal, get key
	//				}
	//			}
	//		}
	//	}
	//}
	//file.close();
	if (key == "") {
		cout << "No station found" << endl;
	}
	else {
		int hash = this->hash(key);
		if (this->find(key) == NULL) {
			cout << "No station found" << endl;
		}
		else {
			cout << "Station found!" << endl;
			cout << this->find(key)->key << endl;
			cout << this->find(key)->item << endl;
			for (int j = 0; j < MAX_INTERCHANGES - 1; j++) {
				if (this->find(key)->interchanges[j] != "") {
					cout << "Interchange with " << this->find(key)->interchanges[j] << endl;
				}
			}
		}
	}
}
void Graph::readCSV() {
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
	file.close();
}
Graph::Node* Graph::find(KeyType key) {
	int hash = this->hash(key);
	if (items[hash]->key == key) {
		return items[hash];
	}
	else {
		Node* current = items[hash];
		while (current->next != NULL) {
			if (current->key == key) {
				return current;
			}
			current = current->next;
		}
		if (current->key == key) {
			return current;
		}
		else {
			return NULL;
		}
	}

}

void Graph::generateInterchanges() {
	ifstream file;
	file.open("Interchanges.csv");
	if (file.is_open()) {
		string key;
		while (!file.eof()) {
			string keys_to_add[3];
			string row;
			int count = 0;
			getline(file, row);
			std::stringstream s_stream(row);
			while (getline(s_stream, key, ',')) {
				keys_to_add[count] = key;
				count++;
				//find hash record, add to interchanges
			}
			for (int i = 0; i < count; i++) {	
				int key_count = 0;
				for (int k = 0; k < count; k++) {					
					if (keys_to_add[k] != this->find(keys_to_add[i])->key) {
						this->find(keys_to_add[i])->interchanges[key_count] = keys_to_add[k];
						key_count++;
					}		
					
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