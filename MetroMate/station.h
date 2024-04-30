#include<string>
#include<iostream>
using namespace std;
class Station {
public:
	string name;
	int lineNumber;

	Station(string n, int num) {
		name = n;
		lineNumber = num;
	}
};