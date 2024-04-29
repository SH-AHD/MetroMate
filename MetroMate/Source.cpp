
#include "SubscriptionDetails.h"
#include "SubscriptionDetails.cpp"
#include"UserAccount.h"
#include"UserAccount.cpp"
//#include"DateTime.h"
#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>
#include <fstream>
#include <sstream>
#include <stdexcept> 
//for time
#include <chrono>
#include <ctime>
using namespace std;


void Admin(bool& isAdmin, unordered_map<string, SubscriptionDetails>& subscription_plans, unordered_map<int, string>& subscriptions_names, vector<vector<string>>& zones);
void User(bool isAdmin, UserAccount user);
void SetZones(vector<vector<string>>& zones);
//subscription file
vector<string> split(const string& str, char delimiter);
void writeToSubscriptionFile(const unordered_map<string, SubscriptionDetails>& data, const string& filename);
unordered_map<string, SubscriptionDetails> readFromSubscriptionFile(const string& filename, unordered_map<int, string>& subscriptions_names);



int main() {
	unordered_map<string, SubscriptionDetails> subscription_plans;//name and details
	unordered_map<int, string> subscriptions_names;//to have id and name only
	unordered_map<string, UserAccount> users;
	
	string SubscriptionFileName = "subscriptions.csv";
	subscription_plans = readFromSubscriptionFile(SubscriptionFileName, subscriptions_names);
	
	vector<vector<string>>zones;

	bool outerLoop = true;
	while (outerLoop) {
		cout << "if you want to register press 1 \n if you want to login press 2  \n press any thing to logout";
		int firstChoice;
		cin >> firstChoice;

		bool registerSucess = false;
		
		//variables needed for register:
		string userName;
		//for login:
		UserAccount user;
		string email="f", password;
		bool isAdmin = true;
		switch (firstChoice) {
		case 1:

			
			cout << "please enter your email , if you want to exit press 0" << endl;
			cin >> user.Email;
			if (user.Email != "0") {
				registerSucess = user.Register(users, user);
				cout << "please enter your password " << endl;
				cin >> user.Password;
				if (user.Email == "Admin@gmail.com")
					isAdmin = true;
				else
					isAdmin = false;
			}
			else {
				break;
			}

			if (!isAdmin) {
				//have to choose in regster only
				user.PurchaceSubscription(user, subscription_plans, subscriptions_names);
			}
			
		case 2:
			
			if (!registerSucess) {
				do {
					cout << "if you want to exit press 0\nenter your email: " << endl;
					cin >> email;
					cout << "enter your password: " << endl;
					cin >> password;
				} while (!user.logIn(email, password, users) && email != "0");

				if (user.Email == "Admin@gmail.com")
					isAdmin = true;
				else
					isAdmin = false;

				registerSucess = false;

				if (email == "0")
					break;
			}
			
			
			
			//logic of program
			//logined as (admin) or ( user with "email" above)
			Admin(isAdmin, subscription_plans, subscriptions_names,zones);
			User(isAdmin, user);


			//outerLoop = false;
			break;
		default:
			outerLoop = false;
			break;
		}


	}

	ifstream file(SubscriptionFileName);
	file.clear();
	writeToSubscriptionFile(subscription_plans, SubscriptionFileName);
	
	return 0;
}


void Admin(bool& isAdmin, unordered_map<string, SubscriptionDetails>& subscription_plans, unordered_map<int, string>& subscriptions_names, vector<vector<string>>& zones)
{
	if (isAdmin) {
		//admin
		bool isAdminLoop = true;
		int answer;

		//for subscription
		string subscriptionName;
		SubscriptionDetails newSubscriptions;//we will need it when creating


		while (isAdminLoop) {
			cout << "enter number of operation you want to perform:\n 1. User Management \n 2. Metro Management \n 3. Subscription Plan Management \n 4. View All Ride Logs \n 5. Station Management \n 6. Fare Management \n 7. Set Zones \n  any other number to exit" << endl;
			cin >> answer;
			switch (answer)
			{
			case 1:
				break;
			case 2:
				break;
			case 3:
				int funcChoice;
				cout << "enter the number of the function you want to perform\n 1- create subscription \n 2- modify subscription \n 3- remove subscription \n    press any key to go back";
				// 1-create
				// 2-modify
				// 3-remove
				cin >> funcChoice;


				switch (funcChoice)
				{
				case 1:
					//create
					newSubscriptions.Create();

					//adding it to hash table
					subscription_plans.insert(make_pair(newSubscriptions.name, newSubscriptions));
					subscriptions_names.insert(make_pair(subscription_plans.size(), newSubscriptions.name));//1-student,2-public...
					break;

				case 2:
					//modify subscription
					newSubscriptions.Modify(subscription_plans, subscriptions_names);

					break;
				case 3:
					int key;
					//remove subscription 
					for (const auto& pair : subscriptions_names) {
						cout << "Key: " << pair.first << ", name: " << pair.second << endl;
					}
					cout << "choose subscription key" << endl;
					cin >> key;
					subscriptionName = subscriptions_names[key];
					subscription_plans.erase(subscriptionName);
					break;
				default:
					break;
				}
				
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				SetZones(zones);
				break;
			default:
				isAdminLoop = false;
				break;
			}

		}


	}
}

void User(bool isAdmin, UserAccount user)
{
	if (!isAdmin) {
		DateTime Date;
		//checking subscription time
		if (Date.current_date().tm_mon - user.startDate.tm_mon >= user.chosenSubscription.valid_duration && Date.is_valid_date(user.startDate)) {
			cout << "please renew your subscription: \n enter y if you want to renew \n enter n if you want to exit from subscription" << endl;
			char answer;
			cin >> answer;
			if (answer == 'y') {
				user.startDate = Date.current_date();
				user.availableTrips = user.chosenSubscription.numberOfTrips;
			}
			else if (answer == 'n') {
				SubscriptionDetails emptySubscription;
				user.chosenSubscription = emptySubscription;
			}
		}


		//manage subscription
		//choose what action you want to perform
		bool isUserLoop = true;
		while (isUserLoop) {
			int manageChoice;
			cout << "if you want to: \n view active subscription type 1 \n renew subscription type 2  \n upgrade subscription type 3";
			cin >> manageChoice;
			string firstDestination;
			string targetDestination;
			switch (manageChoice)
			{
			case 1:
				user.chosenSubscription.DisplayData(user.chosenSubscription.name);
				break;
			case 2:
				//renew
				user.availableTrips = user.chosenSubscription.numberOfTrips;
				user.startDate = Date.current_date();

				break;
			case 3:
				//make him choose a new stage

				// initial and target destination??
				cout << "enter your first and target destination";
				cin >> firstDestination >> targetDestination;

				//cout all paths
				//"calculating the shortest path...."
				// Please select the path of your choosing (knowing that --- is the shortest path to your destination)
				int chosenPath;
				cout << "choose your path";
				cin >> chosenPath;

				//chosenPath= what he chosed

				//calculate price according to the path
				user.chosenSubscription.calcPrice(chosenPath);
				user.availableTrips = user.chosenSubscription.numberOfTrips;

				break;

			default:
				isUserLoop = false;
				break;
			}
		}



	}
}

void SetZones(vector<vector<string>>& zones)
{
	while (true) {
		int zoneNum;
		vector<string> targetZone;
		cout << "enter number of zone you want to put its stations \n press 0 if you want to exit" << endl;
		cin >> zoneNum;
		if (zoneNum == 0)
			break;

		targetZone = zones[zoneNum - 1];//zone 1 as zones[0]
		while (true) {
			cout << "enter station name in that zone \n press 0 if you want to exit (no more stations)  ";
			string stationName;
			cin >> stationName;
			if (stationName == "0")
				break;

			targetZone.push_back(stationName);
		}
		zones.push_back(targetZone);
	}
}
//subscription file
void writeToSubscriptionFile(const unordered_map<string, SubscriptionDetails>& data, const string& filename) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		// Handle error opening file
		return;
	}

	for (const auto& element : data) {
		std::string key = element.first;
		const SubscriptionDetails& value = element.second;
		file << key << "," << value.toString() << std::endl;
	}
	file.close();
}
vector<string> split(const string& str, char delimiter) {
	vector<string> tokens;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}
unordered_map<string, SubscriptionDetails> readFromSubscriptionFile(const string& filename, unordered_map<int, string>& subscriptions_names) {
	ifstream file(filename);
	if (!file.is_open()) {
		//throw std::runtime_error("Error opening file: " + filename);
		//cout << "nofile";
	}

	unordered_map<string, SubscriptionDetails> data;
	string line;
	if (file.good()) {
		while (getline(file, line)) {
			stringstream ss(line);
			string key;
			string attributeStr; // String containing all comma-separated attributes

			if (getline(ss, key, ',') && getline(ss, attributeStr)) {
				vector<string> attributes = split(attributeStr, ',');

				// Check for minimum number of attributes (assuming range)
				if (attributes.size() < 6) {
					std::cerr << "Error: Invalid line format (too few attributes) in \"" << filename << "\"\n";
					// Optionally, log the specific line content for debugging
					// std::cerr << "  Line content: " << line << std::endl;
					continue;
				}

				// Extract and convert attributes to appropriate types
				try {
					double price = stod(attributes[0]);
					int valid_duration = stoi(attributes[1]);

					int cashAmount = (attributes.size() >= 3) ? stoi(attributes[2]) : 0; // Handle optional cashAmount

					int stagesPrices[4];
					// Loop through all attributes for stage prices (assuming 4)
					for (int i = 0; i < 4; ++i) {
						if (i < attributes.size()) {
							stagesPrices[i] = stoi(attributes[i + 3]);
						}
						else {
							// Handle missing stage prices (set default or throw exception)
							stagesPrices[i] = 0; // Or throw an exception if critical
						}
					}

					int stage = (attributes.size() >= 8) ? stoi(attributes[7]) : 0; // Handle optional stage

					int path = stoi(attributes[attributes.size() - 3]); // Assuming path is before last
					string name = attributes[attributes.size() - 2]; // Assuming name is last
					int numberOfTrips = stoi(attributes[attributes.size() - 1]);
					// Create a SubscriptionDetails object from parsed data
					SubscriptionDetails details(price, valid_duration, cashAmount, stagesPrices, stage, name, path, numberOfTrips);
					// Add the object to the map
					data[key] = details;

					subscriptions_names.insert(make_pair(data.size(), details.name));
				}
				catch (const invalid_argument& e) {
					cerr << "Error: Non-numeric value in \"" << filename << "\"\n";
					continue;
				}
			}
		}
	}
	return data;
}