#include <iostream>
#include <list>

using namespace std;

int N, K;
int startIdx = 0;
int durability[200];
bool robotExist[200];

list<int> robots;

void rotate();
void moveRobot();
void putRobot();
bool checkDurability();

int getEndIdx() {
	return (startIdx + N - 1 + 2 * N) % (2 * N);
}


int main() {
	cin >> N >> K;
	for (int i = 0; i < 2 * N; i++) {
		cin >> durability[i];
	}
	int count = 0;
	while (checkDurability()) {
		rotate();
		moveRobot();
		putRobot();
		count++;
	}

	cout << count;
	return 0;
}

void rotate() {
	startIdx--;
	if (startIdx < 0) {
		startIdx += 2 * N;
	}

	int idx = 0, endIdx = getEndIdx();
	for (list<int>::iterator iter = robots.begin(); iter != robots.end();) {
		idx = *iter;
		if (idx == endIdx) {
			robotExist[idx] = false;
			iter = robots.erase(iter);
		}
		else {
			iter++;
		}
	}
}
void moveRobot() {
	int idx = 0, nextIdx = 0, endIdx = getEndIdx();
	for (list<int>::iterator iter = robots.begin(); iter != robots.end();) {
		idx = *iter;
		nextIdx = (idx + 1) % (2*N);
		if (!robotExist[nextIdx] && durability[nextIdx] > 0) {
			*iter = nextIdx;
			robotExist[nextIdx] = true;
			robotExist[idx] = false;
			durability[nextIdx]--;
			if (*iter == endIdx) {
				robotExist[*iter] = false;
				iter = robots.erase(iter);
				continue;
			}
		}
		iter++;
	}
}
void putRobot() {
	if (durability[startIdx] > 0) {
		robots.push_back(startIdx);
		robotExist[startIdx] = true;
		durability[startIdx]--;
	}
}
bool checkDurability() {
	int count = 0;
	for (int i = 0; i < 2 * N; i++) {
		if (durability[i] == 0) {
			count++;
		}
	}

	if (count >= K) {
		return false;
	}
	else {
		return true;
	}
}

