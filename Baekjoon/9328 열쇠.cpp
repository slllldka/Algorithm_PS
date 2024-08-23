#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> i2;

int x[4] = { 1, 0, -1, 0 };
int y[4] = { 0, -1, 0, 1 };

int T, W, H, D;
vector<char> key;
vector<i2> entrance;

char map[100][100];
int check[100][100];
queue<i2> q;

void BFS();

int main() {
	string input = "";
	cin >> T;

	for (int testCase = 0; testCase < T; testCase++) {
		cin >> W >> H;
		D = 0;
		key.clear();
		entrance.clear();
		for (int i = 0; i < W; i++) {
			cin >> input;
			for (int j = 0; j < H; j++) {
				map[i][j] = input[j];
				check[i][j] = -1;
				if (map[i][j] != '*') {
					if (i == 0 || i == (W - 1) || j == 0 || j == (H - 1)) {
						q.push(i2(i, j));
						entrance.push_back(i2(i, j));
					}
				}
			}
		}

		cin >> input;
		if (input != "0") {
			for (int i = 0; i < (int)input.length(); i++) {
				key.push_back(input[i]);
			}
		}

		BFS();
		cout << D << endl;
	}

	return 0;
}

void BFS() {
	while (!q.empty()) {
		i2 data = q.front();
		int xPos = data.first, yPos = data.second;
		q.pop();

		if (map[xPos][yPos] == '$') {
			D++;
			map[xPos][yPos] = '.';
		}
		else if (map[xPos][yPos] >= 65 && map[xPos][yPos] <= 90) {
			for (char c : key) {
				if (c - 32 == map[xPos][yPos]) {
					map[xPos][yPos] = '.';
					break;
				}
			}

			if (map[xPos][yPos] != '.') {
				continue;
			}
		}
		else if (map[xPos][yPos] >= 97 && map[xPos][yPos] <= 122) {
			key.push_back(map[xPos][yPos]);
			map[xPos][yPos] = '.';
			for (i2 pos : entrance) {
				q.push(pos);
			}
			continue;
		}

		if (check[xPos][yPos] < (int)key.size()) {
			check[xPos][yPos] = key.size();
		}
		else {
			continue;
		}

		int newX = 0, newY = 0;
		for (int i = 0; i < 4; i++) {
			newX = xPos + x[i];
			newY = yPos + y[i];
			if (newX >= 0 && newX < W && newY >= 0 && newY < H) {
				if (map[newX][newY] != '*') {
					q.push(i2(newX, newY));
				}
			}
		}
	}
}