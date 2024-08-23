#include <iostream>
#include <utility>
#include <queue>

using namespace std;

typedef pair<int, int> i2;

int x[4] = { 1, 0, -1, 0 };
int y[4] = { 0, -1, 0, 1 };

int N, M;

queue<i2> q;
vector<i2> Switch[100][100];
bool map[100][100];
int check[100][100];

int BFS();

int main() {
	int x = 0, y = 0, a = 0, b = 0;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> a >> b;
		Switch[x - 1][y - 1].push_back(i2(a - 1, b - 1));
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = false;
			check[i][j] = 0;
		}
	}

	cout << BFS();
	return 0;
}

int BFS() {
	int result = 1;
	map[0][0] = true;
	check[0][0] = 1;
	q.push(i2(0, 0));

	while (!q.empty()) {
		i2 data = q.front();
		int xPos = data.first;
		int yPos = data.second;
		q.pop();

		for (i2 pos : Switch[xPos][yPos]) {
			if (map[pos.first][pos.second] == false) {
				map[pos.first][pos.second] = true;
				result++;
			}
		}
		check[xPos][yPos] = result;

		if ((result - 1) == M) {
			return result;
		}

		int newX = 0, newY = 0;
		for (int i = 0; i < 4; i++) {
			newX = xPos + x[i];
			newY = yPos + y[i];
			if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
				if (map[newX][newY] == true) {
					if (check[newX][newY] < result) {
						check[newX][newY] = result;
						q.push(i2(newX, newY));
					}
				}
			}
		}
	}

	return result;
}