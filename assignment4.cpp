#include<iostream>
using namespace std;
class contact{
private:
	int** number;
	int *size;
	string email;
	string postal_address;
	string name;
public:
	contact() {
		number = nullptr;
		size = nullptr;
		name = "";
		postal_address = "";
		email = "";
	}

	contact(string nem) {
		name = nem;
		size = new int [4]();
		number = new int*[4];
		string list[4] = {"mobile","work","home","other"};
		for (int i = 0; i < 4; i++) {
			cout << "How many digits do you need for " << list[i] << " number: ";
			cin >> size[i];

			cout << size[i];
			number[i] = new int[size[i]];
			cout << "Enter number: ";
			for (int j = 0; j < size[i]; j++) {
				cin >> number[i][j];
			}
			
		}
		char choice = ' ';
		cout << "Do you want to add an email address? (y/n): ";
		cin >> choice;
		if (choice == 'y') {
			cout << "Enter email address: ";
			cin >> email;
		}


		cout << "Do you want to add a postal address? (y/n): ";
		cin >> choice;
		if (choice == 'y') {
			cout << "Enter postal address: ";
			cin >> postal_address;
		}


		cout << endl << "User " << name << " has  been created!" << endl;

	}

	contact (contact& b) noexcept{ //cpy
		name = b.name;
		if (b.name.empty()) {
			size = nullptr;
			number = nullptr;
		}
		else {
			size = new int[4];
			number = new int* [4]();
			for (int i = 0; i < 4; i++) {
				size[i] = b.size[i];

				number[i] = new int[size[i]];
				for (int j = 0; j < size[i] && j < b.size[i]; j++) {
					number[i][j] = b.number[i][j];
				}
			}
		}


		email = b.email;

		postal_address = b.postal_address;
	}


	contact& operator=(contact& b) {
		if (this == &b) {
			return *this;
		}

		if (b.name.empty()) {
			size = nullptr;
			number = nullptr;
		}
		else {
			name = b.name;
			size = new int[4];
			number = new int* [4];
			for (int i = 0; i < 4; i++) {
				size[i] = b.size[i];

				number[i] = new int[size[i]];
				for (int j = 0; j < size[i] && j < b.size[i]; j++) {
					number[i][j] = b.number[i][j];
				}
			}

		}


		email = b.email;

		postal_address = b.postal_address;
		return *this;
	}


	contact (contact&& b) noexcept{
		name = b.name;
		b.name = "";

		size = b.size;
		b.size = nullptr;


		number = b.number;
		b.number = nullptr;

		email = b.email;
		b.email = "";

		postal_address = b.postal_address;
		postal_address = "";
	}

	contact& operator=(contact&& b) noexcept {
		if (this == &b) {
			return *this;
		}


		name = b.name;
		b.name = "";

		size = b.size;
		b.size = nullptr;


		number = b.number;
		b.number = nullptr;

		email = b.email;
		b.email = "";

		postal_address = b.postal_address;
		postal_address = "";

		return *this;
	}


	bool operator==(contact&& b) {
		bool same = true;
		if (name == b.name) {
			if (name != "unknown") {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < size[i]; j++) {
						if (number[i][j] != b.number[i][j]) {
							same = false;
							break;
						}
					}
					if (!same) {
						break;
					}
				}
			}
		}
		else {
			same = false;
		}

		return same;
	}

	bool operator==(contact& b) {
		bool same = true;
		if (name == b.name) {
			if (name != "unknown") {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < size[i]; j++) {
						if (number[i][j] != b.number[i][j]) {
							same = false;
							break;
						}
					}
					if (!same) {
						break;
					}
				}
			}
		}
		else {
			same = false;
		}

		return same;
	}

	void print() {
		if (!(this->name.empty())) {
			cout << endl << name << ":\nNumbers:\n";
			string list[4] = { "mobile","work","home","other" };
			for (int i = 0; i < 4; i++) {
				cout << list[i] << ": ";
				for (int j = 0; j < size[i]; j++) {
					cout << number[i][j];
				}
				cout << endl;
			}

			if (!email.empty())cout << endl << "Email address: " << email;
			if (!postal_address.empty())cout << "\nPostal address: " << postal_address << endl;
		}
	}


	~contact() {
		if (!name.empty()) {
			for (int i = 0; i < 4; i++) {
				delete[] number[i];
			}
			delete[] number;

			delete[] size;
		}
	}
};

class phonebook {
private:
	contact* list;
	int capacity;
	int contacts;
public:
	phonebook() {
		list = new contact[10];
		capacity = 5;
		contacts = 5;
	}

	phonebook(phonebook& b) { //cpy
		capacity = b.capacity;
		list = new contact[capacity];
		contacts = b.contacts;
		for (int i = 0; i < b.contacts && i < contacts && contacts <= capacity; i++) {
			list[i] = b.list[i];
		}
	}

	phonebook& operator=(phonebook& b) { //cpy

		if (this == &b) {
			return *this;
		}
		delete[] list;
		capacity = b.capacity;
		list = new contact[capacity];
		contacts = b.contacts;
		for (int i = 0; i < b.contacts && i < contacts && contacts <= capacity; i++) {
			list[i] = b.list[i];
		}
		return *this;
	}

	phonebook(phonebook&& b) noexcept { //move
		capacity = b.capacity;
		b.capacity = 0;

		contacts = b.contacts;
		b.contacts = 0;

		list = b.list;
		b.list = nullptr;
	}

	phonebook operator=(phonebook&& b) noexcept{ //move
		capacity = b.capacity;
		b.capacity = 0;

		contacts = b.contacts;
		b.contacts = 0;

		delete[] list;
		list = b.list;
		b.list = nullptr;

		return *this;
	}

	void checksize() {
		if (contacts >= capacity) {
			int new_capacity = capacity == 0 ? 1 : capacity * 2;
			contact* new_list = new contact[new_capacity];

			for (int i = 0; i < contacts && i < new_capacity; i++) {
				new_list[i] = list[i];
			}
			delete[] list;
			list = new contact[new_capacity];
			for (int i = 0; i < contacts && i < new_capacity; i++) {
				list[i] = new_list[i];
			}
			capacity = new_capacity;

			delete[] new_list;
		}

	}


	void operator+(contact& a) {
		checksize();
		list[contacts++] = a;

		cout << endl << "Contact has been added";
	}

	void operator-(contact& a) {
		bool deleted = false;
		for (int i = 0; i < contacts; i++) {
			if (list[i] == a) {
				deleted = true;
			}

			if (deleted && i < contacts - 1) {
				list[i] = list[i + 1];
			}
		}
		if (deleted) {
			contacts--;
		}

		cout << endl << "contact has been removed";
	}
	~phonebook() {
		delete[] list;
	}

	void get() {
		cout << endl << "Contacts: " << contacts << endl;
		cout << "Capacity: " << capacity << endl;

		for (int i = 0; i < contacts; i++) {
			cout << "Contact" << i + 1 << ":\n";
			list[i].print();
			cout << endl;
		}

	}


};


int main() {
	contact c1("abdul");
	contact cecil("cecil");
	c1.print();

	phonebook sig;

	sig.get();

	sig + c1;

	sig.get();

	sig + cecil;

	sig.get();


}
