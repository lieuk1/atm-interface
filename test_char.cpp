#include <iostream>
#include <cstring>
using namespace std;

/*void get_name(char* name) {
	char str[50] = "Lieu";
	for(int i = 0; i < 50; i++) {
		name[i] = str[i];
	}
}*/

class Book {
	public:
		string get_title() {
			return title_;
		};
		string get_author();
		int get_isbn();

	private:
		char title_[50] = "Title";
		char author_[50];
		int isbn;
};

/*string get_name(char* name) {
	return string(name);
}*/

int main()
{

	char name[50] = "Kristella Lieu";

	//cout << name << endl;
	//get_name(name);
	//cout << name << endl;

	//cout << name[0] << endl;

	Book nevernight;
	cout<<nevernight.get_title()<<endl;

	return 0;
}

