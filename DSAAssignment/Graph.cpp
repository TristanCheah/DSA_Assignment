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
		current->distanceNext = n->distancePrev;
		size += 1;
		return true;
	}
}

bool Graph::add(KeyType newKey, ItemType newItem, int distancePrev, int distanceNext, string interchanges[2]) {
	int hash = this->hash(newKey);
	int Priority = stoi(this->priority(newKey));
	Node *n = new Node;
	Node* other_interchange = new Node;
	n->key = newKey;
	n->priority = Priority;
	n->item = newItem;
	n->next = NULL;
	n->distancePrev = distancePrev;
	n->distanceNext = distanceNext;
	n->previous - NULL;
	for (int i = 0; i < 2; i++) {
		n->interchanges[i] = interchanges[i];
	}
	for (int i = 0; i < 2; i++) {
		if (interchanges[i] == "") {
			continue;
		}
		else {
			other_interchange = this->find(interchanges[i]);
			for (int j = 0; j < 2; j++) {
				if (other_interchange->interchanges[j] == "") {
					other_interchange->interchanges[j] = newKey;
					break;
				}
			}
		}
	}


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
				n->previous->distanceNext = n->distancePrev;
				n->next->distancePrev = n->distanceNext;
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
		n->previous->distanceNext = n->distancePrev;
		size += 1;
		return true;
	}
}

void Graph::addInterchanges(string interchanges[2]) {
	for (int i = 0; i < 2; i++) {
		if (this->find(interchanges[i]) != NULL) {
			Node* interchange_node = this->find(interchanges[i]);
			for (int j = 0; j < 2; j++) {
				if (interchange_node->interchanges[j] == ""  && interchanges[j] != interchange_node->key) {
					interchange_node->interchanges[j] = interchanges[j];
				}
			}
		}
	}
}
bool Graph::addWrite(KeyType newKey, ItemType newItem, int distancePrev,int distanceNext, string interchanges[2]) {
	int hash = this->hash(newKey);
	int Priority = stoi(this->priority(newKey));
	Node *n = new Node;
	Node* other_interchange = new Node;
	n->key = newKey;
	n->priority = Priority;
	n->item = newItem;
	n->next = NULL;
	n->distancePrev = distancePrev;
	n->distanceNext = distanceNext;
	n->previous - NULL;
	for (int i = 0; i < 2; i++) {
		n->interchanges[i] = interchanges[i];	
	}
	for (int i = 0; i < 2; i++) {
		if (interchanges[i] == "") {
			continue;
		}
		else {
			other_interchange = this->find(interchanges[i]);
			for (int j = 0; j < 2; j++) {
				if (other_interchange->interchanges[j] == "") {
					other_interchange->interchanges[j] = newKey;
					break;
				}
			}
		}
	}


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
				n->previous->distanceNext = n->distancePrev;
				n->next->distancePrev = n->distanceNext;
				
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
		n->previous->distanceNext = n->distancePrev;
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
	if (key == "") {
		return NULL;
	}
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
				if (current->previous != NULL) {
					cout << "Previous Station : " << current->previous->item << endl;
					if (current->distancePrev != NULL) {
						cout << "Distance to Prev Station (" << current->previous->item << ") : " << current->distancePrev << endl;
					}
				}
				else {
					cout << "Terminal station" << endl;
				}
				if (current->next != NULL) {
					cout << "Next Station : " << current->next->item << endl;
					if (current->distanceNext != NULL) {
						cout << "Distance to Next Station (" << current->next->item << ") : " << current->distanceNext << endl;
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
	file.close();
	file.open("Routes.csv");
	string stationNo;
	string distance;
	if (file.is_open()) {
		for (int i = 0; i < MAX_SIZE; i++) {
			Node* current = new Node;
			if (items[i] != NULL) {
				current = items[i];
				while (current != NULL) {
					stationNo += current->key + ",";
					if (current->distanceNext > 0) {
						distance += to_string(current->distanceNext) + ",";
					}
					
					current = current->next;
				}
				stationNo += "\n";
				distance += "\n";
				
				file << stationNo;
				file << distance;
				stationNo = "";
				distance = "";
			}
		}
	}
	file.close();
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

void Graph::CalculateFare(int distance_travelled) {
	float fares[16];
	ifstream file;
	file.open("Fares.csv");
	if (file.is_open()) {
		string word;
		int row_count = 0;
		while (!file.eof()) {
			string no;
			string Name;
			string row;
			getline(file, row);
			std::stringstream s_stream(row);
			int count = 0;
			while (getline(s_stream, word, ',')) {
				if (count == 0) {
					fares[row_count] = stof(word);
					row_count++;
					count++;
				}
				else {
					fares[row_count] = stof(word);
					row_count++;
				}
			}
		}
	}
	file.close();

	for (int i = 15; i > -1; i -= 2) {
		if (distance_travelled/1000 > fares[i]) {
			cout << "\nYour fare is $" << fares[i + 1] / 100 << endl;
			return;
		}
	}
	cout << "\nYour fare is $" << fares[15] / 100 << endl;
}
void Graph::displayRoute(KeyType start, KeyType end, string route[100], int route_length, float distance) {
	
	Node* start_node = this->find(start);
	Node* end_node = this->find(end);
	if (start_node == NULL) {
		cout << "Starting station does not exist" << endl;
		return;
	}
	if (end_node == NULL) {
		cout << "End station does not exist" << endl;
		return;
	}

	// if end station's station prefix = start's prefix, iterate down the line.

	string start_prefix = get_station_prefix(start);
	string end_prefix = get_station_prefix(end);
	int prev_route_len = route_length;
	
	if (start_prefix == end_prefix) {

		Node* current = start_node;
		route[route_length] = start_node->item + " (" + start_node->key + ") ";
		route_length++;

		
		while (current->next != NULL)
		{
			if (current->key == end) {
				
				for (int i = 0; i < 100; i++) {
					if (route[i] == "") {
						CalculateFare(distance);
						return;
					}
					if (i != 0) {
						cout << " -> ";
					}

					cout << route[i];
				}
				
			}
			distance += current->distanceNext;
			current = current->next;			
			route[route_length] = current->item + " (" + current->key + ") ";
			route_length++;

		}
		//if reach terminal
		if (current->key == end) {
			distance += current->distanceNext;
			for (int i = 0; i < 100; i++) {
				if (route[i] == "") {
					CalculateFare(distance);
					return;
				}
				if (i != 0) {
					cout << " -> ";
				}
				cout << route[i];
			}
		}

		//resetting
		for (int i = prev_route_len; i < 100; i++) {
			route[i].clear();
		}
		distance = 0;
		route_length = prev_route_len;
		route[route_length] = start_node->item + " (" + start_node->key + ") ";
		route_length++;
		current = start_node;
		//for other dir
		while (current->previous != NULL) {
			if (current->key == end) {
				for (int i = 0; i < 100; i++) {
					if (route[i] == "") {
						CalculateFare(distance);
						return;
					}
					if (i != 0) {
						cout << " -> ";
					}

					cout << route[i];

				}
				
			}
			distance += current->distancePrev;
			current = current->previous;
			route[route_length] = current->item + " (" + current->key + ") ";
			route_length++;
		}
		
		if (current->key == end) {
			distance = current->distancePrev;
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
	}
	else {
		//find an interchange on this line
		Node* current = start_node;
		route[route_length] = current->item + " (" + current->key + ") ";
		route_length++;
		while (current->next != NULL) {
			if (current->interchanges[0] != "") {
				for (int i = 0; i <= 1; i++) {
					string interchange_prefix = get_station_prefix(current->interchanges[i]);
					if (interchange_prefix == end_prefix) {
						Node* new_start = this->find(current->key);
						
						displayRoute(new_start->interchanges[i], end, route, route_length, distance);
						return;
					}
				}
			}
			distance = current->distanceNext;
			current = current->next;
			route[route_length] = current->item + " (" + current->key + ") ";
			route_length++;
		}

		for (int i = prev_route_len; i < 100; i++) {
			route[i].clear();
		}
		distance = 0;
		route_length = prev_route_len;
		route[route_length] = start_node->item + " (" + start_node->key + ") ";
		route_length++;

		current = start_node;
		while (current->previous != NULL) {
			if (current->interchanges[0] != "") {
				for (int i = 0; i <= 1; i++) {
					string interchange_prefix = get_station_prefix(current->interchanges[i]);
					if (interchange_prefix == end_prefix) {
						Node* new_start = this->find(current->key);

						displayRoute(new_start->interchanges[i], end, route, route_length, distance);
						return;
					}
				}
			}
			distance = current->distancePrev;
			current = current->previous;
			route[route_length] = current->item + " (" + current->key + ") ";
			route_length++;
		}
	}
}
void Graph::addLine() {
	cout << "what station prefix do u want for this new line: ";
	string prefix;
	getline(cin, prefix);
	while (true) {
		cout << "what number is this station: ";
		string number;
		getline(cin, number);
		string stationNo = prefix + number;
		cout << stationNo << endl;
		cout << "Is this a terminal Station? (Yes/No) : ";
		string isterminal;
		string name;
		getline(cin, isterminal);
		string distancenext;
		string distanceprev;
		int Distancenext;
		int Distanceprev;
		if (isterminal == "Yes") {
			cout << "Which direction? (Start/End) : ";
			string whatdirection;
			getline(cin, whatdirection);
			if (whatdirection == "Start") {
				cout << "distance to Next Station: ";

				getline(cin, distancenext);
				Distancenext = stoi(distancenext);
				Distanceprev = 0;
			}
			else if (whatdirection == "End") {
				cout << "distance to Previous Station: ";

				getline(cin, distanceprev);
				Distanceprev = stoi(distanceprev);
				Distancenext = 0;
			}
		}
		else if (isterminal == "No") {
			cout << "distance to Next: ";
			getline(cin, distancenext);
			Distancenext = stoi(distancenext);
			cout << "distance to Previous Station: ";
			getline(cin, distanceprev);
			Distanceprev = stoi(distanceprev);
		}
		cout << "Is this an interchange (Yes/No) : ";
		string isinterchange;
		getline(cin, isinterchange);
		string interchanges[2];
		bool more_than_one = false;
		if (isinterchange == "Yes") {
			bool getting_interchange = true;

			int interchange_count = 0;

			while (getting_interchange) {
				string key_new;
				if (interchange_count <= 0) {
					cout << "Provide station number that is an interchange with this station (Type ""No"" to exit): ";
					getline(cin, key_new);
				}
				else {
					getting_interchange = false;
				}

				if (key_new == "No") {
					getting_interchange = false;
				}
				if (this->find(key_new) != NULL) {
					cout << "Station Name will now be " << this->find(key_new)->item << endl;
					name = this->find(key_new)->item;
					for (int i = 0; i < 2; i++) {
						if (this->find(key_new)->interchanges[i] != "") {
							more_than_one = true;
						}
					}
					if (more_than_one == true) {
						cout << "Station has too many interchanges" << endl;
						break;
					}
					interchanges[interchange_count] = key_new;
					interchange_count++;
				}
			}
		}
		else {
			if (name == "") {
				cout << "What is the name of the Station: ";
				getline(cin, name);
			}
		}
		this->add(stationNo, name, Distanceprev, Distancenext, interchanges);
		cout << "do you want to add another station (Yes/No): ";
		string choice;
		getline(cin, choice);
		if (choice == "No") {
			break;
		}
	}
}
