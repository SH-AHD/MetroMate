#include<string>
#include<iostream>
using namespace std;
class station {
public:
	string name;
	int lineNumber;

	station(string n, int num) {
		name = n;
		lineNumber = num;
	}
	station() {

	}
};