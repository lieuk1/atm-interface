/******************************
* Name          : Kristella Lieu
* Date Created  : July 5, 2020
* Last Modified : July 18, 2020
*
* Project	    : ATM Interface
*******************************/

/******************************
*		  HEADER FILE
*******************************/

#ifndef ATMCLASS_H
#define ATMCLASS_H

#include <iostream>
using namespace std;

class Account {
	public:
		void create_account(); // INPUTS ACC INFO

		void deposit(double depositAmt); // DEPOSITS INTO BALANCE
		void withdraw(double withdrawAmt); // WITHDRAWS FROM BALANCE

		void show_acc(); // PRINTS ALL ACC INFO
		string get_name(char* name);
		int get_pin();
		char get_type(); 
		double get_balance();

		void set_name(char* name);
		void set_type(char type);
		void set_pin(int pin);

	private:
		// MEMBER VARIABLES HAVE TRAILING _
		char name_[50]; // OWNER OF ACCOUNT
		int pin_; // PERSONAL PIN # BETWEEN 5-10 DIGITS
		char type_; // CHECKING OR SAVINGS
		double balance_;
};

#endif