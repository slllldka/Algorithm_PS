#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;
using i2 = pair<int, int>;

class TreeNode {
public:
	int parent;
	int latency;
	vector<int> childs;
	int depth;

	int firstLatency, secondLatency;
	int firstIdx, secondIdx;

	TreeNode() {
		parent = -1;
		latency = 0;
		depth = 0;
		firstLatency = 0;
		secondLatency = 0;
		firstIdx = -1;
		secondIdx = -1;
	}

	void reset(int parent, int latency, int depth);
	void addChild(int idx);
};

int deviceNum = 0;
unordered_map<int, int> hashMap;
TreeNode nodes[10001];

void TreeNode::reset(int parent, int latency, int depth) {
	this->parent = parent;
	this->latency = latency;
	childs.clear();
	this->depth = depth;
	if (parent == -1) {
		firstLatency = 0;
		secondLatency = 0;
		firstIdx = -1;
		secondIdx = -1;
	}
	else {
		firstLatency = 0;
		secondLatency = 0;
		firstIdx = -1;
		secondIdx = -1;
	}
}
void TreeNode::addChild(int idx) {
	childs.push_back(idx);

	int parent = nodes[idx].parent;
	int child = idx;
	int temp = 0;
	while (parent != -1) {
		temp += nodes[child].latency;
		if (temp >= nodes[parent].firstLatency) {
			if (child == nodes[parent].firstIdx) {
				nodes[parent].firstLatency = temp;
				nodes[parent].firstIdx = child;
			}
			else {
				nodes[parent].secondLatency = nodes[parent].firstLatency;
				nodes[parent].secondIdx = nodes[parent].firstIdx;
				nodes[parent].firstLatency = temp;
				nodes[parent].firstIdx = child;
			}
		}
		else if (temp >= nodes[parent].secondLatency) {
			if (child != nodes[parent].firstIdx) {
				nodes[parent].secondLatency = temp;
				nodes[parent].secondIdx = child;
			}
		}
		child = parent;
		parent = nodes[parent].parent;
	}
}

void init(int mDevice)
{
	deviceNum = 0;
	hashMap.clear();
	hashMap[mDevice] = deviceNum;
	nodes[deviceNum++].reset(-1, 0, 1);
	return;
}

void connect(int mOldDevice, int mNewDevice, int mLatency)
{
	int oldNum = hashMap[mOldDevice], newNum = deviceNum;
	hashMap[mNewDevice] = deviceNum++;
	nodes[newNum].reset(oldNum, mLatency, nodes[oldNum].depth + 1);
	nodes[oldNum].addChild(newNum);
	return;
}

int measure(int mDevice1, int mDevice2)
{
	int d1 = hashMap[mDevice1], d2 = hashMap[mDevice2];
	int ret = 0;
	if (nodes[d1].depth > nodes[d2].depth) {
		int temp = d1;
		d1 = d2;
		d2 = temp;
	}

	while (nodes[d1].depth < nodes[d2].depth) {
		ret += nodes[d2].latency;
		d2 = nodes[d2].parent;
	}

	while (d1 != d2) {
		ret += nodes[d1].latency;
		ret += nodes[d2].latency;
		d1 = nodes[d1].parent;
		d2 = nodes[d2].parent;
	}
	//cout << ret << '\n';
	return ret;
}

int test(int mDevice)
{
	int d = hashMap[mDevice];
	int downFirst = nodes[d].firstLatency, downSecond = nodes[d].secondLatency;
	int up = 0;
	int parent = nodes[d].parent;
	int child = d;
	int offset = nodes[d].latency;
	int temp;
	while (parent != -1) {
		if (nodes[parent].firstIdx != child) {
			temp = offset + nodes[parent].firstLatency;
		}
		else {
			temp = offset + nodes[parent].secondLatency;
		}

		if (temp > up) {
			up = temp;
		}

		child = parent;
		parent = nodes[parent].parent;
		offset += nodes[child].latency;
	}
	
	int ret = downFirst + downSecond + up;
	ret -= min(min(downFirst, downSecond), up);
	//cout << ret << '\n';
	return ret;
}
