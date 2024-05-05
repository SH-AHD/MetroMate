#include"station.h"
//#include "UserAccount.h"
//
////for time
//#include <ctime>
//using namespace std;
//
//
void Station::findTrips(system_clock::time_point tripTime) {
	for (auto& trainPair : stationSchedule) {
		if (trainPair.second.getTrainSchedule().getArrivalTime() == tripTime) {
			cout << trainPair.second.getTrainID();
		}
	}
}
//
//station::station(string n, int num) {
//	name = n;
//	lineNumber = num;
//}
//station::station() {
//
//}
//
//void station::addTickets(tm date) {
//	if (valueExistsInMap(stationMap, date)) {
//		stationMap[date].soldTickets++;
//	}
//	else {
//		stationInfo SI;
//		SI.soldTickets++;
//		stationMap.insert(date, SI);
//	}
//}
//void station::addIncome(UserAccount user, tm date) {
//
//	if (user.chosenSubscription.name == "wallet") {
//		if (valueExistsInMap(stationMap, date)) {
//			stationMap[date].totalIncome += user.chosenSubscription.price;
//		}
//		else {
//			stationInfo SI;
//			SI.totalIncome += user.chosenSubscription.price;
//			stationMap.insert(date, SI);
//		}
//
//
//	}
//}
//void station::addPassenger(unordered_map<tm, stationInfo> stationMap, tm date, UserAccount user) {
//
//	if (valueExistsInMap(stationMap, date)) {
//		bool userInVector = false;
//		//to itrate over the passengers vector
//		for (const auto& itr : stationMap[date].Passengers) {
//			if (user.Name == *itr) {
//				userInVector = true;
//				break;
//			}
//		}
//		if (!userInVector) {
//			stationMap[date].Passengers.push_back(user.Name);
//
//		}
//
//	}
//	else {
//		stationInfo SI;
//		SI.Passengers.push_back(user.Name);
//		stationMap.insert(date, SI);
//
//	}
//
//}
//
//int station::getSoldTickets(char time, tm date) {
//	//add a variable that will hold the total sold tickets
//	int total = 0;
//	//import the date into a temporary varaible and decrement it by 1
//	tm tempDate = timeDecrement(date);
//
//	if (time == 'd') {
//		total = stationMap[tempDate].soldTickets;
//	}
//	else if (time == 'w') {
//		//when we want to show sold tickets in a week we loop for 7 days and add the values to the total
//		for (int i = 1; i < 8:i++) {
//			total += stationMap[tempDate].soldTickets;
//			tempDate = timeDecrement(tempDate);
//		}
//	}
//	else if (time == 'm') {
//		//in a month we loop for 30 days and add the values to the total
//		for (int i = 1; i < 31:i++) {
//			total += stationMap[tempDate].soldTickets;
//			tempDate = timeDecrement(tempDate);
//		}
//	}
//	else if (time == 'y') {
//		//in a year we loop for 365 days and add the values to the total
//		for (int i = 1; i < 366:i++) {
//			total += stationMap[tempDate].soldTickets;
//			tempDate = timeDecrement(tempDate);
//		}
//	}
//	return total
//}
//double station::getTotalIncome(char time, tm date) {
//	//add a variable that will hold the total sold tickets
//	double total = 0;
//	//import the date into a temporary varaible and decrement it by 1
//	tm tempDate = timeDecrement(date);
//
//	if (time == 'd') {
//		total = stationMap[tempDate].totalIncome;
//	}
//	else if (time == 'w') {
//		//when we want to show sold tickets in a week we loop for 7 days and add the values to the total
//		for (int i = 1; i < 8:i++) {
//			total += stationMap[tempDate].totalIncome;
//			tempDate = timeDecrement(tempDate);
//		}
//	}
//	else if (time == 'm') {
//		//in a month we loop for 30 days and add the values to the total
//		for (int i = 1; i < 31:i++) {
//			total += stationMap[tempDate].totalIncome;
//			tempDate = timeDecrement(tempDate);
//		}
//	}
//	else if (time == 'y') {
//		//in a year we loop for 365 days and add the values to the total
//		for (int i = 1; i < 366:i++) {
//			total += stationMap[tempDate].soldTickets;
//			tempDate = timeDecrement(tempDate);
//		}
//	}
//	return total
//}
//int station::getTotalPassengers(char time, tm date) {
//	//add a variable that will hold the total sold tickets
//	int total = 0;
//	//import the date into a temporary varaible and decrement it by 1
//	tm tempDate = timeDecrement(date);
//
//	if (time == 'd') {
//		total = stationMap[tempDate].Passengers.size();
//	}
//	else if (time == 'w') {
//		//when we want to show sold tickets in a week we loop for 7 days and add the values to the total
//		for (int i = 1; i < 8:i++) {
//			total += stationMap[tempDate].Passengers.size();
//			tempDate = timeDecrement(tempDate);
//		}
//	}
//	else if (time == 'm') {
//		//in a month we loop for 30 days and add the values to the total
//		for (int i = 1; i < 31:i++) {
//			total += stationMap[tempDate].Passengers.size();
//			tempDate = timeDecrement(tempDate);
//		}
//	}
//	else if (time == 'y') {
//		//in a year we loop for 365 days and add the values to the total
//		for (int i = 1; i < 366:i++) {
//			total += stationMap[tempDate].Passengers.size();
//			tempDate = timeDecrement(tempDate);
//		}
//	}
//	return total
//}
//string station::getName() {
//	return name;
//}
//
//bool station::valueExistsInMap(unordered_map<tm, stationInfo>& stationMap, tm date) {
//	for (const auto& pair : map) {
//		if (pair.first == date) {
//			return true;
//		}
//	}
//	return false;
//}
//tm station::timeDecrement(tm date) {
//
//	//store the date in a temporary value
//	tm tempTime = date;
//
//	//check if the month is finished so we dont go to -1 day
//	if (tempTime.tm_mday == 1) {
//		tempTime.tm_mday = 30;
//
//		//check if the year is finished so we dont go to -1 month 
//		if (tempTime.tm_mon == 1) {
//			tempTime.tm_mon = 12;
//			//and decrement the year bc the year is finished 
//			tempTime.tm_year -= 1;
//		}
//		else {
//			//otherwise decrement the month 
//			tempTime.tm_mon -= 1;
//		}
//	}
//	else {
//		//if the month is not finished decrement the day
//		tempTime.tm_mday -= 1;
//	}
//	return tempTime;
//}