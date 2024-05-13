#include "helpingMethods.h"
#include "MetroMate.h"
#include "UserAccount.h"
#include <sstream>
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

void station::writeData(unordered_map<string, station> stationsList)
{
	
	ofstream outputFile;
	outputFile.open("stations.csv", std::ios::app);

	// Iterate over the hash table and write each key-value pair to the file
	for (const auto& entry : stationsList) {
		const string key = entry.first;
		const station Station = entry.second;

		// Write user data to the file
		outputFile << key << "," << Station.chosen << "," << Station.intersection << "," << Station.lineNumber << "," << Station.name << "," <<Station.possiblePaths.size()<<",";
		//paths
		/*list<queue< pair<string, int>>> ::iterator it;
		it = Station.possiblePaths.begin();*/
		/*for(const auto& it : Station.possiblePaths){
			queue< pair<string, int>> tmpqueue = it;
			outputFile << it.size() << ",";
			for (int i = 0; i < tmpqueue.size(); i++) {
				outputFile << tmpqueue.front().first << ","<< tmpqueue.front().second<<",";
				tmpqueue.pop();
			}
		}*/
		//shortest 
	/*
		queue< pair<string, int>> tmpShortest = Station.shortestPath;
		outputFile << tmpShortest.size() << ",";
		for (int i = 0; i < tmpShortest.size(); i++) {
			outputFile << tmpShortest.front().first << "," << tmpShortest.front().second<<",";
			tmpShortest.pop();
		}*/
		//date
		outputFile << Station.stationMap.size() << ",";
		for (const auto& entry : Station.stationMap) {
			outputFile << entry.first.day<<","<< entry.first.month<<","<<entry.first.year << "," << entry.second.Passengers.size()<< "," << entry.second.soldTickets << "," << entry.second.totalIncome << ",";
			for (const auto& entry2 : entry.second.Passengers) {
				outputFile << entry.second.Passengers.front() << ",";
			}
		}

	}


	outputFile.close();
}
unordered_map<string, station> station::readData()
{
	ifstream file("stations.csv");
	unordered_map<string, station> tmpstationsList;
	if (file.is_open()) {
		string line;

		while (getline(file, line)) {
			stringstream ss(line);
			string key;
			string attributeStr;


			if (line.empty()) {
				continue;
			}
			station tmpStation;
			if (getline(ss, key, ',') && getline(ss, attributeStr)) {
				vector<string> attributes = split(attributeStr, ',');
				tmpStation.chosen = stringToBool(attributes[0]);
				tmpStation.intersection = stringToBool(attributes[1]);
				tmpStation.lineNumber = stoi(attributes[2]);
				tmpStation.name = attributes[3];
				int Size = stoi(attributes[4]);
				int startIndex = 5;
				//paths
			/*	for (int i = 0; i < Size; i++) {
					int innerSize = stoi(attributes[startIndex]);
					startIndex++;
					queue< pair<string, int>> tmpQueue;
					for (int j = 0; j < innerSize; j++) {
						tmpQueue.push(make_pair(attributes[startIndex++], stoi(attributes[startIndex++])));
					}
					tmpStation.possiblePaths.push_back(tmpQueue);
				}*/
				//shortest
				/*Size = stoi(attributes[startIndex]);
				startIndex++;
				for (int j = 0; j < Size; j++) {
					tmpStation.shortestPath.push(make_pair(attributes[startIndex++], stoi(attributes[startIndex++])));
				}*/
				//date
				Size = stoi(attributes[startIndex++]);
				for (int i = 0; i < Size; i++) {
					Date date;
					date.day = stoi(attributes[startIndex++]);
					date.month = stoi(attributes[startIndex++]);
					date.year = stoi(attributes[startIndex++]);
					stationInfo tmpStationInfo;
					int Size2;
					Size2 = stoi(attributes[startIndex++]);
					tmpStationInfo.soldTickets = stoi(attributes[startIndex++]);
					tmpStationInfo.totalIncome = stod(attributes[startIndex++]);
					for (int i = 0; i < Size2; i++) {
						tmpStationInfo.Passengers.push_back(attributes[startIndex++]);
					}
					tmpStation.stationMap.insert(make_pair(date, tmpStationInfo));
				}
				
			}
			tmpstationsList.insert(make_pair(key, tmpStation));
		}



		file.close();
		cout << "stations data has been successfully loaded from the file." << endl;
	}
	else {
		cout << "Failed to open the file for reading." << endl;
	}
	return tmpstationsList;
}
bool station::stringToBool(const std::string& str) {
	std::istringstream iss(str);
	iss >> std::boolalpha;
	bool value;
	iss >> value;
	return value;
}

vector<string> station::split(const string& str, char delimiter) {
	vector<string> tokens;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
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
	int choice=-1, line=-1;
	cout << " Line number:";
	line = numberInRange(line, 1, numberOfLines);
	cout << " Station Number";
	choice = numberInRange(choice, 1, MetroLines[line].size());
	if (&MetroLines[line].at(choice).chosen) {
		cout << " This station is already chosen before, please choose again!\n";
		chooseStation();
	}
	else {
		return &MetroLines[line].at(choice);
	}

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


void MetroMate::markAsUnvisited() {
	for (int line = 1; line < numberOfLines; line++) {
		for (int i = 0; i < MetroLines[line].size(); i++) { MetroLines[line][i].visited = false; }
	}
}
station* MetroMate::findStation(string station, int line) {
	for (int i = 0; i < MetroLines[line].size(); i++) {
		if (MetroLines[line][i].name == station)return &MetroLines[line][i];
	}
}
void MetroMate::simpleDFS(string start, int startLine, string end, float fare) {
	stack<pair<pair<string, int>, float>> path; //station name and line number //distance
	path.push(make_pair(make_pair(start, startLine), 0));
	queue< pair< pair<string, int>, float> > pathToDestination;
	while (!path.empty()) {
		station* st = findStation(path.top().first.first, path.top().first.second);
		pair<pair<string, int>, int> current = path.top();
		pathToDestination.push(path.top());
		path.pop();

		if (!st->visited) {
			st->visited = true;
			if (st->name != end) {
				pathToDestination.push(current); //for saving station only
				cout << " [" << st->name << " Line " << st->lineNumber << "] ->";
				for (pair<station*, int> adj : Metromate[st->name]) {
					if (!adj.first->visited) {
						path.push(make_pair(make_pair(adj.first->name, adj.first->lineNumber), adj.second));
					}
				}
			}
			else {
				cout << " [" << st->name << " Line " << st->lineNumber << "]";
				pathToDestination.push(current);
				st->possiblePaths.push_back(make_pair(pathToDestination, fare));
				markAsUnvisited();
				break;
			}
		}
	}
}

