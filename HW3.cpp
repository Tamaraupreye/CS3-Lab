#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

template <typename T>
struct Node {
	T data;
	Node * next = NULL;
};

enum Color {WHITE, GRAY, BLACK};

template <typename T>
void add(Node<T> * head, T val) {
	Node<T> * node = new Node<T>;
	node->data =  val;
	if (head == NULL) {
		head = node;
		return;
	}
	Node<T> * curr = head;
	while (curr->next != NULL) curr = curr->next;
	curr->next = node;
}

vector<vector<bool>> getAdjacencyMatrix(vector<int> du, vector<int> dv) {
	vector<vector<bool>> matrix (8, vector<bool> (8, false));
	for (int i = 0; i < du.size(); i++) {
		matrix[du[i] - 1][dv[i] - 1] = true;
		matrix[dv[i] - 1][du[i] - 1] = true;
	}
	return matrix;
}

char boolToChar(bool b) {
	return b ? 'T' : ' ';
}

void printAdjacencyMatrix(vector<vector<bool>> matrix) {
	cout << "Adjacency Matrix: " << endl << endl;
	cout << "  | 1 2 3 4 5 6 7 8 " << endl;
	cout << "--|-----------------" << endl;
	for (int i = 0; i < 8; i++) {
		cout << i + 1 << " |";
		for (int j = 0; j < 8; j++) {
			cout << " " << boolToChar(matrix[i][j]);
		}
		cout << endl;
	}
}

void getAdjacencyList(vector<int> du, vector<int> dv, Node<int> ** list) {
	for (int i = 0; i < 8; i++) {
		list[i] = new Node<int>;
		list[i]->data = i + 1;
	}

	for (int i = 0; i < du.size(); i++) {
		add<int>(list[du[i] - 1], dv[i]);
		add<int>(list[dv[i] - 1], du[i]);
	}
}

void printAdjacencyList(vector<int> du, vector<int> dv, Node<int> ** list) {
	cout << "Adjacency List: " << endl << endl;
	Node<int> * curr;
	for (int i = 0; i < 8; i++) {
		curr = list[i];
		cout << curr->data;
		curr = curr->next;
		while (curr != NULL) {
			cout << " -> " << curr->data;
			curr = curr->next;
		}
		cout << endl;
	}
}

void dfs_util(Node<int> **list, Color *c, int *parent, int *distance, int *discovered, int *finished, int &time, int curr, int d) {
	discovered[curr - 1] = ++time;
	c[curr - 1] = GRAY;
	distance[curr - 1] = d++;

	Node<int> * node = list[curr - 1]->next;
	while (node != NULL) {
		if (c[node->data - 1] == WHITE) {
			parent[node->data - 1] = curr;
			dfs_util(list, c, parent, distance, discovered, finished, time, node->data, d);
		}
		node = node->next;
	}

	c[curr - 1] = BLACK;
	finished[curr - 1] = ++time;
}

// convert to recursion
void dfs(Node<int> ** list) {
	Color c [8] = {WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE};
	int parent [8] = {-1, -1, -1, -1, -1, -1, -1, -1};
	int distance [8] = {-1, -1, -1, -1, -1, -1, -1, -1};
	int discovered [8] = {-1, -1, -1, -1, -1, -1, -1, -1};
	int finished [8] = {-1, -1, -1, -1, -1, -1, -1, -1};
	int time = 0;
	int source = 1;

	dfs_util(list, c, parent, distance, discovered, finished, time, source, 0);

	cout << "DFS - Adjacency List Traversal: " << endl << endl;
	cout << "Vertices |  1  2  3  4  5  6  7  8 " << endl;
	cout << "---------|-------------------------" << endl;
	cout << "V.Parent |";
	for (int i = 0; i < 8; i++) {
		cout << setw(3) << parent[i];
	}
	cout << endl;

	cout << "Distance |";
	for (int i = 0; i < 8; i++) {
		cout << setw(3) << distance[i];
	}
	cout << endl;

	cout << "Discover |";
	for (int i = 0; i < 8; i++) {
		cout << setw(3) << discovered[i];
	}
	cout << endl;

	cout << "V.Finish |";
	for (int i = 0; i < 8; i++) {
		cout << setw(3) << finished[i];
	}
	cout << endl;
}

int main() {
	vector<int> du {1, 1, 2, 3, 3, 3, 4, 4, 6, 7};
	vector<int> dv {2, 5, 6, 6, 7, 4, 7, 8, 7, 8};

	vector<vector<bool>> matrix = getAdjacencyMatrix(du, dv);
	printAdjacencyMatrix(matrix);

	cout << endl << endl;

	Node<int> ** list = new Node<int> * [8];
	getAdjacencyList(du, dv, list);
	printAdjacencyList(du, dv, list);

	cout << endl << endl;

	dfs(list);
}
