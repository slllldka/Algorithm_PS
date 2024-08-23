#include <iostream>
#include <utility>

using namespace std;

typedef pair<int, int> i2;

int x[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int y[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };

int maxSum = 0;
i2 map[4][4];

void bruteForce(int);

int main() {
	int a = 0, b = 0, first = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> a >> b;
			map[i][j] = i2(a, b - 1);
		}
	}
	first = map[0][0].first;
	map[0][0] = i2(-1, map[0][0].second);

	bruteForce(first);

	cout << maxSum;
	return 0;
}

void bruteForce(int sum) {
	i2 save[4][4];
	i2 shark = i2(0, 0);
	i2 fish[16] = { i2(-1, -1), i2(-1, -1), i2(-1, -1), i2(-1, -1)
		, i2(-1, -1), i2(-1, -1), i2(-1, -1), i2(-1, -1)
		, i2(-1, -1), i2(-1, -1), i2(-1, -1), i2(-1, -1)
		, i2(-1, -1), i2(-1, -1), i2(-1, -1), i2(-1, -1) };

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (map[i][j].first > 0) {
				fish[map[i][j].first - 1] = i2(i, j);
			}
			else if (map[i][j].first == -1) {
				shark = i2(i, j);
			}
		}
	}

	//물고기 이동
	i2 oneFish;
	int num = 0, d = 0, newX = 0, newY = 0;
	for (int i = 0; i < 16; i++) {
		if (fish[i].first != -1) {
			oneFish = map[fish[i].first][fish[i].second];
			d = oneFish.second;

			for (int j = 0; j < 8; j++) {
				newX = fish[i].first + x[(d + j) % 8];
				newY = fish[i].second + y[(d + j) % 8];
				if (newX >= 0 && newX < 4 && newY >= 0 && newY < 4) {
					if (map[newX][newY].first > 0) {
						i2 temp = map[newX][newY];
						map[newX][newY] = i2(i + 1, (d + j) % 8);
						map[fish[i].first][fish[i].second] = temp;
						fish[temp.first - 1] = i2(fish[i].first, fish[i].second);
						fish[i] = i2(newX, newY);
						break;
					}
					else if (map[newX][newY].first == 0) {
						map[newX][newY] = i2(i + 1, (d + j) % 8);
						map[fish[i].first][fish[i].second] = i2(0, 0);
						fish[i] = i2(newX, newY);
						break;
					}
				}
			}

		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			save[i][j] = map[i][j];
		}
	}

	//상어 이동
	bool isSharkMoved = false;
	d = map[shark.first][shark.second].second;
	for (int i = 1;; i++) {
		newX = shark.first + x[d] * i;
		newY = shark.second + y[d] * i;
		if (newX >= 0 && newX < 4 && newY >= 0 && newY < 4) {
			if (map[newX][newY] != i2(0, 0)) {
				isSharkMoved = true;
				num = map[newX][newY].first;
				map[shark.first][shark.second] = i2(0, 0);
				map[newX][newY] = i2(-1, map[newX][newY].second);
				bruteForce(sum + num);

				//restore
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						map[j][k] = save[j][k];
					}
				}
			}
		}
		else {
			break;
		}
	}

	if (!isSharkMoved) {
		maxSum = maxSum > sum ? maxSum : sum;
	}
}