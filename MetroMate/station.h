#include<string>
#include<iostream>
#include<unordered_map>
#include<vector>
//#include"UserAccount.h"


//for time
#include <ctime>
using namespace std;

//class UserAccount;

struct stationInfo {
	int soldTickets = 0;
	double totalIncome = 0;
	vector<string> Passengers;
};

class station {
public:
	string name;
	int lineNumber;
	//unordered_map<tm, stationInfo> stationMap;
	station(string n, int num) {};
	station() {
	};

	/*unordered_map<system_clock::time_point&, deque<Train>>& stationSchedule;

	   void findTrips(system_clock::time_point tripTime);*/

	/*void addTickets(tm date);
	void addIncome(UserAccount user, tm date);
	void addPassenger(unordered_map<tm, stationInfo> stationMap, tm date, UserAccount user);

	int getSoldTickets(char time, tm date);
	double getTotalIncome(char time, tm date);
	int getTotalPassengers(char time, tm date);
	string getName();

	bool valueExistsInMap(unordered_map<tm, stationInfo>& stationMap, tm date);
	tm timeDecrement(tm date);*/
};