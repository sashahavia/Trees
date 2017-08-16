#include<iostream>
#include<fstream>
using namespace std;

struct Node {
	int data;
	Node *left;
	Node *right;

};

Node* insert(Node *root, int data) {
	if (root == NULL) {
		Node *newNode = new Node();
		newNode->data = data;
		newNode->left = newNode->right = NULL;
		root = newNode;
		cout << "Node inserted: " << root->data << endl;
		return root;
	}
	else if (root->data <= data) {
		root->left = insert(root->left, data);
	}
	else {
		root->right = insert(root->right, data);
	}
	return root;
}

void preorder(Node *root) {
	if (root != NULL) {
		if (root->data == -1) {
			preorder(root->left);
			preorder(root->right);
		}
		else {
			cout << root->data << " ";
			preorder(root->left);
			preorder(root->right);
		}
	}
}

void inorder(Node *root) {
	if (root != NULL) {
		inorder(root->left);
		if (root->data == -1)
			inorder(root->right);
		else {
			cout << root->data << " ";
			inorder(root->right);
		}
	}
}

void postorder(Node *root) {
	if (root != NULL) {
		if (root->data == -1) {
			postorder(root->left);
			postorder(root->right);
		}
		else {
			postorder(root->left);
			postorder(root->right);
			cout << root->data << " ";
		}
	}
}

int count(Node *root) {
	if (root == NULL) return 0;
	else {
		return 1 + count(root->left) + count(root->right);
	}
}

void children(Node *root) {
	if (root != NULL) {
		children(root->left);
		children(root->right);
		if (root->left == NULL && root->right == NULL) cout << root->data << ": No children" << endl;
		else if (root->left != NULL && root->right != NULL) cout << root->data << ": 2 children" << endl;
		else cout << root-> data << ": 1 child" << endl;
	}
}

Node *search(Node *root, int data) {
	if (root->data == data) {
		cout << "Node deleted: " << root->data << endl;
		root->data = -1;
		return root;
	}
	else if (root->data > data) {
		if (root->right !=NULL) { 
			root = root->right; 
			return search(root, data); 
		}
	}
	else if (root->data < data) {
		if (root->left !=NULL) { 
			root = root->left; 
			return search(root, data); 
		}
	}
	else {
		cout << "Node not found in search " << endl;
		return NULL;
	}
	cout << "Not Found" << endl;
	return root;
}

void deleteTree(Node *root) {
	if (root != NULL) {
		deleteTree(root->left);
		deleteTree(root->right);
		delete(root);
	}
}

int main() {

	ifstream input("data.txt");
	Node *root;
	root = NULL;
	int temp;
	if (input.is_open()) {
		while (!input.eof()) {
			input >> temp;
			if (temp == -999) {
				break;
			}
			else {
				root = insert(root, temp);
			}
		}
	}
	else {
		cout << "No File" << endl;
	}
	cout << "Preorder: " << endl;
	preorder(root);
	cout << endl;
	cout << "Inorder: " << endl;
	inorder(root);
	cout << endl;
	cout << "Postorder: " << endl;
	postorder(root);
	cout << endl << "Total Nodes: " << count(root) << endl;
	children(root);

	insert(root, 21);
	Node *t = root;
	t = search(root, 11);
	t = search(root, 1);
	t = search(root, 5);
	insert(root, 0);
	t = search(root, 2);
	t = search(root, 10);
	insert(root, 10);
	cout << "Preorder: " << endl;
	preorder(root);
	cout << endl;
	cout << "Inorder: " << endl;
	inorder(root);
	cout << endl;
	cout << "Postorder: " << endl;
	postorder(root);
	cout << endl;
	cout << "Total nodes: " << count(root) << endl;
	children(root);

	deleteTree(root);
	cout << "Tree has been deleted" << endl;

	Node *root1;
	input >> temp;
	while (temp != -999) {
		root1 = insert(root1, temp);
		//cout << temp << endl;
		input >> temp;
	}
	preorder(root1);

	input.close();

	return 0;
}
