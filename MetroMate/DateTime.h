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
	static tm dateInput();
	static system_clock::time_point timeInput();
	static system_clock::time_point timeInputString(string timeStr);
	//void displayTime(system_clock::time_point timePoint);
	static long calculateDateDifference(tm date1, tm date2);
	static long calculateTimeDifferenceHours(system_clock::time_point time1, system_clock::time_point time2);
	static minutes calculateTimeDifferenceMinutes(system_clock::time_point time1, system_clock::time_point time2);
	//void dateDay(string date);
	static string inputDateString();
	static void outputTimePoint(system_clock::time_point timePoint);
};
