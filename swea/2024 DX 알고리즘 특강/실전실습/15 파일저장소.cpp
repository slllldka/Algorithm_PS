#include <unordered_map>
#include <map>
#include <vector>
#include <utility>
#include <cstring>
#include <iostream>

using namespace std;
using i2 = pair<int, int>;

int N;
int fileNum = 0;
unordered_map<int, int> hashMap;
map<int, int> emptySpaces; // address, size
int totalSize;
vector<i2> spaces[12000];
int sizes[12000];

void init(int n) {
	N = n;
	fileNum = 0;
	hashMap.clear();
	emptySpaces.clear();
	emptySpaces[0] = N;
	totalSize = 0;
	for (int i = 0; i < 12000; i++) {
		spaces[i].clear();
	}
	memset(sizes, 0, sizeof(sizes));
	return;
}

int add(int mId, int mSize) {
	int id = fileNum;
	hashMap[mId] = fileNum++;
	if (N - totalSize < mSize) {
		return -1;
	}
	totalSize += mSize;
	sizes[id] = mSize;
	while (mSize != 0) {
		int address = (*emptySpaces.begin()).first;
		int area = (*emptySpaces.begin()).second;
		if (area > mSize) {
			if (spaces[id].size() > 0) {
				i2 data = *spaces[id].rbegin();
				if (data.first + data.second == address) {
					*spaces[id].rbegin() = i2(data.first, data.second + mSize);
				}
				else {
					spaces[id].push_back(i2(address, mSize));
				}
			}
			else {
				spaces[id].push_back(i2(address, mSize));
			}
			emptySpaces.erase(emptySpaces.begin());
			emptySpaces.insert(emptySpaces.begin(), i2(address + mSize, area - mSize));
			mSize = 0;
		}
		else if (area == mSize) {
			if (spaces[id].size() > 0) {
				i2 data = *spaces[id].rbegin();
				if (data.first + data.second == address) {
					*spaces[id].rbegin() = i2(data.first, data.second + mSize);
				}
				else {
					spaces[id].push_back(i2(address, mSize));
				}
			}
			else {
				spaces[id].push_back(i2(address, mSize));
			}
			emptySpaces.erase(emptySpaces.begin());
			mSize = 0;
		}
		else {
			if (spaces[id].size() > 0) {
				i2 data = *spaces[id].rbegin();
				if (data.first + data.second == address) {
					*spaces[id].rbegin() = i2(data.first, data.second + area);
				}
				else {
					spaces[id].push_back(i2(address, area));
				}
			}
			else {
				spaces[id].push_back(i2(address, area));
			}
			emptySpaces.erase(emptySpaces.begin());
			mSize -= area;
		}
	}
	//cout << spaces[id][0].first + 1 << '\n';
	return (spaces[id][0].first + 1);
}

int remove(int mId) {
	int id = hashMap[mId];
	int ret = (int)spaces[id].size();
	for (i2 data : spaces[id]) {
		emptySpaces.insert(data);
	}
	spaces[id].clear();
	totalSize -= sizes[id];
	//cout << ret << '\n';
	return ret;
}

int count(int mStart, int mEnd) {
	mStart--;
	mEnd--;
	int ret = 0;
	for (int i = 0; i < fileNum; i++) {
		int start = 0, end = (int)spaces[i].size() - 1;
		while (start <= end) {
			int mid = (start + end) / 2;
			i2 data = spaces[i][mid];
			if (data.first + data.second - 1 < mStart) {
				start = mid + 1;
			}
			else if (data.first > mEnd) {
				end = mid - 1;
			}
			else {
				ret++;
				break;
			}
		}
	}
	//cout << ret << '\n';
	return ret;
}