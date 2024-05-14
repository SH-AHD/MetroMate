#pragma once

#include "helpingMethods.h"
#include "MetroMate.h"
#include "SubscriptionDetails.h"
#include "DateTime.h"
#include<iostream>
#include<unordered_map>
#include<vector>
#include <ctype.h>//lower case
#include<string>
//for time
#include <chrono>
#include <ctime>
#include <sstream> // Include for istringstream
#include <iomanip> // Include for parse
#include <chrono>  // Include for sys_days and weekday



using namespace std;
using namespace std::chrono;
struct rideDetails {
	string sourceStation, targetStation;
	int lineNo1, lineNo2;
	float fare;
	//date and time
	pair<queue< pair< pair<string, int>, float> >, float> pathChosen;
};



class UserAccount
{
public:
	string Email;
	string Password;
	string Name;
	string Address;
	int Phone;
	tm startDate;
	bool LogedUser;
	list<rideDetails> rideLog;
	SubscriptionDetails chosenSubscription;
	int availableTrips;

	void PurchaceSubscription(UserAccount& user, unordered_map<std::string, SubscriptionDetails> subscription_plans, unordered_map<int, string> subscriptions_names, vector<pair<vector<string>, double>> zones);

	UserAccount() {
		//dont delete it
	}
	UserAccount(string email, string pass);
	UserAccount(string Email, string Password, string Name, string Address, int Phone);
	bool Register(unordered_map<string, UserAccount>& users, UserAccount user);
	bool VailEmail(string email);
	bool logIn(bool& isAdmin, UserAccount& theLog, string email, string password, unordered_map<string, UserAccount>& user);
	void ChangePassword(UserAccount& user, string NewPass);
	UserAccount updateInfo(string key, unordered_map<string, UserAccount>& users);
	UserAccount forgetPass(string mail, unordered_map<string, UserAccount>users);
	UserAccount LogOut(UserAccount& current);
	void displayAccount();
	void checkIn(MetroMate metro, UserAccount user, tm date);
};

//class DateTime {
//public:
//
//	tm current_date();
//	bool is_valid_date(tm date);
//
//
//	//s
//	tm dateInput();
//	system_clock::time_point timeInput();
//	static system_clock::time_point timeInputString(string timeStr);
//
//	long calculateDateDifference(tm date1, tm date2);
//	long calculateTimeDifferenceHours(system_clock::time_point time1, system_clock::time_point time2);
//	long calculateTimeDifferenceMinutes(system_clock::time_point time1, system_clock::time_point time2);
//	//void dateDay(string date);
//	string inputDateString(string inputDate);
//	static void outputTimePoint(system_clock::time_point timePoint);
//};