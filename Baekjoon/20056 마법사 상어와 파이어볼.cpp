#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

typedef tuple<int, int, int, int> i4; //질량, 속력, 방향, 개수
typedef tuple<int, int, int, int, int> i5; //x, y, 질량, 속력, 방향

int x[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int y[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int N, M, K;
i4 map[50][50];
queue<i5> fireBalls;

void moveFireBalls();
void clearMap();

int main() {
	int r, c, m, s, d;
	cin >> N >> M >> K;
	for (int i = 1; i <= M; i++) {
		cin >> r >> c >> m >> s >> d;
		fireBalls.push(i5(r - 1, c - 1, m, s, d));
	}

	for (int i = 0; i < K; i++) {
		moveFireBalls();
	}

	int sum = 0;
	while (!fireBalls.empty()) {
		sum += get<2>(fireBalls.front());
		fireBalls.pop();
	}
	cout << sum;
	return 0;
}

void moveFireBalls() {
	int xPos, yPos, m, s, d, newX, newY;
	int mapM, mapS, mapD, mapN, newM, newS;
	i4 mapData;
	i5 fireBallData;
	clearMap();
	while (!fireBalls.empty()) {
		fireBallData = fireBalls.front();
		tie(xPos, yPos, m, s, d) = fireBallData;
		fireBalls.pop();
		
		newX = xPos + x[d] * s;
		newY = yPos + y[d] * s;
		if (newX < 0) {
			while (newX < 0) {
				newX += N;
			}
		}
		else if (newX >= N) {
			newX %= N;
		}

		if (newY < 0) {
			while (newY < 0) {
				newY += N;
			}
		}
		else if (newY >= N) {
			newY %= N;
		}

		mapData = map[newX][newY];
		tie(mapM, mapS, mapD, mapN) = mapData;
		mapM += m;
		mapS += s;
		if (mapN == 0) {
			mapD = d;
		}
		else if(mapN == 1) {
			mapD = mapD % 2;
			mapD += d % 2;
		}
		else {
			mapD += d % 2;
		}
		mapN++;
		map[newX][newY] = i4(mapM, mapS, mapD, mapN);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			mapData = map[i][j];
			tie(mapM, mapS, mapD, mapN) = mapData;
			if (mapN > 0) {
				if (mapN == 1) {
					fireBalls.push(i5(i, j, mapM, mapS, mapD));
				}
				else {
					if (mapM >= 5) {
						newM = mapM / 5;
						newS = mapS / mapN;
						if (mapD == 0) {
							fireBalls.push(i5(i, j, newM, newS, 0));
							fireBalls.push(i5(i, j, newM, newS, 2));
							fireBalls.push(i5(i, j, newM, newS, 4));
							fireBalls.push(i5(i, j, newM, newS, 6));
						}
						else if(mapD == mapN) {
							fireBalls.push(i5(i, j, newM, newS, 0));
							fireBalls.push(i5(i, j, newM, newS, 2));
							fireBalls.push(i5(i, j, newM, newS, 4));
							fireBalls.push(i5(i, j, newM, newS, 6));
						}
						else {
							fireBalls.push(i5(i, j, newM, newS, 1));
							fireBalls.push(i5(i, j, newM, newS, 3));
							fireBalls.push(i5(i, j, newM, newS, 5));
							fireBalls.push(i5(i, j, newM, newS, 7));
						}
					}
				}
			}
		}
	}
}

void clearMap() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = i4(0, 0, 0, 0);
		}
	}
}