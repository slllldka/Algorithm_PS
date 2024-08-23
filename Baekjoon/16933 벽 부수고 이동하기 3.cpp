#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

typedef tuple<int, int, int, int, int> i5;

int x[4] = { 1, 0, -1, 0 };
int y[4] = { 0, -1, 0, 1 };

int N, M, K;

char map[1000][1000];
int check[1000][1000][11];
queue<i5> q;

int BFS();

int main() {
	string input = "";
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		cin >> input;
		for (int j = 0; j < M; j++) {
			map[i][j] = input[j];
		}
	}

	cout << BFS();
	return 0;
}

int BFS() {
	q.push(i5(0, 0, 1, 0, -1));
	while (!q.empty()) {
		i5 data = q.front();
		int xPos = get<0>(data);
		int yPos = get<1>(data);
		int d = get<2>(data);
		int k = get<3>(data);
		int direction = get<4>(data);
		bool isDay = (d % 2 == 1);
		q.pop();

		if ((xPos == (N - 1)) && (yPos == (M - 1))) {
			return d;
		}

		int newX = 0, newY = 0;
		if (direction == -1) {
			for (int i = 0; i < 4; i++) {
				newX = xPos + x[i];
				newY = yPos + y[i];
				if (newX >= 0 && newX < N && newY >= 0 && newY < M) {
					if (map[newX][newY] == '0') {
						int j = 0;
						for (j = 0; j <= k; j++) {
							if (((d + 1) >= check[newX][newY][j])
								&& (check[newX][newY][j] != 0)) {
								break;
							}
						}
						if (j == k + 1) {
							check[newX][newY][k] = d + 1;
							q.push(i5(newX, newY, d + 1, k, -1));
						}
					}
					else {
						if (k < K) {
							if (isDay) {
								int j = 0;
								for (j = 0; j <= k + 1; j++) {
									if (((d + 1) >= check[newX][newY][j])
										&& (check[newX][newY][j] != 0)) {
										break;
									}
								}
								if (j == k + 2) {
									check[newX][newY][k + 1] = d + 1;
									q.push(i5(newX, newY, d + 1, k + 1, -1));
								}
							}
							else {
								q.push(i5(xPos, yPos, d + 1, k, i));
							}
						}
					}
				}
			}
		}
		else {
			newX = xPos + x[direction];
			newY = yPos + y[direction];
			int j = 0;
			for (j = 0; j <= k + 1; j++) {
				if (((d + 1) >= check[newX][newY][j])
					&& (check[newX][newY][j] != 0)) {
					break;
				}
			}
			if (j == k + 2) {
				check[newX][newY][k + 1] = d + 1;
				q.push(i5(newX, newY, d + 1, k + 1, -1));
			}
		}
	}

	return -1;
}