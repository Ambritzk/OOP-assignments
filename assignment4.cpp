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
			cout << "how many digits do you need for " << list[i] << " number: ";
			cin >> size[i];

			cout << size[i];
			number[i] = new int[size[i]];
			cout << "enter number: ";
			for (int j = 0; j < size[i]; j++) {
				cin >> number[i][j];
			}
			
		}
		char choice = ' ';
		cout << "do you want to add an email address? (y/n): ";
		cin >> choice;
		if (choice == 'y') {
			cout << "enter email address: ";
			cin >> email;
		}


		cout << "do you want to add a postal address? (y/n): ";
		cin >> choice;
		if (choice == 'y') {
			cout << "enter postal address: ";
			cin >> postal_address;
		}


		cout << endl << "user " << name << " has  been created!" << endl;

	}


	bool AreEqual(int a[], int elements) {
		if (name.empty()) {
			return false;
		}
		for (int i = 0; i < 4; i++) {
			if (elements != size[i]) {
				continue;
			}
			bool same = true;
			for (int j = 0; j < size[j]; j++) {
				if (a[j] != number[i][j]) {
					same = false;
					break;
				}
			}

			if (same) {
				return same;
			}
		}
		return false;
	}

	string getName() {
		return name;
	}
	bool operator==(string& a) {
		if (a.empty()) {
			return false;
		}
		string first;
		string last;
		bool frst = true;
		for (int i = 0; frst; i++) {

			if (a[i] == '*' && i < a.length()) {
				first = a.substr(0, i);
				last = a.substr(i + 1, (a.length() - first.length() - 1));
				frst = false;
			}																				 

		}
		if (name.length() < first.length() + last.length()) {
						return false;
					
		}
		bool conditionOne = name.substr(0, first.length()) == first;		// ni*er
		bool conditionTwo = name.substr(name.length() - last.length()) == last;
		return (conditionOne && conditionTwo);
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
		b.postal_address = "";

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
			cout << endl << name << ":\nnumbers:\n";
			string list[4] = { "mobile","work","home","other" };
			for (int i = 0; i < 4; i++) {
				if (number[i] == nullptr) {
					continue;
				}
				cout << "\t" << list[i] << ": ";
				for (int j = 0; j < size[i]; j++) {
					cout << number[i][j];
				}
				cout << endl;
			}

			if (!email.empty())cout << endl << "email address: " << email;
			if (!postal_address.empty())cout << "\npostal address: " << postal_address << endl;
		}
		else {
			cout << "empty\n";
		}
	}


	~contact() {
		if (!name.empty()) {
			for (int i = 0; i < 4; i++) {
				if (number[i] != nullptr) {
					delete[] number[i];
				}

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
		capacity = 10;
		contacts = 4;
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
		if (this == &b) {
			return *this;
		}

		capacity = b.capacity;
		b.capacity = 0;

		contacts = b.contacts;
		b.contacts = 0;

		delete[] list;
		list = b.list;
		b.list = nullptr;

		return *this;
	}

	void expand() {
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

	void shrink() {
		if (contacts < capacity / 2) {
			int new_capacity = capacity / 2;
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
		expand();
		list[contacts++] = a;

		cout << endl << "contact has been added";
	}

	void operator-(contact& a) {
		bool deleted = false;
		for (int i = 0; i < contacts; i++) {
			if (list[i] == a) {
				for (int j = i; j < contacts - 1; j++) {
					list[j] = list[j + 1];
				}
				contacts--;
				shrink();
				cout << "\ncontact has been removed";
				return;
			}
		}
		cout << endl << "contact has been removed";
	}

	
	~phonebook() {
		delete[] list;
	}
	

	void get() {
		cout << endl << "contacts: " << contacts << endl;
		cout << "capacity: " << capacity << endl;
		cout << endl << "------------------------";
		
		cout << "Contacts:\n";

		for (int i = 0; i < contacts; i++) {
			cout << i + 1 << ": ";
			cout << list[i].getName();
			cout << endl;
		}
		int choice = 0;
		cout << "Enter the contact that you want to view information for:";
		cin >> choice;

		if (choice > 0 && choice <= contacts) {
			list[choice + 1].print();
		}


	}

	void searchbycontactname(string nem) {
		for (int i = contacts - 1; i >= 0; i--) {
			if (!(nem.empty())) {
				if (list[i] == nem) {
					cout << "Contact found:\n";
					list[i].print();
				}
			}
		}
	}

	void searchbycontactNumber(int a[], int size) {
		for (int i = contacts - 1; i >= 0; i--) {

			if (list[i].AreEqual(a,size)) {
				cout << "Contact found:\n";
				list[i].print();
			}
		}
	}


};


int main() {
	contact c1("abdul");
//	contact cecil("cecil");

	phonebook sig;

	sig + c1;

	sig.get();

	int a[] = { 1,2,3,4,5 };
	sig.searchbycontactNumber(a, 5);

	cout << "Now searching name:\n";
	sig.searchbycontactname("a*l");



}
