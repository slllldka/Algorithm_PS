#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

typedef tuple<int, int> i2;
typedef tuple<int, int, int, int> i4;

int x[4] = { 1, 0, -1, 0 };
int y[4] = { 0, -1, 0, 1 };
int xHorse[8] = { 2, 2, 1, -1, -2, -2, -1, 1 };
int yHorse[8] = { 1, -1, -2, -2, -1, 1, 2, 2 };

int K, W, H;
char map[200][200];

vector<i2> check[200][200];
queue<i4> q;

int BFS();
void moveMonkey(int, int, int, int);

int main() {
	cin >> K;
	cin >> H >> W;
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			cin >> map[i][j];
		}
	}

	if (W == 1 && H == 1) {
		if (map[0][0] == '0') {
			cout << 0;
		}
		else {
			cout << -1;
		}
	}
	else {
		cout << BFS();
	}
	return 0;
}

int BFS() {
	q.push(i4(0, 0, 0, 0));
	while (!q.empty()) {
		i4 data = q.front();
		int move = get<0>(data);
		int k = get<1>(data);
		int xPos = get<2>(data);
		int yPos = get<3>(data);
		q.pop();

		int newX = 0, newY = 0;
		for (int i = 0; i < 4; i++) {
			newX = xPos + x[i];
			newY = yPos + y[i];
			if (newX >= 0 && newX < W && newY >= 0 && newY < H) {
				if ((newX == (W - 1)) && (newY == (H - 1))) {
					if (map[newX][newY] == '0') {
						return (move + 1);
					}
					else {
						return -1;
					}
				}
				else {
					if (map[newX][newY] == '0') {
						moveMonkey(move + 1, k, newX, newY);
					}
				}
			}
		}

		if (k < K) {
			for (int i = 0; i < 8; i++) {
				newX = xPos + xHorse[i];
				newY = yPos + yHorse[i];
				if (newX >= 0 && newX < W && newY >= 0 && newY < H) {
					if ((newX == (W - 1)) && (newY == (H - 1))) {
						if (map[newX][newY] == '0') {
							return (move + 1);
						}
						else {
							return -1;
						}
					}
					else {
						if (map[newX][newY] == '0') {
							moveMonkey(move + 1, k + 1, newX, newY);
						}
					}
				}
			}
		}
	}

	return -1;
}

void moveMonkey(int move, int k, int newX, int newY) {
	for (int i = 0; i < (int)check[newX][newY].size(); i++) {
		i2 data = check[newX][newY][i];
		if (k == get<1>(data)) {
			if (move < get<0>(data)) {
				check[newX][newY][i] = i2(move, k);
				q.push(i4(move, k, newX, newY));
			}
			return;
		}
	}

	check[newX][newY].push_back(i2(move, k));
	q.push(i4(move, k, newX, newY));
}