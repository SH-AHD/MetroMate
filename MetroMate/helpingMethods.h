#pragma once
#include <iostream>
using namespace std;
bool confirm() {
	char ans;
	std::cin >> ans;
	if (ans == 'y' || ans == 'Y')return true;
	else if (ans == 'n' || ans == 'N')return false;
	else {
		std::cout << " Enter again!!\n ans: ";
		confirm();
	}
}
int checkPositiveNumber(int num) {
	std::cin >> num;
	if (num > 0)return num;
	else {
		std::cout << " Invalid input, please enter again\n =>";
		checkPositiveNumber(num);
	}
}
int numberInRange(int num, int min, int max) {
	int number = checkPositiveNumber(num);
	if ((number >= min && number <= max)) return number;
	else
	{
		std::cout << " Invalid input, please enter again\n =>";
		numberInRange(number, min, max);
	}
}