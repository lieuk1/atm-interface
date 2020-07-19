#include <iostream>
#include <fstream>
#include <limits>

#include "atm_header.h"
using namespace std;

/******************************
*	  FUNCTION DEFINITIONS
*******************************/

void file_acc(); // CREATES ACC AND WRITES TO FILE
void delete_acc(int pin); // DELETES ACC FROM FILE
void display_acc(int pin); // DISPLAYS ACC INFO
void deposit_withdraw(int option, int pin); // DEPOSITS OR WITHDRAWS AND WRITES TO FILE
void modify_acc(int option, int pin); // MODIFY ACC INFO AND WRITES TO FILE

/******************************
*			MAIN
*******************************/

int main() {
	
	int menuOpt;
	do {
		cout << "\tMAIN MENU\n";
		cout << "\t0. QUIT\n";
		cout << "\t1. CREATE ACCOUNT\n";
		cout << "\t2. DELETE ACCOUNT\n";
		cout << "\t3. EXISTING ACCOUNT\n";

		while( (cout << "Enter menu option : ") &&
			(!(cin >> menuOpt) || (menuOpt != 0 && menuOpt != 1 && menuOpt != 2 && menuOpt != 3))) {
			cout << "Invalid input. Retry.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		int pin;

		// CREATE ACCOUNT
		if(menuOpt == 1) {
			file_acc();
			cout << "Record Created.\n";
			cout << "A receipt will print for you in one moment. ";
			cout << "Take this receipt to your nearest bank with a valid ID to confirm and finalize your created bank account.\n\n";
		}
		// DELETE ACCOUNT
		else if(menuOpt == 2) {
			cout << "Enter your personal pin # : ";
			cin >> pin;
			delete_acc(pin);
			cout << "Record Deleted.\n";
			cout << "A receipt will print for you in one moment. ";
			cout << "Take this receipt to your nearest bank with a valid ID to confirm and finalize your deleted bank account.\n\n";
		}
		// USE EXISTING ACCOUNT
		else if(menuOpt == 3) {
			int menuOpt2;
			do {
				cout << "\tACCOUNT MENU\n";
				cout << "\t0. BACK\n";
				cout << "\t1. DEPOSIT AMOUNT\n";
				cout << "\t2. WITHDRAW AMOUNT\n";
				cout << "\t3. MODIFY ACCOUNT\n";

				while( (cout << "Enter menu option : ") &&
					(!(cin >> menuOpt2) || (menuOpt2 != 0 && menuOpt2 != 1 && menuOpt2 != 2 && menuOpt2 != 3))) {
					cout << "Invalid input. Retry.\n";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				switch(menuOpt2) {
					case 0:
						break;
					case 1:
						cout << "Enter your personal pin #:\n";
						cin >> pin;
						display_acc(pin);
						cout << endl;
						deposit_withdraw(1, pin);
						break;
					case 2:
						cout << "Enter your personal pin #:\n";
						cin >> pin;
						display_acc(pin);
						cout << endl;
						deposit_withdraw(2, pin);
						break;
					case 3:
						int opt;

						cout << "Enter your personal pin #:\n";
						cin >> pin;
						display_acc(pin);

						cout << "\tMODIFICATION MENU:\n";
						cout << "\t0. BACK\n";
						cout << "\t1. ACCOUNT NAME\n";
						cout << "\t2. ACCOUNT TYPE\n";
						cout << "\t3. ACCOUNT PIN\n";
						
						while( (cout << "Enter menu option : ") &&
							(!(cin >> opt) || (opt != 0 && opt != 1 && opt != 2 && opt != 3))) {
							cout << "Invalid input. Retry.\n";
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}

						if(opt == 0) {
							break;
						}
						else {
							modify_acc(opt, pin);
						}

						break;
					default:
						break;
				} // END OF SWITCH
			} while (menuOpt != 0 && menuOpt2 != 0); // END OF INNER DO WHILE
		} // END OF ELSE IF
	} while(menuOpt != 0); // END OF OUTER DO WHILE

} // MAIN END

/******************************
*			FUNCTIONS
*******************************/

void file_acc() {
	Account acc;
	acc.create_account();

	ofstream outFS;
	outFS.open("account.dat", ios::binary | ios::app);
	outFS.write(reinterpret_cast<char *> (&acc), sizeof(Account));
	outFS.close();
}

void delete_acc(int pin) {
	Account acc;

	ifstream inFS;
	ofstream outFS;

	inFS.open("account.dat", ios::binary);
	if(!inFS) {
		cout << "File could not open.\n";
		return;
	}

	outFS.open("temp.dat", ios::binary);
	inFS.seekg(0, ios::beg);

	while(inFS.read(reinterpret_cast<char *> (&acc), sizeof(Account))) {
		if(acc.get_pin() != pin) {
			outFS.write(reinterpret_cast<char *> (&acc), sizeof(Account));
		}
	}

	inFS.close();
	outFS.close();

	remove("account.dat");
	rename("temp.dat", "account.dat");
}

void display_acc(int pin) {
	Account acc;
	bool found = false;

	ifstream inFS;
	inFS.open("account.dat", ios::binary);
	if(!inFS) {
		cout << "File could not open.\n";
		return;
	}

	while(inFS.read(reinterpret_cast<char *> (&acc), sizeof(Account))) {
		if(acc.get_pin() == pin) {
			acc.show_acc();
			found = true;
		}
	}
	inFS.close();
}

void deposit_withdraw(int option, int pin) {
	Account acc;
	bool found = false;
	double amt;
	
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if(!File) {
		cout << "File could not open.\n";
		return;
	}

	while(!File.eof() && found == false) {

		File.read(reinterpret_cast<char *> (&acc), sizeof(Account));

		if(acc.get_pin() == pin) {
			if(option == 1) {
				cout << "Enter deposit amount: ";
				cin >> amt;

				if(amt < 0) {
					cout << "Invalid input. Retry.\n";
					return;
				}
				else if(amt > 2000.0) {
					cout << "The maximum deposit allowed via ATM is $2,000. Retry.\n";
					return;
				}
				else {
					acc.deposit(amt);
				}
			}
			else if(option == 2) {
				cout << "Enter withdraw amount: ";
				cin >> amt;

				double bal = acc.get_balance() - amt;
				if(bal < 0) {
					cout << "Your balance would be negative. Retry.\n";
					return;
				}
				acc.withdraw(amt);
			}

			int pos = (-1)*static_cast<int>(sizeof(acc));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&acc), sizeof(Account));
			cout << "Successful action.\n";
			acc.show_acc();
			found = true;
		}

	}

	File.close();

	if(found == false) {
		cout << "Record doesn't exist.\n";
	}

}

void modify_acc(int option, int pin) {
	Account acc;
	bool found = false;

	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if(!File) {
		cout << "File could not open.\n";
		return;
	}

	while(!File.eof() && found == false) {

		File.read(reinterpret_cast<char *> (&acc), sizeof(Account));

		if(acc.get_pin() == pin) {
			if(option == 1) {
				char name[50];
				cout << "Enter new name:\n";
				cin.ignore();
				cin.getline(name, 50);
				acc.set_name(name);
			}
			else if(option == 2) {
				char type;
				cout << "Confirm change to account type (C or S):\n";
				cin >> type;
				acc.set_type(type);
			}
			else if(option == 3) {
				int pin;
				cout << "Enter new pin: ";
				cin >> pin;
				acc.set_pin(pin);
			}

			int pos = (-1)*static_cast<int>(sizeof(acc));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&acc), sizeof(Account));
			cout << "Successful action.\n";
			acc.show_acc();
			found = true;
		}

	}

	File.close();

	if(found == false) {
		cout << "Record doesn't exist.\n";
	}

}