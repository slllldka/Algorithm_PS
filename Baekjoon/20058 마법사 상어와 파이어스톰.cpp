#include <iostream>
#include <cmath>
#include <queue>
#include <utility>
#include <cstring>

using namespace std;

typedef pair<int, int> i2;

int x[4] = { -1, 0, 1, 0 };
int y[4] = { 0, -1, 0, 1 };

bool visit[64][64];

int n, N, Q;
int map[64][64];
int stepL[1000];
int temp[64];
queue<i2> reduceIdx, areaQueue;

void fireStorm(int);
void rotate(int, int, int);
void reduceIce();
int getMaxArea();

int main() {
	cin >> n >> Q;
	N = (int)pow(2, n);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < Q; i++) {
		cin >> stepL[i];
		fireStorm(stepL[i]);
	}


	int sum = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			sum += map[i][j];
		}
	}
	cout << sum << endl << getMaxArea();

	return 0;
}

void fireStorm(int L) {
	int len = (int)pow(2, L);
	for (int i = 0; i < N / len; i++) {
		for (int j = 0; j < N / len; j++) {
			rotate(len * i, len * j, len);
		}
	}
	reduceIce();
}

void rotate(int xPos, int yPos, int len) {
	if (len > 1) {
		int startX = xPos - x[0] * (len - 1);
		int startY = yPos - y[0] * (len - 1);
		int endX = xPos, endY = yPos;
		for (int i = 0; i < len - 1; i++) {
			temp[i] = map[xPos][yPos + i];
		}
		
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < len - 1; j++) {
				if (i < 3) {
					map[endX + x[(i + 3) % 4] * j][endY + y[(i + 3) % 4] * j]
						= map[startX + x[i] * j][startY + y[i] * j];
				}
				else {
					map[endX + x[(i + 3) % 4] * j][endY + y[(i + 3) % 4] * j]
						= temp[j];
				}
			}
			if (i < 3) {
				endX = startX;
				endY = startY;
				startX -= x[i + 1] * (len - 1);
				startY -= y[i + 1] * (len - 1);
			}
		}

		rotate(xPos + 1, yPos + 1, len - 2);
	}
}

void reduceIce() {
	int newX = 0, newY = 0, count = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			count = 0;
			if (map[i][j] > 0) {
				for (int k = 0; k < 4; k++) {
					newX = i + x[k];
					newY = j + y[k];
					if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
						if (map[newX][newY] == 0) {
							count++;
						}
					}
					else {
						count++;
					}
				}

				if (count >= 2) {
					reduceIdx.push(i2(i, j));
				}
			}
		}
	}

	i2 data;
	while (!reduceIdx.empty()) {
		data = reduceIdx.front();
		map[data.first][data.second]--;
		reduceIdx.pop();
	}
}

int getMaxArea() {
	int area = 0, maxArea = 0, newX = 0, newY = 0;
	i2 data;
	memset(visit, false, sizeof(visit));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!visit[i][j] && map[i][j] > 0) {
				visit[i][j] = true;
				areaQueue.push(i2(i, j));
				area = 1;
				while (!areaQueue.empty()) {
					data = areaQueue.front();
					areaQueue.pop();
					for (int k = 0; k < 4; k++) {
						newX = data.first + x[k];
						newY = data.second + y[k];
						if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
							if (!visit[newX][newY] && map[newX][newY] > 0) {
								visit[newX][newY] = true;
								areaQueue.push(i2(newX, newY));
								area++;
							}
						}
					}
				}
				maxArea = area > maxArea ? area : maxArea;
			}
		}
	}

	return maxArea;
}