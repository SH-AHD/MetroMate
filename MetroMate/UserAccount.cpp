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
	users.insert(make_pair(Email, user));
	//	Users[Email] = UserAccount(Email, Password, Name, Address, Phone);
	cout << "succesful Registertion" << endl;
	LogedUser = true;
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

UserAccount UserAccount::forgetPass(string mail,unordered_map<string,UserAccount>users)
{
	if (users.count(mail) == 0)
	{
		cout << "sorry there is no account with this mail.\n";
		throw runtime_error("Account not found");
	}
	UserAccount& usa = users[mail];
	string pass;
	cout << "enter the new password:";
	cin >> pass;
	usa.Password = pass;
	cout << "Done\n";
	return usa;
}





UserAccount  UserAccount::updateInfo(string key, unordered_map<string, UserAccount>& users)
{

	UserAccount& user = users[key];
	cout << "what the information you want to update:\n1.Name\n2.Adderss\n3.Phone\n4.Password\n5.All your information" << endl;
	int choice, phone;
	string name, address,pass;
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
	return UserAccount ();

}

void UserAccount::displayAccount()
{
	cout << this->Name << '\t' << this->Email << '\t' << this->Address << '\t' << this->Phone << endl;

}

void UserAccount::PurchaceSubscription(UserAccount& user, unordered_map<string, SubscriptionDetails> subscription_plans, unordered_map<int, string> subscriptions_names, vector<pair<vector<string>, double>> zones)
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
			string firstDestination;
			string targetDestination;
			cout << "enter your first station" << endl;
			cin >> firstDestination;
			cout << "enter your target  station" << endl;
			cin >> targetDestination;

			int answer;


			//print all avaliable paths
			for (auto it = availablePaths.begin(); it != availablePaths.end(); ++it) {
				cout << "path " << index << " : ";

				pair<station, int> front = it->front();
				cout << front.first.name << " , ";
				it->push(it->front());
				it->pop();

				// path must not have repeated values to make this code work
				while (it->front().first.name != front.first.name && availablePaths.size() != 1) {
					cout << it->front().first.name << " , ";
					it->push(it->front());
					it->pop();
				}
				index++;
			}

			cout << "\npress \n 1. if you want to subscripe by stages \n 2. if you want to subscripe by zones " << endl;
			cin >> answer;
			if (answer == 1) {

				//making him choose
				cout << "enter the index of the path you want " << endl;
				cin >> index;
				if (index - 1 < 0 || index - 1 >= availablePaths.size()) {
					cout << "no index like this" << endl;
				}
				else {
					auto it = availablePaths.begin();
					advance(it, index - 1);//go to this index
					queue <pair< station, int>> chosenPath = *it;
					chosenSubscription.chosenPath = chosenPath;
					cout << "your price is : " << chosenSubscription.calcPrice(chosenPath, 0, true) << " every " << chosenSubscription.valid_duration;

				}

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


					cout << "enter the index of the path you want " << endl;
					cin >> index;
					if (index - 1 < 0 || index - 1 >= availablePaths.size()) {
						cout << "no index like this" << endl;
					}
					else {
						auto it = availablePaths.begin();
						advance(it, index - 1);//go to this index
						queue <pair< station, int>> chosenPath = *it;

						queue <pair< station, int>> tmp = chosenPath;

						while (!tmp.empty()) {
							for (unsigned int j = 0; j < zones[zoneChoice].first.size(); j++) {
								if (tmp.front().first.name != zones[zoneChoice].first[j]) {
									stationInZone = false;
								}
								else {
									stationInZone = true;
									break;
								}

							}
							if (!stationInZone) {
								cout << "the chosen path not exist in your zone please choose your path again" << endl;
								break;
							}
							tmp.pop();

						}

						if (stationInZone)
							cout << "your price is : " << chosenSubscription.calcPrice(chosenPath, zoneChoice, false) << " every " << chosenSubscription.valid_duration;

					}
				} while (!stationInZone);
			}

			user.chosenSubscription = chosenSubscription;
			user.availableTrips = user.chosenSubscription.numberOfTrips;

			//calculating start date
			DateTime Date;
			user.startDate = Date.current_date();

		}
	}
}

void UserAccount::checkIn(MetroMate metro,UserAccount user, tm date) {
	cout << " Hello, " << Name << ".\n";
	cout << " Here are the steps to save your ride details:\n -> choose the station you will ride from.\n";
	cout << "-> choose the target station.\n";
	cout << " we will show you possible path/s to your target, if they are more than one path,\n choose the one you want\n";
	cout << " Station available right now:\n";
	metro.displayStations();
	cout << " Choose the station you will ride from:\n";
	station* source = metro.chooseStation(); //DepartureStation 
	chrono::system_clock::time_point currentTime = chrono::system_clock::now();//CheckIn Time; 
	source->chosen = true;

	//upgrading the station's info
	source->addIncome(user,date);
	source->addTickets(date);
	source->addPassenger(source->stationMap,date,user);

	cout << "\n\n";
	cout << " Now choose the target station:\n";
	station* target = metro.chooseStation();

	//upgrade the target's info
	target->addPassenger(target->stationMap, date, user);

	float fare = 0.0; //temp var will be deleted later according to scenrio
	cout << " The possible path to your target:\n";
	metro.simpleDFS(source->name, source->lineNumber, target->name, fare); //dijkstra will be continued 
	//dijkstra
	cout << " Choose the path you want:\n";
	int pathChosen = -1;
	pathChosen = numberInRange(pathChosen, 1, 2);
	rideDetails newLog;
	if (pathChosen == 1) {
		newLog.pathChosen = target->possiblePaths[0];
	}
	else {
		newLog.pathChosen = target->possiblePaths[1];
	}
	//subscribtion datils will complete here
}


//
//tm DateTime::current_date() {
//	auto now = std::chrono::system_clock::now();
//	time_t now_c = std::chrono::system_clock::to_time_t(now);
//	static tm date;
//	localtime_s(&date, &now_c);
//	date.tm_year += 1900;
//	date.tm_mon += 1;
//	return date;
//}
//
//bool DateTime::is_valid_date(std::tm date) {
//	if (date.tm_year == -1) {
//		return false;
//	}
//	if (date.tm_mon < 0 || date.tm_mon > 11) {
//		return false;
//	}
//	if (date.tm_mday < 1 || date.tm_mday > 31) {
//		return false;
//	}
//	
//	// Additional checks can be added for the range of tm_mday based on tm_mon
//	return true;
//}
//
//////s
////tm  DateTime::dateInput() {
////	tm date = {};   // initialize struct with zeros
////	cout << "Enter date \"DD-MM_YYYY\": ";
////	cin >> get_time(&date, "%d-%m-%Y");
////	if (cin.fail()) {
////		cerr << "Error: Invalid input format." << endl;
////	}
////	return date;
////}
////
////system_clock::time_point   DateTime::timeInput() {
////	tm intime = {}; // initialize struct with zeros
////	cout << "Enter time (HH:MM:SS): ";
////	cin >> get_time(&intime, "%H:%M:%S");
////	auto time = system_clock::from_time_t(std::mktime(&intime));
////	if (cin.fail()) {
////		cerr << "Error: Invalid input format." << endl;
////	}
////	return time;
////}
////
////long   DateTime::calculateDateDifference(tm date1, tm date2) {
////	// Convert dates to time points
////	system_clock::time_point tp1 = system_clock::from_time_t(std::mktime(&date1));
////	system_clock::time_point tp2 = system_clock::from_time_t(std::mktime(&date2));
////
////	// Calculate the duration between the two time_points
////	auto duration = tp2 - tp1;
////
////	// Convert the duration to days
////	auto days = std::chrono::duration_cast<std::chrono::hours>(duration).count() / 24;
////
////	return days;
////}
////
////void DateTime::dateDay(string date) {
////	
////		
////		cin>> istringstream in{ date};
////		/*cin >> get_time(&date, "%d-%m-%Y");
////		if (cin.fail()) {
////			cerr << "Error: Invalid input format." << endl;
////		}*/
////		
////		sys_days dd;
////		in >> chrono::parse("%d/%m/%Y", dd);
////		cout << "Day of the week is " << weekday{ dd } << '\n';
////		//cout << "Day of the year is " << dd - sys_days{ year_month_day{dd}.year() / 1 / 0 } << '\n';
////	
////}
////
////long   DateTime::calculateTimeDifferenceHours(system_clock::time_point time1, system_clock::time_point time2) {
////	auto duration = time2 - time1;
////
////	// Convert the duration to hours
////	auto hours = std::chrono::duration_cast<std::chrono::hours>(duration).count();
////
////	return hours;
////}
////
////long   DateTime::calculateTimeDifferenceMinutes(system_clock::time_point time1, system_clock::time_point time2) {
////	auto duration = time2 - time1;
////
////	// Convert the duration to hours
////	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration).count();
////
////	return minutes;
////}
////
////string DateTime::inputDateString(string inputDate){
////
////	cout << "Enter a string in the format (DD-MM-YYYY): ";
////	std::getline(cin, inputDate);
////
////	// Create a string stream to parse the input
////	std::istringstream iss(inputDate);
////
////	int day, month, year;
////	char delimiter;
////
////	// Attempt to extract the day, month, and year from the input string
////	if (iss >> day >> delimiter >> month >> delimiter >> year) {
////		// Check if the delimiter is correct and if the values are within valid ranges
////		if (delimiter == '-' && day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 0) {
////			//cout << "Input is valid. Day: " << day << ", Month: " << month << ", Year: " << year << std::endl;
////			return inputDate;
////		}
////		else {
////			cout << "Invalid input format." << endl;
////		}
////	}
////	else {
////		cout << "Error reading input." << endl;
////	}
////}
//
//
//tm DateTime::dateInput() {
//	tm date = {};   // initialize struct with zeros
//	cout << "Enter date \"DD-MM-YYYY\": ";
//	cin >> get_time(&date, "%d-%m-%Y");
//	if (cin.fail()) {
//		cerr << "Error: Invalid input format." << endl;
//	}
//	return date;
//}
//
//system_clock::time_point DateTime::timeInput() {
//	tm intime = {}; // initialize struct with zeros
//	cout << "Enter time (HH:MM:SS): ";
//	cin >> get_time(&intime, "%H:%M:%S");
//	auto time = system_clock::from_time_t(std::mktime(&intime));
//	if (cin.fail()) {
//		cerr << "Error: Invalid input format." << endl;
//	}
//	return time;
//}
//
//system_clock::time_point DateTime::timeInputString(string timeStr) {
//	// Initialize a tm struct with zeros
//	tm timeStruct = {};
//
//	// Create a stringstream to parse the input
//	istringstream ss(timeStr);
//
//	// Parse the input into the tm struct
//	ss >> get_time(&timeStruct, "%H:%M:%S");
//
//	// Check if parsing was successful
//	if (ss.fail()) {
//		cerr << "Error: Invalid input format." << endl;
//		// Return a default time if parsing fails
//		return system_clock::time_point();
//	}
//
//	// Convert the tm struct to a system_clock::time_point
//	time_t t = mktime(&timeStruct);
//	return system_clock::from_time_t(t);
//}
//
//
//long DateTime::calculateDateDifference(tm date1, tm date2) {
//	// Convert dates to time points
//	system_clock::time_point tp1 = system_clock::from_time_t(std::mktime(&date1));
//	system_clock::time_point tp2 = system_clock::from_time_t(std::mktime(&date2));
//
//	// Calculate the duration between the two time_points
//	auto duration = tp2 - tp1;
//
//	// Convert the duration to days
//	auto days = std::chrono::duration_cast<std::chrono::hours>(duration).count() / 24;
//
//	return days;
//}
//
//
//
////void DateTime::dateDay(string date) {
////	std::istringstream in{date}; // Corrected namespace to std::
////	std::chrono::sys_days
////		dd;      // Corrected namespace to std::chrono::
////	in >> std::chrono::parse("%d/%m/%Y", dd);// Corrected namespace to std::chrono::
////	std::cout << "Day of the week is " << std::get_weekday(dd) << '\n'; // Corrected namespace to std::chrono::
////}
//
////void DateTime::dateDay(string date) {
////	istringstream in{ date };
////	sys_days dd;
////	in >> parse("%d/%m/%Y", dd);
////	cout << "Day of the week is " << weekday{ dd } << '\n';
////}
//
//long DateTime::calculateTimeDifferenceHours(system_clock::time_point time1, system_clock::time_point time2) {
//	auto duration = time2 - time1;
//
//	// Convert the duration to hours
//	auto hours = std::chrono::duration_cast<std::chrono::hours>(duration).count();
//
//	return hours;
//}
//
//long DateTime::calculateTimeDifferenceMinutes(system_clock::time_point time1, system_clock::time_point time2) {
//	auto duration = time2 - time1;
//
//	// Convert the duration to minutes
//	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration).count();
//
//	return minutes;
//}
//
//string DateTime::inputDateString(string inputDate) {
//	cout << "Enter a string in the format (DD-MM-YYYY): ";
//	std::getline(cin, inputDate);
//
//	// Create a string stream to parse the input
//	std::istringstream iss(inputDate);
//
//	int day, month, year;
//	char delimiter;
//
//	// Attempt to extract the day, month, and year from the input string
//	if (iss >> day >> delimiter >> month >> delimiter >> year) {
//		// Check if the delimiter is correct and if the values are within valid ranges
//		if (delimiter == '-' && day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 0) {
//			return inputDate;
//		}
//		else {
//			cout << "Invalid input format." << endl;
//		}
//	}
//	else {
//		cout << "Error reading input." << endl;
//	}
//
//	return "";
//}
//
////
////void DateTime:: outputTimePoint(const std::chrono::system_clock::time_point& timePoint) {
////	// Convert time_point to std::time_t
////	time_t time = system_clock::to_time_t(timePoint);
////
////	// Convert std::time_t to std::tm
////	tm tm = *localtime(&time);
////
////	// Output formatted time
////	cout << put_time(&tm, "%d-%m-%Y %H:%M:%S");
////}
//
//void DateTime::outputTimePoint(system_clock::time_point timePoint) {
//	// Convert time_point to std::time_t
//	time_t time = system_clock::to_time_t(timePoint);
//
//	// Declare a tm structure to store the local time
//	tm tm = {};
//
//	// Convert std::time_t to std::tm using localtime_s
//	if (localtime_s(&tm, &time) == 0) {
//		// Output formatted time
//		std::cout << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
//	}
//	else {
//		// Handle error if localtime_s fails
//		std::cerr << "Error: Unable to convert time." << std::endl;
//	}
//}