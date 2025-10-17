#include <iostream>
#include<string>
#include<vector>
#include <fstream>
using namespace std;

template<typename T>
class BST {
private:
	class Node {
	public:
		T value;
		int key;
		Node* parent;
		Node* right;
		Node* left;

		Node() {
			value = T();
			key = -1;
			right = nullptr;
			left = nullptr;
			parent = nullptr;
		}
		Node(int key,T value) {
			this->key = key;
			this->value = value;
			right = nullptr;
			left = nullptr;
			parent = nullptr;
		}
	};


	void PreorderTraversal(Node* temp) {
		if (temp != nullptr) {
			cout << temp->value << "->";
			PreorderTraversal(temp->left);
			PreorderTraversal(temp->right);
		}

	}


	void inorderTraversal(Node* temp) {
		if (temp != nullptr) {
			inorderTraversal(temp->left);
			cout << temp->value << "->";
			inorderTraversal(temp->right);
		}

	}


	void postorderTraversal(Node* temp) {
		if (temp != nullptr) {
			postorderTraversal(temp->left);
			postorderTraversal(temp->right);
			cout << temp->value << "->";
		}
	}

	void Rotation(Node* temp) {
		//first determine whether the child is a left child or a right child


		while (temp->parent != nullptr) {
			bool left = false;
			if (temp->parent->left != nullptr && temp->parent->left == temp) {
				left = true;
			}
			else {
				left = false;
			}

			if (left) {
				if (temp->right) { // if there's a subtree, we need to merge it with the parent's.
					temp->parent->left = temp->right;
					temp->right->parent = temp->parent;
					temp->right = nullptr;
				}
				else {
					temp->parent->left = nullptr; //severs the connection of temp's parent with temp
				}
				Node* prnt = temp->parent; //make pointers for ease of use
				Node* grandprnt = prnt->parent;

				temp->right = prnt;
				if (grandprnt == nullptr) {
					temp->parent = nullptr;
					prnt->parent = temp;
					root = temp;
					break;
				}
				else {
					temp->parent = grandprnt;
					if (grandprnt->left != nullptr && grandprnt->left == prnt) {
						grandprnt->left = temp;
					}
					else {
						grandprnt->right = temp;
					}

					prnt->parent = temp;
				}


			}
			else {
				if (temp->left) {
					temp->parent->right = temp->left;
					temp->left->parent = temp->parent;
					temp->left = nullptr;
				}
				else {
					temp->parent->right = nullptr;
				}
				Node* prnt = temp->parent;
				Node* grandprnt = prnt->parent;

				temp->left = prnt;
				if (grandprnt == nullptr) {
					temp->parent = nullptr;
					prnt->parent = temp;
					root = temp;
					break;
				}
				else {
					temp->parent = grandprnt;
					if (grandprnt->right != nullptr && grandprnt->right == prnt) {
						grandprnt->right = temp;
					}
					else {
						grandprnt->left = temp;
					}

					prnt->parent = temp;
				}

			}



		}



	}

	void deleteTree(Node* temp) {
		if (temp == nullptr) {
			return;
		}


		deleteTree(temp->left);
		deleteTree(temp->right);
		delete temp;
	}


	bool isEmpty() {
		return root == nullptr;
	}


	void DeleteAndGetRight(Node* temp) {
		if (isLeaf(temp)) {
			if (temp == root) {
				delete temp;
				root = nullptr;

			}
			else {

				if (isLeftChild(temp)) {
					temp->parent->left = nullptr;
				}
				else {
					temp->parent->right = nullptr;;
				}

				delete temp;

			}


			return;
		}


		if (temp->left == NULL) {

			if (temp == root) {
				root = temp->right;
				temp->right->parent = nullptr;
				delete temp;
				return;
			}




			temp->right->parent = temp->parent;


			if (isLeftChild(temp)) {
				temp->parent->left = temp->right;
			}
			else {
				temp->parent->right = temp->right;
			}

			delete temp;
			return;


		}
		else if (temp->right == NULL) {

			if (temp == root) {
				root = temp->left;
				temp->left->parent = nullptr;
				delete temp;
				return;
			}




			temp->left->parent = temp->parent;


			if (isLeftChild(temp)) {
				temp->parent->left = temp->left;
			}
			else {
				temp->parent->right = temp->left;
			}

			delete temp;
			return;
		}

		else {

			Node* rightptr = temp->right;
			while (rightptr->left != nullptr) {
				rightptr = rightptr->left;
			}


			temp->key = rightptr->key;
			temp->value = rightptr->value;

			if (rightptr->parent == temp) {
				temp->right = rightptr->right;
				if (rightptr->right) {
					rightptr->right->parent = temp;
				}
			}

			else {
				rightptr->parent->left = rightptr->right;
				if (rightptr->right) {
					rightptr->right->parent = rightptr->parent;
				}
			}

			delete rightptr;

		}



	}

	void levelMembers(vector<T>* list, Node* temp, int lvl, int desired_lvl) {
		if (temp == nullptr) {
			return;
		}

		if (lvl == desired_lvl) {
			list->push_back(temp->value);
			return;
		}


		levelMembers(list, temp->left,lvl + 1, desired_lvl);

		levelMembers(list, temp->right,lvl + 1, desired_lvl);




	}

	
	Node* root;


public:





	BST() {
		root = NULL;
	}


	void PreorderDisplay() {

		cout << endl;
		if (isEmpty()) {
			cout << "Tree is empty";
			return;
		}
		PreorderTraversal(root);
	}

	void InorderDisplay() {
		cout << endl;
		if (isEmpty()) {
			cout << "Tree is empty";
			return;
		}
		inorderTraversal(root);
	}
	void PostOrderDisplay() {
		cout << endl;
		if (isEmpty()) {
			cout << "Tree is empty";
			return;
		}
		postorderTraversal(root);
	}


	bool isLeaf(Node* temp) {
		return (temp->left == NULL && temp->right == NULL);
	}

	bool isLeftChild(Node* temp) {
		if (temp->parent == NULL) {
			return false;
		}


		return temp->parent->left == temp;
	}

	bool isRightChild(Node* temp) {
		if (temp->parent == NULL) {
			return false;
		}


		return temp->parent->right == temp;
	}






	bool Insert(int key,T value) {
		if (root == nullptr) {
			root = new Node(key, value);
			return true;
		}

		Node* temp = root;

		while (true) {
			if (key > temp->key) {
				if (temp->right != nullptr) {
					temp = temp->right;
				}
				else {
					temp->right = new Node(key, value);
					temp->right->parent = temp;
					Rotation(temp->right);
					return true;
				}
			}
			else if (key < temp->key) {
				if (temp->left != nullptr) {
					temp = temp->left;
				}
				else {
					temp->left = new Node(key,value);
					temp->left->parent = temp;
					Rotation(temp->left);
					return true;
				}
			}
			else {
				cout << endl << "Value already exists inside the tree";
				return false;
			}
		}
	}
	bool InsertWithoutRotation(int key,T value) {
		if (root == nullptr) {
			root = new Node(key,value);
			return true;
		}

		Node* temp = root;

		while (true) {
			if (key > temp->key) {
				if (temp->right != nullptr) {
					temp = temp->right;
				}
				else {
					temp->right = new Node(key,value);
					temp->right->parent = temp;
					return true;
				}
			}
			else if (key < temp->key) {
				if (temp->left != nullptr) {
					temp = temp->left;
				}
				else {
					temp->left = new Node(key,value);
					temp->left->parent = temp;
					return true;
				}
			}
			else {
				cout << endl << "Value already exists inside the tree";
				return false;
			}
		}
	}




	T* searchElement(int key) {
		if (isEmpty()) {
			cout << endl << "Tree is empty";
			return nullptr;
		}
		Node* temp = root;
		while (true) {
			if (temp == nullptr) {
				return nullptr;
			}



			if (key > temp->key) {
				temp = temp->right;
			}
			else if (key < temp->key) {
				temp = temp->left;
			}
			else {
				Rotation(temp);
				return &root->value;
			}
		}



	}


	bool Delete(int key) {
		if (isEmpty()) {
			cout << endl << "Tree is empty";
			return false;
		}

		Node* temp = root;

		while (temp != nullptr) {
			if (key > temp->key) {
				temp = temp->right;
			}
			else if (key < temp->key) {
				temp = temp->left;
			}
			else {
				DeleteAndGetRight(temp);
				return true;
			}


		}
		return false;
	}


	vector<T> LevelWiseMembers(int desired_lvl) {
		vector<T> result_list;
		if (root == nullptr) {
			return result_list;
		}
		levelMembers(&result_list, root, 0,desired_lvl);
		return result_list;
	}








	~BST() {
		deleteTree(root);
	}
};

class StudentList {
private:
	class StudentNode {
	public:
			int rollnumber;
			string firstname;
			string lastname;
			int batch;
			string department;
			float cgpa;
			friend class StudentList;
//			friend ostream& operator<<(ostream& os, const StudentList::StudentNode& obj);


			StudentNode() {
				rollnumber = 0;
				firstname = "";
				batch = 0;
				cgpa = 0;
				lastname = "";
				department = "";
			}
			StudentNode(int roll, string first, string last, int batch, string dept, float cgpa) {
				rollnumber = roll;
				firstname = first;
				lastname = last;
				this->batch = batch;
				department = dept;
				this->cgpa = cgpa;
			}


	};




	BST<StudentNode> studentlist;
public:
	friend ostream& operator<<(ostream& os, const StudentList::StudentNode& obj);
	void InsertStudentNode(int roll, string first, string last, int batch, string dept, float cgpa) {
		studentlist.Insert(roll,StudentNode(roll, first, last, batch, dept, cgpa));
	}


	void DeleteStudent(int roll) {
		if (studentlist.Delete(roll)) {
			cout << endl << "Student removed";
		}
		else {
			cout << endl << "Student does not exist";
		}
	}

	void SearchStudent(int roll) {
		StudentNode* ptr = studentlist.searchElement(roll);
		if (ptr == nullptr) {
			cout << endl << "Student not found";
		}
		else {
			cout << ptr;
		}
	}

	void PrintAllStudents() {
		studentlist.InorderDisplay();
	}

	bool UpdateStudentData(int OldRollno, int NewRollno, string newfirstname, string newlastname, int newbatch, string newDepartment, float newcgpa) {
		//first we'll check if the student even exists or not
		//Then we'll check if the new rollno is the same as the previous or not
		//in case of the latter, we'll delete that node and insert a new node

		StudentNode* ptr = studentlist.searchElement(OldRollno);
		if (ptr == nullptr) {
			return false;
		}
		else {
			if (OldRollno == NewRollno) {
				ptr->firstname = newfirstname;
				ptr->lastname = newlastname;
				ptr->batch = newbatch;
				ptr->department = newDepartment;
				ptr->cgpa = newcgpa;
			}
			else {
				studentlist.Delete(OldRollno);
				studentlist.Insert(NewRollno, StudentNode(NewRollno,newfirstname, newlastname, newbatch,newDepartment, newcgpa));
			}
			return true;



		}



	}


};
 
void Inputvalidation(int& var) {
	while (!(cin >> var)) {
		cout << endl << "Invalid Roll number.";
		cout << endl << "Please enter an integer type data: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

void Inputvalidation(float& var) {
	while (!(cin >> var)) {
		cout << endl << "Invalid Roll number.";
		cout << endl << "Please enter an integer type data: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}


void Menu(StudentList& list) {
	char choice;
	do {
		cout << endl << "1)Press I to insert a new student";
		cout << endl << "2)Press D to remove a student";
		cout << endl << "3)Press U to update the data of a student";
		cout << endl << "4)Press P to print the names of students in the order of their roll numbers";
		cout << endl << "5)Press E to quit";
		cout << endl << "Enter: ";
		cin >> choice;

		choice = toupper(choice);
		int rollnumber, batch, old, newno = -1;
		float cgpa = 0;
		string firstname = "";
		string lastname = "";
		string department = "";
		system("cls");
		switch (choice) {
		case 'I':
			
			cout << endl << "Enter first name: ";
			cin >> firstname;
			cout << "Enter last name: ";
			cin >> lastname;
			cout << "Enter roll number: ";
			Inputvalidation(rollnumber);
			cout << "Enter Batch: ";
			Inputvalidation(batch);
			cout << "Enter department: ";
			cin >> department;
			cout << "Enter cgpa: ";
			cin >> cgpa;
			list.InsertStudentNode(rollnumber, firstname, lastname, batch, department,cgpa);
			break;
		case 'P':
			list.PrintAllStudents();
			break;
		case 'U':
			cout << endl << "Enter old roll number: ";
			Inputvalidation(old);
			cout << "Enter new roll number: ";
			Inputvalidation(rollnumber);

			cout << endl << "Enter new first name: ";
			cin >> firstname;
			cout << "Enter new last name: ";
			cin >> lastname;

			cout << "Enter new Batch: ";
			Inputvalidation(batch);
			cout << "Enter new department: ";
			cin >> department;
			cout << "Enter new cgpa: ";
			cin >> cgpa;
			list.UpdateStudentData(old, newno, firstname, lastname, batch, department, cgpa);
			break;
		case 'D':
			cout << endl << "Enter the roll number of the student you want to remove: ";
			Inputvalidation(rollnumber);
			list.DeleteStudent(rollnumber);
		case 'E':
			break;
		}


	} while (toupper(choice) != 'E');
}

int main() {
	StudentList pp;
	Menu(pp);

	return 0;
}

ostream& operator<<(ostream& os, const StudentList::StudentNode& obj)
{
	os << endl << "First name: " << obj.firstname << endl << "Last name: " << obj.lastname;
	os << endl << "Roll number: " << obj.rollnumber << endl << "Batch: " << obj.batch;
	os << endl << "Department: " << obj.department << endl << "CGPA: " << obj.cgpa;
	return os;
}
