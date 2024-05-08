#pragma once
#include <iostream>
#include <String>
#include <list>
#include <unordered_map>
#include <iterator>
#include <queue>
#include<vector>
#include <stack>
#include <fstream>
//for time
#include <ctime>
using namespace std;

class UserAccount;

struct Date {
	int day;
	int month;
	int year;

	bool operator==(const Date& other) const {
		return day == other.day && month == other.month && year == other.year;
	}
};

struct stationInfo {
	int soldTickets = 0;
	double totalIncome = 0;
	vector<string> Passengers;
};

struct DateHash {
	std::size_t operator()(const Date& date) const {
		return std::hash<int>()(date.day) ^ std::hash<int>()(date.month) ^ std::hash<int>()(date.year);
	}
};

struct DateEqual {
	bool operator()(const Date& lhs, const Date& rhs) const {
		return lhs.day == rhs.day && lhs.month == rhs.month && lhs.year == rhs.year;
	}
};


class station
{
public:
	string name;
	int lineNumber=0;
	bool intersection = false;
	bool visited = false;
	bool chosen = false;
	list<queue< pair<string, int>>> possiblePaths;
	queue <pair<string, int>> shortestPath;
	unordered_map<Date, stationInfo, DateHash, DateEqual> stationMap;

	station(string n, int num);
	station();

	void addTickets(tm date);
	void addIncome(UserAccount user, tm date);
	void addPassenger(unordered_map<Date, stationInfo, DateHash, DateEqual>  stationMap, tm date, UserAccount user);

	int getSoldTickets(char time, tm date);
	double getTotalIncome(char time, tm date);
	int getTotalPassengers(char time, tm date);
	string getName();

	bool valueExistsInMap(unordered_map<Date, stationInfo, DateHash, DateEqual>& stationMap, Date date);
	Date timeDecrement(Date date);
	Date convertTm(tm current);

	void writeData(unordered_map<string, station> stationsList);
	unordered_map<string, station> readData();
	bool stringToBool(const std::string& str);
	vector<string> split(const string& str, char delimiter);
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
	void removeStation(int lineNumber, string stationName, bool& successfulEdit/* = false*/);
};