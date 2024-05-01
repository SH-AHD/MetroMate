#pragma once
#include<string>
#include<unordered_map>
#include"station.h"
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
	//int stagesPrices[4];//
	int numberOfTrips = 0;
	vector<pair<double, pair<int, int>>> availableStages;//<price,<min stations,max stations>>
	vector<pair<vector<string>, double>> availableZones;//<<stations names>,zone price>
	//vector<int> zonesPrices;//

	pair<double, pair<int, int>> chosenStage;//same as availableStages but one stage"no vector"
	//int stage = 0;
	//int path = 0;//to be in the data of user
	queue <pair< station, int>> chosenPath;
	

public:
	//SubscriptionDetails(double price, int valid_duration, int cashAmount = 0,
	//	const int* stagesPrices = nullptr, int stage = 0, string name = "", int path = 0, int numberOfTrips = 0)
	//	: price(price), valid_duration(valid_duration), cashAmount(cashAmount), stage(stage), name(name), path(path), numberOfTrips(numberOfTrips) {
	//	// Copy values from the array pointed to by stagesPrices
	//	for (int i = 0; i < 4; ++i) {
	//		this->stagesPrices[i] = stagesPrices[i];
	//	}
	//}

	/*SubscriptionDetails(const string& name, double price, int valid_duration,
		const vector<pair<double, pair<int, int>>>& availableStages,
		const vector<pair<vector<string>, double>>& availableZones, pair<double, pair<int, int>> chosenStage, queue <pair< station, int>> chosenPath, int numberOfTrips) :{
		name(name),
		price(price),
		valid_duration(valid_duration),
		availableStages(availableStages),
		availableZones(availableZones),
		chosenStage(make_pair(chosenStage.first, make_pair(chosenStage.second.first, chosenStage.second.second))),
			chosenPath(chosenPath),
			numberOfTrips(numberOfTrips)
		}*/


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

	
	string toString() const;
};

