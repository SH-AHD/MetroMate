#pragma once
#include <iostream>
#include <String>
#include <list>
#include <unordered_map>
#include <iterator>
#include <queue>
#include <stack>
#include <fstream>
using namespace std;
class station
{
public:
	string name;
	int lineNumber=0;
	bool intersection = false;
	bool visited = false;
	bool chosen = false;
	list<queue< pair<station*, int>>> possiblePaths;
	queue <pair<station*, int>> shortestPath;
	station(string n, int num);
};
class MetroMate
{
public:
	int numberOfStations=0;
	int numberOfLines=0;
	unordered_map<int, vector<station>> MetroLines;
	unordered_map<string, list<pair<station*, int>>> Metromate;
	void createNewStation(int lineNumber, int stationNumber = 0);
	void addStationToMetroSystem(string stationName);
	void connectStations(station* station1, station* station2, int distance);
	void stationPositioning();
	void displayStations();
	void connectionDetails(station* sourceStation);
	void remove_connection(station* station1, station* station2, int distance);
	station* chooseStation();
	void displayMetroMate();
	void editStationName(int lineNumber, string oldName, string newName, bool& notFoundStation);
	void editStationPosition(int lineNumber, string stationName);
	void removeStation(int lineNumber, string stationName, bool& successfulEdit = false);
};