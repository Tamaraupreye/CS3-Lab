#include <iostream>
#include <string>

using namespace std;

//Node Struct
struct node {
    int value;
    node *lchild;
    node *rchild;
};

//Function creates the unbalanced BST
node* BSTInsert(node *root, int vvalue) {
    if (root==NULL) {
        node *newnode = new node;
        newnode->lchild = newnode->rchild = NULL;
        newnode->value = vvalue;
        return newnode;
    }

    if (root->value == vvalue) {
        return root;
    }

    if (vvalue < root->value) {
        root->lchild = BSTInsert(root->lchild, vvalue);
    }
    else {
        root->rchild = BSTInsert(root->rchild, vvalue);
    }

    return root;
}

/* Q-7A Section.	
   Write a recursive version of preorder function to perform the total sum of the values 
   for all the leaf nodes in the BST. (Note: You must not use any auxiliary storage). 
*/


int sum(node* root) {
	if (root == NULL) return 0;
	return sum(root->lchild) + sum(root->rchild) + root->value;
}


/* Q-7B Section.	
   Write a function that will scan through the tree and display in descending order the 
   values of the tree nodes in a linear time complexity without any auxiliary storage
*/


void descending(node* root) {
	if (root == NULL) return;
	descending(root->rchild);
	cout << root->value << " ";
	descending(root->lchild);
}


/* Q-7C.	
   Use AVL concepts to write a function that corrects the tree height to a balanced binary search tree. 
   (Hint: Rotate once and no need for checking height or balance factor).
*/


node* balance(node* root) {  // this is an LL problem
	node* temp = root;
	root = root->lchild;
	temp->lchild = root->rchild;
	root->rchild = temp;
	return root;
}


/* Q-7D.	
   After 7c, write a function to print Pre-order traversal of the balanced BST. 
*/


void preorder(node* root) {
	if (root == NULL) return;
	cout << root->value << " ";
	preorder(root->lchild);
	preorder(root->rchild);
}




int main() {
    node *root;
    root = BSTInsert(NULL, 60);
    root = BSTInsert(root, 40);
    root = BSTInsert(root, 70);
    root = BSTInsert(root, 20);
    root = BSTInsert(root, 50);
    root = BSTInsert(root, 65);
    root = BSTInsert(root, 90);
    root = BSTInsert(root, 45);
    root = BSTInsert(root, 58);
    root = BSTInsert(root, 10);
    root = BSTInsert(root, 30);
    root = BSTInsert(root, 28);
    root = BSTInsert(root, 35);
    root = BSTInsert(root, 15);
    root = BSTInsert(root, 5);

    // 7A - Call function and Display the result here.
	cout << "Sum: " << sum(root) << endl;


    // 7B - Call function and display the result of here.
	cout << "Descending: ";
	descending(root);
	cout << endl;


    // 7C - Call function for balancing the tree
	// cout << "Pre-Order before balancing: ";
	// preorder(root);
	// cout << endl;
	root = balance(root);


    // 7D - call to display the Pre-Order result of the balanced BST here.
	cout << "Pre-Order after balancing: ";
	preorder(root);
	cout << endl;
	

    return 0;
}