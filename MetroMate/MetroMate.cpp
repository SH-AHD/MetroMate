#include "MetroMate.h"
#include "UserAccount.h"

#include <ctime>
using namespace std;
DateEqual de;
DateHash dh;

station::station(string n, int num) {
	name = n;
	lineNumber = num;
}
station::station() {

}

void station::addTickets(tm date) {
	Date mapDate = convertTm(date);
	if (valueExistsInMap(stationMap, mapDate)) {
		stationMap[mapDate].soldTickets++;
	}
	else {
		stationInfo SI;
		SI.soldTickets++;
		stationMap.insert(make_pair(mapDate, SI));
	}
}
void station::addIncome(UserAccount user, tm date) {
	Date mapDate = convertTm(date);
	if (user.chosenSubscription.name == "wallet") {
		if (valueExistsInMap(stationMap, mapDate)) {
			stationMap[mapDate].totalIncome += user.chosenSubscription.price;
		}
		else {
			stationInfo SI;
			SI.totalIncome += user.chosenSubscription.price;
			stationMap.insert(make_pair(mapDate, SI));
		}


	}
}
void station::addPassenger(unordered_map<Date, stationInfo, DateHash, DateEqual>  stationMap, tm date, UserAccount user) {
	Date mapDate = convertTm(date);
	if (valueExistsInMap(stationMap, mapDate)) {
		bool userInVector = false;
		//to itrate over the passengers vector
		for (const auto& itr : stationMap[mapDate].Passengers) {
			if (user.Name == itr) {
				userInVector = true;
				break;
			}
		}
		if (!userInVector) {
			stationMap[mapDate].Passengers.push_back(user.Name);

		}

	}
	else {
		stationInfo SI;
		SI.Passengers.push_back(user.Name);
		stationMap.insert(make_pair(mapDate, SI));

	}

}

int station::getSoldTickets(char time, tm date) {
	//add a variable that will hold the total sold tickets
	int total = 0;
	//import the date into a temporary varaible and decrement it by 1
	Date tempDate = convertTm(date);
	tempDate = timeDecrement(tempDate);

	if (time == 'd') {
		total = stationMap[tempDate].soldTickets;
	}
	else if (time == 'w') {
		//when we want to show sold tickets in a week we loop for 7 days and add the values to the total
		for (int i = 1; i < 8; i++) {
			total += stationMap[tempDate].soldTickets;
			tempDate = timeDecrement(tempDate);
		}
	}
	else if (time == 'm') {
		//in a month we loop for 30 days and add the values to the total
		for (int i = 1; i < 31; i++) {
			total += stationMap[tempDate].soldTickets;
			tempDate = timeDecrement(tempDate);
		}
	}
	else if (time == 'y') {
		//in a year we loop for 365 days and add the values to the total
		for (int i = 1; i < 366; i++) {
			total += stationMap[tempDate].soldTickets;
			tempDate = timeDecrement(tempDate);
		}
	}
	return total;
}
double station::getTotalIncome(char time, tm date) {
	//add a variable that will hold the total sold tickets
	double total = 0;
	//import the date into a temporary varaible and decrement it by 1
	Date tempDate = convertTm(date);
	tempDate = timeDecrement(tempDate);

	if (time == 'd') {
		total = stationMap[tempDate].totalIncome;
	}
	else if (time == 'w') {
		//when we want to show sold tickets in a week we loop for 7 days and add the values to the total
		for (int i = 1; i < 8; i++) {
			total += stationMap[tempDate].totalIncome;
			tempDate = timeDecrement(tempDate);
		}
	}
	else if (time == 'm') {
		//in a month we loop for 30 days and add the values to the total
		for (int i = 1; i < 31; i++) {
			total += stationMap[tempDate].totalIncome;
			tempDate = timeDecrement(tempDate);
		}
	}
	else if (time == 'y') {
		//in a year we loop for 365 days and add the values to the total
		for (int i = 1; i < 366; i++) {
			total += stationMap[tempDate].totalIncome;
			tempDate = timeDecrement(tempDate);
		}
	}
	return total;
}
int station::getTotalPassengers(char time, tm date) {
	//add a variable that will hold the total sold tickets
	int total = 0;
	//import the date into a temporary varaible and decrement it by 1
	Date tempDate = convertTm(date);
	tempDate = timeDecrement(tempDate);

	if (time == 'd') {
		total = stationMap[tempDate].Passengers.size();
	}
	else if (time == 'w') {
		//when we want to show sold tickets in a week we loop for 7 days and add the values to the total
		for (int i = 1; i < 8; i++) {
			total += stationMap[tempDate].Passengers.size();
			tempDate = timeDecrement(tempDate);
		}
	}
	else if (time == 'm') {
		//in a month we loop for 30 days and add the values to the total
		for (int i = 1; i < 31; i++) {
			total += stationMap[tempDate].Passengers.size();
			tempDate = timeDecrement(tempDate);
		}
	}
	else if (time == 'y') {
		//in a year we loop for 365 days and add the values to the total
		for (int i = 1; i < 366; i++) {
			total += stationMap[tempDate].Passengers.size();
			tempDate = timeDecrement(tempDate);
		}
	}
	return total;
}
string station::getName() {
	return name;
}

bool station::valueExistsInMap(unordered_map<Date, stationInfo, DateHash, DateEqual>& stationMap, Date date) {
	for (const auto& pair : stationMap) {
		if (pair.first == date) {
			return true;
		}
	}
	return false;
}

Date station::timeDecrement(Date date) {

	//store the date in a temporary value
	Date tempTime = date;

	//check if the month is finished so we dont go to -1 day
	if (tempTime.day == 1) {
		tempTime.day = 30;

		//check if the year is finished so we dont go to -1 month 
		if (tempTime.month == 1) {
			tempTime.month = 12;
			//and decrement the year bc the year is finished 
			tempTime.year -= 1;
		}
		else {
			//otherwise decrement the month 
			tempTime.month -= 1;
		}
	}
	else {
		//if the month is not finished decrement the day
		tempTime.day -= 1;
	}
	return tempTime;
}
Date station::convertTm(tm current) {
	Date final;
	final.day = current.tm_mday;
	final.month = current.tm_mon;
	final.year = current.tm_year;
	return final;
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
				bool test = false;
				removeStation(lineNumber, stationName,test);
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
