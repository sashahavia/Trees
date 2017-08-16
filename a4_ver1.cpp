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
	void deleteNode(int, TreeNode *&);
	void makeDeletion(TreeNode *&);
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
	void freeT(){freeTree(root);}
	void remove(int);
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
		cout << "new" << endl;
		nodePtr = newNode;
	} else if (newNode->value < nodePtr->value){
		insert(nodePtr->left, newNode);
	} else if (newNode->value > nodePtr->value){
		insert(nodePtr->right, newNode);
	} else {
		cout << "Duplicate " << endl;
	} 
}

void BinaryTree::freeT(TreeNode *root){
	if(root == nullptr)
		return;
	if (root->left != nullptr){
		freeTree(root->left);	
	}
	if (root->right != nullptr){
		freeTree(root->right);
	}
	delete root;
}

void BinaryTree::remove(int num){
	deleteNode(num, root);
}

void BinaryTree::deleteNode(int num, TreeNode *&nodePtr){
	if (num < nodePtr->value){
		deleteNode(num, nodePtr->left);
	}else if (num > nodePtr->value){
		deleteNode(num, nodePtr->right);
	} else {
		makeDeletion(nodePtr);
	}
}

void BinaryTree::makeDeletion(TreeNode *&nodePtr){
	TreeNode *tempNodePtr = nullptr;

	if(nodePtr == nullptr){
		cout << "Cannot delete empty node.\n";
	} else if (nodePtr->right == nullptr){
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->left;
		delete tempNodePtr;
	} else if (nodePtr->left == nullptr){
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->right;
		delete nodePtr;
	} else {
		// If node ahs two children
		// Move one node to the right
		tempNodePtr = nodePtr->right;
		//Go to the end left node
		while(tempNodePtr->left){
			tempNodePtr = tempNodePtr->left;
		}
		// Reattach the left subtree
		tempNodePtr->left = nodePtr->left;
		tempNodePtr = nodePtr;
		// Reattach the right subtree
		nodePtr = nodePtr->right;
		delete tempNodePtr;
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

void processTree(BinaryTree tree, int total){
	total = tree.countNodes();
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

void deleteTree(BinaryTree tree){
	tree.freeTree();
}

void manipulate(BinaryTree tree, int set){
	switch(set){
		case 0:
			cout << "Here " << endl;
			tree.insertNode(21);
			tree.remove(1);
			tree.insertNode(0);
			tree.remove(10);
			tree.remove(11);
			tree.remove(5);
			tree.remove(2);
			tree.insertNode(10);
			break;
		case 1:
			cout << "Here " << endl;
			break;
		case 2:
			cout << "Here " << endl;
			break;
		case 3:
			cout << "Here " << endl;
			break;
		case 4:
			cout << "Here " << endl;
			break;
		case 5:
			cout << "Here " << endl;
			break;
		case 6:
			cout << "Here " << endl;
			break;
	}
}

int main(){
	ifstream input("data.txt");
	BinaryTree tree;
	int n;
	int total = 0;
	int count = 0;
	int set = 0;
	if(input.is_open()){
		while( !input.eof()){
			input >> n;
			while(n != -999){
				count++;
				cout << n << " ";
				tree.insertNode(n);
				input >> n;
			}
			cout << "N " << n << endl;
			
			if(count > 0){
			processTree(tree, total);
			manipulate(tree, set);
			// processTree(tree, total);
			deleteTree(tree);
			count = 0;
			total = 0;
				
			} else {
				cout << "Tree is empty" << endl;
			}
			set++;
				
			
		}	
	}
	return 0;
}
