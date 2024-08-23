#include <iostream>
#include <queue>
#include <utility>

using namespace std;
using i2 = pair<int, int>;

int R, C, N;
int map[200][200];
int xDir[4] = { 1, 0, -1, 0 };
int yDir[4] = { 0, 1, 0, -1 };

int main() {
	int time = 0, newX, newY;
	string input;
	cin >> R >> C >> N;
	for (int i = 0; i < R; i++) {
		cin >> input;
		for (int j = 0; j < C; j++) {
			if (input[j] == '.') {
				map[i][j] = -1;
			}
			else {
				map[i][j] = 0;
			}
		}
	}
	time = 2;
	while (time <= N) {
		if (time % 2 == 0) {
			//install
			for (int i = 0; i < R; i++) {
				for (int j = 0; j < C; j++) {
					if (map[i][j] == -1) {
						map[i][j] = time;
					}
				}
			}
		}
		else {
			//explode
			for (int i = 0; i < R; i++) {
				for (int j = 0; j < C; j++) {
					if (map[i][j] == (time - 3)) {
						map[i][j] = -1;
						for (int k = 0; k < 4; k++) {
							newX = i + xDir[k];
							newY = j + yDir[k];
							if (newX >= 0 && newX < R && newY >= 0 && newY < C) {
								if (map[newX][newY] > (time - 3)) {
									map[newX][newY] = -1;
								}
							}
						}
					}
				}
			}
		}
		time++;
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (map[i][j] == -1) {
				cout << '.';
			}
			else {
				cout << 'O';
			}
		}
		cout << '\n';
	}

	return 0;
}