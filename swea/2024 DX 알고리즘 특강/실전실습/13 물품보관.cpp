#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int base;
int maxTree[2 << 18];
int N;

void update(int idx, int val) {
	int parent = (base + idx) / 2;
	maxTree[base + idx] += val;
	while (parent > 0) {
		maxTree[parent] = max(maxTree[parent * 2], maxTree[parent * 2 + 1]);
		parent /= 2;
	}
}
int getMaxIdx() {
	int child = 1;
	while (child < base) {
		if (maxTree[child * 2] == maxTree[child]) {
			child *= 2;
		}
		else {
			child *= 2;
			child++;
		}
	}
	return (child - base);
}

int leftQuery(int node, int qs, int qe, int ts, int te) {
	if (qe < ts || te < qs) {
		return -1;
	}
	if (qs <= ts && te <= qe) {
		return node;
	}
	
	int mid = (ts + te) / 2;
	int leftNode = leftQuery(node * 2, qs, qe, ts, mid);
	int rightNode = leftQuery(node * 2 + 1, qs, qe, mid + 1, te);
	if (leftNode == -1) {
		return rightNode;
	}
	else if (rightNode == -1) {
		return leftNode;
	}
	else if (maxTree[leftNode] >= maxTree[rightNode]) {
		return leftNode;
	}
	else {
		return rightNode;
	}
}
int rightQuery(int node, int qs, int qe, int ts, int te) {
	if (qe < ts || te < qs) {
		return -1;
	}
	if (qs <= ts && te <= qe) {
		return node;
	}

	int mid = (ts + te) / 2;
	int leftNode = rightQuery(node * 2, qs, qe, ts, mid);
	int rightNode = rightQuery(node * 2 + 1, qs, qe, mid + 1, te);
	if (leftNode == -1) {
		return rightNode;
	}
	else if (rightNode == -1) {
		return leftNode;
	}
	else if (maxTree[rightNode] >= maxTree[leftNode]) {
		return rightNode;
	}
	else {
		return leftNode;
	}
}

int getSize() {
	int maxIdx = getMaxIdx();
	int prevHeight = maxTree[maxIdx + base];
	int ret = prevHeight;
	//cout << ret << '\n';
	//left
	int leftIdx = maxIdx - 1;
	while (leftIdx >= 0) {
		int temp = leftQuery(1, 0, leftIdx, 0, base - 1);
		while (temp < base) {
			if (maxTree[temp * 2] >= maxTree[temp * 2 + 1]) {
				temp = temp * 2;
			}
			else {
				temp = temp * 2 + 1;
			}
		}
		temp -= base;
		ret += (maxTree[temp + base] * (leftIdx - temp + 1));
		prevHeight = maxTree[temp + base];
		leftIdx = temp - 1;
		//cout << leftIdx << '\n';
	}
	//right
	prevHeight = maxTree[maxIdx + base];
	int rightIdx = maxIdx + 1;
	while (rightIdx < N) {
		//cout << rightIdx << '\n';
		int temp = rightQuery(1, rightIdx, N - 1, 0, base - 1);
		//cout << temp << '\n';
		while (temp < base) {
			if (maxTree[temp * 2 + 1] >= maxTree[temp * 2]) {
				temp = temp * 2 + 1;
			}
			else {
				temp = temp * 2;
			}
		}
		temp -= base;
		ret += (maxTree[temp + base] * (temp - rightIdx + 1));
		prevHeight = maxTree[temp + base];
		rightIdx = temp + 1;
	}
	return ret;
}

void init(int n)
{
	N = n;
	base = 1;
	while (base < N) {
		base <<= 1;
	}
	memset(maxTree, 0, sizeof(maxTree));
	return;
}

int stock(int mLoc, int mBox)
{
	update(mLoc - 1, mBox);
	int ret = getSize();
	//cout << ret << '\n';
	return ret;
}

int ship(int mLoc, int mBox)
{
	update(mLoc - 1, -mBox);
	int ret = getSize();
	//cout << ret << '\n';
	return ret;
}

int getHeight(int mLoc)
{
	//cout << maxTree[base + mLoc] << '\n';
	return maxTree[base + mLoc - 1];
}
