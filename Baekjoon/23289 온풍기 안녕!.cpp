#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <utility>
#include <tuple>

using namespace std;

typedef pair<int, int> i2;
typedef tuple<int, int, int> i3;
typedef tuple<bool, bool, bool, bool> b4;

int xDir[4] = { 0, 0, -1, 1 };
int yDir[4] = { 1, -1, 0, 0 };

int R, C, K, W, Chocolate = 0;
int map[20][20];
int temp[20][20];
bool visit[20][20];
b4 walls[20][20];
queue<i3> q;
vector<i3> fans;
vector<i2> investigateSpace;

void spreadWind(int, int, int);
bool getWallExist(int, int, int);
void controlTemperatureAndReduceOutermost();
bool investigate();

int main() {
	int input, x, y, t;
	cin >> R >> C >> K;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> input;
			if (input >= 1 && input < 5) {
				input--;
				fans.push_back(i3(i, j, input));
			}
			else if (input == 5) {
				investigateSpace.push_back(i2(i, j));
			}
		}
	}

	cin >> W;
	for (int i = 0; i < W; i++) {
		cin >> x >> y >> t;
		x--;
		y--;
		if (t == 0) {
			get<2>(walls[x][y]) = true;
			get<3>(walls[x - 1][y]) = true;
		}
		else if (t == 1) {
			get<0>(walls[x][y]) = true;
			get<1>(walls[x][y + 1]) = true;
		}
	}

	while (Chocolate <= 100) {
		for (i3 fan : fans) {
			spreadWind(get<0>(fan), get<1>(fan), get<2>(fan));
		}
		controlTemperatureAndReduceOutermost();
		Chocolate++;

		/*for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				cout << map[i][j];
			}
			cout << endl;
		}
		cout << endl;*/
		if (investigate()) {
			break;
		}
	}
	cout << Chocolate;

	return 0;
}

void spreadWind(int x, int y, int d) {
	memset(visit, false, sizeof(visit));
	q.push(i3(x + xDir[d], y + yDir[d], 5));
	map[x + xDir[d]][y + yDir[d]] += 5;
	visit[x + xDir[d]][y + yDir[d]] = true;
	while(!q.empty()) {
		i3 data = q.front();
		q.pop();
		int xPos, yPos, amt;
		tie(xPos, yPos, amt) = data;

		xPos += xDir[d];
		yPos += yDir[d];

		if (xPos >= 0 && xPos < R && yPos >= 0 && yPos < C) {
			if (amt > 1) {
				amt--;
				if (xDir[d] != 0) {
					if (xPos >= 0 && xPos < R
						&& (yPos - 1) >= 0 && (yPos - 1) < C) {
						if (!getWallExist(xPos - xDir[d], yPos, 1)
							&& !getWallExist(xPos - xDir[d], yPos - 1, d)) {
							if (!visit[xPos][yPos - 1]) {
								map[xPos][yPos - 1] += amt;
								visit[xPos][yPos - 1] = true;
								q.push(i3(xPos, yPos - 1, amt));
							}
						}
					}
					if (xPos >= 0 && xPos < R
						&& yPos >= 0 && yPos < C) {
						if (!getWallExist(xPos - xDir[d], yPos, d)) {
							if (!visit[xPos][yPos]) {
								map[xPos][yPos] += amt;
								visit[xPos][yPos] = true;
								q.push(i3(xPos, yPos, amt));
							}
						}
					}
					if (xPos >= 0 && xPos < R
						&& (yPos + 1) >= 0 && (yPos + 1) < C) {
						if (!getWallExist(xPos - xDir[d], yPos, 0)
							&& !getWallExist(xPos - xDir[d], yPos + 1, d)) {
							if (!visit[xPos][yPos + 1]) {
								map[xPos][yPos + 1] += amt;
								visit[xPos][yPos + 1] = true;
								q.push(i3(xPos, yPos + 1, amt));
							}
						}
					}
				}
				else if (yDir[d] != 0) {
					if ((xPos - 1) >= 0 && (xPos - 1) < R
						&& yPos >= 0 && yPos < C) {
						if (!getWallExist(xPos, yPos - yDir[d], 2)
							&& !getWallExist(xPos - 1, yPos - yDir[d], d)) {
							if (!visit[xPos - 1][yPos]) {
								map[xPos - 1][yPos] += amt;
								visit[xPos - 1][yPos] = true;
								q.push(i3(xPos - 1, yPos, amt));
							}
						}
					}
					if (xPos >= 0 && xPos < R
						&& yPos >= 0 && yPos < C) {
						if (!getWallExist(xPos, yPos - yDir[d], d)) {
							if (!visit[xPos][yPos]) {
								map[xPos][yPos] += amt;
								visit[xPos][yPos] = true;
								q.push(i3(xPos, yPos, amt));
							}
						}
					}
					if ((xPos + 1) >= 0 && (xPos + 1) < R
						&& yPos >= 0 && yPos < C) {
						if (!getWallExist(xPos, yPos - yDir[d], 3)
							&& !getWallExist(xPos + 1, yPos - yDir[d], d)) {
							if (!visit[xPos + 1][yPos]) {
								map[xPos + 1][yPos] += amt;
								visit[xPos + 1][yPos] = true;
								q.push(i3(xPos + 1, yPos, amt));
							}
						}
					}
				}
			}
		}
	}
}

bool getWallExist(int x, int y, int d) {
	switch (d) {
	case 0:
		return get<0>(walls[x][y]);
	case 1:
		return get<1>(walls[x][y]);
	case 2:
		return get<2>(walls[x][y]);
	case 3:
		return get<3>(walls[x][y]);
	}
}

void controlTemperatureAndReduceOutermost() {
	int newX, newY, amt = 0;
	memset(temp, 0, sizeof(temp));

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			for (int d = 0; d < 4; d++) {
				newX = i + xDir[d];
				newY = j + yDir[d];
				if (newX >= 0 && newX < R && newY >= 0 && newY < C) {
					if (!getWallExist(i, j, d)) {
						if (map[i][j] > map[newX][newY]) {
							amt = (map[i][j] - map[newX][newY]) / 4;
							temp[newX][newY] += amt;
							temp[i][j] -= amt;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			map[i][j] += temp[i][j];
			if ((i == 0) || (i == (R - 1)) || (j == 0) || (j == (C - 1))) {
				if (map[i][j] >= 1) {
					map[i][j]--;
				}
			}
		}
	}
}

bool investigate() {
	for (i2 pos : investigateSpace) {
		if (map[pos.first][pos.second] < K) {
			return false;
		}
	}

	return true;
}