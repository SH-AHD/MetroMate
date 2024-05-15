#pragma once
#include<string>
#include<unordered_map>
#include"MetroMate.h"
#include<queue>
//#include "User.h"
using namespace std;
class SubscriptionDetails
{
public:
	string name = "";
	double price = 0;
	int valid_duration = 0;
	int cashAmount = 0;//for cash wallet only(multiply of 10)
	int numberOfTrips = 0;
	int chosenZoneNum=0;//chosen zone number(new)
	bool isStageChoice = true; //his subscription by zone or stage(new)


	vector<pair<double, pair<int, int>>> availableStages;//<price,<min stations,max stations>>
	vector<pair<vector<string>, double>> availableZones;//<<stations names>,zone price>
	
	pair<double, pair<int, int>> chosenStage;//same as availableStages but one stage"no vector"
	queue <pair< station, int>> chosenPath;
	

	SubscriptionDetails() {
		//just empty constructor
		//don't delete it
	}
	void DisplayData(string name);
	void calcStage(queue <pair< station, int>> chosenPath);
	double calcPrice(queue <pair< station, int>> chosenPath ,int zoneNum, bool isStage);
	void displayFixedData();
	void Create(vector<pair<vector<string>, double>> zones, vector<pair<double, pair<int, int>>> stages);
	void Modify(unordered_map<string, SubscriptionDetails>& subscription_plans, unordered_map<int, string>& subscriptions_names);
	void remove(unordered_map<string, SubscriptionDetails>& subscription_plans, unordered_map<int, string>& subscriptions_names);
	void putMoneyInWallet(UserAccount user);
	void cashWalletTicket(UserAccount user);

	
	string toString() const;
};

