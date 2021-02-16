#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct Node {
	int data;
	Node * parent;
	Node * left;
	Node * right;
};

Node * createBinaryTree(int arr[], int arrLength) {
	if (arrLength == 0) return NULL;
	
	Node * root = new Node {arr[0], NULL, NULL, NULL};

	if (arrLength == 1) return root;

	queue<Node*> q;
	q.push(root);
	Node * curr;

	int i = 1;
	while (i < arrLength) {
		curr = q.front();
		q.pop();
		if (arr[i] != -1) {
			curr->left = new Node {arr[i], curr, NULL, NULL};
			q.push(curr->left);
		}
		i++;
		if (arr[i] != -1) {
			curr->right = new Node {arr[i], curr, NULL, NULL};
			q.push(curr->right);
		}
		i++;
	}

	return root;
}

void bulo(Node * root) {  // bottom up level order traversal - from right to left, level by level from leaf to root
	queue<Node*> nodeQueue;
	stack<int> dataStack;
	Node * curr;

	nodeQueue.push(root);
	while (!nodeQueue.empty()) {
		curr = nodeQueue.front();
		nodeQueue.pop();
		dataStack.push(curr->data);

		if (curr->left != NULL) nodeQueue.push(curr->left);
		if (curr->right != NULL) nodeQueue.push(curr->right);
	}

	while (!dataStack.empty()) {
		cout << dataStack.top() << " ";
		dataStack.pop();
	}
	cout << endl;
}

int main() {
	int arr[21] = {65, 40, 70, 20, 50, -1, 90, 10, -1, 45, 58, -1, -1, -1, 100, -1, 45, 42, 47, -1, 60};
	Node * root = createBinaryTree(arr, 21);
	bulo(root);
	return 0;
}

/* -- Testing Non-Programming Section Q3 --

template <typename T>
struct Node {
	T data;
	Node<T> * left;
	Node<T> * right;
};


void inOrderTraversal(Node<int> * root) {
	if (root->left != NULL) inOrderTraversal(root->left);
	cout << root->data << " ";
	if (root->right != NULL) inOrderTraversal(root->right);
}

void postOrderTraversal(Node<int> * root) {
	if (root->left != NULL) postOrderTraversal(root->left);
	if (root->right != NULL) postOrderTraversal(root->right);
	cout << root->data << " ";
}

int main() {
	Node<int> root = {10, new Node<int> {15, new Node<int> {7, new Node<int> {4, NULL, NULL}, new Node<int> {16, NULL, NULL}}, new Node<int> {17, new Node<int> {29, NULL, NULL}, NULL}}, new Node<int> {20, new Node<int> {19, NULL, new Node<int> {53, new Node<int> {25, NULL, NULL}, new Node<int> {9, NULL, NULL}}}, new Node<int> {35, new Node<int> {27, NULL, NULL}, new Node<int> {40, NULL, NULL}}}};

	inOrderTraversal(&root);
	cout << endl;
	postOrderTraversal(&root);
	cout << endl;
	cout << endl;
}

*/