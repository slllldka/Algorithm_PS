#include <iostream>
#include <string>

using namespace std;

class TreeNode {
public:
	int parent = 0, left = 0, right = 0;
};

TreeNode treeArr[10001];
int V, E, n1, n2;
int parentArr1[10001];
int parentArrSize1 = 0;

int inOrder(int idx) {
	int ret = 0;
	if (idx > 0 && idx <= V) {
		ret++;
		ret += inOrder(treeArr[idx].left);
		ret += inOrder(treeArr[idx].right);
	}
	return ret;
}

int main() {
	int test_case, parent, child;
	string input;
	cin >> test_case;
	for (int t = 1; t <= test_case; t++) {
		cin >> V >> E >> n1 >> n2;
		for (int i = 0; i <= V; i++) {
			treeArr[i] = TreeNode();
		}
		for (int i = 0; i < E; i++) {
			cin >> parent >> child;
			if (treeArr[parent].left == 0) {
				treeArr[parent].left = child;
			}
			else {
				treeArr[parent].right = child;
			}
			treeArr[child].parent = parent;
		}
		parent = n1;
		parentArrSize1 = 0;
		while (parent != 0) {
			parentArr1[parentArrSize1++] = parent;
			parent = treeArr[parent].parent;
		}
		parent = n2;
		while (parent != 0) {
			for (int i = 0; i < parentArrSize1; i++) {
				if (parent == parentArr1[i]) {
					cout << '#' << t << ' ' << parent << ' ';
					cout << inOrder(parent) << '\n';
					parent = 0;
					break;
				}
			}
			parent = treeArr[parent].parent;
		}
	}

	return 0;
}