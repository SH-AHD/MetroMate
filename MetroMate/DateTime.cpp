//#include <iostream>
//#include<chrono>
//#include<ctime>
////#include"DateTime.h"
////#include"UserAccount.h"
//using namespace std;
//
//tm* DateTime::current_date() {
//	auto now = std::chrono::system_clock::now();
//	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
//	static std::tm date;
//	localtime_s(&date, &now_c);
//	date.tm_year += 1900;
//	date.tm_mon += 1;
//	return &date;
//}