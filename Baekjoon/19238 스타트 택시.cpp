#include <iostream>
#include <utility>
#include <tuple>
#include <queue>
#include <cstring>

using namespace std;

typedef pair<int, int> i2;
typedef tuple<int, int, int> i3;

int x[4] = { 1, 0, -1, 0 };
int y[4] = { 0, -1, 0, 1 };

int N, M, Fuel, customerNum;

int firstX, firstY;
int map[20][20];
bool isVisited[20][20];
i2 goal[401];

queue<i3> q;

i3 findCustomer();
int transportCustomer(int, int);

int main() {
	cin >> N >> M >> Fuel;
	customerNum = M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			map[i][j] *= -1;
		}
	}

	cin >> firstX >> firstY;
	firstX--;
	firstY--;

	int input1, input2;
	for (int i = 1; i <= M; i++) {
		cin >> input1 >> input2;
		map[input1 - 1][input2 - 1] = i;
		cin >> input1 >> input2;
		goal[i] = i2(input1 - 1, input2 - 1);
	}

	int cX, cY, cD, distance;
	while (M > 0) {
		i3 customer = findCustomer();
		tie(cX, cY, cD) = customer;
		if (cD == -1) {
			cout << -1;
			return 0;
		}
		else {
			Fuel -= cD;
			distance = transportCustomer(cX, cY);
			if (distance == -1) {
				cout << -1;
				return 0;
			}
			else if (Fuel - distance < 0) {
				cout << -1;
				return 0;
			}
			else {
				Fuel += distance;
				M--;
			}
		}
	}

	cout << Fuel;
	return 0;
}

i3 findCustomer() {
	memset(isVisited, false, sizeof(isVisited));

	int cX = -1, cY = -1, cD = -1;
	q = queue<i3>();
	q.push(i3(firstX, firstY, 0));
	isVisited[firstX][firstY] = true;
	while (!q.empty()) {
		int xPos, yPos, dis;
		i3 data = q.front();
		tie(xPos, yPos, dis) = data;
		q.pop();

		if (Fuel - dis < 0) {
			if (cD == -1) {
				return i3(-1, -1, -1);
			}
			else {
				return i3(cX, cY, cD);
			}
		}

		if (cD == -1) {
			if (map[xPos][yPos] > 0) {
				cX = xPos;
				cY = yPos;
				cD = dis;
			}
		}
		else {
			if (dis > cD) {
				return i3(cX, cY, cD);
			}
			else {
				if (map[xPos][yPos] > 0) {
					if (cX == xPos) {
						if (cY > yPos) {
							cX = xPos;
							cY = yPos;
							cD = dis;
						}
					}
					else {
						if (cX > xPos) {
							cX = xPos;
							cY = yPos;
							cD = dis;
						}
					}
				}
			}
		}

		int newX = 0, newY = 0;
		for (int i = 0; i < 4; i++) {
			newX = xPos + x[i];
			newY = yPos + y[i];
			if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
				if (map[newX][newY] != -1) {
					if (!isVisited[newX][newY]) {
						isVisited[newX][newY] = true;
						q.push(i3(newX, newY, dis + 1));
					}
				}
			}
		}
	}

	return i3(cX, cY, cD);
}

int transportCustomer(int cX, int cY) {
	int num = map[cX][cY];
	int goalX = goal[num].first, goalY = goal[num].second;
	memset(isVisited, false, sizeof(isVisited));
	q = queue<i3>();
	q.push(i3(cX, cY, 0));
	isVisited[cX][cY] = true;

	while (!q.empty()) {
		int xPos, yPos, dis;
		i3 data = q.front();
		tie(xPos, yPos, dis) = data;
		q.pop();

		if (Fuel - dis < 0) {
			return -1;
		}

		if (xPos == goalX && yPos == goalY) {
			firstX = xPos;
			firstY = yPos;
			map[cX][cY] = 0;
			return dis;
		}

		int newX = 0, newY = 0;
		for (int i = 0; i < 4; i++) {
			newX = xPos + x[i];
			newY = yPos + y[i];
			if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
				if (map[newX][newY] != -1) {
					if (!isVisited[newX][newY]) {
						isVisited[newX][newY] = true;
						q.push(i3(newX, newY, dis + 1));
					}
				}
			}
		}
	}

	return -1;
}