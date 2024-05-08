#include "MetroMate.h"
station::station(string n, int num) {
	name = n;
	lineNumber = num;
}
//Done functions
void MetroMate::createNewStation(int lineNumber, int stationNumber) { //station number is used when the admin add more than one station at time
	string sName;
	if (stationNumber == 0)
		cout << "Enter the station name you want to add: ";
	else cout << " Station " << stationNumber << " name: ";
	cin >> sName;
	MetroLines[lineNumber].push_back(station(sName, lineNumber));
	addStationToMetroSystem(MetroLines[lineNumber].back().name);
}
void MetroMate::addStationToMetroSystem(string stationName) {
	Metromate[stationName] = list < pair<station*, int>>();
	numberOfStations++;
}
void MetroMate::connectStations(station* station1, station* station2, int distance) {
	Metromate[station1->name].push_back(make_pair(station2, distance));
	Metromate[station2->name].push_back(make_pair(station1, distance));
}
void MetroMate::displayStations() {
	for (int LineNumber = 1; LineNumber <= numberOfLines; LineNumber++) {
		int i = 1;
		cout << " Stations in Line " << LineNumber << ":\n";
		for (station current : MetroLines[LineNumber]) {
			if (!current.chosen) cout << i++ << ". " << current.name << "\n";
			if (current.chosen) cout << i++ << ". " << current.name << " ( Chosen )\n";
		}
		cout << "________________________________\n";
	}
}
station* MetroMate::chooseStation() {
	int choice, line;
	while (true) {
		cout << " Enter Line number:";
		cin >> line;
		cout << " Station Number";
		cin >> choice;
		//if (&MetroLines[line].at(choice).chosen) {
		//	cout << " This station is already chosen before, please choose again!\n";
		//}
		//else 
			break;
	}
	return &MetroLines[line].at(choice);
}

void MetroMate::stationPositioning() {
	displayStations();
	station* s1 = chooseStation();
	cout << "What is the position of this station?\n";
	cout << " 1- Terminal station\n 2- between two stations\n";
	cout << "Enter your choice : ";
	int choice;
	cin >> choice;
	cout << "-----------------------\n";
	displayStations();
	switch (choice) {
	case 1:
		cout << "\t\t*** the Adition is the first or the end ***  \n";
		cout << " The name station connected to this one is: ";
		connectionDetails(s1);
		break;
	case 2:
		cout << "\t\t*** the Adition is between two stations ***  \n";
		cout << " the name of tha station before it is: ";
		connectionDetails(s1);
		cout << " the name of station after it is: ";
		connectionDetails(s1);
		break;
	}
	//delete s1;
}
void MetroMate::connectionDetails(station* sourceStation) {
	int distance;
	station* destinationStation = chooseStation();
	if (sourceStation->lineNumber == destinationStation->lineNumber) {
		sourceStation->intersection = true;
		destinationStation->intersection = true;
	}
	cout << "Distance between them:";
	cin >> distance;
	connectStations(sourceStation, destinationStation, distance);
	//delete destinationStation;
}
void MetroMate::remove_connection(station* station1, station* station2, int distance) {
	Metromate[station2->name].remove(make_pair(station1, distance));
	Metromate[station1->name].remove(make_pair(station2, distance));
}
void MetroMate::displayMetroMate() {
	for (int LineNumber = 1; LineNumber <= numberOfLines; LineNumber++) {
		cout << " Stations in Line: " << LineNumber << " >>\n";
		for (station currentstation : MetroLines[LineNumber]) {
			cout << "- " << currentstation.name << " Connected with:\n";
			for (auto connection : Metromate[currentstation.name]) {
				cout << " Station " << connection.first->name;
				cout << " - line : " << connection.first->lineNumber << endl;
			}
		}
		cout << "________________________________\n";
	}
}

void MetroMate::editStationName(int lineNumber, string oldName, string newName, bool& notFoundStation) {
	// Find the station to edit
	bool found = false;
	for (auto it = MetroLines.begin(); it != MetroLines.end(); ++it) {
		int currentLine = it->first;
		if (currentLine == lineNumber) {
			int i = 0;
			for (auto station : it->second) {
				i++;
				if (station.name == oldName) {
					station.name = newName;
					it->second[i].name = newName;
					found = true;
					break; // Exit inner loop after finding the station
				}
			}
		}
	}
	if (found) {
		cout << "Station name updated successfully!\n";
		notFoundStation = false;
	}
	else {
		cout << "Station not found. Please enter a valid line number and station name.\n";
		notFoundStation = true;
	}
}
void MetroMate::editStationPosition(int lineNumber, string stationName) {
	// Find the line
	auto it = MetroLines.find(lineNumber);
	if (it != MetroLines.end()) {
		// Find the station to edit
		for (auto iter = it->second.begin(); iter != it->second.end(); ++iter) {
			if (iter->name == stationName) {
				station* stationToEdit = &(*iter);
				// Display current position
				cout << "Current position of station " << stationName << ":\n";
				//connectionDetails(stationToEdit);
				removeStation(lineNumber, stationName);
				// Choose new position for the station
				stationPositioning();
				cout << "Station position edited successfully.\n";
				return;
			}
		}
		cout << "Station " << stationName << " not found in line " << lineNumber << ".\n";
	}
	else {
		cout << "Line " << lineNumber << " not found.\n";
	}
}
void MetroMate::removeStation(int lineNumber, string stationName, bool& successfulEdit) {
	//Find the line 
	auto it = MetroLines.find(lineNumber);
	if (it != MetroLines.end()) {
		// Find the station to remove
		for (auto iter = it->second.begin(); iter != it->second.end(); ++iter) {
			if (iter->name == stationName) {
				// Remove station from the metro system
				MetroLines[lineNumber].erase(iter);
				// Remove connections related to the station
				auto it2 = Metromate.find(stationName);
				if (it2 != Metromate.end()) {
					for (auto& connection : it2->second) {
						station* connectedStation = connection.first;
						int distance = connection.second;
						auto it3 = Metromate.find(connectedStation->name);
						if (it3 != Metromate.end()) {
							it3->second.remove(make_pair(connectedStation, distance));
						}
					}
					Metromate.erase(it2);
				}
				successfulEdit = true;
				return;
			}
		}
		cout << "Station " << stationName << " not found in line " << lineNumber << ".\n";
	}
	else {
		cout << "Line " << lineNumber << " not found.\n";
	}
}
