#pragma once
#include <iostream>
#include <unordered_map>
using namespace std;
#include <string>
class UserAccount
{
public:
	string Email;
	string Password;
	string Name;
	string Address;
	int Phone;
	UserAccount(string email, string pass);
	UserAccount(string Email, string Password, string Name, string Address, int Phone);
	bool Register(unordered_map<string, UserAccount>& users, UserAccount user);
	bool VailEmail(string email);
	bool logIn(string email, string password, unordered_map<string, UserAccount>& user);
};

