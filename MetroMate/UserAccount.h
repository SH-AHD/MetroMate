#pragma once
#include "SubscriptionDetails.h"
#include<iostream>
#include<unordered_map>
#include <ctype.h>//lower case
#include<string>
//for time
#include <chrono>
#include <ctime>
using namespace std;

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

};

