#pragma once

#include "MetroMate.h"
class SubscriptionDetails;
class station;
class DateTime;
class Admin
{
public:
	Admin();
	void HomePage(bool& isAdmin, unordered_map<string, SubscriptionDetails>& subscription_plans, unordered_map<int, string>& subscriptions_names, vector<pair<vector<string>, double>>& zones,
		vector<pair<double, pair<int, int>>>& stages, unordered_map<string, station> stationsList, DateTime date, MetroMate metro, unordered_map<string, UserAccount> users, Train train, Schedule schedule);
	void SetZones(vector<pair<vector<string>, double>>& zones);
	void manageStages(vector<pair<double, pair<int, int>>>& stages, int choice);
	void ModifyUsers(bool& isAdmin, unordered_map<string, UserAccount>& users);
	void stationManagement(MetroMate metro);
};