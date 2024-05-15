#include "Admin.h"
#include "helpingMethods.h"
Admin::Admin() {
}
void Admin::stationManagement(MetroMate metro) {
	bool existFlag = false;
	int lineId = 0;
	while (!existFlag)
	{
		int choice{};
		cout << " 1- Add a new station    2- Make connecions \n";
		cout << " 3 - View MetroMate\n";
		cout << " 4 - Edit station(details / connections)\n";
		cout << " 5 - Delete station\n";
		cout << " 6 - To Exit\n";

		choice = numberInRange(choice, 1, 6);
		switch (choice)
		{
		case 1:
		{
			cout << " How many stations do you want to add ? note: should be on the same line\n";
			cout << " Number of stations:";
			int num = 0;
			num = checkPositiveNumber(num);
			cout << "Enter the line number where the station/s will be added: ";
			lineId = checkPositiveNumber(lineId);
			for (int i = 0; i < num; i++) metro.createNewStation(lineId, i + 1);
			break;
		}
		case 2:
		{
			cout << " 1- connection between two stations on the same line\n 2- make Intersection between two lines\n choice:";
			choice = numberInRange(choice, 1, 2);
			if (choice == 1) {
				cout << "Enter the line number where stations exist: ";
				lineId = checkPositiveNumber(lineId);
				if (metro.MetroLines[lineId].size() < 2) {
					cout << "You have only one station on this line, You must add at least another station to your metromate to make a connection.\n";
					cout << "Add a new station? (y/n)";
					cout << "\nans:";
					if (confirm()) {
						cout << "Enter the line number: ";
						lineId = checkPositiveNumber(lineId);
						metro.createNewStation(lineId);
					}
					cout << " Do you want to connect the current 2 stations? (y/n)";
					cout << "\nans:";
					if (confirm()) metro.stationPositioning();
					else cout << " No connection is made.\n";
				}
				else {
					cout << " How many connections you will make? ";
					int count = 0;
					count = checkPositiveNumber(count);
					for (int i = 0; i < count; i++) metro.stationPositioning();
				}
			}
			else { //make intersection case                            //will be edited
				cout << "Enter the first line number: ";
				lineId = checkPositiveNumber(lineId);
				if (metro.MetroLines[lineId].size() > 0) {
					cout << "Enter the second line number: ";
					lineId = checkPositiveNumber(lineId);
					if (metro.MetroLines[lineId].size() > 0) {
						cout << " How many connections you will make? ";
						int count = 0;
						count = checkPositiveNumber(count);
						for (int i = 0; i < count; i++) metro.stationPositioning();
					}
					else cout << " Sorry, this line does not exist. You cannot make connections\n";
				}
				else cout << " Sorry, this line does not exist. You cannot make connections\n";
			}
			break;
		}
		case 3: //view
		{
			cout << " 1- Display Metro Stations\n 2- Display Stations with connections\n";
			choice = numberInRange(choice, 1, 2);
			if (choice == 1) metro.displayStations();
			else metro.displayMetroMate();
			break;
		}
		case 4:
		{
			cout << "*** Edit zoon ***\n";
			while (true)
			{
				cout << "1-Edit name\n 2-Edit position\n";
				cout << "choose what you need to edit: ";
				int editChoice;
				cin >> editChoice;
				if (editChoice == 1)
				{
					bool notFoundStation = true;
					while (notFoundStation) {
						cout << "enter the line number that the station will be edit on it : ";
						cin >> lineId;
						lineId = checkPositiveNumber(lineId);
						cout << "enter the name of the station that you want to edit : ";
						string oldName;
						cin >> oldName;
						cout << "enter the new name of the station : ";
						string newName;
						cin >> newName;
						metro.editStationName(lineId, oldName, newName, notFoundStation);
						metro.displayStations();
					}
					break;
				}
				else if (editChoice == 2)
				{
					cout << "enter the line number that the station will be edit on it : ";
					cin >> lineId;
					lineId = checkPositiveNumber(lineId);
					cout << "enter the name of the station that you want to edit : ";
					string stationName;
					cin >> stationName;
					metro.editStationPosition(lineId, stationName);
					break;
				}
				else
				{
					cout << "Invalid choice! Please choose again.\n";

				}
			}
			break;
		}
		//new stations will be stored in file by lineId
		case 5: //delete
		{
			bool successfulEdit = false;
			cout << "Enter the line number that the station will be delete from it : ";
			cin >> lineId;
			lineId = checkPositiveNumber(lineId);
			cout << "Enter the name of the station that you want to delete : ";
			string stationName;
			cin >> stationName;
			metro.removeStation(lineId, stationName, successfulEdit);
			if (successfulEdit) {
				cout << "Station " << stationName << " removed successfully.\n";
			}
		}
		case 6:
		{
			existFlag = true;
			break;
		}
		}
	}
}

//void Admin::HomePage(bool& isAdmin, unordered_map<string, SubscriptionDetails>& subscription_plans, unordered_map<int, string>& subscriptions_names, vector<pair<vector<string>, double>>& zones,
//	vector<pair<double, pair<int, int>>>& stages, unordered_map<string, station> stationsList, DateTime date, MetroMate metro, unordered_map<string, UserAccount> users) {
//	//DateTime date;
//	if (isAdmin) {
//		//admin
//		bool isAdminLoop = true;
//		int answer;
//
//		//for station management
//		string stName;
//		int stFunct;
//		char timePeriod;
//
//		//for subscription
//		string subscriptionName;
//		SubscriptionDetails newSubscriptions;//we will need it when creating
//
//
//		while (isAdminLoop) {
//			cout << "enter number of operation you want to perform:\n 1. User Management \n 2. Metro Management \n 3. Subscription Plan Management \n 4. View All Ride Logs \n 5. Station Management \n 6. Fare Management \n any other number to exit" << endl;
//			cin >> answer;
//			switch (answer)
//			{
//			case 1:
//				ModifyUsers(isAdmin, users);
//				break;
//			case 2:
//				stationManagement(metro);
//				break;
//			case 3:
//				int funcChoice;
//				cout << "enter the number of the function you want to perform\n 1- create subscription \n 2- modify subscription \n 3- remove subscription \n    press any key to go back";
//
//				cin >> funcChoice;
//
//				switch (funcChoice)
//				{
//				case 1:
//					//create
//					newSubscriptions.Create(zones, stages);
//
//					//adding it to hash table
//					subscription_plans.insert(make_pair(newSubscriptions.name, newSubscriptions));
//					subscriptions_names.insert(make_pair(subscription_plans.size(), newSubscriptions.name));//1-student,2-public...
//					break;
//
//				case 2:
//					//modify subscription
//					newSubscriptions.Modify(subscription_plans, subscriptions_names);
//
//					break;
//				case 3:
//					int key;
//					//remove subscription 
//					for (const auto& pair : subscriptions_names) {
//						cout << "Key: " << pair.first << ", name: " << pair.second << endl;
//					}
//					cout << "choose subscription key" << endl;
//					cin >> key;
//					subscriptionName = subscriptions_names[key];
//					subscription_plans.erase(subscriptionName);
//					break;
//				default:
//					break;
//				}
//
//			case 4:
//				break;
//			case 5:
//				//station management
//				cout << "Enter the station's name in which you want to access it's data" << endl;
//				cin >> stName;
//
//				cout << "choose what you want to view:\n 1-number of sold tickets \n 2-total income \n 3-number of passengers " << endl;
//				cin >> stFunct;
//
//				cout << "type the time period required:\n d for day \n w for week \n m for month \n y for year " << endl;
//				cin >> timePeriod;
//
//
//				if (stationsList.count(stName) != 0) {
//					switch (stFunct)
//					{
//					case 1:
//						//number of sold tickets
//						cout << stationsList[stName].getSoldTickets(timePeriod, date.current_date()) << endl;
//						break;
//					case 2:
//						//total income
//						cout << stationsList[stName].getTotalIncome(timePeriod, date.current_date()) << endl;
//						break;
//					case 3:
//						//number of passengers
//						cout << stationsList[stName].getTotalPassengers(timePeriod, date.current_date()) << endl;
//						break;
//					}
//
//					break;
//				}
//				break;
//			case 6:
//				cout << "press 1. to manage zones 2. to manage stages";
//				int choice;
//				cin >> choice;
//				switch (choice)
//				{
//				case 1:
//					SetZones(zones);
//					break;
//				case 2:
//					manageStages(stages, choice);
//					break;
//				default:
//					break;
//				}
//				break;
//			case 7:
//				isAdminLoop = false;
//				cout << "hkhku";
//			default:
//
//				break;
//			}
//
//		}
//
//
//	}
//}

void Admin::HomePage(bool& isAdmin, unordered_map<string, SubscriptionDetails>& subscription_plans, unordered_map<int, string>& subscriptions_names, vector<pair<vector<string>, double>>& zones,
	vector<pair<double, pair<int, int>>>& stages, unordered_map<string, station> stationsList, DateTime date, MetroMate metro, unordered_map<string, UserAccount> users, Train train, Schedule schedule) {
	//DateTime date;
	if (isAdmin) {
		//admin
		bool isAdminLoop = true;
		int answer;

		//for station management
		string stName;
		int stFunct;
		char timePeriod;

		//for subscription
		string subscriptionName;
		SubscriptionDetails newSubscriptions;//we will need it when creating


		while (isAdminLoop) {
			cout << "Welcome ,Admin!!\nEnter number of operation you want to perform:\n 1. User Management \n 2. Metro Management \n 3. Subscription Plan Management \n 4. View All Ride Logs \n 5. Station Management \n 6. Fare Management \n 7.Train Management \n 8. Exit" << endl;
			cin >> answer;
			switch (answer)
			{
			case 1:
				ModifyUsers(isAdmin, users);
				break;
			case 2:
				stationManagement(metro);
				break;
			case 3:
				int funcChoice;
				cout << "enter the number of the function you want to perform\n 1- create subscription \n 2- modify subscription \n 3- remove subscription \n    press any key to go back";

				cin >> funcChoice;

				switch (funcChoice)
				{
				case 1:
					//create
					newSubscriptions.Create(zones, stages);

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
				//station management
				cout << "Enter the station's name in which you want to access it's data" << endl;
				cin >> stName;

				cout << "choose what you want to view:\n 1-number of sold tickets \n 2-total income \n 3-number of passengers " << endl;
				cin >> stFunct;

				cout << "type the time period required:\n d for day \n w for week \n m for month \n y for year " << endl;
				cin >> timePeriod;


				if (stationsList.count(stName) != 0) {
					switch (stFunct)
					{
					case 1:
						//number of sold tickets
						cout << stationsList[stName].getSoldTickets(timePeriod, date.current_date()) << endl;
						break;
					case 2:
						//total income
						cout << stationsList[stName].getTotalIncome(timePeriod, date.current_date()) << endl;
						break;
					case 3:
						//number of passengers
						cout << stationsList[stName].getTotalPassengers(timePeriod, date.current_date()) << endl;
						break;
					}

					break;
				}
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
				//case 7:
				//	cout << "\nMetro Management System\n";
				//	cout << "1. Train Management\n";
				//	cout << "2. Display Functions\n";
				//	cout << "3. Exit\n";
				//	cout << "Enter your choice: ";
				//	
				//	//cout << "Press: 1. For addition, modification, and removal functions\n 2. For display functions\n";
				//	int in;
				//	cin >> in;
				//	switch (in)
				//	{
				//	
				//	case 1:
				//	
				//		cout << "\nTrain Management\n";
				//		cout << "1. Add Train\n";
				//		cout << "2. Edit Train\n";
				//		cout << "3. Remove Train\n";
				//		cout << "4. Add Trip To Train Schedule\n";
				//		cout << "5. Modify Trip From Train Schedule\n";
				//		cout << "6. Delete Trip From Train Schedule\n";
				//		cout << "7. Back\n";
				//		cout << "Enter your choice: ";

				//		int trainChoice;
				//			cin >> trainChoice;
				//		switch (trainChoice)
				//		{
				//		case 1:
				//			cout << "To add train you need to enter its information first \nplease,";
				//			train.setTrainInfo();
				//			metro.addTrain(train);
				//			break;
				//		case 2:
				//			cout << "Enter the train ID you want to modify:\n";
				//			int tid;
				//			cin >> tid;
				//			metro.editTrain(tid);
				//			break;
				//		case 3:
				//			cout << "Enter the train ID you want to remove:\n";
				//			
				//			cin >> tid;
				//			metro.removeTrain(tid);
				//			break;
				//		case 4:
				//			cout << "Enter the train ID:\n";
				//			
				//			cin >> tid;
				//			cout << "Enter trip details:\n";
				//			metro.addTripToTrainSchedule(tid, train.setTripInfo());
				//			break;
				//		case 5:
				//			cout << "Enter the line ID:\n";
				//			int lid;
				//			cin >> lid;
				//			cout << "Enter the train ID:\n";
				//			cin >> tid;
				//			cout << "Enter trip date (DD-MM-YYYY):\n";
				//			string date;
				//			cin >> date;
				//			cout << "Enter trip departure time (HH:MM):\n";
				//			string time;
				//			cin >> time;
				//			if (metro.MetroLines.find(lid) != metro.MetroLines.end()) {
				//				metro.modifyTripFromTrainSchedule(lid, tid, date, time);
				//			}
				//			else {
				//				cout << "The line ID is not found!\n";
				//			}
				//			break;
				//		case 6:
				//			cout << "Enter the line ID:\n";
				//			cin >> lid;
				//			cout << "Enter the train ID:\n";
				//			cin >> tid;
				//			cout << "Enter trip date (DD-MM-YYYY):\n";
				//			cin >> date;
				//			cout << "Enter trip departure time (HH:MM):\n";
				//			cin >> time;
				//			if (metro.MetroLines.find(lid) != metro.MetroLines.end()) {
				//				metro.deleteTripFromTrainSchedule(tid, date, time);
				//			}
				//			else {
				//				cout << "The line ID is not found !!\n";
				//			}
				//			break;

				//		case 7:
				//			break;
				//			
				//		}
				//		break;
				//	case 2:
				//		cout << "\nDisplay Functions\n";
				//		cout << "1. In Case Train Breakdown\n";
				//		cout << "2. Display Trains\n";
				//		cout << "3. View information for a specific train\n";
				//		cout << "4. View information for a specific train trip\n";
				//		cout << "5. View information for train trips for specific date\n";
				//		cout << "6. Back\n";
				//		cout << "Enter your choice: ";

				//		int displayChoice;
				//		cin >> displayChoice;
				//		switch (displayChoice)
				//		{
				//		case 1:
				//			cout << "Enter the train ID:\n";
				//			cin >> tid;
				//			cout << "Enter trip date (DD-MM-YYYY):\n";
				//			cin >> date;
				//			cout << "Enter trip departure time (HH:MM):\n";
				//			cin >> time;
				//			metro.simulateTrainBreakdown(tid, time, date);
				//			break;
				//		case 2:
				//			cout << "Enter the line ID:\n";
				//			cin >> lid;
				//			if (metro.MetroLines.find(lid) != metro.MetroLines.end()) {
				//				metro.displayTrains(lid);
				//			}
				//			else {
				//				cout << "The line ID is not found!\n";
				//			}
				//			break;

				//	
				//		case 3:
				//			cout << "Enter the line ID:\n";
				//			cin >> lid;
				//			cout << "Enter the train ID:\n";
				//			cin >> tid;
				//			if (metro.MetroLines.find(lid) != metro.MetroLines.end()) {
				//				metro.displaySpecificTrain(lid, tid);
				//			}
				//			else {
				//				cout << "The line ID is not found!\n";
				//			}
				//			break;
				//		
				//		case 4:
				//			cout << "Enter the line ID:\n";
				//			cin >> lid;
				//			cout << "Enter the train ID:\n";
				//			cin >> tid;
				//			cout << "Enter trip date (DD-MM-YYYY):\n";
				//			cin >> date;
				//			cout << "Enter trip departure time (HH:MM):\n";
				//			cin >> time;
				//			if (metro.MetroLines.find(lid) != metro.MetroLines.end() && train.getTrainID() == tid) {
				//				train.displaySchedule(date, time);
				//			}
				//			else cout << "Line or train ID not found!!\n";
				//			break;

				//		case 5:
				//			cout << "Enter the line ID:\n";
				//			cin >> lid;
				//			cout << "Enter the train ID:\n";
				//			cin >> tid;
				//			cout << "Enter trip date (DD-MM-YYYY):\n";
				//			cin >> date;
				//			if (metro.MetroLines.find(lid) != metro.MetroLines.end() && train.getTrainID() == tid) {
				//				train.displaySchedule(date);
				//			}
				//			else cout << "Line or train ID not found!!\n";
				//			break;
				//			
				//		case 6:
				//			break;
				//			
				//		}

				//	case 3:
				//		cout << "Exiting Metro Management System...\n";
				//		break;

				//	default:
				//		cout << "Invalid choice. Please try again.\n";
				//		break;
				//	}
				//	break;

			case 7:
				char check;
				do {

					cout << "\nTrain Management System\n";
					cout << "1. Train Management Functions\n";
					cout << "2. Display Functions\n";
					cout << "3. Exit\n";
					cout << "Enter your choice: ";

					int in;
					cin >> in;

					if (in == 1) {
						cout << "\nTrain Management\n";
						cout << "1. Add Train\n";
						cout << "2. Edit Train\n";
						cout << "3. Remove Train\n";
						cout << "4. Add Trip To Train Schedule\n";
						cout << "5. Modify Trip From Train Schedule\n";
						cout << "6. Delete Trip From Train Schedule\n";
						cout << "7. Back\n";
						cout << "Enter your choice: ";

						int trainChoice;
						cin >> trainChoice;
						if (trainChoice == 1) {

						/*	cout << "To add train you need to enter its information first \nplease,";
							
							
							train.setTrainInfo();
							for (auto& t :metro.trains) {
				if (train.getTrainID() == t.getTrainID()) {
								cout << "This train " << train.getTrainID() << "is already exist";
				}
				else {
								metro.addTrain(train);
								break;
				}
								
}*/
				
							cout << "To add train you need to enter its information first \nplease,";

							train.setTrainInfo();
							for (int i = 0; i < metro.trains.size(); i++) {
								cout << "loop";
								if (train.getTrainID() == metro.trains[i].getTrainID()) {
									cout << "\nThis train " << train.getTrainID() << " is already exist\n";
								}
								else {
									metro.addTrain(train);
									break;
								}

							}


							//metro.addTrain(train);

						}
						else if (trainChoice == 2) {
							cout << "Enter the train ID you want to modify:\n";
							int tidModify;
							cin >> tidModify;
							metro.editTrain(tidModify);

						}
						else if (trainChoice == 3) {
							cout << "Enter the train ID you want to remove:\n";
							int tidRemove;
							cin >> tidRemove;
							metro.removeTrain(tidRemove);

						}
						else if (trainChoice == 4) {
							cout << "Enter the train ID:\n";
							int tidAddTrip;
							cin >> tidAddTrip;
							cout << "Enter trip details:\n";
							//schedule.setTripScheduleInfo();
							//train.setTripInfo();
							/*metro.addTripToTrainSchedule(tidAddTrip, schedule);*/
							metro.addTripToTrainSchedule(tidAddTrip, train.setTripInfo());

						}
						else if (trainChoice == 5) {
							cout << "Enter the line ID:\n";
							int lidModify;
							cin >> lidModify;
							cout << "Enter the train ID:\n";
							int tidModifyTrip;
							cin >> tidModifyTrip;
							cout << "Enter trip date (DD-MM-YYYY):\n";
							string dateModify;
							cin >> dateModify;
							string timeModify;
							cout << "Enter trip departure time (HH:MM):\n";

							cin >> timeModify;
							if (metro.MetroLines.find(lidModify) != metro.MetroLines.end()) {
								metro.modifyTripFromTrainSchedule(lidModify, tidModifyTrip, dateModify, timeModify);
							}
							else {
								cout << "The line ID is not found!\n";
							}

						}
						else if (trainChoice == 6) {
							cout << "Enter the line ID:\n";
							int lidDelete;
							cin >> lidDelete;
							cout << "Enter the train ID:\n";
							int tidDelete;
							cin >> tidDelete;
							cout << "Enter trip date (DD-MM-YYYY):\n";
							string dateDelete;
							cin >> dateDelete;
							cout << "Enter trip departure time (HH:MM):\n";
							string timeDelete;
							cin >> timeDelete;
							if (metro.MetroLines.find(lidDelete) != metro.MetroLines.end()) {
								metro.deleteTripFromTrainSchedule(tidDelete, dateDelete, timeDelete);
							}
							else {
								cout << "The line ID is not found!\n";
							}

						}
						else if (trainChoice == 7)
							break;
						else {
							cout << "Invalid choice. Please try again.\n";
						}

					}
					else if (in == 2) {
						cout << "\nDisplay Functions\n";
						cout << "1. In Case Train Breakdown\n";
						cout << "2. Display Trains\n";
						cout << "3. View information for a specific train\n";
						cout << "4. View information for a specific train trip\n";
						cout << "5. View information for train trips for specific date\n";
						cout << "6. Back\n";
						cout << "Enter your choice: ";

					

						int displayChoice;
						cin >> displayChoice;
						if (displayChoice == 1) {

							cout << "Enter the train ID:\n";
							int tidBreakdown;
							cin >> tidBreakdown;
							cout << "Enter trip date (DD-MM-YYYY):\n";
							string dateBreakdown;
							cin >> dateBreakdown;
							cout << "Enter trip departure time (HH:MM):\n";
							string timeBreakdown;
							cin >> timeBreakdown;
							metro.simulateTrainBreakdown(tidBreakdown, timeBreakdown, dateBreakdown);

						}
						else if (displayChoice == 2) {
							cout << "Enter the line ID:\n";
							int lidDisplay;
							cin >> lidDisplay;
							if (metro.MetroLines.find(lidDisplay) != metro.MetroLines.end()) {
								metro.displayTrains(lidDisplay);
							}
							else {
								cout << "The line ID is not found!\n";
							}

						}
						else if (displayChoice == 3) {
							cout << "Enter the line ID:\n";
							int lidDisplayTrain;
							cin >> lidDisplayTrain;
							cout << "Enter the train ID:\n";
							int tidDisplayTrain;
							cin >> tidDisplayTrain;
							if (metro.MetroLines.find(lidDisplayTrain) != metro.MetroLines.end()) {
								metro.displaySpecificTrain(lidDisplayTrain, tidDisplayTrain);
							}
							else {
								cout << "The line ID is not found!\n";
							}

						}
						else if (displayChoice == 4) {
							cout << "Enter the line ID:\n";
							int lidDisplayTrip;
							cin >> lidDisplayTrip;
							cout << "Enter the train ID:\n";
							int tidDisplayTrip;
							cin >> tidDisplayTrip;
							cout << "Enter trip date (DD-MM-YYYY):\n";
							string dateDisplayTrip;
							cin >> dateDisplayTrip;
							string timeDisplayTrip;
							do {
								cout << "Enter trip departure time (HH:MM):\n";
								
								cin >> timeDisplayTrip;
							} while (DateTime::timeInputString(timeDisplayTrip) == system_clock::time_point());
							if (metro.MetroLines.find(lidDisplayTrip) != metro.MetroLines.end() && train.getTrainID() == tidDisplayTrip) {
								train.displaySchedule(dateDisplayTrip, timeDisplayTrip);
							}
							else {
								cout << "Line or train ID not found!\n";
							}
						}
						else if (displayChoice == 5) {
							cout << "Enter the line ID:\n";
							int lidDisplayDate;
							cin >> lidDisplayDate;
							cout << "Enter the train ID:\n";
							int tidDisplayDate;
							cin >> tidDisplayDate;
							//cout << "Enter trip date (DD-MM-YYYY):\n";
							string dateDisplayDate = DateTime::inputDateString();;
							//cin >> dateDisplayDate;
							if (metro.MetroLines.find(lidDisplayDate) != metro.MetroLines.end() && train.getTrainID() == tidDisplayDate) {
								train.displaySchedule(dateDisplayDate);
							}
							else {
								cout << "Line or train ID not found!\n";
							}
						}
						else if (displayChoice == 6) {
							break;
						}
						else {
							cout << "Invalid choice. Please try again.\n";
						}

					}
					else if (in == 3) {
						cout << "Exiting Metro Management System...\n";
						break;
					}
					else
					{
						cout << "Invalid choice. Please try again.\n";

					}



					cout << "Do you want to do another operation in the train management system?\"Enter y to continue\"\n";

					cin >> check;
				} while (check == 'y');

				break;

				//case 8: 
				//	
				//	cout << "Exiting Admin Mode...\n";
				//	isAdminLoop = false;
				//	break;

				//default:
				//	//isAdminLoop = false;
				//	cout << "Invalid choice. Please try again.\n";
				//	//break;


			case 8:
				isAdminLoop = false;
				cout << "Exiting Admin Mode...\n";
				break;
			default:
				cout << "Invalid choice. Please try again.\n";
				break;
			}

		}


	}
}


void Admin::SetZones(vector<pair<vector<string>, double>>& zones)
{
	while (true) {
		unsigned int zoneNum;
		vector<string> targetZone;
		int choice;
		cout << "press 1. if you want to add zone \n 2. edit zone\n";
		cin >> choice;
		if (choice == 1) {
			//add zone
			double price;
			cout << "enter price of zone" << zones.size() + 1 << endl;
			cin >> price;
			while (true) {
				cout << "enter station name in zone" << zones.size() + 1 << " \n press 0 if you want to exit (no more stations)  ";
				string stationName;
				cin >> stationName;

				if (stationName == "0")
					break;

				for (unsigned int i = 0; i < zones.size(); i++) {
					for (unsigned int j = 0; j < zones[i].first.size(); j++) {
						if (zones[i].first[j] == stationName) {
							cout << "station is already in another zone";
							continue;
						}
					}
				}
				targetZone.push_back(stationName);
			}
			if (!targetZone.empty())
				zones.push_back(make_pair(targetZone, price));
		}
		else if (choice == 2) {
			//edit zone
			bool validZone = false;
			while (true) {
				vector<pair<vector<string>, double>>::iterator zoneIt;
				zoneIt = zones.begin(); int i = 0;
				while (zoneIt != zones.end())
				{
					cout << "zone " << i + 1 << " : \n";
					for (unsigned int j = 0; j < zoneIt->first.size(); j++) {
						cout << "station " << j + 1 << ": " << zoneIt->first[j] << endl;
					}
					cout << "zone price " << zoneIt->second << "\n";
					zoneIt++;
					i++;
				}
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
					if (targetZone.empty()) {
						cout << "no stations here";
						continue;
					}
					for (unsigned int i = 0; i < targetZone.size(); i++) {
						cout << "station index " << i + 1 << " : " << targetZone[i] << endl;
					}
					cout << "enter station index you want to delete \n press 0 if you want to exit (no more stations)  " << endl;
					unsigned int stationIndex;
					cin >> stationIndex;
					if (stationIndex == 0)
						break;

					//if (stationIndex > 0 && stationIndex < targetZone.size() + 1) {
					//	vector<string> ::iterator it;
					//	it = targetZone.begin();
					//	//zones[zoneNum].erase(stationIndex - 1);
					//	while (*it != targetZone[stationIndex - 1]) {
					//		it++;
					//	}
					//	zones[zoneNum-1].first.erase(it);

					//}
					if (stationIndex > 0 && stationIndex < targetZone.size() + 1) {
						auto it = find(zones[zoneNum - 1].first.begin(), zones[zoneNum - 1].first.end(), targetZone[stationIndex - 1]);
						if (it != zones[zoneNum - 1].first.end()) {
							zones[zoneNum - 1].first.erase(it);
							cout << zones[zoneNum - 1].first[0];
						}
					}
				}
				else if (choice == 3) {
					//add station
					while (true) {
						cout << "enter station name in zone" << zoneNum << " \n press 0 if you want to exit (no more stations)  ";
						string stationName;
						cin >> stationName;
						if (stationName == "0")
							break;
						for (unsigned int i = 0; i < zones.size(); i++) {
							for (unsigned int j = 0; j < zones[i].first.size(); j++) {
								if (zones[i].first[j] == stationName) {
									cout << "station is already in another zone";
									continue;
								}
							}
						}
						zones[zoneNum - 1].first.push_back(stationName);
					}
				}
				else if (choice == 4) {
					//edit zone price
					double price;
					cout << "enter zone new price" << zoneNum << " \n ";
					cin >> price;
					zones[zoneNum - 1].second = price;

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

void Admin::manageStages(vector<pair<double, pair<int, int>>>& stages, int choice)
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

void Admin::ModifyUsers(bool& isAdmin, unordered_map<string, UserAccount>& users)
{
	int c;

	do
	{
		cout << "what is action you want to do\n1.view all the accounts\n2. edit a user account\n3.delete a user account\n enter 0 if you want to exit\n";

		string loop;
		cin >> c;
		if (c == 1)
		{
			for (const auto& pair : users) {
				const UserAccount& value = pair.second;
				cout << value.Name << '\t' << value.Email << '\t' << value.Phone << endl;
			}
		}
		else if (c == 2)
		{
			cout << "enter the email of the account you want to edit in:\n";
			string mail;
			cin >> mail;
			if (users.count(mail) == 0)
				cout << "there is no account in the system like this\n";
			else
			{
				UserAccount finded = users.at(mail);
				finded.displayAccount();
				finded = finded.updateInfo(finded.Email, users);
			}
		}
		else if (c == 3)
		{
			cout << "enter the email of the account you want to delete:\n";
			string mail;
			cin >> mail;
			if (users.count(mail) == 0)
				cout << "there is no account in the system like this\n";
			users.erase(mail);
			if (users.count(mail) == 0)
				cout << "The account no longer exists\n";
		}
		else
			break;
	} while (c != 0);
}
