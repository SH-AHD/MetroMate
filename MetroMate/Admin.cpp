#include "Admin.h"
#include "helpingMethods.h"
void Admin::HomePage(MetroMate metro) {
	bool existFlag = false;
	int lineId=0;
	while (!existFlag)
	{
		int choice{};
		cout << " 1- Add a new station    2- Make connecions \n";
		cout << " 3 - View MetroMate\n";
		cout << " 4 - Edit station(details / connections)\n";
		cout << " 5 - Delete station\n";
		cout << " 6 - To Exit\n";

		choice = numberInRange(choice, 1, 5);
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
						int count=0;
						   count= checkPositiveNumber(count);
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
			metro.removeStation(lineId, stationName);
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