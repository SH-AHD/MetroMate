#pragma once
#include<string>
#include<unordered_map>
//#include "User.h"
using namespace std;
class SubscriptionDetails
{
public:
	string name = "";
	double price = 0;
	int valid_duration = 0;/*
	string firstDestination;
	string targetDestination;*/
	int cashAmount = 0;//for cash wallet only(multiply of 10)
	int stagesPrices[4];
	vector<int> zonesPrices;
	int stage = 0;
	int path = 0;//to be in the data of user
	int numberOfTrips = 0;

public:
	SubscriptionDetails(double price, int valid_duration, int cashAmount = 0,
		const int* stagesPrices = nullptr, int stage = 0, string name = "", int path = 0, int numberOfTrips = 0)
		: price(price), valid_duration(valid_duration), cashAmount(cashAmount), stage(stage), name(name), path(path), numberOfTrips(numberOfTrips) {
		// Copy values from the array pointed to by stagesPrices
		for (int i = 0; i < 4; ++i) {
			this->stagesPrices[i] = stagesPrices[i];
		}
	}
	SubscriptionDetails() {
		//just empty constructor
		//don't delete it
	}
	void DisplayData(string name);
	//void PurchaceSunscription(User user, unordered_map<std::string, SubscriptionDetails> subscription_plans, unordered_map<int, string> subscriptions_names);
	void calcStage(int chosenPath);
	double calcPrice(int chosenPath);
	void displayFixedData();
	void Create();
	void Modify(unordered_map<string, SubscriptionDetails>& subscription_plans, unordered_map<int, string>& subscriptions_names);
	void remove(unordered_map<string, SubscriptionDetails>& subscription_plans, unordered_map<int, string>& subscriptions_names);

	
	string toString() const;
};

