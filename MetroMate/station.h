#include<string>
#include<iostream>
#include<unordered_map>
#include<vector>
#pragma once
//#include"UserAccount.h"


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

class station {
public:
	string name;
	int lineNumber;
	unordered_map<Date, stationInfo,DateHash,DateEqual> stationMap;
	station(string n, int num);
	station();

	/*unordered_map<system_clock::time_point&, deque<Train>>& stationSchedule;

	   void findTrips(system_clock::time_point tripTime);*/


	//void findTrips(system_clock::time_point tripTime);

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
};