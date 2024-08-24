#include <iostream>
#include <deque>
#include <unordered_map>

int length;
std::deque<char> str;

bool reversed;
std::unordered_map<int, int> hashMap;

void modifyHashes(bool add, int startIdx, int endIdx) {
	int hash;
	for (int i = startIdx - 3; i < endIdx; i++) {
		if (i < 0) {
			continue;
		}
		hash = str[i] - 'a' + 1;
		if (i >= startIdx) {
			if (hashMap.count(hash)) {
				if (add) {
					hashMap[hash]++;
				}
				else {
					hashMap[hash]--;
					if (hashMap[hash] == 0) {
						hashMap.erase(hash);
					}
				}
			}
			else {
				if (add) {
					hashMap[hash] = 1;
				}
			}
		}
		if (i + 1 < length) {
			hash += (str[i + 1] - 'a' + 1) * 32;
			if (i + 1 >= startIdx) {
				if (hashMap.count(hash)) {
					if (add) {
						hashMap[hash]++;
					}
					else {
						hashMap[hash]--;
						if (hashMap[hash] == 0) {
							hashMap.erase(hash);
						}
					}
				}
				else {
					if (add) {
						hashMap[hash] = 1;
					}
				}
			}
		}
		if (i + 2 < length) {
			hash += (str[i + 2] - 'a' + 1) * 32 * 32;
			if (i + 2 >= startIdx) {
				if (hashMap.count(hash)) {
					if (add) {
						hashMap[hash]++;
					}
					else {
						hashMap[hash]--;
						if (hashMap[hash] == 0) {
							hashMap.erase(hash);
						}
					}
				}
				else {
					if (add) {
						hashMap[hash] = 1;
					}
				}
			}
		}
		if (i + 3 < length) {
			hash += (str[i + 3] - 'a' + 1) * 32 * 32 * 32;
			if (i + 3 >= startIdx) {
				if (hashMap.count(hash)) {
					if (add) {
						hashMap[hash]++;
					}
					else {
						hashMap[hash]--;
						if (hashMap[hash] == 0) {
							hashMap.erase(hash);
						}
					}
				}
				else {
					if (add) {
						hashMap[hash] = 1;
					}
				}
			}
		}
	}
}

void init(char mStr[])
{
	int i = 0;
	reversed = false;
	str.clear();
	hashMap.clear();
	while (mStr[i] != 0) {
		str.push_back(mStr[i]);
		i++;
	}
	length = i;
	modifyHashes(true, 0, length);
}

void appendWord(char mWord[])
{
	int i = 0, wordLen;
	while (mWord[i] != 0) {
		if (reversed) {
			str.push_front(mWord[i]);
		}
		else {
			str.push_back(mWord[i]);
		}
		i++;
	}
	wordLen = i;
	length += wordLen;

	if (reversed) {
		modifyHashes(true, 0, wordLen);
	}
	else {
		modifyHashes(true, length - wordLen, length);
	}
}

void cut(int k)
{
	if (reversed) {
		modifyHashes(false, 0, k);
		for (int i = 0; i < k; i++) {
			str.pop_front();
		}
	}
	else {
		modifyHashes(false, length - k, length);
		for (int i = 0; i < k; i++) {
			str.pop_back();
		}
	}
	length -= k;
}

void reverse()
{
	reversed = !reversed;
}

int countOccurrence(char mWord[])
{
	int i = 0, hash = 0;
	if (reversed) {
		while (mWord[i] != 0) {
			hash += (mWord[i] - 'a' + 1) * (1 << (5 * (3 - i)));
			i++;
		}
		hash /= (1 << 5 * (4 - i));
	}
	else {
		while (mWord[i] != 0) {
			hash += (mWord[i] - 'a' + 1) * (1 << (5 * i));
			i++;
		}
	}
	//std::cout << hash << '\n';
	if (hashMap.count(hash)) {
		//std::cout << hashMap[hash] << '\n';
		return hashMap[hash];
	}
	else {
		//std::cout << 0 << '\n';
		return 0;
	}
}