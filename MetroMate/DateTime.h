#pragma once
#include<iostream>
//for time
#include <chrono>
#include <ctime>
#include <sstream> // Include for istringstream
#include <iomanip> // Include for parse
#include <chrono>  // Include for sys_days and weekday



using namespace std;
using namespace std::chrono;

class DateTime {
public:

	tm current_date();
	bool is_valid_date(tm date);


	//s
	tm dateInput();
	system_clock::time_point timeInput();
	static system_clock::time_point timeInputString(string timeStr);

	long calculateDateDifference(tm date1, tm date2);
	long calculateTimeDifferenceHours(system_clock::time_point time1, system_clock::time_point time2);
	long calculateTimeDifferenceMinutes(system_clock::time_point time1, system_clock::time_point time2);
	//void dateDay(string date);
	string inputDateString(string inputDate);
	static void outputTimePoint(system_clock::time_point timePoint);
};
