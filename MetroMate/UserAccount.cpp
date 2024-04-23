#include "UserAccount.h"
#include<iostream>
#include <string>
#include <unordered_map>
unordered_map<string, UserAccount>Users;
using namespace std;
UserAccount::UserAccount(string email, string pass, string Name, string Address, int Phone)
{
	this->Name = Name;
	this->Address = Address;
	this->Phone = Phone;
	this->Email = email;
	this->Password = pass;
}

UserAccount::UserAccount(string email, string passw)
{
	this->Email = email;
	this->Password = passw;
}


bool UserAccount::Register(unordered_map<string, UserAccount>& users, UserAccount user)
{
	if (!VailEmail(Email))
	{
		while (VailEmail(Email) == false)
		{
			cout << "the email is not vaild check it and try again" << endl;
			cout << "Email:";
			cin >> Email;

		}
	}


	users.insert(make_pair(Email, user));
	//	Users[Email] = UserAccount(Email, Password, Name, Address, Phone);
	cout << "succesful Registertion";
	//	Users[Email] = UserAccount(Email, Password, Name, Address, Phone);
	return true;


}
bool UserAccount::VailEmail(string email)
{
	size_t vaild = email.find('@');

	if (vaild == string::npos)
		return false;
	if (vaild == 0 || email.at(vaild - 1) == '.' || email.at(vaild - 1) == '\t')
		return false;
	if (email.length() - 1 == vaild || email.at(vaild + 1) == '.' || email.at(vaild + 1) == '\t')
		return false;
	for (char c : email)
		if (!isalnum(c) && c != '.' && c != '@')
			return false;
	return true;
}

bool UserAccount::logIn(string email, string password, unordered_map<string, UserAccount>& users)
{

	if (users.count(email) == 0)
		return false;
	UserAccount user = users.at(email);
	if (user.Password != password)
	{
		cout << "the password is incorrect" << endl;
		return false;
	}
	else
		return true;
}

