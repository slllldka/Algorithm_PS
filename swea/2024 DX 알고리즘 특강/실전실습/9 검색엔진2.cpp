#include <cstring>
#include <string>
#include <unordered_map>
#include <queue>
#include <utility>
#include <vector>
#include <list>
#include <iostream>

using namespace std;
using ill = pair<int, long long>;

struct Result
{
	int mOrder;
	int mRank;
};

struct TreeNode {
	string str;
	long long hash;
	int parent;
	int child[26];
	int count;
	priority_queue<ill> pq; // (count, string hash)
	int setNum;

	TreeNode() {
		str = "";
		hash = 0;
		parent = -1;
		memset(child, 0, sizeof(child));
		count = 0;
		pq = priority_queue<ill>();
		setNum = -1;
	}

	TreeNode(string str, int parent) {
		this->str = str;
		hash = 0;
		this->parent = parent;
		memset(child, 0, sizeof(child));
		count = 0;
		pq = priority_queue<ill>();
		setNum = -1;
	}
};

constexpr int root = 0;
int nodeNum = 0;
TreeNode nodes[150000];
unordered_map<long long, int> hashMap; // (string hash, node index)
list<int> relateList[150000];

int Find(int node) {
	if (nodes[node].setNum == node) {
		return node;
	}
	else {
		return (nodes[node].setNum = Find(nodes[node].setNum));
	}
}

int Union(int node1, int node2) {
	int parent1 = Find(node1);
	int parent2 = Find(node2);
	nodes[parent2].setNum = parent1;
	relateList[parent1].splice(relateList[parent1].end(), relateList[parent2]);
	return parent1;
}

long long stringHash(char str[]) {
	long long ret = 0;
	int idx = 0;
	while (str[idx]) {
		ret += ((long long)str[idx] - 'a' + 1) * ((long long)1 << ((7 - idx) * 5));
		idx++;
	}
	return ret;
}

void init()
{
	nodeNum = 0;
	nodes[nodeNum++] = TreeNode();
	hashMap.clear();
	return;
}

void search(char mStr[], int mCount)
{
	int idx = 0;
	int parent = root;
	long long hash = 0;
	int count = 0;
	while (mStr[idx]) {
		if (nodes[parent].child[mStr[idx] - 'a'] == 0) {
			nodes[nodeNum] = TreeNode("", parent);
			nodes[parent].child[mStr[idx] - 'a'] = nodeNum;
			parent = nodeNum++;
		}
		else {
			parent = nodes[parent].child[mStr[idx] - 'a'];
		}
		idx++;
	}

	hash = stringHash(mStr);
	if (!hashMap.count(hash)) {
		hashMap[hash] = parent;
		nodes[parent].str = mStr;
		nodes[parent].hash = hash;
		nodes[parent].setNum = parent;
		relateList[parent].clear();
		relateList[parent].push_back(parent);
	}

	int setNum = Find(parent);
	for (int idx : relateList[setNum]) {
		nodes[idx].count += mCount;
		count = nodes[idx].count;
		hash = nodes[idx].hash;
		parent = idx;
		while (parent != -1) {
			nodes[parent].pq.push(ill(count, -hash));
			parent = nodes[parent].parent;
		}
	}

	return;
}

Result recommend(char mStr[])
{
	Result ret = { 0, 0 };

	int idx = -1;
	int node = root;
	long long hash = stringHash(mStr);
	vector<ill> vec;
	
	do {
		if (idx == -1) {
			node = root;
		}
		else {
			node = nodes[node].child[mStr[idx] - 'a'];
		}

		for (int i = 0; i < 5;) {
			if (nodes[node].pq.empty()) {
				break;
			}
			ill data = nodes[node].pq.top();
			if (data.first != nodes[hashMap[-data.second]].count) {
				nodes[node].pq.pop();
				continue;
			}

			//cout << idx + 1 << ' ' << nodes[hashMap[-data.second]].str << '\n';
			if (-data.second == hash) {
				ret = { idx + 1, i + 1};
				break;
			}
			vec.push_back(data);
			nodes[node].pq.pop();
			i++;
		}

		for (ill data : vec) {
			nodes[node].pq.push(data);
		}
		vec.clear();

		if (ret.mRank != 0) {
			//cout << ret.mOrder << ' ' << ret.mRank << '\n';

			int parent = hashMap[hash];
			int setNum = Find(parent);
			int count = 0;
			for (int idx : relateList[setNum]) {
				nodes[idx].count++;
				count = nodes[idx].count;
				hash = nodes[idx].hash;
				parent = idx;
				while (parent != -1) {
					nodes[parent].pq.push(ill(count, -hash));
					parent = nodes[parent].parent;
				}
			}

			return ret;
		}

		idx++;
	} while (mStr[idx]);
	return ret;
}

int relate(char mStr1[], char mStr2[])
{
	long long hash1 = stringHash(mStr1);
	long long hash2 = stringHash(mStr2);
	int node1 = hashMap[hash1];
	int node2 = hashMap[hash2];
	int count = nodes[node1].count + nodes[node2].count;

	int result = Union(node1, node2);
	for (int idx : relateList[result]) {
		int parent = idx;
		long long hash = nodes[idx].hash;
		nodes[idx].count = count;
		while (parent != -1) {
			nodes[parent].pq.push(ill(count, -hash));
			parent = nodes[parent].parent;
		}
	}
	//cout << count << '\n';
	return count;
}

void rank(char mPrefix[], int mRank, char mReturnStr[])
{
	vector<ill> vec;
	int idx = 0;
	int node = root;
	while (mPrefix[idx]) {
		node = nodes[node].child[mPrefix[idx] - 'a'];
		idx++;
	}

	int rank = 0;
	while (!nodes[node].pq.empty()) {
		ill data = nodes[node].pq.top();
		if (data.first != nodes[hashMap[-data.second]].count) {
			nodes[node].pq.pop();
			continue;
		}

		rank++;
		if (rank == mRank) {
			string str = nodes[hashMap[-data.second]].str;
			if (!str.compare("tdjiug")) {
				char temp[] = "tdjta";
				//cout << nodes[hashMap[stringHash(temp)]].count << '\n';
			}
			for (int i = 0; i < (int)str.length(); i++) {
				mReturnStr[i] = str[i];
			}
			mReturnStr[str.length()] = '\0';
			//cout << str << nodes[hashMap[-data.second]].count << '\n';
			break;
		}
		vec.push_back(data);
		nodes[node].pq.pop();
	}

	for (ill data : vec) {
		nodes[node].pq.push(data);
	}

	return;
}