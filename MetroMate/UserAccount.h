#pragma once
#include "SubscriptionDetails.h"
#include<iostream>
#include<unordered_map>
#include <ctype.h>//lower case
#include<string>
//for time
#include <chrono>
#include <ctime>
//s
//#include "date/date.h"
#include <sstream>


using namespace std;
using namespace std::chrono;

//s
using namespace std::chrono;
//using namespace date;

class UserAccount
{
public:
	string Email;
	string Password;
	string Name;
	string Address;
	int Phone;
	tm startDate;

	SubscriptionDetails chosenSubscription;
	int availableTrips;

	void PurchaceSubscription(UserAccount& user, unordered_map<std::string, SubscriptionDetails> subscription_plans, unordered_map<int, string> subscriptions_names , vector<pair<vector<string>, double>> zones);

	UserAccount() {
		//dont delete it
	}
	UserAccount(string email, string pass);
	UserAccount(string Email, string Password, string Name, string Address, int Phone);
	bool Register(unordered_map<string, UserAccount>& users, UserAccount user);
	bool VailEmail(string email);
	bool logIn(string email, string password, unordered_map<string, UserAccount>& user);
};

class DateTime {
public:

	tm current_date();
	bool is_valid_date(tm date);


	//s
	tm dateInput();
	system_clock::time_point timeInput();
	long calculateDateDifference(tm date1, tm date2);
	long calculateTimeDifferenceHours(system_clock::time_point time1, system_clock::time_point time2);
	long calculateTimeDifferenceMinutes(system_clock::time_point time1, system_clock::time_point time2);
	void dateDay(string date);
	string inputDateString(string inputDate);
};

