#include <iostream>
#include <tuple>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> i2;
typedef tuple<int, int, int, int> i4;

int x[4] = { 1, 0, -1, 0 };
int y[4] = { 0, -1, 0, 1 };

int N, M, K;
char map[1000][1000];
vector<i2> check[1000][1000];
queue<i4> q;

int BFS();
void moveMe(int, int, int, int);

int main() {
	string input = "";
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		cin >> input;
		for (int j = 0; j < M; j++) {
			map[i][j] = input[j];
		}
	}

	if (N == 1 && M == 1) {
		cout << 1;
	}
	else {
		cout << BFS();
	}

	return 0;
}

int BFS() {
	check[0][0].push_back(i2(1, 0));
	q.push(i4(1, 0, 0, 0));
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
			if (newX >= 0 && newX < N && newY >= 0 && newY < M) {
				if ((newX == (N - 1)) && (newY == (M - 1))) {
					return (move + 1);
				}
				else {
					if (map[newX][newY] == '0') {
						moveMe(move + 1, k, newX, newY);
					}
					else {
						if (k < K) {
							moveMe(move + 1, k + 1, newX, newY);
						}
					}
				}
			}
		}
	}
	
	return -1;
}

void moveMe(int move, int k, int newX, int newY) {
	for (int i = 0; i < (int)check[newX][newY].size(); i++) {
		if (check[newX][newY][i].second == k) {
			if (move < check[newX][newY][i].first) {
				check[newX][newY][i] = i2(move, k);
				q.push(i4(move, k, newX, newY));
			}
			return;
		}
	}

	check[newX][newY].push_back(i2(move, k));
	q.push(i4(move, k, newX, newY));
}