#include <iostream>

using namespace std;

int N, Score = 0;
int red[4][4], green[4][6], blue[4][6];

void moveBlock(int, int, int(*)[6]);
bool score(int(*)[6]);
void light(int(*)[6]);
void removeLine(int, int(*)[6]);

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

		/*for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 4; j++) {
				cout << green[j][i];
			}
			cout << ' ';
			for (int j = 0; j < 4; j++) {
				cout << blue[j][i];
			}
			cout << '\n';
		}
		cout << '\n';*/
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

void moveBlock(int t, int x, int(*map)[6]) {
	bool stop = false;
	if (t == 1) {
		for (int i = 0; i < 4; i++) {
			if (map[x][2 + i]) {
				map[x][1 + i] = t;
				stop = true;
				break;
			}
		}
		if (!stop) {
			map[x][5] = t;
		}
	}
	else if (t == 2) {
		for (int i = 0; i < 4; i++) {
			if (map[x][2 + i]) {
				map[x][i] = t;
				map[x][1 + i] = t;
				stop = true;
				break;
			}
		}
		if (!stop) {
			map[x][4] = t;
			map[x][5] = t;
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (map[x][2 + i] || map[x + 1][2 + i]) {
				map[x][1 + i] = t;
				map[x + 1][1 + i] = t;
				stop = true;
				break;
			}
		}
		if (!stop) {
			map[x][5] = t;
			map[x + 1][5] = t;
		}
	}

	while (score(map));
	light(map);
}

bool score(int(*map)[6]) {
	bool isScored = false;
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
			isScored = true;
			Score++;
			removeLine(i, map);
			i--;
		}
	}

	return isScored;
}
void light(int(*map)[6]) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			if (map[j][1]) {
				removeLine(5, map);
				break;
			}
		}
	}
}

void removeLine(int y, int(*map)[6]) {
	map[0][y] = 0;
	map[1][y] = 0;
	map[2][y] = 0;
	map[3][y] = 0;
	if (y == 5) {
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < 4; j++) {
				map[j][y - i] = map[j][y - i - 1];
			}
		}
	}
	else {
		for (int i = 5; i > 0; i--) {
			for (int j = 0; j < 4; j++) {
				int height = i;
				if (map[j][i - 1] == 1) {
					map[j][i - 1] = 0;
					while (height < 6) {
						if (map[j][height] != 0) {
							break;
						}
						height++;
					}
					map[j][height - 1] = 1;
				}
				else if (map[j][i - 1] == 2) {
					if ((i > 1) && (map[j][i - 2] == 2)) {
						map[j][i - 2] = 0;
						map[j][i - 1] = 0;
						while (height < 6) {
							if (map[j][height] != 0) {
								break;
							}
							height++;
						}
						map[j][height - 1] = 2;
						map[j][height - 2] = 2;
					}
					else {
						map[j][i - 1] = 0;
						while (height < 6) {
							if (map[j][height] != 0) {
								break;
							}
							height++;
						}
						map[j][height - 1] = 2;
					}
				}
			}
			for (int j = 0; j < 3; j++) {
				int height = i;
				if (map[j][i - 1] == 3 && map[j + 1][i - 1] == 3) {
					map[j][i - 1] = 0;
					map[j + 1][i - 1] = 0;
					while (height < 6) {
						if (map[j][height] != 0 || map[j + 1][height] != 0) {
							break;
						}
						height++;
					}
					map[j][height - 1] = 3;
					map[j + 1][height - 1] = 3;
				}
			}
		}
	}

	map[0][0] = false;
	map[1][0] = false;
	map[2][0] = false;
	map[3][0] = false;
}