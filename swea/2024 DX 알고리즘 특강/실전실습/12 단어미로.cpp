#include <unordered_map>
#include <queue>
#include <cstring>
#include <iostream>

using namespace std;

unordered_map<long long, int> hashMap;
char str[30001][12];
long long hashVal[30001];
priority_queue<long long> firstTwo[1 << 10], lastTwo[1 << 10]
, firstFour[1 << 20], lastFour[1 << 20], middleThree[1 << 15];
int firstLen[30001], lastLen[30001];
int cur;

long long stringHash(char word[]) {
	int idx = 0;
	long long ret = 0;
	while (word[idx]) {
		ret += ((long long)word[idx] - 'a' + 1) * ((long long)1 << (5 * (10 - idx)));
		idx++;
	}
	return ret;
}

int first2(char word[]) {
	int ret = 0;
	for (int i = 0; i < 2; i++) {
		ret += (word[i] - 'a' + 1) * (1 << 5 * (1 - i));
	}
	return ret;
}
int first4(char word[]) {
	int ret = 0;
	for (int i = 0; i < 4; i++) {
		ret += (word[i] - 'a' + 1) * (1 << 5 * (3 - i));
	}
	return ret;
}
int middle3(char word[]) {
	int ret = 0;
	for (int i = 0; i < 3; i++) {
		ret += (word[i + 4] - 'a' + 1) * (1 << 5 * (2 - i));
	}
	return ret;
}
int last2(char word[]) {
	int ret = 0;
	for (int i = 0; i < 2; i++) {
		ret += (word[i + 9] - 'a' + 1) * (1 << 5 * (1 - i));
	}
	return ret;
}
int last4(char word[]) {
	int ret = 0;
	for (int i = 0; i < 4; i++) {
		ret += (word[i + 7] - 'a' + 1) * (1 << 5 * (3 - i));
	}
	return ret;
}

void init()
{
	hashMap.clear();
	/*for (int i = 0; i < (1 << 10); i++) {
		firstTwo[i] = priority_queue<long long>();
		lastTwo[i] = priority_queue<long long>();
	}
	for (int i = 0; i < (1 << 15); i++) {
		middleThree[i] = priority_queue<long long>();
	}
	for (int i = 0; i < (1 << 20); i++) {
		firstFour[i] = priority_queue<long long>();
		lastFour[i] = priority_queue<long long>();
	}*/
	/*memset(str, 0, sizeof(str));
	memset(hashVal, 0, sizeof(hashVal));
	memset(firstLen, 0, sizeof(firstLen));
	memset(lastLen, 0, sizeof(lastLen));*/
	cur = -1;
}

void addRoom(int mID, char mWord[], int mDirLen[])
{
	long long hash = stringHash(mWord);
	hashMap[hash] = mID;
	for (int i = 0; i < 12; i++) {
		str[mID][i] = mWord[i];
	}
	hashVal[mID] = hash;
	firstLen[mID] = mDirLen[0];
	lastLen[mID] = mDirLen[2];
	firstTwo[first2(mWord)].push(-hash);
	firstFour[first4(mWord)].push(-hash);
	middleThree[middle3(mWord)].push(-hash);
	lastTwo[last2(mWord)].push(-hash);
	lastFour[last4(mWord)].push(-hash);
}

void setCurrent(char mWord[])
{
	cur = hashMap[stringHash(mWord)];
}

int moveDir(int mDir)
{
	int comp = cur;
	if (mDir == 0) {
		if (firstLen[cur] == 2) {
			int hash = first2(str[cur]);
			while (!lastTwo[hash].empty()) {
				if (hashMap.count(-lastTwo[hash].top())) {
					break;
				}
				else {
					lastTwo[hash].pop();
				}
			}

			if (!lastTwo[hash].empty()) {
				if (lastTwo[hash].top() == -hashVal[cur]) {
					long long temp = hashVal[cur];
					lastTwo[hash].pop();
					while (!lastTwo[hash].empty()) {
						if (hashMap.count(-lastTwo[hash].top())) {
							break;
						}
						else {
							lastTwo[hash].pop();
						}
					}
					if (!lastTwo[hash].empty()) {
						cur = hashMap[-lastTwo[hash].top()];
					}
					lastTwo[hash].push(-temp);
				}
				else {
					if (!lastTwo[hash].empty()) {
						cur = hashMap[-lastTwo[hash].top()];
					}
				}
			}
		}
		else if (firstLen[cur] == 4) {
			int hash = first4(str[cur]);
			while (!lastFour[hash].empty()) {
				if (hashMap.count(-lastFour[hash].top())) {
					break;
				}
				else {
					lastFour[hash].pop();
				}
			}
			if (!lastFour[hash].empty()) {
				if (lastFour[hash].top() == -hashVal[cur]) {
					long long temp = hashVal[cur];
					lastFour[hash].pop();
					while (!lastFour[hash].empty()) {
						if (hashMap.count(-lastFour[hash].top())) {
							break;
						}
						else {
							lastFour[hash].pop();
						}
					}
					if (!lastFour[hash].empty()) {
						cur = hashMap[-lastFour[hash].top()];
					}
					lastFour[hash].push(-temp);
				}
				else {
					if (!lastFour[hash].empty()) {
						cur = hashMap[-lastFour[hash].top()];
					}
				}
			}
		}
	}
	else if (mDir == 1) {
		int hash = middle3(str[cur]);
		while (!middleThree[hash].empty()) {
			if (hashMap.count(-middleThree[hash].top())) {
				break;
			}
			else {
				middleThree[hash].pop();
			}
		}
		if (!middleThree[hash].empty()) {
			if (middleThree[hash].top() == -hashVal[cur]) {
				long long temp = hashVal[cur];
				middleThree[hash].pop();
				while (!middleThree[hash].empty()) {
					if (hashMap.count(-middleThree[hash].top())) {
						break;
					}
					else {
						middleThree[hash].pop();
					}
				}
				if (!middleThree[hash].empty()) {
					cur = hashMap[-middleThree[hash].top()];
				}
				middleThree[hash].push(-temp);
			}
			else {
				if (!middleThree[hash].empty()) {
					cur = hashMap[-middleThree[hash].top()];
				}
			}
		}
	}
	else if (mDir == 2) {
		if (lastLen[cur] == 2) {
			int hash = last2(str[cur]);
			while (!firstTwo[hash].empty()) {
				if (hashMap.count(-firstTwo[hash].top())) {
					break;
				}
				else {
					firstTwo[hash].pop();
				}
			}
			if (!firstTwo[hash].empty()) {
				if (firstTwo[hash].top() == -hashVal[cur]) {
					long long temp = hashVal[cur];
					firstTwo[hash].pop();
					while (!firstTwo[hash].empty()) {
						if (hashMap.count(-firstTwo[hash].top())) {
							break;
						}
						else {
							firstTwo[hash].pop();
						}
					}
					if (!firstTwo[hash].empty()) {
						cur = hashMap[-firstTwo[hash].top()];
					}
					firstTwo[hash].push(-temp);
				}
				else {
					if (!firstTwo[hash].empty()) {
						cur = hashMap[-firstTwo[hash].top()];
					}
				}
			}
		}
		else if (lastLen[cur] == 4) {
			int hash = last4(str[cur]);
			while (!firstFour[hash].empty()) {
				if (hashMap.count(-firstFour[hash].top())) {
					break;
				}
				else {
					firstFour[hash].pop();
				}
			}
			if (!firstFour[hash].empty()) {
				if (firstFour[hash].top() == -hashVal[cur]) {
					long long temp = hashVal[cur];
					firstFour[hash].pop();
					while (!firstFour[hash].empty()) {
						if (hashMap.count(-firstFour[hash].top())) {
							break;
						}
						else {
							firstFour[hash].pop();
						}
					}
					if (!firstFour[hash].empty()) {
						cur = hashMap[-firstFour[hash].top()];
					}
					firstFour[hash].push(-temp);
				}
				else {
					if (!firstFour[hash].empty()) {
						cur = hashMap[-firstFour[hash].top()];
					}
				}
			}
		}
	}

	if (comp == cur) {
		//cout << 0 << '\n';
		return 0;
	}
	else {
		//cout << cur << '\n';
		return cur;
	}
}

void changeWord(char mWord[], char mChgWord[], int mChgLen[])
{
	long long curHash = stringHash(mWord);
	long long nextHash = stringHash(mChgWord);
	int mID = hashMap[curHash];
	hashMap.erase(curHash);
	hashMap[nextHash] = mID;
	for (int i = 0; i < 12; i++) {
		str[mID][i] = mChgWord[i];
	}
	hashVal[mID] = nextHash;
	firstLen[mID] = mChgLen[0];
	lastLen[mID] = mChgLen[2];
	firstTwo[first2(mChgWord)].push(-nextHash);
	firstFour[first4(mChgWord)].push(-nextHash);
	middleThree[middle3(mChgWord)].push(-nextHash);
	lastTwo[last2(mChgWord)].push(-nextHash);
	lastFour[last4(mChgWord)].push(-nextHash);
}