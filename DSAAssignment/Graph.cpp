#include "pch.h"
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
//#include <math.h>

using namespace std;

int charvalue(char c)
{
	if (isalpha(c))
	{
		return (int)toupper(c) - (int) 'A' + 1;
	}
	else
		return 0;
}

char isno(char c) {
	if (isdigit(c)) {

		return c;
	}
	return '\0';

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
	for (int i = 0; i <key.length(); i++) {
		double p = pow(26, i);
		int val = (int)p;
		hash += charvalue(key[i]) * val; //(int) pow(26.0,i);
		//cout << hash<<endl;
	}
	hash = hash % MAX_SIZE;
	return hash;
}
string Graph::priority(KeyType key) {
	string numbers;
	for (int i = 0; i < key.length(); i++) {
		stringstream ss;
		ss << key[i];
		string temp;
		int number;
		
		while (!ss.eof()) {
			ss >> temp;
			if (stringstream(temp) >> number) {
				numbers += to_string(number);
			}
			temp = "";
		}
	}
	if (numbers == "") {
		return "0";
	}

	return numbers;
	//string no = "";
	//for (int i = 0; i < key.length(); i++) {
	//	char x = isno(key[i]);
	//	no += (string)x;
	//}
	///*int n = stoi(no);*/
	//return no;
}

bool Graph::add(KeyType newKey, ItemType newItem) {
	int hash = this->hash(newKey);
	int Priority = stoi(this->priority(newKey));
	Node *n = new Node;
	n->key = newKey;
	n->priority = Priority;
	n->item = newItem;
	n->previous = NULL;
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
			if (current->next->priority > n->priority) {
				n->next = current->next;
				n->previous = current;
				current->next = n;
				n->next->previous = n;
				return true;
			}
			if (current->key == n->key) {
				//cout << "duplicate found" << endl;
				return false;
			}
			current = current->next;
		}
		n->previous = current;
		current->next = n;
		size += 1;
		return true;
	}
}

bool Graph::addWrite(KeyType newKey, ItemType newItem) {
	int hash = this->hash(newKey);
	int Priority = stoi(this->priority(newKey));
	Node *n = new Node;
	n->key = newKey;
	n->priority = Priority;
	n->item = newItem;
	n->next = NULL;
	n->previous - NULL;
	if (items[hash] == NULL) {
		items[hash] = n;
		size += 1;
		this->write();
		return true;
	}
	else {
		Node *current = items[hash];
		if (current->key == n->key) {
			//cout << "duplicate found" << endl;
			return false;
		}
		while (current->next != NULL) {
			if (current->next->priority > n->priority) {
				n->next = current->next;
				n->previous = current;				
				current->next = n;
				n->next->previous = n;
				this->write();
				return true;
			}
			if (current->key == n->key) {
				//cout << "duplicate found" << endl;
				return false;
			}
			current = current->next;
		}
		n->previous = current;
		current->next = n;
		
		this->write();
		size += 1;
		return true;
	}
}

void Graph::getLine(KeyType key) {
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
			cout << "Station No.: " + current->key << endl;
			cout << "Station Name: " + current->item << endl;
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
		//no += "\n";
		//output = no + name;
	}
	//return output;
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


	if (key == "") {
		cout << "No station found" << endl;
	}
	else {
		int hash = this->hash(key);
		Node* station = this->find(key);
		if (station == NULL) {
			cout << "No station found" << endl;
		}
		else {
			cout << "Station found!" << endl;
			cout << "Station Number : " << station->key << endl;
			cout << "Station Name : " << station->item << endl;
			for (int j = 0; j < MAX_INTERCHANGES; j++) {
				if (station->interchanges[j] != "") {
					cout << "Interchange with " << station->interchanges[j] << endl;
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
	file.open("Routes.csv");
	if (file.is_open()) {
		int count = 0;
		string station_key_array[40];
		int distance_array[40];
		while (!file.eof()) {
			string word;
			//string station_key_array[40];
			//int distance_array[40];
			getline(file, word);
			std::stringstream s_stream(word);
			int array_count = 0;
			while (getline(s_stream, word, ',')) {
				if (count == 0) {
					station_key_array[array_count] = word;
					array_count += 1;
				}
				else if(count == 1){
					distance_array[array_count] = stoi(word);
					array_count += 1;
				}
			}
			if (count == 0) {
				count = 1;
			}
			else {
				int iterative_count = 0;
				while (station_key_array[iterative_count + 1] != ""){
					Node* station1 = this->find(station_key_array[iterative_count]);
					Node* station2 = this->find(station_key_array[iterative_count + 1]);

					int distance = distance_array[iterative_count];
					
					station1->distanceNext = distance;
					station2->distancePrev = distance;
					/*cout << station2->item + " : " << station2->distancePrev << endl;*/
					iterative_count++;
				}
				/*Node* station1 = this->find(station_key_array[iterative_count]);
				if (this->find(station_key_array[iterative_count + 1]) == NULL) {
					station1->distancePrev = distance_array[iterative_count];
				}*/
				count = 0;
				std::fill(distance_array, distance_array + array_count, 0);
				for (int i = 0; i < array_count + 1; i++) {
					station_key_array[i].clear();
					
				}
				
			}

		}
	}

	
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
				cout << "===============================" << endl;
				cout << "Number : " << current->key << endl;
				cout << "Name : " << current->item << endl;
				cout << "Priority: " << current->priority << endl;
				if (current->next != NULL) {
					cout << "Next Station : " << current->next->item << endl;
					if (current->distanceNext != NULL) {
						cout << "Distance to Next Station (" << current->next->item << ") : " << current->distanceNext << endl;
					}
				}
				else {
					cout << "Terminal station" << endl;
				}
				if (current->previous != NULL) {
					cout << "Previous Station : " << current->previous->item << endl;
					if (current->distancePrev != NULL) {
						cout << "Distance to Prev Station (" << current->previous->item << ") : " << current->distancePrev << endl;
					}
				}
				else {
					cout << "Terminal station" << endl;
				}

				
				
				
				current = current->next;
			}
		}
	}
}

void Graph::write() {
	ofstream file;
	//remove("Stations.csv");
	file.open("Stations.csv");
	if (file.is_open()) {
		for (int i = 0; i < MAX_SIZE; i++) {
			Node* current = new Node;
			if (items[i] != NULL) {
				current = items[i];
				while (current != NULL) {
					file << current->key+",";
					file << current->item+"\n";
					current = current->next;
				}
			}
		}
	}
	else {
		cout << "can't open";
	}
}
string Graph::get_station_prefix(string station_no) {
	string station_prefix;
	for (int i = 0; i < station_no.length(); i++) {
		stringstream ss;
		ss << station_no[i];
		string temp;
		int number;

		while (!ss.eof()) {
			ss >> temp;
			if (stringstream(temp) >> number) {
				
			}
			else {
				station_prefix += temp;
			}
			temp = "";
		}
	}
	return station_prefix;
}
void Graph::displayRoute(KeyType start, KeyType end) {
	Node* start_node = this->find(start);
	if (start_node == NULL) {
		cout << "Starting station does not exist" << endl;
		return;
	}
	string route[100];
	// if end station's station prefix = start's prefix, iterate down the line.

	string start_prefix = get_station_prefix(start);
	string end_prefix = get_station_prefix(end);
	int route_length = 1;
	if (start_prefix == end_prefix) {
		
		Node* current = start_node;
		route[0] = start_node->item + " (" + start_node->key + ") " ;
		while (current->next != NULL)
		{
			if (current->key == end) {
				for (int i = 0; i < 100; i++) {
					if (route[i] == "") {
						return;
					}
					if (i != 0) {
						cout << " -> ";
					}
					
					cout << route[i] ;
					
				}
				
			}
			current = current->next;
			route[route_length] = current->item + " (" + current->key + ") ";
			route_length++;
			
		}
		for (int i = 0; i < route_length; i++) {
			route[i].clear();
		}
		route_length = 1;
		route[0] = start_node->item + " (" + start_node->key + ") ";
		current = start_node;
		while (current->previous != NULL) {
			if (current->key == end) {
				for (int i = 0; i < 100; i++) {
					if (route[i] == "") {
						return;
					}
					if (i != 0) {
						cout << " -> ";
					}

					cout << route[i];

				}

			}
			current = current->previous;
			route[route_length] = current->item + " (" + current->key + ") ";
			route_length++;
		}
	}
	else {
		
	}
	
	

}
