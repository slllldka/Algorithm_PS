#include <iostream>
#include <vector>

using namespace std;

class TreeNode {
public:
	char data;
	vector<int> childs;
	int idx, len;
	TreeNode() {
		data = 0;
		childs.clear();
		idx = -1;
		len = -1;
	}
	TreeNode(char data, int idx, int len) {
		this->data = data;
		childs.clear();
		this->idx = idx;
		this->len = len;
	}

	int findChild(char target);
	void addChild(char item, int idx, int len);
};


static const int root = 0;

int nodeNum = 0;

string str, ret;
int K;
int countNum;
TreeNode nodes[81000];

int TreeNode::findChild(char target) {
	int start = 0;
	int end = childs.size() - 1;
	int mid = 0;
	while (start <= end) {
		mid = (start + end) / 2;
		if (nodes[childs[mid]].data == target) {
			return mid;
		}
		else if (nodes[childs[mid]].data < target) {
			start = mid + 1;
		}
		else {
			end = mid - 1;
		}
	}
	return -1;
}

void TreeNode::addChild(char item, int idx, int len) {
	nodes[nodeNum] = TreeNode(item, idx, len);
	for (int i = 0; i < childs.size(); i++) {
		if (item < nodes[childs[i]].data) {
			childs.insert(childs.begin() + i, nodeNum++);
			return;
		}
	}
	childs.push_back(nodeNum++);
}

void findKth(int node) {
	if (countNum >= K) {
		return;
	}
	if (node > 0) {
		countNum++;
	}
	if (countNum == K) {
		ret = str.substr(nodes[node].idx, nodes[node].len);
		return;
	}
	for (int i = 0; i < nodes[node].childs.size(); i++) {
		findKth(nodes[node].childs[i]);
	}
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T, idx, childIdx;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> K >> str;
		nodeNum = 0;
		nodes[nodeNum++] = TreeNode();

		for (int i = 0; i < str.length(); i++) {
			idx = root;
			for (int j = i; j < str.length(); j++) {
				childIdx = nodes[idx].findChild(str[j]);
				if (childIdx >= 0) {
					idx = nodes[idx].childs[childIdx];
				}
				else {
					nodes[idx].addChild(str[j], i, (j - i + 1));
					idx = nodeNum - 1;
				}
			}
		}

		countNum = 0;
		findKth(0);
		if (countNum < K) {
			ret = "none";
		}

		cout << '#' << t << ' ' << ret << '\n';
	}
	return 0;
}