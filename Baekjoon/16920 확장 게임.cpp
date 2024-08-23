#include <iostream>
#include <tuple>
#include <queue>

using namespace std;

typedef tuple<int, int, int> i3;

int x[4] = { 1, 0, -1, 0 };
int y[4] = { 0, -1, 0, 1 };

int N, M, P;
char map[1000][1000];
int* SI, * countCastle;
int Turn = 0;

queue<i3> q[9], subQ;

void BFS();

int main() {
	string input = "";
	cin >> N >> M >> P;
	SI = new int[P];
	countCastle = new int[P];
	for (int i = 0; i < P; i++) {
		cin >> SI[i];
		countCastle[i] = 0;
	}

	for (int i = 0; i < N; i++) {
		cin >> input;
		for (int j = 0; j < M; j++) {
			map[i][j] = input[j];
			if (map[i][j] >= '1' && map[i][j] <= '9') {
				q[map[i][j]-'1'].push(i3(i, j, 0));
			}
		}
	}

	BFS();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] >= '1' && map[i][j] <= '9') {
				countCastle[map[i][j] - '1']++;
			}
		}
	}

	for (int i = 0; i < P; i++) {
		cout << countCastle[i] << ' ';
	}
	
	return 0;
}

void BFS() {
	while (!(q[0].empty() && q[1].empty() && q[2].empty()
		&& q[3].empty() && q[4].empty() && q[5].empty()
		&& q[6].empty() && q[7].empty() && q[8].empty())) {
		for (int i = 0; i < 9; i++) {
			while (!q[i].empty()) {
				i3 data1 = q[i].front();
				int x1 = get<0>(data1);
				int y1 = get<1>(data1);
				int turn = get<2>(data1);
				if (turn > Turn) {
					break;
				}
				q[i].pop();

				subQ.push(i3(x1, y1, 0));
			}
			while (!subQ.empty()) {
				i3 data2 = subQ.front();
				int x1 = get<0>(data2);
				int y1 = get<1>(data2);
				int d = get<2>(data2);
				subQ.pop();

				int newX = 0, newY = 0;
				for (int j = 0; j < 4; j++) {
					newX = x1 + x[j];
					newY = y1 + y[j];
					if (newX >= 0 && newX < N && newY >= 0 && newY < M) {
						if (map[newX][newY] == '.') {
							map[newX][newY] = i + '1';
							if ((d + 1) < SI[i]) {
								subQ.push(i3(newX, newY, d + 1));
							}
							else if ((d + 1) == SI[i]) {
								q[i].push(i3(newX, newY, Turn + 1));
							}
						}
					}
				}
			}

			if (i == 8) {
				Turn++;
			}
		}
	}
}