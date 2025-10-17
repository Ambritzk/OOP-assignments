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

	void inorderTraversal(Node* temp) {
		if (temp != nullptr) {
			inorderTraversal(temp->left);
			cout << temp->value << "->";
			inorderTraversal(temp->right);
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



	int getheight(Node* temp) {
		if (temp == nullptr) {
			return 0;
		}
		
		int left = getheight(temp->left);
		int right = getheight(temp->right);

		return 1 + max(left,right);
	}
	
	Node* root;


public:





	BST() {
		root = NULL;
	}



	void InorderDisplay() {
		cout << endl;
		if (isEmpty()) {
			cout << "Tree is empty";
			return;
		}
		inorderTraversal(root);
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

	int height() {
		return getheight(root);

	}

	~BST() {
		deleteTree(root);
	}


	void DisplayLevelWiseMembers() {

		int height = this->height();

		for (int i = 0; i < height; i++) {
			vector<T> ptr = this->LevelWiseMembers(i);
			cout << endl << "Level " << i << " members: ";

			for (auto itr = ptr.begin(); itr != ptr.end(); itr++) {
				cout << *itr << " ";
			}
		}


	}
};


int main() {

	BST<int> pp;
	pp.InsertWithoutRotation(13, 13);
	pp.InsertWithoutRotation(7, 7);
	pp.InsertWithoutRotation(25, 25);
	pp.InsertWithoutRotation(39, 39);
	pp.InsertWithoutRotation(15, 15);
	pp.InsertWithoutRotation(14, 14);
	pp.InsertWithoutRotation(17, 17);
	pp.searchElement(17);


	pp.DisplayLevelWiseMembers();

	return 0;
}
