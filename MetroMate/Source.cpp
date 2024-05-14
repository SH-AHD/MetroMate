
#include "SubscriptionDetails.h"
#include "SubscriptionDetails.cpp"
#include"UserAccount.h"
#include"UserAccount.cpp"
#include"TrainManagement.h"
#include"TrainManagement.cpp"
#include"MetroMate.h"
#include"MetroMate.cpp"
#include"Admin.h"
#include"Admin.cpp"

#include <iostream>
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




void saveData(unordered_map<string, UserAccount>& users);
//void ModifyUsers(bool& isAdmine, unordered_map<string, UserAccount>&users);
//void Admin(bool& isAdmin, unordered_map<string, SubscriptionDetails>& subscription_plans,unordered_map<int, string>& subscriptions_names, vector<pair<vector<string>, double>>& zones,vector<pair<double, pair<int, int>>>& stages, vector<station> stationsList, DateTime date); 
void User(bool isAdmin, UserAccount user, unordered_map<string, SubscriptionDetails>& subscription_plans, unordered_map<int, string>& subscriptions_names, vector<pair<vector<string>, double>>& zones, unordered_map<string, UserAccount>users, MetroMate metro, Train train, Schedule schedule);
//void SetZones(vector<pair<vector<string>, double>>& zones);
//void manageStages(vector<pair<double, pair<int, int>>>& stages,int choice);
//subscription file
vector<string> split(const string& str, char delimiter);
void writeToSubscriptionFile(const unordered_map<string, SubscriptionDetails>& data, const string& filename);
unordered_map<string, SubscriptionDetails> readFromSubscriptionFile(const string& filename, unordered_map<int, string>& subscriptions_names, unordered_map<string, station>stationsList);
unordered_map<string, UserAccount> ReadData(unordered_map<string, UserAccount>& users);

//Line lines;
Train train;
Schedule schedule;
MetroMate metro;
deque<Train> trains;
unordered_map<string, UserAccount> users;
int main() {
	


	//temp data to metro graph
	metro.numberOfLines = 2;
	//entering data to graph manually
	//metro.noOfStationsInLine = { 3,3 };
	metro.noOfStationsInLine.push_back(3);
	metro.noOfStationsInLine.push_back(3);

	station A("a", 1);
	station b("b", 1);
	station c("c", 2);
	station d("d", 1);
	station e("e", 2);
	station f("f", 2);
	metro.MetroLines[1].push_back(A);
	metro.MetroLines[1].push_back(b);
	metro.MetroLines[2].push_back(c);
	metro.MetroLines[1].push_back(d);
	metro.MetroLines[2].push_back(e);
	metro.MetroLines[2].push_back(f);
	metro.Metromate["a"].push_back(make_pair(&b, 4));
	metro.Metromate["a"].push_back(make_pair(&c, 5));
	metro.Metromate["b"].push_back(make_pair(&A, 4));
	metro.Metromate["b"].push_back(make_pair(&c, 11));
	metro.Metromate["b"].push_back(make_pair(&e, 7));
	metro.Metromate["b"].push_back(make_pair(&d, 9));
	metro.Metromate["e"].push_back(make_pair(&c, 3));
	metro.Metromate["e"].push_back(make_pair(&b, 7));
	metro.Metromate["e"].push_back(make_pair(&d, 13));
	metro.Metromate["e"].push_back(make_pair(&f, 6));
	metro.Metromate["d"].push_back(make_pair(&b, 9));
	metro.Metromate["d"].push_back(make_pair(&e, 13));
	metro.Metromate["d"].push_back(make_pair(&f, 2));
	metro.Metromate["c"].push_back(make_pair(&A, 5));
	metro.Metromate["c"].push_back(make_pair(&b, 11));
	metro.Metromate["c"].push_back(make_pair(&e, 3));
	metro.Metromate["f"].push_back(make_pair(&d, 2));
	metro.Metromate["f"].push_back(make_pair(&e, 6));


	station tmpStation;

	unordered_map<string, SubscriptionDetails> subscription_plans;//name and details
	unordered_map<int, string> subscriptions_names;//to have id and name only
	string SubscriptionFileName = "subscriptions.csv";

	users = ReadData(users);

	Admin admin;


	vector<pair<vector<string>, double>>zones;//zone[1][station1]
	vector<pair<double, pair<int, int>>> stages; // <price , <min_stations,max_stations>> for 4 stages

	//vector<station> stationsList;
	unordered_map<string, station> stationsList;
	stationsList = tmpStation.readData();

	subscription_plans = readFromSubscriptionFile(SubscriptionFileName, subscriptions_names, stationsList);


	//stationslist = read station
	//read metro ,add station
	DateTime date;
	//variables needed for register:
	string name, email, address, password;
	int phone;
	//for login:
	bool isAdmin = false;
	UserAccount currentUser;

	bool outerLoop = true;
	while (outerLoop) {
		cout << "welcome to the metro system" << endl;
		cout << "---------------------------" << endl;
		cout << "chose what you want to do:" << endl;
		cout << "1.Rigester\n2.log in" << endl;
		int firstChoice;
		cin >> firstChoice;

		bool registerSucess = false;
		switch (firstChoice)
		{
		case 1:
		{

			cout << "Register" << endl;
			cout << "--------" << endl;
			cout << "Name:";
			cin >> name;
			cout << "Email:";
			cin >> email;
			cout << "Phone Number:";
			cin >> phone;
			cout << "Address:";
			cin >> address;
			cout << "Password:";
			cin >> password;
			UserAccount user(email, password, name, address, phone);
			user.Register(users, user);
			currentUser = user;
			currentUser.PurchaceSubscription(currentUser, subscription_plans, subscriptions_names, zones);
			currentUser.displayAccount();
			//	currentUser.updateInfo(currentUser);

			User(isAdmin, currentUser, subscription_plans, subscriptions_names, zones, users,metro,train,schedule);
			break;
		}
		case 2:
		{
			cout << "please enter the email and password of your account:\n";
			cout << "Email: ";
			cin >> email;
			cout << "Password: ";
			cin >> password;
			UserAccount userLog(email, password);
			if (userLog.logIn(isAdmin, currentUser, email, password, users))
			{
				if (isAdmin == true)
				{
					cout << "Login successful" << endl;
					admin.HomePage(isAdmin, subscription_plans, subscriptions_names, zones, stages, stationsList, date, metro, users,train,schedule);
				}
				else if (isAdmin == false)
				{
					cout << "Login successful" << endl;
					currentUser.displayAccount();
					currentUser = currentUser.updateInfo(currentUser.Email, users);
					currentUser.displayAccount();
					User(isAdmin, currentUser, subscription_plans, subscriptions_names, zones, users,metro,train,schedule);
				}
			}


			else
				cout << "Login failed" << endl;
			break;
		}

		default:
			outerLoop = false;
			break;
		}


	}
	tmpStation.writeData(stationsList);
	saveData(users);
	ifstream file(SubscriptionFileName);
	file.clear();
	writeToSubscriptionFile(subscription_plans, SubscriptionFileName);

	return 0;
}


void saveData(unordered_map<string, UserAccount>& users)
{
	ofstream outputFile;
	outputFile.open("UsersData.txt", std::ios::app);

	// Iterate over the hash table and write each key-value pair to the file
	for (const auto& entry : users) {
		const string& email = entry.first;
		const UserAccount& user = entry.second;

		// Write user data to the file
		outputFile << email << "," << user.Name << "," << user.Phone << "," << user.Address << "," << user.Password << "," << endl;
	}


	outputFile.close();
}

unordered_map<string, UserAccount> ReadData(unordered_map<string, UserAccount>& users) {
	ifstream file("UsersData.txt");

	if (file.is_open()) {
		string line;
		//string name, email, phone, address, password;


		while (getline(file, line)) {
			stringstream ss(line);
			string key;
			string attributeStr;


			if (line.empty()) {
				continue;
			}
			UserAccount tmpuser;
			if (getline(ss, key, ',') && getline(ss, attributeStr)) {
				vector<string> attributes = split(attributeStr, ',');
				tmpuser.Email = key;
				tmpuser.Name = attributes[0];
				tmpuser.Phone = stoi(attributes[1]);
				tmpuser.Address = attributes[2];
				tmpuser.Password = attributes[3];
			}
			users.insert(make_pair(key, tmpuser));
		}



		file.close();
		cout << "User data has been successfully loaded from the file." << endl;
	}
	else {
		cout << "Failed to open the file for reading." << endl;
	}
	return users;
}




void User(bool isAdmin, UserAccount user, unordered_map<string, SubscriptionDetails>& subscription_plans, unordered_map<int, string>& subscriptions_names, vector<pair<vector<string>, double>>& zones, unordered_map<string, UserAccount>users,MetroMate metro,Train train,Schedule schedule)
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
			int answer;
			cout << "press the number of the functionality you want \n 1- Manage Subscription \n 2- Check-In/Check-Out for Rides \n 3- View Ride History \n 4- View Estimated Time of Arrival (ETA) \n 5-Update Personal Information \n";
			cin >> answer;

			//needed variables in manage subscribtion 
			string firstDestination;
			string targetDestination;
			int index = 1;//looping in path
			list<queue <pair< station, int>>> availablePaths;


			switch (answer)
			{
			case 1:
				int manageChoice;
				cout << "if you want to: \n view active subscription type 1 \n renew subscription type 2  \n upgrade subscription type 3";
				cin >> manageChoice;

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
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				
			//	metro.displayTrainETAForUser(stationName, chickindate, checkintime);
				break;
			case 5:
				user = user.updateInfo(user.Email, users);
				break;
			default:
				isUserLoop = false;
				break;
			}

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
unordered_map<string, SubscriptionDetails> readFromSubscriptionFile(const string& filename, unordered_map<int, string>& subscriptions_names, unordered_map<string, station>stationsList) {

	ifstream file(filename);
	if (!file.is_open()) {
		//throw std::runtime_error("Error opening file: " + filename);
		cout << "nofile"; perror(("Error opening file: " + filename).c_str());
	}

	unordered_map<string, SubscriptionDetails> data;
	string line;
	if (file.good()) {
		while (getline(file, line)) {

			stringstream ss(line);
			string key;
			string attributeStr; // Stringall comma-separated attributes

			if (getline(ss, key, ',') && getline(ss, attributeStr)) {
				vector<string> attributes = split(attributeStr, ',');
				/*for (int i = 0; i < attributes.size(); i++) {
					cout << attributes[i] << endl;
				}*/

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
					details.name = attributes[3];
					details.numberOfTrips = stoi(attributes[4]);// Assuming numberOfTrips is last

					int vectorSize = 0;
					unsigned int startIndex = 6;
					if (attributes.size() > 5) {
						vectorSize = stoi(attributes[5]);
					}


					pair<double, pair<int, int>> tmp;
					for (int i = 0; i < vectorSize; i++) {
						//because availableStages has 3 attributes
						tmp.first = stod(attributes[startIndex]);// 0 _ _    3 _ _     6 _ _
						tmp.second.first = stoi(attributes[startIndex + 1]);// _ 1 _    _ 4 _   _ 7 _
						tmp.second.second = stoi(attributes[startIndex + 2]);// _ _ 2    _ _ 5   _ _ 8
						startIndex += 3;
						details.availableStages.push_back(tmp);
					}

					vectorSize = 0;
					if (attributes.size() > startIndex) {
						vectorSize = stoi(attributes[startIndex]);
						startIndex++;
					}

					int innerVectorSize;
					vector<pair<vector<string>, double>> tmpZones;
					pair<vector<string>, double> tmpZonesPairs;
					for (int i = 0; i < vectorSize; i++) {
						innerVectorSize = stoi(attributes[startIndex]);
						startIndex++;
						for (int j = 0; j < innerVectorSize; j++) {
							tmpZonesPairs.first.push_back(attributes[startIndex]);
							startIndex++;

						}
						tmpZonesPairs.second = stod(attributes[startIndex]);
						tmpZones.push_back(tmpZonesPairs);
						startIndex++;
					}
					details.availableZones = tmpZones;
					startIndex++; //it is an empty cell in file (i dont know why)"dont delete it"
					if (attributes.size() > startIndex + 2) {
						details.chosenStage.first = stod(attributes[startIndex]);
						details.chosenStage.second.first = stoi(attributes[++startIndex]);
						details.chosenStage.second.second = stoi(attributes[++startIndex]);
						startIndex++;
					}

					int queueSize = 0;

					if (attributes.size() > startIndex) {
						queueSize = stoi(attributes[startIndex]);
						startIndex++;
					}
					queue <pair< station, int>> tmpQueue;
					pair< station, int> tmpPair;
					for (int i = 0; i < queueSize; i++) {
						string name = attributes[startIndex];

						tmpPair.first = stationsList[name];
						//tmpPair.first.lineNumber = stoi(attributes[++startIndex]);

						tmpPair.second = stoi(attributes[++startIndex]);
						startIndex++;
						tmpQueue.push(tmpPair);
					}
					details.chosenPath = tmpQueue;

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
	}

	return data;
}