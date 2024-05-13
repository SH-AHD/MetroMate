


#include"DateTime.h"
tm DateTime::current_date() {
	auto now = std::chrono::system_clock::now();
	time_t now_c = std::chrono::system_clock::to_time_t(now);
	static tm date;
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

tm DateTime::dateInput() {
	tm date = {};   // initialize struct with zeros
	cout << "Enter date \"DD-MM-YYYY\": ";
	cin >> get_time(&date, "%d-%m-%Y");
	if (cin.fail()) {
		cerr << "Error: Invalid input format." << endl;
	}
	return date;
}

system_clock::time_point DateTime::timeInput() {
	tm intime = {}; // initialize struct with zeros
	cout << "Enter time (HH:MM:SS): ";
	cin >> get_time(&intime, "%H:%M:%S");
	auto time = system_clock::from_time_t(std::mktime(&intime));
	if (cin.fail()) {
		cerr << "Error: Invalid input format." << endl;
	}
	return time;
}

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


system_clock::time_point DateTime::timeInputString(string timeStr) {
	// Initialize a tm struct with valid date and time
	tm timeStruct = {};
	timeStruct.tm_year = 70;  // Year 1970 (epoch)
	timeStruct.tm_mon = 0;    // January (month 0)
	timeStruct.tm_mday = 1;   // 1st day of the month

	// Create a stringstream to parse the input
	istringstream ss(timeStr);

	// Parse hours
	int hours;
	ss >> hours;
	if (ss.fail() || hours < 0 || hours > 23) {
		cerr << "Error: Invalid hours." << endl;
		return system_clock::time_point();
	}

	// Expect and discard the colon
	char colon;
	ss >> colon;
	if (colon != ':') {
		cerr << "Error: Invalid input format." << endl;
		return system_clock::time_point();
	}

	// Parse minutes
	int minutes;
	ss >> minutes;
	if (ss.fail() || minutes < 0 || minutes > 59) {
		cerr << "Error: Invalid minutes." << endl;
		return system_clock::time_point();
	}

	// Check for any trailing characters
	char c;
	if (ss >> c) {
		cerr << "Error: Unexpected character '" << c << "'." << endl;
		return system_clock::time_point();
	}

	// Set the time values in the tm struct
	timeStruct.tm_hour = hours;
	timeStruct.tm_min = minutes;

	// Convert the tm struct to a system_clock::time_point
	time_t t = mktime(&timeStruct);
	if (t == -1) {
		cerr << "Error: Unable to convert time." << endl;
		return system_clock::time_point();
	}

	return system_clock::from_time_t(t);
}

//void DateTime:: displayTime(system_clock::time_point timePoint) {
//	// Convert time_point to std::time_t
//	time_t time = system_clock::to_time_t(timePoint);
//
//	// Declare a tm structure to store the local time
//	tm tm = {};
//
//	// Convert std::time_t to std::tm using localtime
//	localtime_s(&tm, &time); // Use localtime_s for safer multi-threading
//
//	// Output formatted time (hours, minutes, seconds)
//	cout << setw(2) << setfill('0') << tm.tm_hour << ":"
//		<< setw(2) << setfill('0') << tm.tm_min << ":"
//		<< setw(2) << setfill('0') << tm.tm_sec << endl;
//}


long DateTime::calculateDateDifference(tm date1, tm date2) {
	// Convert dates to time points
	system_clock::time_point tp1 = system_clock::from_time_t(std::mktime(&date1));
	system_clock::time_point tp2 = system_clock::from_time_t(std::mktime(&date2));

	// Calculate the duration between the two time_points
	auto duration = tp2 - tp1;

	// Convert the duration to days
	auto days = std::chrono::duration_cast<std::chrono::hours>(duration).count() / 24;

	return days;
}



//void DateTime::dateDay(string date) {
//	std::istringstream in{date}; // Corrected namespace to std::
//	std::chrono::sys_days
//		dd;      // Corrected namespace to std::chrono::
//	in >> std::chrono::parse("%d/%m/%Y", dd);// Corrected namespace to std::chrono::
//	std::cout << "Day of the week is " << std::get_weekday(dd) << '\n'; // Corrected namespace to std::chrono::
//}

//void DateTime::dateDay(string date) {
//	istringstream in{ date };
//	sys_days dd;
//	in >> parse("%d/%m/%Y", dd);
//	cout << "Day of the week is " << weekday{ dd } << '\n';
//}

long DateTime::calculateTimeDifferenceHours(system_clock::time_point time1, system_clock::time_point time2) {
	auto duration = time2 - time1;

	// Convert the duration to hours
	auto hours = std::chrono::duration_cast<std::chrono::hours>(duration).count();

	return hours;
}

//minutes DateTime::calculateTimeDifferenceMinutes(system_clock::time_point time1, system_clock::time_point time2) {
//	auto duration = time2 - time1;
//
//	// Convert the duration to minutes
//	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration).count();
//
//	return minutes;
//}

std::chrono::minutes DateTime::calculateTimeDifferenceMinutes(system_clock::time_point time1, system_clock::time_point time2) {
	auto duration = time2 - time1;

	// Convert the duration to minutes
	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);

	return minutes;
}




string DateTime::inputDateString() {
	cout << "Enter Date in the format (DD-MM-YYYY): ";

	// Clear the newline character from the input buffer
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	string inputDate;
	// Read the input line
	std::getline(cin, inputDate);


	// Create a string stream to parse the input
	std::istringstream iss(inputDate);

	int day, month, year;
	char delimiter;

	// Attempt to extract the day, month, and year from the input string
	if (iss >> day >> delimiter >> month >> delimiter >> year) {
		// Check if the delimiter is correct and if the values are within valid ranges
		if (delimiter == '-' && day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 0) {
			return inputDate;
		}
		else {
			cout << "Invalid input format." << endl;
		}
	}
	else {
		cout << "Error reading input." << endl;
	}

	return "";
}


//string DateTime::inputDateString(string inputDate) {
//	//cout << "Enter a string in the format (DD-MM-YYYY): ";
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
//void DateTime:: outputTimePoint(const std::chrono::system_clock::time_point& timePoint) {
//	// Convert time_point to std::time_t
//	time_t time = system_clock::to_time_t(timePoint);
//
//	// Convert std::time_t to std::tm
//	tm tm = *localtime(&time);
//
//	// Output formatted time
//	cout << put_time(&tm, "%d-%m-%Y %H:%M:%S");
//}

void DateTime::outputTimePoint(system_clock::time_point timePoint) {
	// Convert time_point to std::time_t
	time_t time = system_clock::to_time_t(timePoint);

	// Declare a tm structure to store the local time
	tm tm = {};

	// Convert std::time_t to std::tm using localtime_s
	if (localtime_s(&tm, &time) == 0) {
		// Output formatted time
		std::cout << std::put_time(&tm, "%H:%M:%S");
	}
	else {
		// Handle error if localtime_s fails
		std::cerr << "Error: Unable to convert time." << std::endl;
	}
}
