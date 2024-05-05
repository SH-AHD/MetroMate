//#include"station.h"
////#include "UserAccount.h"
////
//////for time
//#include <ctime>
//using namespace std;
////
////
//void Station::findTrips(system_clock::time_point tripTime) {
//	for (auto& trainPair : stationSchedule) {
//		if (trainPair.second.getTrainSchedule().getArrivalTime() == tripTime) {
//			cout << trainPair.second.getTrainID();
//		}
//	}
//}
#include"station.h"
#include "UserAccount.h"

//for time
#include <ctime>
using namespace std;
DateEqual de;
DateHash dh;
//
//
//void station::findTrips(system_clock::time_point tripTime) {
//	for (auto& trainPair : stationSchedule) {
//		if (trainPair.second.getTrainSchedule().getArrivalTime() == tripTime) {
//			cout << trainPair.second.getTrainID();
//		}
//	}
//}

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
		stationMap.insert(make_pair( mapDate, SI));

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