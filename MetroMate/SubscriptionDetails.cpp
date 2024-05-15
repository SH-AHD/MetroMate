#include "SubscriptionDetails.h"
#include "UserAccount.h"
//#include"station.h"
#include<queue>

#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>
#include <fstream>
#include <ctype.h>//lower case
//for time
#include <chrono>
#include <ctime>
using namespace std;

void SubscriptionDetails::DisplayData(string name)
{
	cout << "your subscribtion name is: " << name << endl;
	if (name == "Cash_wallet") {
		cout << "your wallet money is: " << cashAmount << endl;
	}
	else {
		cout << "price: " << price << endl;
		cout << "valid duration: " << valid_duration << endl;
		//scout << "your path" << path << endl;
	}
}
void SubscriptionDetails::calcStage(queue <pair< station, int>> chosenPath)
{
	int pathSize = chosenPath.size();
	for (unsigned int i = 0; i < availableStages.size(); i++) {
		if (pathSize > availableStages[i].second.first && pathSize < availableStages[i].second.first) {
			chosenStage = availableStages[i];
			break;
		}
	}
}
double SubscriptionDetails::calcPrice(queue <pair< station, int>> chosenPath,int zoneNum, bool isStage) {

	chosenZoneNum = zoneNum;//will need this two variables while calling the function in check in (in cash wallet ) i won't know what arguments to pass
	isStageChoice = isStage;//and they will be initialize in purchase (in register)

	if (isStage) {
		calcStage(chosenPath);
		price = chosenStage.first;//price
		return price;
	}
	else {
		price = availableZones[zoneNum-1].second;
		return price;
	}
	
}
void SubscriptionDetails::displayFixedData() {
	cout << "valid duration:  " << endl << valid_duration << endl;
	for (unsigned int i = 0; i < availableStages.size(); i++) {
		cout << "price for stage " << i + 1 << " : " << availableStages[i].first << endl;
	}
	for (unsigned int i = 0; i < availableZones.size(); i++) {
		cout << "price for zone " << i + 1 << " : " << availableZones[i].second << endl;
	}
}

void SubscriptionDetails::Create(vector<pair<vector<string>, double>> zones, vector<pair<double, pair<int, int>>> stages)
{
	cout << "enter subscription name";
	cin >> name;
	if (name != "Cash_wallet") {
		cout << "enter subscription valid duration" << endl;
		cin >> valid_duration;
		
		cout << "enter the available number of trips " << endl;
		cin >> numberOfTrips;

		availableZones = zones;//we will change price only
		for (unsigned int i = 0; i < zones.size(); i++) {
			cout << "enter subscription price for zone " << i + 1 << endl;
			cin >> availableZones[i].second;
		}

		availableStages = stages;//we will change price only not min and max stations
		for (unsigned int i = 0; i < stages.size(); i++) {
			cout << "enter subscription price for stage " << i + 1 << endl;
			cin >> availableStages[i].first;
		}


	}
	else {
		availableStages = stages;
		availableZones = zones;
	}
	
	
	

}

void SubscriptionDetails::Modify(unordered_map<string, SubscriptionDetails>& subscription_plans, unordered_map<int, string>& subscriptions_names)
{
	int key;
	string subscriptionName;
	if (subscription_plans.empty()) {
		cout << "no subscriptions avalibale";
	}
	else {

		cout << "choose subscription key:" << endl;
		for (const auto& pair : subscriptions_names) {
			cout << "Key: " << pair.first << ", name: " << pair.second << endl;
		}
		cin >> key;
		subscriptionName = subscriptions_names[key];

		//display chosen subscribtion's details
		subscription_plans[subscriptionName].displayFixedData();

		cout << "choose 1-modify subscription's fare \n 2- modify subscription's valid duration \n 3- modify number of trips available";
		int modChoice;
		cin >> modChoice;
		if (modChoice == 1)
		{
			cout << "1. subscription's new fare of stage \n3. subscription's new fare of zone";
			cin >> modChoice;
			switch (modChoice)
			{
			case 1:
				for (unsigned int i = 0; i < availableStages.size(); i++) {
					cout << "enter subscription's new fare of stage" << i + 1 << endl;
					cin >> subscription_plans[subscriptionName].availableStages[i].first;
				}
				break;
			case 2:
				for (unsigned int i = 0; i < availableZones.size(); i++) {
					cout << "enter subscription's new fare of zone" << i + 1 << endl;
					cin >> subscription_plans[subscriptionName].availableZones[i].second;
				}
				break;
			default:
				break;
			}

			for (int i = 0; i < 4; i++) {
				cout << "enter subscription's new fare of stage" << i + 1 << endl;
				cin >> subscription_plans[subscriptionName].availableStages[i].first;
			}

		}
		else if (modChoice == 2)
		{
			cout << "enter subscription's new vaild duration" << endl;
			cin >> subscription_plans[subscriptionName].valid_duration;
		}
		else if (modChoice == 3)
		{
			cout << "enter the available number of trips" << endl;
			cin >> subscription_plans[subscriptionName].numberOfTrips;
		}
	}
}

void SubscriptionDetails::remove(unordered_map<string, SubscriptionDetails>& subscription_plans, unordered_map<int, string>& subscriptions_names)
{
	int key;
	string subscriptionName;
	//remove subscription 
	for (const auto& pair : subscriptions_names) {
		cout << "Key: " << pair.first << ", name: " << pair.second << endl;
	}
	cout << "choose subscription key" << endl;
	cin >> key;
	subscriptionName = subscriptions_names[key];
	subscription_plans.erase(subscriptionName);
}

void SubscriptionDetails::putMoneyInWallet(UserAccount user)
{

	if (name == "Cash_wallet") {
		cout << "your cash amount is :" << user.chosenSubscription.cashAmount;
		int cashMoney;
		do {
			cout << "please put money in wallet (multiple of 10)\n" << endl;
			cin >> cashMoney;
		} while (cashMoney % 10 != 0);
		user.chosenSubscription.cashAmount += cashMoney;
	}
	else {
		cout << "you didn't subscripe in cash wallet \n";
	}
	
}

void SubscriptionDetails::cashWalletTicket(UserAccount user)
{
	while (true) {
		int userCashAmount = user.chosenSubscription.cashAmount;
		double pathPrice = user.chosenSubscription.price;
		if (userCashAmount > pathPrice && userCashAmount != 0) {
			user.chosenSubscription.cashAmount -= (int)pathPrice;
			user.chosenSubscription.price = 0;//in the end to restart path price(becaues it is cash wallet)
		}
		else {
			cout << "sorry there is no enough money in your wallet \n press 1 if you want to put money \n else press any number";
			int answer;
			cin >> answer;
			if (answer == 1) {
				user.chosenSubscription.putMoneyInWallet(user);
			}
			else {
				user.chosenSubscription.price = 0;
				return;
			}
		}
	}
}





string SubscriptionDetails::toString() const{
	string ss;
	// You can modify the format string to control output appearance
	ss = to_string(price) + "," + to_string(valid_duration) + "," + to_string(cashAmount) + ","+ name + "," + to_string(numberOfTrips)+"," + to_string(chosenZoneNum)+","+ to_string(isStageChoice);
	/*for (int i = 0; i < 4; i++) {
		ss += to_string(stagesPrices[i]) + ",";
	}*/
	
	ss += ","+ to_string(availableStages.size()) + ",";
	for (unsigned int i = 0; i < availableStages.size(); i++) {

		ss +=to_string(availableStages[i].first) + "," + to_string(availableStages[i].second.first) + "," + to_string(availableStages[i].second.second) + ",";
	}
	ss += to_string(availableZones.size())+",";
	for (unsigned int i = 0; i < availableZones.size(); i++) {
		ss += to_string(availableZones[i].first.size()) + ",";
		for (unsigned int j = 0; j < availableZones[i].first.size(); j++) {
			ss += availableZones[i].first[j] + ",";
			
		}
		ss += to_string(availableZones[i].second) + ",";
	}
	
	ss +=to_string(chosenStage.first) + "," + to_string(chosenStage.second.first) + "," + to_string(chosenStage.second.second) + ",";
	
	
	queue <pair< station, int>> tmp = chosenPath;
	if (!chosenPath.empty()) {
		ss += to_string(chosenPath.size()) + ",";
		while (!tmp.empty()) {
			ss += tmp.front().first.name + ",";
			ss += to_string(tmp.front().second) + ",";
			tmp.pop();
		}
	}
	
	cout << "write done";
	return ss;
}
