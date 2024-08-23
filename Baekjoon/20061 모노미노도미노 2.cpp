#include <iostream>

using namespace std;

int N, Score = 0;
bool red[4][4], green[4][6], blue[4][6];

void moveBlock(int, int, bool(*)[6]);
void score(bool(*)[6]);
void light(bool(*)[6]);
void removeLine(int, bool(*)[6]);

int main() {
	int t = 0, x = 0, y = 0;
	cin >> N;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			if (j < 4) {
				red[i][j] = false;
			}
			green[i][j] = false;
			blue[i][j] = false;
		}
	}

	for (int i = 0; i < N; i++) {
		cin >> t >> x >> y;
		if (t == 1) {
			moveBlock(t, x, blue);
			moveBlock(t, y, green);
		}
		else if (t == 2) {
			moveBlock(t, x, blue);
			moveBlock(t + 1, y, green);
		}
		else {
			moveBlock(t, x, blue);
			moveBlock(t - 1, y, green);
		}
	}

	cout << Score << endl;
	
	int tileNum = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (green[i][j + 2]) {
				tileNum++;
			}
			if (blue[i][j + 2]) {
				tileNum++;
			}
		}
	}
	cout << tileNum;

	return 0;
}

void moveBlock(int t, int x, bool (*map)[6]) {
	bool stop = false;
	if (t == 1) {
		for (int i = 0; i < 4; i++) {
			if (map[x][2 + i]) {
				map[x][1 + i] = true;
				stop = true;
				break;
			}
		}
		if (!stop) {
			map[x][5] = true;
		}
	}
	else if (t == 2) {
		for (int i = 0; i < 4; i++) {
			if (map[x][2 + i]) {
				map[x][i] = true;
				map[x][1 + i] = true;
				stop = true;
				break;
			}
		}
		if (!stop) {
			map[x][4] = true;
			map[x][5] = true;
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (map[x][2 + i] || map[x + 1][2 + i]) {
				map[x][1 + i] = true;
				map[x + 1][1 + i] = true;
				stop = true;
				break;
			}
		}
		if (!stop) {
			map[x][5] = true;
			map[x + 1][5] = true;
		}
	}

	score(map);
	light(map);
}

void score(bool(*map)[6]) {
	bool canScore = true;
	for (int i = 2; i < 6; i++) {
		canScore = true;
		for (int j = 0; j < 4; j++) {
			if (!map[j][i]) {
				canScore = false;
				break;
			}
		}
		if (canScore) {
			Score++;
			removeLine(i, map);
			i--;
		}
	}
}
void light(bool(*map)[6]) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			if (map[j][1]) {
				removeLine(5, map);
				break;
			}
		}
	}
}

void removeLine(int y, bool(*map)[6]) {
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < 4; j++) {
			map[j][y - i] = map[j][y - i - 1];
		}
	}
	map[0][0] = false;
	map[1][0] = false;
	map[2][0] = false;
	map[3][0] = false;
}