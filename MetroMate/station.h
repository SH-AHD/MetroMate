#include<string>
#include<iostream>
using namespace std;
class station {
public:
	string name;
	int lineNumber;

	station(string n, int num) {
		name = n;
		lineNumber = num;
	}
	station() {

	}

 unordered_map<system_clock::time_point&, deque<Train>>& stationSchedule;

    void findTrips(system_clock::time_point tripTime);
};
