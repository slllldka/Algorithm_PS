#include <iostream>
#include <string>
#include <stack>

using namespace std;

class TreeNode {
public:
	double num = 0;
	char op = NULL;
	int left = 0, right = 0;
	TreeNode(){}
	TreeNode(char op, int left, int right) {
		num = 0;
		this->op = op;
		this->left = left;
		this->right = right;
	}
	TreeNode(double num) {
		this->num = num;
		op = NULL;
		left = 0;
		right = 0;
	}
};

TreeNode treeArr[1001];
int N;
stack<double> s;

void postOrder(int idx) {
	if (idx > 0 && idx <= N) {
		postOrder(treeArr[idx].left);
		postOrder(treeArr[idx].right);
		if (treeArr[idx].op == NULL) {
			s.push(treeArr[idx].num);
		}
		else {
			int n1, n2;
			n2 = s.top();
			s.pop();
			n1 = s.top();
			s.pop();
			switch (treeArr[idx].op) {
			case '+':
				s.push(n1 + n2);
				break;
			case '-':
				s.push(n1 - n2);
				break;
			case '*':
				s.push(n1 * n2);
				break;
			case '/':
				s.push(n1 / n2);
				break;
			default:
				break;
			}
		}
	}
}

int main() {
	int idx, leftChild, rightChild;
	string input;
	for (int t = 1; t <= 10; t++) {
		cin >> N;
		s = stack<double>();
		for (int i = 1; i <= N; i++) {
			cin >> idx;
			cin >> input;
			if (input[0] >= '0' && input[0] <= '9') {
				treeArr[idx] = TreeNode(stod(input));
			}
			else {
				cin >> leftChild >> rightChild;
				treeArr[idx] = TreeNode(input[0], leftChild, rightChild);
			}
		}
		postOrder(1);
		cout << '#' << t << ' ';
		cout << (int)s.top();
		cout << '\n';
	}
	return 0;
}