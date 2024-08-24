#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class TreeNode {
public:
	char data;
	int childs[26];
	int num;
	TreeNode() {
		data = 0;
		memset(childs, 0, sizeof(childs));
		num = -1;
	}
	TreeNode(char data, int len) {
		this->data = data;
		memset(childs, 0, sizeof(childs));
		this->num = len;
	}

	int findChild(char target);
	void addChild(char item, int len);
};


static const int root = 0;

int nodeNum = 0;
TreeNode nodes[1000000];

int TreeNode::findChild(char target) {
	if (childs[target - 'a'] > 0) {
		return childs[target - 'a'];
	}
	return -1;
}

void TreeNode::addChild(char item, int num) {
	nodes[nodeNum] = TreeNode(item, num);
	childs[item - 'a'] = nodeNum++;
}

void findStr(int& ret, int idx, int node, string str, bool remove) {
	if (idx == str.length()) {
		ret += nodes[node].num;
		if (remove) {
			nodes[node].num = 0;
		}
		return;
	}
	if (str[idx] == '?') {
		for (int i = 0; i < 26; i++) {
			if (nodes[node].childs[i] > 0) {
				findStr(ret, idx + 1, nodes[node].childs[i] , str, remove);
			}
		}
	}
	else {
		if (nodes[node].childs[str[idx] - 'a'] > 0) {
			findStr(ret, idx + 1, nodes[node].childs[str[idx] - 'a'], str, remove);
		}
	}
}

void init() {
	nodeNum = 0;
	nodes[nodeNum++] = TreeNode();
	return;
}

int add(char str[]) {
	int i = 0, idx = 0, childIdx, ret = 0;
	while (str[i] != 0) {
		childIdx = nodes[idx].findChild(str[i]);
		if (childIdx > 0) {
			idx = childIdx;
		}
		else {
			nodes[idx].addChild(str[i], 0);
			idx = nodeNum - 1;
		}
		i++;
	}
	nodes[idx].num++;
	ret = nodes[idx].num;

	return ret;
}

int remove(char str[]) {
	int ret = 0;
	findStr(ret, 0, 0, str, true);
	return ret;
}

int search(char str[]) {
	int ret = 0;
	findStr(ret, 0, 0, str, false);
	return ret;
}