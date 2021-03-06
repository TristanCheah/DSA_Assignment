#pragma once
using namespace std;
#include <string>

const int MAX_SIZE = 676;
const int MAX_INTERCHANGES = 4; //demo data fix
const int FARES_NUM = 10;//demo data fix
typedef string ItemType;
typedef string KeyType;
typedef int PriorityType;

class MRT_System {
private:
	struct Node {
		ItemType item;
		KeyType key;
		PriorityType priority;
		Node* previous;
		Node* next;
		int distanceNext;
		int distancePrev;
		KeyType interchanges[MAX_INTERCHANGES];

	};
	Node *items[MAX_SIZE];
	int size;
	float fares[FARES_NUM];

public:
	MRT_System();
	~MRT_System();
	void readCSV();
	void generateInterchanges();
	void LoadFares();
	void displayStationInfo(string station_name);
	Node* find(KeyType key);
	int hash(KeyType key);
	void displayRoute(KeyType start, KeyType end, string route[100], int route_length, float distance);
	void CalculateFare(int distance_travelled);
	string priority(KeyType key);
	bool add(KeyType newKey, ItemType newItem);
	bool add(KeyType newKey, ItemType newItem, int distancePrev, int distanceNext, string interchanges[3]);
	bool addWrite(KeyType newKey, ItemType newItem, int distancePrev, int distanceNext, string interchanges[3]);
	void getLine(KeyType key);
	void addInterchanges(string interchanges[3]);
	string get_station_prefix(string station_no);
	void print();
	void write();
};