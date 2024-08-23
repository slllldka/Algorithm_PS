#include <iostream>
#include <utility>
#include <queue>

using namespace std;

using i2 = pair<int, int>;

int R, C, N, H;
char map[100][101];

int xDir[4] = { 1, 0, -1, 0 };
int yDir[4] = { 0, 1, 0, -1 };

i2 stick(int height) {
	static int d = 1;
	i2 ret = i2(-1, -1);
	if (d == 1) {
		for (int i = 0; i < C; i++) {
			if (map[R - height][i] == 'x') {
				map[R - height][i] = '.';
				ret = i2(R - height, i);
				break;
			}
		}
	}
	else if (d == -1) {
		for (int i = C - 1; i >= 0; i--) {
			if (map[R - height][i] == 'x') {
				map[R - height][i] = '.';
				ret = i2(R - height, i);
				break;
			}
		}
	}
	d *= -1;
	return ret;
}
void drop(i2 pos) {
	i2 cluster[10000];
	bool visited[100][100];
	queue<i2> q;
	int size = 0;
	int x = pos.first;
	int y = pos.second;
	int newX, newY;
	for (int i = 0; i < 4; i++) {
		newX = x + xDir[i];
		newY = y + yDir[i];
		if (newX >= 0 && newX < (R - 1) && newY >= 0 && newY < C) {
			if (map[newX][newY] == 'x') {
				for (int j = 0; j < R; j++) {
					for (int k = 0; k < C; k++) {
						visited[j][k] = false;
					}
				}
				size = 0;
				q = queue<i2>();
				q.push(i2(newX, newY));
				while (!q.empty()) {
					i2 data = q.front();
					q.pop();
					if (!visited[data.first][data.second]) {
						//cout << i << ' ' << data.first << data.second << '\n';
						visited[data.first][data.second] = true;
						cluster[size++] = i2(data.first, data.second);
						for (int j = 0; j < 4; j++) {
							newX = data.first + xDir[j];
							newY = data.second + yDir[j];
							if (newX >= 0 && newX < R && newY >= 0 && newY < C) {
								if (map[newX][newY] == 'x') {
									if (newX == R - 1) {
										size = 0;
										q = queue<i2>();
										break;
									}
									q.push(i2(newX, newY));
								}
							}
						}
					}
				}
				if (size > 0) {
					for (int j = 0; j < size; j++) {
						map[cluster[j].first][cluster[j].second] = 'y';
					}
					int deltaX = 1;
					bool done = false;
					while (!done) {
						for (int j = 0; j < size; j++) {
							if (cluster[j].first + deltaX < R) {
								if (map[cluster[j].first + deltaX][cluster[j].second] == 'x') {
									deltaX--;
									done = true;
									break;
								}
							}
							else {
								deltaX--;
								done = true;
								break;
							}
						}
						if (!done) {
							deltaX++;
						}
					}

					for (int j = 0; j < size; j++) {
						map[cluster[j].first][cluster[j].second] = '.';
					}
					for (int j = 0; j < size; j++) {
						map[cluster[j].first + deltaX][cluster[j].second] = 'x';
					}
					break;
				}
			}
		}
	}
	


}

int main() {
	i2 pos;
	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		cin >> map[i];
	}
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> H;
		pos = stick(H);
		if (pos != i2(-1, -1)) {
			drop(pos);
		}
	}

	for (int j = 0; j < R; j++) {
		for (int k = 0; k < C; k++) {
			cout << map[j][k];
		}
		cout << '\n';
	}
	cout << '\n';

	return 0;
}