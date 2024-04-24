
#include "SubscriptionDetails.h"
#include "SubscriptionDetails.cpp"
#include"UserAccount.h"
#include"UserAccount.cpp"
#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>
#include <fstream>
#include <sstream>
#include <stdexcept> 

using namespace std;
void writeToFile(const unordered_map<string, SubscriptionDetails>& data, const string& filename);
unordered_map<string, SubscriptionDetails> readFromFile(const string& filename, unordered_map<int, string>& subscriptions_names);
vector<string> split(const string& str, char delimiter);

int main() {
	unordered_map<string, SubscriptionDetails> subscription_plans;//name and details
	unordered_map<int, string> subscriptions_names;//to have id and name only
	unordered_map<string, UserAccount> users;
	
	string filename = "subscriptions.csv";
	subscription_plans = readFromFile(filename, subscriptions_names);
	/*unordered_map<string, UserAccount>& users;
	UserAccount user;

	string email;
	string password
	if (user.Register(users, user));
	do {
		cout << "enter your email: " << endl;
		cin >> email;
		cout << "enter your password: " << endl;
		cin >> password;
	}while(!user.logIn())*/

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
			//logined as admin or user with "userName" above
			if (isAdmin) {
				//admin
				bool isAdminLoop = true;
				while (isAdminLoop) {
					int funcChoice;
					cout << "enter the name of the function you want to perform\n 1- creat subscription \n 2- modify subscription \n 3- remove subscription \n    press any key to go back";
					// 1-create
					// 2-modify
					// 3-remove
					cin >> funcChoice;

					string subscriptionName;
					SubscriptionDetails newSubscriptions;//we will need it when creating
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
						isAdminLoop = false;
					}
				}


			}
			else if (!isAdmin) {
				//manage subscription
				//choose what action you want to perform
				bool isNotAdminLoop = true;
				while (isNotAdminLoop) {
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
						user.availableTrips = user.chosenSubscription.numberOfTrips;
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
						isNotAdminLoop = false;
						break;
					}
				}



			}


			//outerLoop = false;
			break;
		default:
			outerLoop = false;
			break;
		}


	}

	ifstream file(filename);
	file.clear();
	writeToFile(subscription_plans, filename);
	
	return 0;
}

void writeToFile(const unordered_map<string, SubscriptionDetails>& data, const string& filename) {
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
unordered_map<string, SubscriptionDetails> readFromFile(const string& filename, unordered_map<int, string>& subscriptions_names) {
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