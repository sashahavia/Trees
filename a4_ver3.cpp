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
	int findSmallestP(TreeNode *);
	void removeRootMatch();
	void removeMatch(TreeNode *, TreeNode *, bool);
	void removeNode(int, TreeNode *);
	void displayInOrder(TreeNode *);
	void displayPreOrder(TreeNode *);
	void displayPostOrder(TreeNode *);
	int countNodes(TreeNode *);
	TreeNode *returnNodeP(int, TreeNode *);
public:
	// Constructor
	BinaryTree(){
		root = nullptr;
	}
	
	// Binary tree operations
	void insertNode(int);
	void freeTree(){freeTree(root); root = nullptr;};
	int findSmallest();
	void remove(int);
	void displayInOrder(){displayInOrder(root);};
	void displayPreOrder(){displayPreOrder(root);};
	void displayPostOrder(){displayPostOrder(root);};
	int countNodes(){ return countNodes(root);};
	int returnRootNum();
	void countChildren(int);
	TreeNode *returnNode(int);
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
  		if(root->left != NULL)
			freeTree(root->left);
		if(root->right != NULL)
			freeTree(root->right);
		cout << "Deleting the node containing number " << root->value << endl;
		delete root;
	}

}

int BinaryTree::findSmallest(){
	return findSmallestP(root);
}

int BinaryTree::findSmallestP(TreeNode *nodePtr){
	if(root == NULL){
		cout << "The tree is empty.\n";
		return -1000;
	} else {
		if(nodePtr->left != NULL){
			return findSmallestP(nodePtr->left);
		} else {
			return nodePtr->value;
		}
	}
}

void BinaryTree::remove(int num){
	removeNode(num, root);
}

void BinaryTree::removeNode(int num, TreeNode *parent){
	if(root != NULL){
		if(root->value == num){
			removeRootMatch();
		} else {
			if(num < parent->value && parent->left != NULL){
				parent->left->value == num ?
				removeMatch(parent, parent->left, true):
				removeNode(num, parent->left);
			}else if(num > parent->value && parent->right != NULL){
				parent->right->value == num ?
				removeMatch(parent, parent->right, false):
				removeNode(num, parent->right);
			} else {
				cout << "The number " << num << " was not found\n";
			}
		}
	} else {
		cout << "The tree is empty\n";
	}

}

void BinaryTree::removeRootMatch(){
	if(root != NULL){
		TreeNode* delPtr = root;
		int rootNum = root->value;
		int smallestInRightSubTree;
		if(root->left == NULL && root->right == NULL){
			// case 0 - 0 children
			root = NULL;
			delete delPtr;

		} else if(root->left == NULL && root->right != NULL){
			// case 1 - 1 child
			root = root->right;
			delPtr->right = NULL;
			delete delPtr;
			cout << "The root node with number " << rootNum << " was deleted. " <<
					"The new root contains number " << root->value << endl;
		} else if(root->right == NULL && root->left != NULL){
			root = root->left;
			delPtr->left = NULL;
			delete delPtr;
			cout << "The root node with number " << rootNum << " was deleted. " <<
					"The new root contains number " << root->value << endl;
		} else {
			// case 2 - 2 children
			smallestInRightSubTree = findSmallestP(root->right);
			removeNode(smallestInRightSubTree, root);
			root->value = smallestInRightSubTree;
			cout << "The root number containing number " << rootNum <<
					" was overwritten with number " << root->value << endl;
		}	
	} else {
		cout << "Can not remove root. The tree is empty.\n";
	}
}

void BinaryTree::removeMatch(TreeNode *parent, TreeNode *match, bool left){
	if(root != NULL){
		TreeNode *delPtr;
		int matchNum = match->value;
		int smallestInRightSubTree;

		// case 0 - 0 children
		if(match->left == NULL && match->right == NULL){
			delPtr = match;
			left == true ? parent->left = NULL : parent->right = NULL;
			delete delPtr;
			cout << "The node conatining the number " << matchNum <<
					" was removed.\n";
		} else if(match->left == NULL && match->right != NULL){
			// case 1 - 1 child
			left == true ? parent->left = match->right : parent->right = match->right;
			match->right = NULL;
			delPtr = match;
			delete delPtr;
			cout << "The node conatining the number " << matchNum <<
					" was removed.\n";
		} else if(match->left != NULL && match->right == NULL){
			// case 1 - 1 child
			left == true ? parent->left = match->left : parent->right = match->left;
			match->left = NULL;
			delPtr = match;
			delete delPtr;
			cout << "The node conatining the number " << matchNum <<
					" was removed.\n";
		} else {
			// case 2 - 2 children
			smallestInRightSubTree = findSmallestP(match->right);
			removeNode(smallestInRightSubTree,match);
			match->value = smallestInRightSubTree;
		}
	}else{
		cout << "Can not remove match. The tree is empty.\n";
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

BinaryTree::TreeNode *BinaryTree::returnNode(int num){
 	 return returnNodeP(num, root);
}

BinaryTree::TreeNode *BinaryTree::returnNodeP(int num, TreeNode *nodePtr){
	if(nodePtr != NULL){
		if(nodePtr->value == num){
			return nodePtr;
		} else {
			if(num < nodePtr->value){
				return returnNodeP(num, nodePtr->left);
			} else {
				return returnNodeP(num, nodePtr->right);
			}
		}
	} else {
		return NULL;
	}
}

int BinaryTree::returnRootNum(){
 	if(root != NULL){
 		return root->value;
 	} else {
 		return -1000;
 	}
}

void BinaryTree::countChildren(int num){
 	TreeNode *nodePtr = returnNode(num);
 	if(nodePtr != NULL){
 		cout << "Parent node = " << nodePtr->value << endl;

 		nodePtr->left == NULL ?
 		cout << "Left Child is = NULL\n":
 		cout << "Left Child = " << nodePtr->left->value << endl;
 		
 		nodePtr->right == NULL ?
 		cout << "Right Child is = NULL\n":
 		cout << "Right Child = " << nodePtr->right->value << endl;
 	} else {
 		cout << "Number " << num << " is not in the tree\n";
 	}
}

void processTree(BinaryTree tree){
	int total = tree.countNodes();
	if(total == 0){
		cout << "No nodes in the tree" << endl;
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
	tree.countChildren(tree.returnRootNum());
	total = 0;
}

void manipulate(BinaryTree &tree, int set){
	switch(set){
		case 0:
			cout << "Tree 0" << endl;
			cout << "Inserting 21\n";
			tree.insertNode(21);
			cout << "Deleting 1\n";
			tree.remove(1);
			cout << "Inserting 0\n";
			tree.insertNode(0);
			tree.remove(10);
			tree.remove(11);
			tree.remove(5);
			tree.remove(2);
			cout << "Inserting 10\n";
			tree.insertNode(10);
			processTree(tree);
			break;
		case 1:
			cout << "Tree 1" << endl;
			cout << "Deleting 3\n";
			tree.remove(3);
			cout << "Deleting 1\n";
			tree.remove(1);
			processTree(tree);
			break;
		case 2:
			cout << "Tree 2" << endl;
			cout << "Deleting 15\n";
			tree.remove(1);
			cout << "Inserting 30\n";
			tree.insertNode(30);
			cout << "Inserting 5\n";
			tree.insertNode(5);
			cout << "Inserting 10\n";
			tree.insertNode(10);
			cout << "Inserting 20\n";
			tree.insertNode(20);
			cout << "Deleting 20\n";
			tree.remove(20);
			cout << "Deleting 10\n";
			tree.remove(10);
			cout << "Deleting 5\n";
			tree.remove(5);
			cout << "Deleting 15\n";
			tree.remove(15);
			cout << "Deleting 30\n";
			tree.remove(30);
			processTree(tree);
			break;
		case 3:
			cout << "Tree 3" << endl;
			cout << "Deleting 2\n";
			tree.remove(2);
			processTree(tree);
			break;
		case 4:
			cout << "Tree 4" << endl;
			cout << "Deleting 37\n";
			tree.remove(37);
			cout << "Deleting 15\n";
			tree.remove(15);
			cout << "Inserting 40\n";
			tree.insertNode(40);
			cout << "Inserting 99\n";
			tree.insertNode(99);
			processTree(tree);
			break;
		case 5:
			cout << "Tree 5" << endl;
			break;
		case 6:
			cout << "Tree 6" << endl;
			break;
	}
}


int main(){
	ifstream input("data.txt");
	BinaryTree tree;
	int n;
	int set = 0;
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
				manipulate(tree,set);
				tree.freeTree();
				set++;
				cout << endl;
			}
			
		}	
	}
	return 0;
}
