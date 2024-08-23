#include <iostream>
#include <tuple>
#include <utility>

using namespace std;

typedef pair<int, int> i2;
typedef tuple<int, int, int> i3;

int x[4] = { -1, 1, 0, 0 };
int y[4] = { 0, 0, -1, 1 };

int N, M, K, Time = 0;
i3 sharks[401];
i2 smell[20][20];
int map[20][20];
int priority[401][4][4];

void bruteForce();
void reduceSmell();
void spreadSmell();
bool moveSharks();

int main() {
	cin >> N >> M >> K;
	int input = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> input;
			map[i][j] = input;
			if (input > 0) {
				sharks[input] = i3(i, j, 0);
				
			}
		}
	}

	for (int i = 1; i <= M; i++) {
		cin >> get<2>(sharks[i]);
	}

	for (int i = 1; i <= M; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				cin >> priority[i][j][k];
			}
		}
	}

	bruteForce();
	if (Time > 1000) {
		cout << -1;
	}
	else {
		cout << Time;
	}
	return 0;
}

void bruteForce() {
	spreadSmell();
	while (moveSharks());
}

void reduceSmell() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (smell[i][j].first > 0) {
				smell[i][j].second--;
				if (smell[i][j].second == 0) {
					smell[i][j] = i2(0, 0);
				}
			}
		}
	}
}

void spreadSmell() {
	for (int i = 1; i <= M; i++) {
		if (get<0>(sharks[i]) != -1) {
			smell[get<0>(sharks[i])][get<1>(sharks[i])] = i2(i, K);
		}
	}
}

bool moveSharks() {
	int xPos = 0, yPos = 0, dir = 0;
	int newX = 0, newY = 0, newDir = 0;
	int subNewX = 0, subNewY = 0, subNewDir = 0;
	int smellX = 0, smellY = 0;
	bool isMoved = false;
	for (int i = 1; i <= M; i++) {
		tie(xPos, yPos, dir) = sharks[i];
		subNewX = -1;
		subNewY = -1;
		subNewDir = -1;
		isMoved = false;
		if (xPos != -1) {
			map[xPos][yPos] = 0;
			for (int j = 0; j < 4; j++) {
				newDir = priority[i][dir - 1][j] - 1;
				newX = xPos + x[newDir];
				newY = yPos + y[newDir];
				if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
					if (smell[newX][newY].first == 0) {
						if (map[newX][newY] > 0 && map[newX][newY] < i) {
							sharks[i] = i3(-1, -1, -1);
							isMoved = true;
							break;
						}
						else {
							sharks[i] = i3(newX, newY, newDir + 1);
							map[newX][newY] = i;
							isMoved = true;
							break;
						}
					}
					else if (smell[newX][newY].first == i) {
						if (subNewX == -1) {
							subNewX = newX;
							subNewY = newY;
							subNewDir = newDir + 1;
						}
					}
				}
			}

			if (!isMoved) {
				if (map[subNewX][subNewY] > 0 && map[subNewX][subNewY] < i) {
					sharks[i] = i3(-1, -1, -1);
				}
				else {
					sharks[i] = i3(subNewX, subNewY, subNewDir);
					map[subNewX][subNewY] = i;
				}
			}
		}
	}
	Time++;

	reduceSmell();
	spreadSmell();

	if (Time > 1000) {
		return false;
	}
	else {
		for (int i = 2; i <= M; i++) {
			if (get<0>(sharks[i]) != -1) {
				return true;
			}
		}

		return false;
	}
}