#include <iostream>
#include <cstring>
#include <queue>
#include <utility>

using namespace std;

typedef pair<int, int> i2;

int x[4] = { 1, 0, -1, 0 };
int y[4] = { 0, -1, 0, 1 };

char map[12][7];
bool visit[12][6];

bool chain();
void fall();

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for (int i = 0; i < 12; i++) {
		cin >> map[i];
	}

	int result = 0;
	while (chain()) {
		result++;
		fall();
		/*for (int i = 0; i < 12; i++) {
			cout << map[i] << '\n';
		}
		cout << '\n';*/
	}

	cout << result;

	return 0;
}

bool chain() {
	bool result = false;
	queue<i2> q;
	queue<i2> connected;
	memset(visit, false, sizeof(visit));
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			if (!visit[i][j]) {
				visit[i][j] = true;
				if (map[i][j] != '.') {
					q = queue<i2>();
					connected = queue<i2>();
					q.push(i2(i, j));
					connected.push(i2(i, j));
					while (!q.empty()) {
						i2 data = q.front();
						q.pop();
						int newX, newY;
						for (int k = 0; k < 4; k++) {
							newX = data.first + x[k];
							newY = data.second + y[k];
							if (newX >= 0 && newX < 12 && newY >= 0 && newY < 6) {
								if (map[newX][newY] == map[i][j]) {
									if (!visit[newX][newY]) {
										visit[newX][newY] = true;
										q.push(i2(newX, newY));
										connected.push(i2(newX, newY));
									}
								}
							}
						}
					}

					//cout << connected.size() << '\n';

					if (connected.size() >= 4) {
						result = true;
						while (!connected.empty()) {
							i2 data = connected.front();
							connected.pop();
							map[data.first][data.second] = '.';
						}
					}
				}
			}
		}
	}

	return result;
}

void fall() {
	for (int i = 10; i >= 0; i--) {
		for (int j = 0; j < 6; j++) {
			if (map[i][j] != '.') {
				int idx = i + 1;
				while (idx <= 11) {
					if (map[idx][j] == '.') {
						idx++;
					}
					else {
						if (idx - 1 > i) {
							map[idx - 1][j] = map[i][j];
							map[i][j] = '.';
						}
						break;
					}

					if (idx == 12) {
						map[11][j] = map[i][j];
						map[i][j] = '.';
					}
				}
			}
		}
	}
}