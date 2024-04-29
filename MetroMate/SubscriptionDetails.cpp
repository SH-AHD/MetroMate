#include "SubscriptionDetails.h"
#include "UserAccount.h"
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
		cout << "your path" << path << endl;
	}
}
void SubscriptionDetails::calcStage(int chosenPath)
{
	stage = 4;
	path = chosenPath;
}
double SubscriptionDetails::calcPrice(int chosenPath) {
	calcStage(chosenPath);
	switch (stage)
	{
	case 1: price = stagesPrices[0];
		return stagesPrices[0];
		//stagesPrices[i] already defined (for each stage) by admin in "subscription_plans hash table"
		break;
	case 2: price = stagesPrices[1];
		return stagesPrices[1];
		break;
	case 3: price = stagesPrices[2];
		return stagesPrices[2];
		break;
	case 4: price = stagesPrices[3];
		return stagesPrices[3];
		break;
	}
}
void SubscriptionDetails::displayFixedData() {
	cout << "valid duration:  " << endl << valid_duration << endl;
	for (int i = 0; i < 4; i++) {
		cout << "price for stage " << i + 1 << " : " << stagesPrices[i] << endl;
	}
}

void SubscriptionDetails::Create()
{
	cout << "enter subscription name";
	cin >> name;
	if (name != "Cash_wallet") {
		cout << "enter subscription valid duration" << endl;
		cin >> valid_duration;
		
		cout << "enter the available number of trips " << endl;
		cin >> numberOfTrips;
	}
	for (int i = 0; i < zonesPrices.size(); i++) {
		cout << "enter subscription price for zone " << i + 1 << endl;
		cin >> zonesPrices[i];
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
		//display chosen subscribtion's 
		subscription_plans[subscriptionName].displayFixedData();
		//choose 1-modify subscription's fare
		//2- modify subscription's valid duration
		//3- modify number of trips available
		int modChoice;
		cin >> modChoice;
		if (modChoice == 1)
		{
			for (int i = 0; i < 4; i++) {
				cout << "enter subscription's new fare of stage" << i + 1 << endl;
				cin >> subscription_plans[subscriptionName].stagesPrices[i];
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





string SubscriptionDetails::toString() const {
	string ss;
	// You can modify the format string to control output appearance
	ss = to_string(price) + "," + to_string(valid_duration) + "," + to_string(cashAmount) + ",";
	for (int i = 0; i < 4; i++) {
		ss += to_string(stagesPrices[i]) + ",";
	}
	ss += to_string(stage) + "," + to_string(path) + "," + name + "," + to_string(numberOfTrips);
	return ss;
}
