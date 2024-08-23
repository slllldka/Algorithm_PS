#include <iostream>
#include <utility>
#include <tuple>
#include <list>

using namespace std;

typedef pair<int, int> i2;
typedef tuple<int, int, int> i3;

int x[9] = {-100,  0, -1, -1, -1, 0, 1, 1, 1 };
int y[9] = {-100,  -1, -1, 0, 1, 1, 1, 0, -1 };

int N, M;

int map[50][50];
list<i2> clouds;
list<i2> removedClouds;
list<i3> copyBugIdx;

void moveClouds(int, int);
int movePos(int, int);

int main() {
	int d = 0, s = 0;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	clouds.push_back(i2(N - 1, 0));
	clouds.push_back(i2(N - 1, 1));
	clouds.push_back(i2(N - 2, 0));
	clouds.push_back(i2(N - 2, 1));
	for (int i = 0; i < M; i++) {
		cin >> d >> s;
		moveClouds(d, s);
	}

	int sum = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			sum += map[i][j];
		}
	}
	cout << sum;
	return 0;
}

void moveClouds(int d, int s) {
	//1, 2, 3
	for (list<i2>::iterator iter = clouds.begin(); iter != clouds.end();) {
		iter->first = movePos(iter->first, x[d] * s);
		iter->second = movePos(iter->second, y[d] * s);
		map[iter->first][iter->second] += 1;
		removedClouds.push_back(*iter);
		iter = clouds.erase(iter);
	}

	//4
	copyBugIdx.clear();
	int count = 0, newX = 0, newY = 0;
	for (list<i2>::iterator iter = removedClouds.begin();
		iter != removedClouds.end(); iter++) {
		count = 0;
		for (int i = 2; i <= 8; i += 2) {
			newX = iter->first + x[i];
			newY = iter->second + y[i];
			if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
				if (map[newX][newY] > 0) {
					count++;
				}
			}
		}
		copyBugIdx.push_back(i3(iter->first, iter->second, count));
	}
	int xPos = 0, yPos = 0, quantity = 0;
	for (list<i3>::iterator iter = copyBugIdx.begin();
		iter != copyBugIdx.end(); iter++) {
		tie(xPos, yPos, quantity) = *iter;
		map[xPos][yPos] += quantity;
	}

	//5
	bool canMakeCloud = true;
	clouds.clear();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] >= 2) {
				canMakeCloud = true;
				for (list<i2>::iterator iter = removedClouds.begin();
					iter != removedClouds.end(); iter++) {
					if (i == iter->first && j == iter->second) {
						canMakeCloud = false;
						break;
					}
				}
				if (canMakeCloud) {
					clouds.push_back(i2(i, j));
					map[i][j] -= 2;
				}
			}
		}
	}
	removedClouds.clear();
}

int movePos(int pos, int delta) {
	int result = pos + delta;
	if (result < 0) {
		while (result < 0) {
			result += N;
		}
	}
	else if (result >= N) {
		while(result >= N) {
			result -= N;
		}
	}

	return result;
}