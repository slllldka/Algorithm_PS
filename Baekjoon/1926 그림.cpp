#include <iostream>
#include <utility>
#include <queue>

using namespace std;

typedef pair<int, int> i2;

int x[4] = { 1, 0, -1, 0 };
int y[4] = { 0, -1, 0, 1 };

int N, M;
char drawing[500][500];
queue<i2> queuePos;

int BFS();

int main() {
	int result = 0, area = 0, num = 0;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> drawing[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (drawing[i][j] == '1') {
				num++;
				drawing[i][j] = '0';
				queuePos = queue<i2>();
				queuePos.push(i2(i, j));
				area = BFS();
				result = result > area ? result : area;
			}
		}
	}

	cout << num << endl << result;
	return 0;
}

int BFS() {
	int area = 0;
	while(!queuePos.empty()) {
		i2 data = queuePos.front();
		area++;
		for (int i = 0; i < 4; i++) {
			if (((data.first + x[i]) >= 0) && ((data.first + x[i]) < N) && ((data.second + y[i]) >= 0) && ((data.second + y[i]) < M)) {
				if (drawing[data.first + x[i]][data.second + y[i]] == '1') {
					drawing[data.first + x[i]][data.second + y[i]] = '0';
					queuePos.push(i2(data.first + x[i], data.second + y[i]));
				}
			}
		}
		queuePos.pop();
	}

	return area;
}