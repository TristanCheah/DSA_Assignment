// DSAAssignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "Graph.h"
#include <cmath>
using namespace std;


int main()
{
    cout << "Hello World!\n"; 
	Graph graph = Graph();
	//cout << x<<endl;
	graph.readCSV();
	graph.generateInterchanges();
	//graph.print();
	while (true) {
		cout << "\nPlease pick an option" << endl;
		cout << "1. Find Line" << endl;
		cout << "2. Add Station to existing line" << endl;
		cout << "3. Find Information about Station" << endl;
		cout << "4. Find a route from 1 station to another " << endl;
		cout << "5. Add a new line"<<endl;
		cout << "0. Exit" << endl;
		cout << "Choice: ";
		string choice;
		getline(cin, choice);
		if (choice == "1") {
			cout << "which line are u looking for: ";
			string line;
			getline(cin, line);
			graph.getLine(line);
			system("PAUSE");
		}
		else if (choice == "2") {
			cout << "Station No. : ";
			string key;
			getline(cin,key);
			cout << "Station Name: ";
			string name;
			getline(cin,name);
			cout << "Is this a terminal? (Yes/No) : ";
			string isterminal;
			getline(cin, isterminal);
			string distancenext;
			string distanceprev;
			int Distancenext;
			int Distanceprev;
			if (isterminal == "Yes") {
				cout << "Which direction? (Start/End) : ";
				string whatdirection;
				if (whatdirection == "Start") {
					cout << "distance to Next: ";
					
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
			bool added = graph.addWrite(key, name, Distancenext, Distanceprev);
			if (added == true) {
				cout << "Station added" << endl;
			}
			else {
				cout << "Station could not be added" << endl;
			}
			
		}
		else if (choice == "3") {
			cout << "Which Station are you looking for:";
			string name;
			getline(cin, name);
			graph.displayStationInfo(name);
		}
		else if (choice == "4") {
			cout << "Please input a starting station:";
			string start;			
			getline(cin, start);
			cout << "Please input a ending station:";
			string end;
			getline(cin, end);

			string route[100];
			
			graph.displayRoute(start, end, route, 0, 0);
		}
		else if (choice == "5") {
			graph.addLine();
		}
		else if (choice == "0") {
			graph.print();
			break;
		}
		else {
			cout << "please enter a valid option"<<endl;
		}
	}
	//graph.displayStationInfo("Tanah Merah");
	system("PAUSE");
	
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
