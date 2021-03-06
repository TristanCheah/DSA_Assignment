// DSAAssignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "MRT_System.h"
#include <cmath>
using namespace std;


int main()
{
    cout << "Hello World!\n"; 
	MRT_System System = MRT_System();
	//cout << x<<endl;
	System.readCSV();
	System.generateInterchanges();
	System.LoadFares();
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
			System.getLine(line);
			system("PAUSE");
		}
		else if (choice == "2")
		{
			string name;
			cout << "Station No. : ";
			string key;
			getline(cin,key);
			cout << "Is this a terminal Station? (Yes/No) : ";
			string isterminal;
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
			string interchanges[3];
			bool has_interchange_space = false;
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
					if (System.find(key_new) != NULL) {
						cout << "Station Name will now be " << System.find(key_new)->item << endl;
						name = System.find(key_new)->item;
						int interchange_validation_count = 0;
						for (int i = 0; i < 2; i++) {
							if (System.find(key_new)->interchanges[i] != "") {
								interchange_validation_count++;
							}
						}
						if (interchange_validation_count >= 2) {
							has_interchange_space = false;
							cout << "Station has too many interchanges" << endl;
							continue;
						}
						interchanges[interchange_count] = key_new;
						interchange_count++;
					}
					
					
				}
				
			}
			else {
				cout << "Station Name: ";
				string stat_name;
				getline(cin, stat_name);
				name = stat_name;
			}
			bool added;
			if (!has_interchange_space) {
				 added = System.addWrite(key, name, Distanceprev, Distancenext, interchanges);
			}
			else {
				added = false;
			}
			if (added == true) {
				cout << "Station added" << endl;
			}
			else {
				cout << "Station could not be added" << endl;
			}
		}
		else if (choice == "3") {
			cout << "Which Station are you looking for (Station Name):";
			string name;
			getline(cin, name);
			System.displayStationInfo(name);
		}
		else if (choice == "4") {
			cout << "Please input a starting station:";
			string start;			
			getline(cin, start);
			cout << "Please input a ending station:";
			string end;
			getline(cin, end);

			string route[100];
			
			System.displayRoute(start, end, route, 0, 0);
		}
		else if (choice == "5") {
			cout << "what station prefix do u want for this new line: ";
			string prefix;
			getline(cin, prefix);
			while (true) {
				cout << "Station No. : ";
				string no;
				getline(cin, no);
				string key = prefix + no;

				cout << "Is this a terminal Station? (Yes/No) : ";
				string name;
				string isterminal;
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
				string interchanges[3];
				bool has_interchange_space = false;
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
						if (System.find(key_new) != NULL) {
							cout << "Station Name will now be " << System.find(key_new)->item << endl;
							name = System.find(key_new)->item;
							int interchange_validation_count = 0;
							for (int i = 0; i < 2; i++) {
								if (System.find(key_new)->interchanges[i] != "") {
									interchange_validation_count++;
								}
							}
							if (interchange_validation_count >= 2) {
								has_interchange_space = false;
								cout << "Station has too many interchanges" << endl;
								continue;
							}
							interchanges[interchange_count] = key_new;
							interchange_count++;
						}


					}
				}
				else {
					cout << "Station Name: ";
					string stat_name;
					getline(cin, stat_name);
					name = stat_name;
				}
				bool added;
				if (!has_interchange_space) {
					added = System.addWrite(key, name, Distanceprev, Distancenext, interchanges);
				}
				else {
					added = false;
				}
				if (added == true) {
					cout << "Station added" << endl;
				}
				else {
					cout << "Station could not be added" << endl;
				}
				cout << "Do you want to add another station (Yes/No): ";
				string Continue;
				getline(cin, Continue);
				if (Continue == "No") {
					break;
				}
			}
		}
		else if (choice == "0") {
			System.print();
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
