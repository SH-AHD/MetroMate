#pragma once //DONE
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
#include <deque>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std::chrono;
//for time
#include <ctime>
using namespace std;
#include "TrainManagement.h"

#include"DateTime.h"

class UserAccount;
class Train;
class Schedule;

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
	int lineNumber = 0;
	bool intersection = false;
	bool visited = false;
	bool end = false;
	bool chosen = false;
	queue<pair<string, int>> possiblePaths;
	queue<string > shortestPath;
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
	int numberOfStations = 0;
	int numberOfLines = 0;
	vector<int> noOfStationsInLine;
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

	////Line 

	deque<Train> trains;

	void addTrain(Train newTrain);
	void editTrain(int editTrainid);
	void removeTrain(int removedTrainid);
	void addTripToTrainSchedule(int trainid, Schedule schedule);
	void modifyTripFromTrainSchedule(int lineID, int id, string date, string DepartureTime);
	void deleteTripFromTrainSchedule(int trainID, string  date, string time);
	void simulateTrainBreakdown(int  brokenTrainID, string time, string date);
	size_t findScheduleIndex(Train train, string time, string date);
	void adjustNextTrainDepartureTime(Train t);
	void displaySpecificTrain(int lineID, int trainID);
	void displayTrains(int lineID);
	void displayTrainETAForUser(string stationName, string checkindate, chrono::system_clock::time_point currentTime);



	//check in functions
	void markAsUnvisited();
	station* findStation(string station, int line);
	void simpleDFS(string start, int startLine, string end);
	queue<string> shortestPath(string startStation, string endStation);

	//new 
	void undoChoice();
};