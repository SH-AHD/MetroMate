
#include<iostream>
//#include "Tickets.h"
#include <ctime>
//#include <string>
using namespace std;
class Tickets {
	string id;
	string checkInStation;
	string checkOutStation;
	float fare;
	float calculateFareForIndividualRides(string metroStages) {
		if (metroStages == "stage #1") {
			return fare = 6;
		}
		else if (metroStages == "stage #2") {
			return fare = 8;
		}
		else if (metroStages == "stage #3") {
			return fare = 12;
		}
		else if (metroStages == "stage #4") {
			return fare = 15;
		}
		return fare = 0;
	}



};
