#include <queue>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;
using i2 = pair<int, int>;

constexpr int maxLen = 110000;

int len;
int wall[maxLen];
int leftIdx[maxLen], rightIdx[maxLen];
int idxHash[maxLen];
set<i2> pieceIdx[maxLen];

int base = 1 << 17;
int segTree[1 << 18];
int fiveIdx[5];

void update(int idx) {
	int parent = base + idx;
	while (parent > 0) {
		segTree[parent] += 5;
		parent /= 2;
	}
}
int query(int node, int qs, int qe, int ts, int te) {
	if (qe < ts || te < qs) {
		return 0;
	}
	if (qs <= ts && te <= qe) {
		return segTree[node];
	}

	int mid = (ts + te) / 2;
	int a = query(node * 2, qs, qe, ts, mid);
	int b = query(node * 2 + 1, qs, qe, mid + 1, te);
	return a + b;
}

void init()
{
	len = 0;
	//memset(wall, 0, sizeof(wall));
	for (int i = 0; i < maxLen; i++) {
		leftIdx[i] = i - 1;
		rightIdx[i] = i + 1;
	}
	//memset(idxHash, 0, sizeof(idxHash));
	for (int i = 0; i < maxLen; i++) {
		pieceIdx[i].clear();
	}

	memset(segTree, 0, sizeof(segTree));
}

void makeWall(int mHeights[5])
{
	int hash = 0;
	int multiple = 10000;
	for (int i = 0; i <= 4; i++) {
		wall[len + i] = mHeights[i] - 1;
		hash += wall[len + i] * multiple;
		multiple /= 10;
	}
	int start = len, end = len + 4;
	int count = 0;
	while (count < 5) {
		pieceIdx[hash].insert(i2(start, end));
		idxHash[start] = hash;

		hash -= wall[end];
		hash /= 10;
		
		start = leftIdx[start];
		end = leftIdx[end];

		if (start == -1) {
			break;
		}

		hash += wall[start] * 10000;
		count++;
	}

	len += 5;

	//cout << len << '\n';
	/*for (int i = 0; i < len; i++) {
		cout << wall[i] << ' ';
	}
	cout << '\n';*/
}

int matchPiece(int mHeights[5])
{
	int minH = 11, maxH = 0, hash = 0, multiple = 0, newHash = 0, c = 0, ret = 0;
	i2 maxPos = i2(-1, -1), newPos = i2(-1, -1);
	for (int i = 0; i < 5; i++) {
		minH = min(minH, mHeights[i]);
		maxH = max(maxH, mHeights[i]);
	}
	maxH -= minH;
	multiple = 1;
	for (int i = 0; i < 5; i++) {
		mHeights[i] -= minH;
		hash += multiple * (maxH - mHeights[i]);
		multiple *= 10;
	}
	for (int i = maxH; i < 10; i++) {
		while (!pieceIdx[hash].empty()) {
			if (hash != idxHash[(*pieceIdx[hash].rbegin()).first]) {
				pieceIdx[hash].erase(*pieceIdx[hash].rbegin());
			}
			else {
				break;
			}
		}
		if (!pieceIdx[hash].empty()) {
			maxPos = max(maxPos, *pieceIdx[hash].rbegin());
		}
		hash += 11111;
	}

	if (maxPos.first == -1) {
		//cout << -1 << '\n';
		return -1;
	}
	
	ret = maxPos.first - query(1, 0, maxPos.first - 1, 0, base - 1) + 1;
	update(maxPos.first);

	hash = idxHash[maxPos.first];
	pieceIdx[hash].erase(*pieceIdx[hash].rbegin());
	idxHash[maxPos.first] = -1;
	//left
	c = 0;
	newPos = i2(leftIdx[maxPos.first], leftIdx[maxPos.second]);
	while (newPos.first != -1 && c < 4) {
		idxHash[newPos.first] = -1;
		newPos = i2(leftIdx[newPos.first], leftIdx[newPos.second]);
		c++;
	}

	//right
	c = 0;
	newPos = i2(rightIdx[maxPos.first], rightIdx[maxPos.second]);
	while ((newPos.second < len) && (c < 4)) {
		idxHash[newPos.first] = -1;
		newPos = i2(rightIdx[newPos.first], rightIdx[newPos.second]);
		c++;
	}

	int startLeft = leftIdx[maxPos.first];
	int endRight = rightIdx[maxPos.second];

	leftIdx[endRight] = startLeft;
	if (startLeft >= 0) {
		rightIdx[startLeft] = endRight;
	}

	if (endRight == len) {
		//cout << ret << '\n';
		return ret;
	}

	int prev = startLeft;

	if (prev == -1) {
		//cout << ret << '\n';
		return ret;
	}

	c = 0;
	while (leftIdx[prev] != -1 && c < 3) {
		prev = leftIdx[prev];
		c++;
	}

	fiveIdx[0] = prev;
	newHash = wall[fiveIdx[0]] * 10000;
	for (int i = 0; i < 4; i++) {
		multiple = 1000;
		for (int j = 1; j <= 4; j++) {
			fiveIdx[j] = rightIdx[fiveIdx[j - 1]];
			newHash += multiple * wall[fiveIdx[j]];
			multiple /= 10;
		}
		if (fiveIdx[4] >= len) {
			break;
		}

		pieceIdx[newHash].insert(i2(fiveIdx[0], fiveIdx[4]));
		idxHash[fiveIdx[0]] = newHash;

		fiveIdx[0] = rightIdx[fiveIdx[0]];
		newHash = 10000 * wall[fiveIdx[0]];
	}
	//cout << ret << '\n';
	return ret;
}