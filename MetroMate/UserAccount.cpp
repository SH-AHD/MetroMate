#include "UserAccount.h"

#include "SubscriptionDetails.h"
#include <ctype.h>//lower case

#include "DateTime.h"

#include<iostream>
#include <string>
#include <unordered_map>
//for time
#include <chrono>
#include <ctime>

unordered_map<string, UserAccount>Users;
using namespace std;
UserAccount::UserAccount(string email, string pass, string Name, string Address, int Phone)
{
	this->Name = Name;
	this->Address = Address;
	this->Phone = Phone;
	this->Email = email;
	this->Password = pass;
}

UserAccount::UserAccount(string email, string passw)
{
	this->Email = email;
	this->Password = passw;
}


bool UserAccount::Register(unordered_map<string, UserAccount>& users, UserAccount user)
{
	if (!VailEmail(Email))
	{
		while (VailEmail(Email) == false || Email == "Admin@gmail.com")
		{
			cout << "the email is not vaild check it and try again" << endl;
			cout << "Email:";
			cin >> Email;

		}
	}


	users.insert(make_pair(Email, user));
	//	Users[Email] = UserAccount(Email, Password, Name, Address, Phone);
	cout << "succesful Registertion";
	//	Users[Email] = UserAccount(Email, Password, Name, Address, Phone);
	return true;


}
bool UserAccount::VailEmail(string email)
{
	size_t vaild = email.find('@');

	if (vaild == string::npos)
		return false;
	if (vaild == 0 || email.at(vaild - 1) == '.' || email.at(vaild - 1) == '\t')
		return false;
	if (email.length() - 1 == vaild || email.at(vaild + 1) == '.' || email.at(vaild + 1) == '\t')
		return false;
	for (char c : email)
		if (!isalnum(c) && c != '.' && c != '@')
			return false;
	return true;
}

bool UserAccount::logIn(string email, string password, unordered_map<string, UserAccount>& users)
{

	if (users.count(email) == 0)
		return false;
	UserAccount user = users.at(email);
	if (user.Password != password)
	{
		cout << "the password is incorrect" << endl;
		return false;
	}
	else
		return true;
}

void UserAccount::PurchaceSubscription(UserAccount& user, unordered_map<string, SubscriptionDetails> subscription_plans, unordered_map<int, string> subscriptions_names)
{



	// Please select your subscription plan or view details
	/*1 - Students card
		2 - Public yearly card
		3 - public monthly card
		3 - Cash wallet
		4 - More details*/
		//if he chosed more details-> iterator in hash table
	int key;
	string chosenSubscribtionName;
	SubscriptionDetails chosenSubscription;


	if (subscription_plans.empty()) {
		cout << "no subscriptions available ";
	}
	else {
		cout << "available subscriptions: " << endl;
		for (const auto& pair : subscriptions_names) {
			cout << "Key: " << pair.first << ", name: " << pair.second << endl;
		}
		cout << "choose subscription key" << endl;

		cin >> key;

		//find subscription name from hash table of their keys
		chosenSubscribtionName = subscriptions_names[key];

		//picking a subscription plan
		chosenSubscription = subscription_plans[chosenSubscribtionName];

		if (chosenSubscribtionName == "Cash_wallet") {
			while (true) {
				cout << "do you want to put amount of money in wallet (y/n)" << endl;
				char answer;
				cin >> answer;
				if (tolower(answer) == 'y') {
					int cashMoney;
					do {
						cout << "please put money in wallet (multiple of 10)" << endl;
						cin >> cashMoney;
					} while (cashMoney % 10 != 0);
					chosenSubscription.cashAmount += cashMoney;
					user.chosenSubscription = chosenSubscription;
					break;
				}
				else if (tolower(answer) == 'n') {
					user.chosenSubscription = chosenSubscription;
					break;
				}
				else {
					cout << "please enter y for yes or n for no" << endl;
				}
			}


		}
		else {
			// initial and target destination??
			string firstDestination;
			string targetDestination;
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
			chosenSubscription.calcPrice(chosenPath);
			user.chosenSubscription = chosenSubscription;

			//calculating start date
			DateTime Date;
			user.startDate=Date.current_date();
			 
				 
			user.availableTrips = chosenSubscription.numberOfTrips;
		}
	}
}


tm DateTime::current_date() {
	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	static std::tm date;
	localtime_s(&date, &now_c);
	date.tm_year += 1900;
	date.tm_mon += 1;
	return date;
}
bool DateTime::is_valid_date(std::tm date) {
	if (date.tm_year == -1) {
		return false;
	}
	if (date.tm_mon < 0 || date.tm_mon > 11) {
		return false;
	}
	if (date.tm_mday < 1 || date.tm_mday > 31) {
		return false;
	}
	// Additional checks can be added for the range of tm_mday based on tm_mon
	return true;
}