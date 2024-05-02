
#include "SubscriptionDetails.h"
#include "SubscriptionDetails.cpp"
#include"UserAccount.h"
//#include"UserAccount.cpp"
#include"TrainManagement.h"
//#include"TrainManagement.cpp"
//#include"DateTime.h"
#include<iostream>
#include <unordered_map>
#include<vector>
#include<deque>
#include <random>
#include<string>
#include<list>
#include<queue>
#include <fstream>
#include <sstream>
#include <stdexcept> 
//for time
#include <chrono>
#include <ctime>
using namespace std;
using namespace std::chrono;
//using namespace date;

//int main();

void Admin(bool& isAdmin, unordered_map<string, SubscriptionDetails>& subscription_plans, unordered_map<int, string>& subscriptions_names, vector<pair<vector<string>, double>>& zones, vector<pair<double, pair<int, int>>>& stages);
void User(bool isAdmin, UserAccount user, unordered_map<string, SubscriptionDetails>& subscription_plans, unordered_map<int, string>& subscriptions_names, vector<pair<vector<string>, double>>& zones);
void SetZones(vector<pair<vector<string>, double>>& zones);
void manageStages(vector<pair<double, pair<int, int>>>& stages,int choice);
//subscription file
vector<string> split(const string& str, char delimiter);
void writeToSubscriptionFile(const unordered_map<string, SubscriptionDetails>& data, const string& filename);
unordered_map<string, SubscriptionDetails> readFromSubscriptionFile(const string& filename, unordered_map<int, string>& subscriptions_names);

//unordered_map < system_clock::time_point, deque<Train>>& stationSchedule;
//Station station;
Line lines;
deque<Train> trains;

int main() {

	unordered_map<string, SubscriptionDetails> subscription_plans;//name and details
	unordered_map<int, string> subscriptions_names;//to have id and name only
	unordered_map<string, UserAccount> users;
	
	string SubscriptionFileName = "subscriptions.csv";
	subscription_plans = readFromSubscriptionFile(SubscriptionFileName, subscriptions_names);
	
	vector<pair<vector<string>, double>>zones;//zone[1][station1]
	vector<pair<double, pair<int, int>>> stages; // <price , <min_stations,max_stations>> for 4 stages

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
				user.PurchaceSubscription(user, subscription_plans, subscriptions_names, zones);
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
			Admin(isAdmin, subscription_plans, subscriptions_names,zones,stages);
			User(isAdmin, user, subscription_plans, subscriptions_names, zones);

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


void Admin(bool& isAdmin, unordered_map<string, SubscriptionDetails>& subscription_plans, unordered_map<int, string>& subscriptions_names, vector<pair<vector<string>, double>>& zones , vector<pair<double, pair<int, int>>>& stages)
{
	if (isAdmin) {
		//admin
		bool isAdminLoop = true;
		int answer;

		//for subscription
		string subscriptionName;
		SubscriptionDetails newSubscriptions;//we will need it when creating


		while (isAdminLoop) {
			cout << "enter number of operation you want to perform:\n 1. User Management \n 2. Metro Management \n 3. Subscription Plan Management \n 4. View All Ride Logs \n 5. Station Management \n 6. Fare Management  \n  any other number to exit" << endl;
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
				
				cin >> funcChoice;

				switch (funcChoice)
				{
				case 1:
					//create
					newSubscriptions.Create(zones,stages);

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
				cout << "press 1. to manage zones 2. to manage stages";
				int choice;
				cin >> choice;
				switch (choice)
				{
				case 1:
					SetZones(zones);
					break;
				case 2:
					manageStages(stages, choice);
					break;
				default:
					break;
				}
				
				break;
			default:
				isAdminLoop = false;
				break;
			}

		}


	}
}

void User(bool isAdmin, UserAccount user, unordered_map<string, SubscriptionDetails>& subscription_plans, unordered_map<int, string>& subscriptions_names, vector<pair<vector<string>, double>>& zones)
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
			int index = 1;//looping in path
			list<queue <pair< station, int>>> availablePaths;
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
				//ubgrade
				user.PurchaceSubscription(user, subscription_plans, subscriptions_names, zones);
				break;

			default:
				isUserLoop = false;
				break;
			}
		}



	}
}

void SetZones(vector<pair<vector<string>, double>>& zones)
{
	while (true) {
		unsigned int zoneNum;
		vector<string> targetZone;
		int choice;
		cout << "press 1. if you want to add zone \n 2. edit zone\n";
		cin >> choice;
		if (choice == 1){
			//add zone
			double price;
			while (true) {
				cout << "enter station name in zone"<< zones.size()+1<<" \n press 0 if you want to exit (no more stations)  ";
					string stationName;
					cin >> stationName;
					for (unsigned int i = 0; i < zones.size(); i++) {
						for (unsigned int j = 0; j < zones[i].first.size(); j++) {
							if (zones[i].first[j] == stationName) {
								cout << "station is already in another zone";
								continue;
							}
						}
					}
					cout << "enter zone price in zone" << zones.size() + 1<<endl;
					cin >> price;
					if (stationName == "0")
						break;

					targetZone.push_back(stationName);
			}
			if(!targetZone.empty())
				zones.push_back(make_pair(targetZone,price));
		}
		else if (choice == 2) {
			//edit zone
			bool validZone = false;
			while (true) {
				cout << "enter number of zone you want to edit \n press 0 if you want to exit" << endl;
				cin >> zoneNum;
				if (zoneNum == 0) {
					//chosed to exit
					validZone = false;
					break;
				}


				if (zoneNum > 0 && zoneNum < zones.size() + 1) {
					validZone = true;
					targetZone = zones[zoneNum - 1].first;//zone 1 as zones[0]
					break;
				}
				else {
					cout << "not valid zone num \n";
					validZone = false;
				}

			}

			while (validZone) {
				cout << "press \n 1. to delete that zone \n2. delete station in that zone \n3. add station in that zone\n4. change that zone price";
				cin >> choice;
				if (choice == 1) {
					//delete zone
					vector<pair<vector<string>, double>> ::iterator deletedZone;
					deletedZone = zones.begin();
					//zones.erase(zoneNum - 1);
					while (*deletedZone != zones[zoneNum - 1]) {
						deletedZone++;
					}
					zones.erase(deletedZone);
				}
				else if (choice == 2) {
					//delete station
					for (unsigned int i = 0; i < targetZone.size(); i++) {
						cout << "station index " << i + 1 << " : " << targetZone[i];
					}
					cout << "enter station index you want to delete \n press 0 if you want to exit (no more stations)  ";
					unsigned int stationIndex;
					cin >> stationIndex;
					if (stationIndex == 0)
						break;

					if (stationIndex > 0 && stationIndex < targetZone.size() + 1) {
						vector<string> ::iterator it;
						it = targetZone.begin();
						//zones[zoneNum].erase(stationIndex - 1);
						while (*it != targetZone[stationIndex - 1]) {
							it++;
						}
						zones[zoneNum-1].first.erase(it);

					}
				}
				else if (choice == 3) {
					//add station
					while (true) {
						cout << "enter station name in zone" << zoneNum << " \n press 0 if you want to exit (no more stations)  ";
						string stationName;
						cin >> stationName;
						for (unsigned int i = 0; i < zones.size(); i++) {
							for (unsigned int j = 0; j < zones[i].first.size(); j++) {
								if (zones[i].first[j] == stationName) {
									cout << "station is already in another zone";
									continue;
								}
							}
						}
						if (stationName == "0")
							break;

						zones[zoneNum-1].first.push_back(stationName);
					}
				}
				else if (choice == 4) {
					//edit zone price
					double price;
					while (true) {
						cout << "enter zone new price" << zoneNum << " \n press 0 if you want to exit";
						cin >> price;
						if (price == 0)
							break;

						zones[zoneNum - 1].second = price;
					}
				}
				else {
					break;
				}
				
			}
		}
		else {
			break;
		}
		
		
	}
}
void manageStages(vector<pair<double, pair<int, int>>>& stages, int choice)
{
	cout << "1. if you want to add stage \n2. if you want to edit stage\n any thing to exit";
	cin >> choice;
	pair<double, pair<int, int>> tmpStage;
	if (choice == 1) {
		cout << "you will add details of stage " << stages.size() + 1 << " : \n enter its price : \n";
		cin >> tmpStage.first;
		cout << "enter its min stations : \n";
		cin >> tmpStage.second.first;
		cout << "enter its max stations : \n";
		cin >> tmpStage.second.second;
		stages.push_back(tmpStage);
	}
	else if (choice == 2) {
		for (unsigned int i = 0; i < stages.size(); i++) {
			cout << "stage " << i + 1 << " : price = " << stages[i].first << ", min stations : " << stages[i].second.first << ", max stations : " << stages[i].second.second << endl;
		}
		cout << "enter stage number : ";
		int stageNum;
		cin >> stageNum;

		cout << "1. if you want to change price \n2. min stations\n 3. max stations";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "enter new price\n";
			cin >> stages[stageNum - 1].first;
			break;
		case 2:
			cout << "enter new min stations\n";
			cin >> stages[stageNum - 1].second.first;
			break;
		case 3:
			cout << "enter new max stations\n";
			cin >> stages[stageNum - 1].second.first;
			break;
		default:
			break;
		}
	}
}
//subscription file
void writeToSubscriptionFile(const unordered_map<string, SubscriptionDetails>& data, const string& filename) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		// Handle error opening file
		cout << "not open";
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
		cout << "nofile"; perror(("Error opening file: " + filename).c_str());
	}

	unordered_map<string, SubscriptionDetails> data;
	string line;
	int lineNum=1;
	if (file.good()) {
		while (getline(file, line)) {
			stringstream ss(line);
			string key;
			string attributeStr; // Stringall comma-separated attributes

			if (lineNum == 1) {

				if (getline(ss, key, ',') && getline(ss, attributeStr)) {
					vector<string> attributes = split(attributeStr, ',');


					// Check for minimum number of attributes (assuming range)
					if (attributes.size() < 5) {
						std::cerr << "Error: Invalid line format (too few attributes) in \"" << filename << "\"\n";
						continue;
					}

					// Extract and convert attributes to appropriate types
					try {
						SubscriptionDetails details;
						details.price = stod(attributes[0]);
						details.valid_duration = stoi(attributes[1]);
						details.cashAmount = (attributes.size() >= 3) ? stoi(attributes[2]) : 0; // Handle optional cashAmount
						details.name = attributes[attributes.size() - 2];
						details.numberOfTrips = stoi(attributes[attributes.size() - 1]);// Assuming numberOfTrips is last


						// Add the object to the hash table
						data[key] = details;

						subscriptions_names.insert(make_pair(data.size(), details.name));
					}
					catch (const invalid_argument& e) {
						cerr << "Error: Non-numeric value in \"" << filename << "\"\n";
						continue;
					}
				}
			}
			else if (lineNum == 2) {
				
				if (getline(ss, attributeStr)) {
					vector<string> attributes = split(attributeStr, ',');

					// Check for minimum number of attributes (assuming range)
					if (attributes.size() < 3) {
						data[key].availableStages.push_back(make_pair(0, make_pair(0, 0)));
						//continue;
					}

					// Extract and convert attributes to appropriate types
					try {
						if (attributes.size() >= 3) {
							for (unsigned int i = 0; i < attributes.size() / 3; i++) {

								pair<double, pair<int, int>> tmp;
								for (unsigned int i = 0; i < attributes.size() / 3; i++) {
									//because availableStages has 3 attributes
									tmp.first = stod(attributes[(i * 3)]);// 0 _ _    3 _ _     6 _ _
									tmp.second.first = stoi(attributes[(i * 3) + 1]);// _ 1 _    _ 4 _   _ 7 _
									tmp.second.second = stoi(attributes[(i * 3) + 2]);// _ _ 2    _ _ 5   _ _ 8
									data[key].availableStages.push_back(tmp);
								}
							}
						}
						
					}
					catch (const invalid_argument& e) {
						cerr << "Error: Non-numeric value in \"" << filename << "\"\n";
						continue;
					}
				}
			}
			else if (lineNum == 3) {
				string v;
				string num;
			    while (getline(ss, v, '+') && getline(ss, num,'+')) {
					vector<string> firstVector = split(v, ',');
					//vector<string> attributes = split(attributeStr, ',');
					


					// Check for minimum number of attributes (assuming range)
					//1 for num
					if (firstVector.size()+1 < 2) {
						std::cerr << "Error: Invalid line format (too few attributes) in \"" << filename << "\"\n";
						continue;
					}

					// Extract and convert attributes to appropriate types
					try {
						data[key].availableZones.push_back(make_pair(firstVector, stod(num)));
					}
					catch (const invalid_argument& e) {
						cerr << "Error: Non-numeric value in \"" << filename << "\"\n";
						continue;
					}
				}
			}
			else if (lineNum == 4) {
				
				if (getline(ss,attributeStr)) {
					vector<string> attributes = split(attributeStr, ',');
					//vector<string> attributes = split(attributeStr, ',');



					// Check for minimum number of attributes (assuming range)
					if (attributes.size() < 3) {
						std::cerr << "Error: Invalid line format (too few attributes) in \"" << filename << "\"\n";
						continue;
					}

					// Extract and convert attributes to appropriate types
					try {
						data[key].chosenStage.first = stod(attributes[0]);
						data[key].chosenStage.second.first = stoi(attributes[1]);
						data[key].chosenStage.second.first = stoi(attributes[2]);
					}
					catch (const invalid_argument& e) {
						cerr << "Error: Non-numeric value in \"" << filename << "\"\n";
						continue;
					}
				}
			}
			else if (lineNum == 5) {
				string classStationString;
				string num;
				while (getline(ss, classStationString, '+') && getline(ss, num, '+')) {
					vector<string> classStation = split(classStationString, ',');
					//vector<string> attributes = split(attributeStr, ',');



					// Check for minimum number of attributes (assuming range)
					/*if (attributes.size() < 3) {
						std::cerr << "Error: Invalid line format (too few attributes) in \"" << filename << "\"\n";
						continue;
					}*/
					pair< station, int> tmp;
					// Extract and convert attributes to appropriate types
					try {
						tmp.first.name = classStation[0];
						tmp.first.lineNumber = stoi(classStation[1]);
						tmp.second = stoi(num);
						data[key].chosenPath.push(tmp);
					}
					catch (const invalid_argument& e) {
						cerr << "Error: Non-numeric value in \"" << filename << "\"\n";
						continue;
					}
				}
			}


			lineNum++;
			if (lineNum % 6 == 0) {
				lineNum = 1;
			}
		}
	
	

	}
	
	return data;
}

//
//int main() {
//	Train t;
//	trains.push_back(t);
//	cout << "hi ? ";
//	 trains[0].displayTrainInfo();
//}