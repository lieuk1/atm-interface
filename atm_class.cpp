#include <iostream>
#include <cstring> // FOR strcpy
#include <limits> // FOR numeric_limits

#include "atm_header.h"
using namespace std;

/******************************
*  MEMBER FUNCTION DEFINITIONS
*******************************/

void Account::create_account() {
	cout << "Enter your name : ";
	cin.ignore();
	cin.getline(name_, 50);
	
	while( (cout << "Enter a personal pin # (5-10 digits) : ") && 
		(!(cin >> pin_) || pin_ < 10000 || pin_ > 9999999999) ) {
		cout << "Invalid input.\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	while( (cout << "Enter your account type (C or S):\n") &&
		(!(cin >> type_) || (type_ != 'C' && type_ != 'S')) ) {
		cout << "Invalid input.\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	// MAXIMUM DEPOSIT ALLOWED VIA ATM : $2,000
	while( (cout << "Enter an initial deposit:\n")
		&& (!(cin >> balance_) || (balance_ > 2000)) ) {
		cout << "The maximum deposit allowed via ATM is $2,000. Retry.\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

void Account::deposit(double depositAmt) {
	balance_ += depositAmt;
}

void Account::withdraw(double withdrawAmt) {
	balance_ -= withdrawAmt;
}

void Account::show_acc() {
	cout << "\nAccount Owner Name: " << name_ << endl;
	cout << "Account Number: " << "HIDDEN" << endl;
	cout << "Account Type: " << type_ << endl;
	cout << "Balance: $" << balance_ << "\n";
}

string get_name(char* name) {
	return string(name);
}

int Account::get_pin() {
	return pin_;
}

char Account::get_type() {
	return type_;
}

double Account::get_balance() {
	return balance_;
}

void Account::set_name(char* name) {
	strcpy(name_, name);
}

void Account::set_type(char type) {
	type_ = type;
}

void Account::set_pin(int pin) {
	pin_ = pin;
}