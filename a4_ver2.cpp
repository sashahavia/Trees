/********************************************************/
// Assignment 4
// Aliaksandra Havia
// Trees
/********************************************************/

#include<iostream>
#include<fstream>
using namespace std;

class BinaryTree {
private:
	// Declare a structure for the Tree
	struct TreeNode {
		int value; 
		struct TreeNode *left;
		struct TreeNode *right;
	};

	TreeNode *root; 
	// Private member functions
	void insert(TreeNode *&, TreeNode *&);
	void freeTree(TreeNode *);
	void displayInOrder(TreeNode *);
	void displayPreOrder(TreeNode *);
	void displayPostOrder(TreeNode *);
	int countNodes(TreeNode *);
public:
	// Constructor
	BinaryTree(){
		root = nullptr;
	}
	
	// Binary tree operations
	void insertNode(int);
	void freeTree(){freeTree(root); root = nullptr;};
	void displayInOrder(){displayInOrder(root);};
	void displayPreOrder(){displayPreOrder(root);};
	void displayPostOrder(){displayPostOrder(root);};
	int countNodes(){ return countNodes(root);};

};

void BinaryTree::insertNode(int num){
	TreeNode *newNode;
	newNode = new TreeNode;
	newNode->value = num;
	newNode->left = newNode->right = nullptr;
	insert(root, newNode);
}

void BinaryTree::insert(TreeNode *&nodePtr, TreeNode *&newNode){
	if (nodePtr == nullptr){
		// cout << "new" << endl;
		nodePtr = newNode;
	} else if (newNode->value < nodePtr->value){
		insert(nodePtr->left, newNode);
	} else if (newNode->value > nodePtr->value){
		insert(nodePtr->right, newNode);
	} else {
		cout << "Duplicate " << endl;
	} 
}

void BinaryTree::freeTree(TreeNode *root){
  if (root != NULL) {
  		if(root->left)
			freeTree(root->left);
		if(root->right)
			freeTree(root->right);
		delete root;
	}

}

void BinaryTree::displayInOrder(TreeNode *nodePtr){
	if (nodePtr){
		displayInOrder(nodePtr->left);
		cout << nodePtr->value << " ";
		displayInOrder(nodePtr->right);
	}
}

void BinaryTree::displayPreOrder(TreeNode *nodePtr){
	if (nodePtr){
		cout << nodePtr->value << " ";
		displayInOrder(nodePtr->left);
		displayInOrder(nodePtr->right);
	}
}

void BinaryTree::displayPostOrder(TreeNode *nodePtr){
	if (nodePtr){
		displayInOrder(nodePtr->left);
		displayInOrder(nodePtr->right);
		cout << nodePtr->value << " ";
	}
}

int BinaryTree::countNodes( TreeNode *root ) {
    // Count the nodes in the binary tree to which
    // root points, and return the answer.
    if ( root == NULL )
        return 0;  // The tree is empty.  It contains no nodes.
    else {
        int count = 1;   // Start by counting the root.
        count += countNodes(root->left);  // Add the number of nodes in the left subtree.
		count += countNodes(root->right); // Add the number of nodes in the right subtree.
        return count;  // Return the total.
    }
 } // end countNodes()

void processTree(BinaryTree tree){
	int total = tree.countNodes();
	if(total == 0){
		cout << "Tree is empty" << endl;
	}else{
		cout << "\nTotal number of nodes " << total << endl;
		cout << "\nIn order" << endl;
		tree.displayInOrder();
		cout << "\nPre order" << endl;
		tree.displayPreOrder();
		cout << "\nPost order" << endl;
		tree.displayPostOrder();
		cout << endl;
	}
}


int main(){
	ifstream input("data.txt");
	BinaryTree tree;
	int n;
	if(input.is_open()){
		while( !input.eof()){
			input >> n;
			while(n != -999){
				cout << n << " ";
				tree.insertNode(n);
				input >> n;
			}
			if(n == -999){
				processTree(tree);
				tree.freeTree();
			}
			
		}	
	}
	return 0;
}
