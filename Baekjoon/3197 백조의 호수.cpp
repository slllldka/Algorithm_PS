#include <iostream>
#include <utility>
#include <tuple>
#include <queue>

using namespace std;

typedef pair<int, int> i2;
typedef tuple<int, int, int> i3;

int x[4] = { 1, 0, -1, 0 };
int y[4] = { 0, -1, 0, 1 };

int R, C, globalDay = 0;
char map[1500][1500];
char check[1500][1500];
i2 swan[2];

queue<i3> queueSwan;
queue<i3> queueMap;

void meltIce();
int moveSwan();

int main() {
	int countSwan = 0;
	string input = "";
	cin >> R >> C;
	
	for (int i = 0; i < R; i++) {
		cin >> input;
		for (int j = 0; j < C; j++) {
			map[i][j] = input[j];
			if (map[i][j] == '.') {
				queueMap.push(i3(i, j, 0));
			}
			if (map[i][j] == 'L') {
				swan[countSwan++] = i2(i, j);
				map[i][j] = '.';
				queueMap.push(i3(i, j, 0));
			}
		}
	}

	cout << moveSwan();

	return 0;
}

void meltIce() {
	while (!queueMap.empty()) {
		i3 data = queueMap.front();
		int xPos = get<0>(data);
		int yPos = get<1>(data);
		int day = get<2>(data);
		
		if (day > globalDay) {
			globalDay++;
			break;
		}
		queueMap.pop();

		int newX = 0, newY = 0;
		for (int i = 0; i < 4; i++) {
			newX = xPos + x[i];
			newY = yPos + y[i];
			if (newX >= 0 && newX < R && newY >= 0 && newY < C) {
				if (map[newX][newY] == 'X') {
					map[newX][newY] = '.';
					queueMap.push(i3(newX, newY, day + 1));
				}
			}
		}
	}
}
int moveSwan() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			check[i][j] = ' ';
		}
	}
	queue<i3> queueTemp;
	queueSwan = queue<i3>();
	queueSwan.push(i3(0, swan[0].first, swan[0].second));
	check[swan[0].first][swan[0].second] = 'F';
	queueSwan.push(i3(1, swan[1].first, swan[1].second));
	check[swan[1].first][swan[1].second] = 'S';

	while (!queueSwan.empty()) {
		i3 data = queueSwan.front();
		int idx = get<0>(data);
		int xPos = get<1>(data);
		int yPos = get<2>(data);
		int countX = 0;
		queueSwan.pop();

		int newX = 0, newY = 0;
		for (int i = 0; i < 4; i++) {
			newX = xPos + x[i];
			newY = yPos + y[i];
			if (newX >= 0 && newX < R && newY >= 0 && newY < C) {
				if (map[newX][newY] == '.') {
					if (check[newX][newY] == ' ') {
						if (idx == 0) {
							check[newX][newY] = 'F';
						}
						else {
							check[newX][newY] = 'S';
						}
						queueSwan.push(i3(idx, newX, newY));
					}
					else {
						if (idx == 0 && check[newX][newY] == 'S') {
							return globalDay;
						}
						else if (idx == 1 && check[newX][newY] == 'F') {
							return globalDay;
						}
					}
				}
				else if (map[newX][newY] == 'X') {
					countX++;
				}
			}
		}

		if (countX > 0) {
			queueTemp.push(i3(idx, xPos, yPos));
		}

		if (queueSwan.empty()) {
			queueSwan = queueTemp;
			queueTemp = queue<i3>();
			meltIce();
		}
	}
}