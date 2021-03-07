#include <iostream>
#include <cmath>
#include <queue>
#include <stack>

using namespace std;

struct Node {
	int data;
	Node * parent;
	Node * left;
	Node * right;
};

void bulo(Node * root) {  // bottom up level order traversal - from right to left, level by level from leaf to root
	queue<Node*> nodeQueue;
	stack<int> dataStack;
	Node * curr;

	nodeQueue.push(root);  // insertion to queue is O(1)
	while (!nodeQueue.empty()) {  // checking empty is O(1)
		curr = nodeQueue.front();   // checking front of queue is O(1)
		nodeQueue.pop();   // deletion from queue is O(1)
		dataStack.push(curr->data);   // insertion to stack is O(1)

		if (curr->left != NULL) nodeQueue.push(curr->left);   // insertion to queue is O(1)
		if (curr->right != NULL) nodeQueue.push(curr->right);   // insertion to queue is O(1)
	}

	// loop above has O(n) time complexity where n is number of elements in tree because that's the number of things ever in the node queue

	while (!dataStack.empty()) {  // checking empty is O(1)
		cout << dataStack.top() << " ";   // checking top of stack is O(1)
		dataStack.pop();   // deletion from stack is O(1)
	}

	// loop above has O(n) time complexity where n is number of elements in tree because that's the number of things ever in the data stack
	cout << endl;
}


void insert(Node * root, int val) {
	if (val > root->data) {
		if (root->right == NULL) {
			root->right = new Node{val, root, NULL, NULL};
			return;
		}
		return insert(root->right, val);
	}

	if (val < root->data) {
		if (root->left == NULL) {
			root->left = new Node{val, root, NULL, NULL};
			return;
		}
		return insert(root->left, val);
	}
}

Node * createBST(int arr[], int arrLength) {
	Node *root = new Node {arr[0], NULL, NULL, NULL};
	for (int i = 1; i < arrLength; i++) {  // loop runs n times where n is the number of items in array
		insert(root, arr[i]);  // since array not sorted and tree is unbalanced, worst case of insertion is n
	}
	return root;
}
// time complexity of making BST is O(n)*O(n) = O(n*n) = O(n^2)

int treeHeight(Node * root) {
	return (root == NULL) ? 0 : max(treeHeight(root->left), treeHeight(root->right)) + 1;
}

bool isBalanced(Node * root) {  // O(n^2) - for each node, find height of tree. and finding height is already O(n)
	if (root == NULL) return true;
	return (abs(treeHeight(root->left) - treeHeight(root->right)) <= 1) && isBalanced(root->left) && isBalanced(root->right);
}

/*
T1, T2, T3 and T4 are subtrees.
  z                                y
 /  \                            /   \ 
T1   y     Left Rotate(z)       z      x
    /  \   - - - - - - - ->    / \    / \
   T2   x                     T1  T2 T3  T4
       / \
     T3  T4
*/
Node * leftRotate(Node * root) {  // actual rotate is O(1)
	Node * y = root->right;
	Node * T2 = y->left;
	root->right = T2;
	y->left = root;
	return y;
}

/*
T1, T2, T3 and T4 are subtrees.
         z                                      y 
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \ 
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2
*/
Node * rightRotate(Node * root) {  // actual rotate is O(1)
	Node * y = root->left;
	Node * T3 = y->right;
	root->left = T3;
	y->right = root;
	return y;
}


// recursive depth of this function is n where n is size of array. So whole time complexity is (n^3)
Node * balanceBST(Node * root) {  // convert the search tree to AVL
	if (isBalanced(root)) return root;  // O(n^2)
	root->left = balanceBST(root->left);
	root->right = balanceBST(root->right);

	if (isBalanced(root)) return root;  // O(n^2)


	// whole loop is O(n^2)
	if (treeHeight(root->left) > treeHeight(root->right)) {  // L       ----> O(n)
		if (treeHeight(root->left->left) > treeHeight(root->left->right)) {  // LL     ------> O(n)
			return rightRotate(root);     // O(1)
		} else {  // LR
			root->left = leftRotate(root->left);     //O(1)
			return rightRotate(root);       // O(1)
		}
	} else {  // R
		if (treeHeight(root->right->left) > treeHeight(root->right->right)) {  // RL
			root->right = rightRotate(root->right);
			return leftRotate(root);
		} else {  // RR
			return leftRotate(root);
		}
	}
	return root;
}

void inOrderTraversal(Node * root) {
	if (root->left != NULL) inOrderTraversal(root->left);
	cout << root->data << " ";
	if (root->right != NULL) inOrderTraversal(root->right);
}

int main() {
	int arr[] = {6, 4, 16, 1, 5, 10, 17, 3, 9, 12, 18, 2, 8, 11, 13, 7, 14, 15};
	Node * root = createBST(arr, sizeof(arr)/sizeof(arr[0]));
	root = balanceBST(root);
	// cout << isBalanced(root) << endl;
	// cout << treeHeight(root) << endl;
	// inOrderTraversal(root); cout << endl;
	// bulo(root); cout << endl;
	return 0;
}
