#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int x[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int y[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dir[4] = { 2, 1, 4, 3 };

int M, S;
int smell[5][5];
int map[5][5][8], copiedFish[5][5][8];
int sharkX, sharkY;

void copyFish();
void fishMove();
void sharkMoves();
void smellDisappears();
void pasteFish();


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int fishX, fishY, d, result = 0;

	memset(map, 0, sizeof(map));

	cin >> M >> S;
	for (int i = 0; i < M; i++) {
		cin >> fishX >> fishY >> d;
		map[fishX][fishY][d - 1]++;
	}
	cin >> sharkX >> sharkY;

	for (int i = 0; i < S; i++) {
		copyFish();
		fishMove();

		/*for (int j = 1; j <= 4; j++) {
			for (int k = 1; k <= 4; k++) {
				int cumSum = 0;
				for (int n = 0; n < 8; n++) {
					cumSum += map[j][k][n];
				}
				cout << cumSum << ' ';
			}
			cout << '\n';
		}*/

		smellDisappears();
		sharkMoves();
		pasteFish();
	}

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int k = 0; k < 8; k++) {
				result += map[i][j][k];
			}
		}
	}
	cout << result;

	return 0;
}

void copyFish() {
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int k = 0; k < 8; k++) {
				copiedFish[i][j][k] = map[i][j][k];
			}
		}
	}
}
void fishMove() {
	int num[5][5][8] = {0}, newX, newY;
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int k = 0; k < 8; k++) {
				num[i][j][k] = map[i][j][k];
			}
		}
	}

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int k = 0; k < 8; k++) {
				for (int m = 0; m < 8; m++) {
					newX = i + x[(k + 8 - m) % 8];
					newY = j + y[(k + 8 - m) % 8];
					if (newX >= 1 && newX <= 4 && newY >= 1 && newY <= 4) {
						if (((newX != sharkX) || (newY != sharkY)) && (smell[newX][newY] == 0)) {
							map[newX][newY][(k + 8 - m) % 8] += num[i][j][k];
							map[i][j][k] -= num[i][j][k];
							break;
						}
					}
				}
			}
		}
	}
}

void sharkMoves() {
	bool canMove = true, visit[5][5];
	int num = 0, maxNum = 0, newX = 0, newY = 0;
	vector<int> maxPath = {4, 4, 4}, path = {0, 0, 0};

	while (true) {
		canMove = true;
		newX = sharkX;
		newY = sharkY;
		num = 0;
		memset(visit, false, sizeof(visit));
		for (int i = 0; i < 3; i++) {
			newX += x[path[i]];
			newY += y[path[i]];
			if (newX >= 1 && newX <= 4 && newY >= 1 && newY <= 4) {
				if (!visit[newX][newY]) {
					visit[newX][newY] = true;
					num += map[newX][newY][0] + map[newX][newY][1] + map[newX][newY][2] + map[newX][newY][3]
						+ map[newX][newY][4] + map[newX][newY][5] + map[newX][newY][6] + map[newX][newY][7];
				}
			}
			else {
				canMove = false;
				break;
			}
		}
		if (canMove) {
			if (num > maxNum) {
				maxNum = num;
				maxPath = vector<int>(path);
			}
			else if (num == maxNum) {
				int pathNum = dir[path[0] / 2] * 100 + dir[path[1] / 2] * 10 + dir[path[2] / 2];
				int maxPathNum = dir[maxPath[0] / 2] * 100 + dir[maxPath[1] / 2] * 10 + dir[maxPath[2] / 2];
				if (pathNum < maxPathNum) {
					maxNum = num;
					maxPath = vector<int>(path);
				}
			}
		}

		if (path[2] == 6) {
			if (path[1] == 6) {
				if (path[0] == 6) {
					break;
				}
				else {
					path[0] += 2;
					path[1] = 0;
					path[2] = 0;
				}
			}
			else {
				path[1] += 2;
				path[2] = 0;
			}
		}
		else {
			path[2] += 2;
		}
	}

	//cout << maxNum << ' ' << maxPath[0] << maxPath[1] << maxPath[2] << '\n';

	newX = sharkX;
	newY = sharkY;
	for (int i : maxPath) {
		newX += x[i];
		newY += y[i];
		if (newX >= 1 && newX <= 4 && newY >= 1 && newY <= 4) {
			for (int j = 0; j < 8; j++) {
				if (map[newX][newY][j] > 0) {
					map[newX][newY][j] = 0;
					smell[newX][newY] = 2;
				}
			}
		}
	}
	sharkX = newX;
	sharkY = newY;
	//cout << sharkX << sharkY << '\n';
}

void smellDisappears() {
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			if (smell[i][j] > 0) {
				smell[i][j]--;
			}
		}
	}
}

void pasteFish() {
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int k = 0; k < 8; k++) {
				map[i][j][k] += copiedFish[i][j][k];
			}
		}
	}
}