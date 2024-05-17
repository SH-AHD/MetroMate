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
using namespace std;
using namespace std::chrono;
unordered_map<string, UserAccount>Users;

UserAccount::UserAccount(string email, string pass, string Name, string Address, int Phone, double balance)
{
	this->Name = Name;
	this->Address = Address;
	this->Phone = Phone;
	this->Email = email;
	this->Password = pass;
	this->balance = balance;
}

UserAccount::UserAccount(string email, string passw)
{
	this->Email = email;
	this->Password = passw;
}


bool UserAccount::Register(unordered_map<string, UserAccount>& users, UserAccount& user)
{
	//	ofstream _file;
	if (!VailEmail(Email))
	{
		while (VailEmail(Email) == false || Email == "Admin@gmail.com")
		{
			cout << "the email is not vaild check it and try again" << endl;
			cout << "Email:";
			cin >> Email;

		}

	}
	if (users.count(Email) > 0)
	{
		cout << "This email is already registered. Please use another one or log in." << endl;
		cout << "to login to the account press 1\nto create a new account press 2\n";
		return false;
	}
	users.insert(make_pair(Email, user));
	cout << "succesful Registertion" << endl;
	LogedUser = true;
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

bool UserAccount::logIn(bool& isAdmin, UserAccount& theLog, string email, string password, unordered_map<string, UserAccount>& users)
{
	if (email == "Admin@gmail.com") {
		isAdmin = true;
		return true;
	}
	else {
		isAdmin = false;
	}
	if (users.count(email) == 0)
		return false;
	UserAccount user = users.at(email);
	if (user.Password != password)
	{
		cout << "the password is incorrect" << endl;
		return false;
	}
	else
		theLog = user;
	LogedUser = true;
	return true;
}

UserAccount UserAccount::forgetPass(string mail, unordered_map<string, UserAccount>& users)
{
	if (users.count(mail) == 0)
	{
		cout << "sorry there is no account with this mail.\n";
		static UserAccount dummyAccount;
		return dummyAccount;
	}
	UserAccount& usa = users[mail];
	string pass;
	cout << "enter the new password:";
	cin >> pass;
	usa.Password = pass;
	cout << "Done\n";
	return usa;
}


bool UserAccount::existMail(UserAccount& user, unordered_map<string, UserAccount>& users)
{
	int c;
	cin >> c;
	string email, password;
	bool isAdmin = false;
	if (c == 1)
	{
		cout << "please enter the password of your account:\n";
		cout << "Password: ";
		cin >> password;
		UserAccount userLog(user.Email, password);
		userLog.logIn(isAdmin, userLog, user.Email, password, users);
		cout << "Login successful" << endl;
		return true;
	}
	string input;
	while (true)
	{
		cout << "enter another email:";
		cin >> input;
		if (users.count(input) == 0)
			break;
	}
	user.Email = input;
	users.insert(make_pair(input, user));
	return false;
}

UserAccount  UserAccount::updateInfo(string key, unordered_map<string, UserAccount>& users)
{

	UserAccount& user = users[key];
	cout << "what the information you want to update:\n1.Name\n2.Adderss\n3.Phone\n4.Password\n5.All your information" << endl;
	int choice, phone;
	string name, address, pass;
	cin >> choice;
	if (choice == 1)
	{
		cout << "enter the new name:";
		cin >> name;
		user.Name = name;
	}
	else if (choice == 2)
	{
		cout << "enter the new address:";
		cin >> address;
		user.Address = address;
	}
	else if (choice == 3)
	{
		cout << "enter the new Phone number:";
		cin >> phone;
		user.Phone = phone;

	}
	else if (choice == 4)
	{
		cout << "enter the new password:";
		cin >> pass;
		user.Password = pass;
	}
	else if (choice == 5)
	{
		cout << "enter the new name:";
		cin >> name;
		user.Name = name;
		cout << "enter the new address:";
		cin >> address;
		user.Address = address;
		cout << "enter the new Phone number:";
		cin >> phone;
		user.Phone = phone;
		cout << "enter the new password:";
		cin >> pass;
		user.Password = pass;
	}
	else
		return user;
	return user;
}


UserAccount UserAccount::LogOut(UserAccount& current)
{
	LogedUser = false;
	return UserAccount();

}

void UserAccount::displayAccount()
{
	cout << this->Name << '\t' << this->Email << '\t' << this->Address << '\t' << this->Phone << endl;

}

void UserAccount::PurchaceSubscription(UserAccount& user, unordered_map<string, SubscriptionDetails> subscription_plans, unordered_map<int, string> subscriptions_names, vector<pair<vector<string>, double>> zones, MetroMate metro)
{



	// select your subscription plan 
	/*1 - Students card
		2 - Public yearly card
		3 - public monthly card
		3 - Cash wallet
	*/

	int key;
	string chosenSubscribtionName;
	SubscriptionDetails chosenSubscription;


	unsigned int index = 1;//looping in the path
	list<queue <pair< station, int>>> availablePaths;

	if (subscription_plans.empty()) {
		cout << "no subscriptions available " << endl;
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
			cout << " Hello, " << Name << ".\n";
			cout << " Here are the steps to save your ride details:\n -> choose the station you will ride from.\n";
			cout << "-> choose the target station.\n";
			cout << " we will show you possible path/s to your target, if they are more than one path,\n choose the one you want\n";
			cout << " Station available right now:\n";
			metro.displayStations();
			cout << " Choose the station you will ride from:\n";
			station* source = metro.chooseStation(); //DepartureStation 
			//chrono::system_clock::time_point currentTime = chrono::system_clock::now();//CheckIn Time; 
			source->chosen = true;

			cout << "\n\n";
			cout << " Now choose the target station:\n";
			station* target = metro.chooseStation();

			cout << " A possible path to your target:\n";
			metro.simpleDFS(source->name, source->lineNumber, target->name);
			target->shortestPath = metro.shortestPath(source->name, target->name);
			cout << " Choose the path you want:\n";
			cout << "1- Normal path\n2- Shortest path\n";
			int pathChosen = -1;
			pathChosen = numberInRange(pathChosen, 1, 2);

			rideDetails newLog;
			queue<pair<string, int>> chosenPath;
			if (pathChosen == 1) {
				newLog.pathChosen = target->possiblePaths;//possible paths size =0
				chosenPath = target->possiblePaths;
			}
			else {
				newLog.shortestPath = target->shortestPath;
				//chosenPath = target->shortestPath;
			}
			int answer;
			cout << "\npress \n 1. if you want to subscripe by stages \n 2. if you want to subscripe by zones " << endl;
			cin >> answer;
			if (answer == 1) {
				cout << "your price is : " << chosenSubscription.calcPrice(chosenPath, 0, true) << " every " << chosenSubscription.valid_duration<<" month";

			}
			else if (answer == 2) {
				for (unsigned int i = 0; i < zones.size(); i++) {
					cout << "zone " << i + 1 << " : \n";
					cout << "its price :" << chosenSubscription.availableZones[i].second << endl;
					for (unsigned int j = 0; j < zones[i].first.size(); j++) {
						cout << "station " << i + 1 << " : " << zones[i].first[j] << endl;

					}
				}
				int zoneChoice;
				cout << "enter zone number you want to subscripe \n";
				cin >> zoneChoice;
				bool stationInZone = false;
				do {


					queue<pair<string, int>> tmp = chosenPath;
					while (!tmp.empty()) {
						for (unsigned int j = 0; j < zones[zoneChoice].first.size(); j++) {
							if (tmp.front().first != zones[zoneChoice].first[j]) {
								stationInZone = false;
							}
							else {
								stationInZone = true;
								break;
							}

						}
						if (!stationInZone) {
							cout << "the chosen path not exist in your zone please choose your zone again" << endl;
							cin >> zoneChoice;
							break;
						}
						tmp.pop();

					}

					if (stationInZone)
						cout << "your price is : " << chosenSubscription.calcPrice(chosenPath, zoneChoice, false) << " every " << chosenSubscription.valid_duration;


				} while (!stationInZone);
			}

			user.chosenSubscription = chosenSubscription;
			user.availableTrips = user.chosenSubscription.numberOfTrips;
			user.balance -= user.chosenSubscription.price;
			cout << "\n subscribtion done to " << user.chosenSubscription.name << endl;
			//calculating start date
			DateTime Date;
			user.startDate = Date.current_date();

		}
	}
}

void UserAccount::checkIn(MetroMate metro, UserAccount user, tm date) {
	
	string departureStation, datee;
	chrono::system_clock::time_point currentTime;
	rideDetails newLog;
	//checking if he has cash wallet or card
	if (user.chosenSubscription.name == "Cash_wallet") {
		cout << " Hello, " << Name << ".\n";
		cout << " Here are the steps to save your ride details:\n -> choose the station you will ride from.\n";
		cout << "-> choose the target station.\n";
		cout << " we will show you possible path/s to your target, if they are more than one path,\n choose the one you want\n";
		cout << " Station available right now:\n";
		metro.displayStations();
		cout << " Choose the station you will ride from:\n";
		station* source = metro.chooseStation(); //DepartureStation 
		 
		
		departureStation == source->getName();
		//upgrading the station's info
		source->addIncome(user, date);
		source->addTickets(date);
		source->addPassenger(source->stationMap, date, user);

		cout << "\n\n";
		cout << " Now choose the target station:\n";
		station* target = metro.chooseStation();

		//upgrade the target's info
		target->addPassenger(target->stationMap, date, user);
		cout << " A possible path to your target:\n";
		metro.simpleDFS(source->name, source->lineNumber, target->name);
		target->shortestPath = metro.shortestPath(source->name, target->name);
		cout << " Choose the path you want:\n";
		cout << "1- Normal path\n2- Shortest path\n";
		int pathChosen = -1;
		pathChosen = numberInRange(pathChosen, 1, 2);

		

		if (pathChosen == 1) {
			newLog.pathChosen = target->possiblePaths;//possible paths size =0
			//calculate price
			user.chosenSubscription.calcPrice(newLog.pathChosen, user.chosenSubscription.chosenZoneNum, user.chosenSubscription.isStageChoice);
			user.chosenSubscription.cashWalletTicket(user);
		}
		else {
			newLog.shortestPath = target->shortestPath;
			//calculate price
			user.chosenSubscription.calcPrice(newLog.pathChosen, user.chosenSubscription.chosenZoneNum, user.chosenSubscription.isStageChoice);
			user.chosenSubscription.cashWalletTicket(user);
		}


	}
	else {

		queue <pair< string, int>> tmpchosenPath = user.chosenSubscription.chosenPath;
		if (tmpchosenPath.empty()) {
			cout << "your didn't choose a path ";
			return;
		}
		else {
			cout << "your path is ";//display his path
			while (!tmpchosenPath.empty()) {
				cout << tmpchosenPath.front().first;
				tmpchosenPath.pop();
			}
		}

		DateTime Date;
		//checking that he didn't exceeds subscription valid duration
		if (Date.current_date().tm_mon - user.startDate.tm_mon >= user.chosenSubscription.valid_duration && Date.is_valid_date(user.startDate)) {
			cout << "please renew your subscription(your duration is done): \n enter y if you want to renew \n enter n if you want to exit" << endl;
			char answer;
			cin >> answer;
			if (answer == 'y') {
				//renew
				user.startDate = Date.current_date();
				user.availableTrips = user.chosenSubscription.numberOfTrips;
				cout << "renew done";
			}
			else if (answer == 'n') {
				cout << "sorry you will not able to check in \n";
				return;
			}
		}
		//checking that his available Trips didn't finish
		if (user.availableTrips == 0) {
			cout << "please renew your subscription(your available Trips is done): \n enter y if you want to renew \n enter n if you want to exit" << endl;
			char answer;
			cin >> answer;
			if (answer == 'y') {
				//renew
				user.startDate = Date.current_date();
				user.availableTrips = user.chosenSubscription.numberOfTrips;
				cout << "renew done";
			}
			else if (answer == 'n') {
				cout << "sorry you will not able to check-in \n";
				return;
			}
		}
		//done check in
		user.chosenSubscription.numberOfTrips -= 1;
		cout << "check-in done";
	
	 currentTime = chrono::system_clock::now();//CheckIn Time;
	 datee = DateTime::get_current_date_string();
	 newLog.rideDate = datee;
	}
	metro.displayTrainETAForUser(departureStation ,datee,currentTime );

	user.rideLog.push_back(newLog);


}

void UserAccount::viewRideLogs() {
	list<rideDetails>::iterator logs;
	if (rideLog.size() != 0) {
		int i = 1;
		for (logs = rideLog.begin(); logs != rideLog.end(); logs++) {
			cout << " Log no." << i << " :\n";
			cout << " Time: " << logs->rideDate << ".\n";
			cout << " From " << logs->sourceStation << " station to " << logs->targetStation << " station\n";
			cout << " Path : \n";
			queue< pair<string, int> > pathOFLog = logs->pathChosen;
			while (!pathOFLog.empty()) {
				cout << pathOFLog.front().first << " station [" << pathOFLog.front().second << "] - ";
			}
			cout << "\n";
			cout << " Total fare: " << logs->fare << "\n";
			cout << "-----------------------------\n";
			i++;
		}
	}
	else cout << " You do not have any logs.\n";
}