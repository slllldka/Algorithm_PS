#include <iostream>

using namespace std;

int x[4] = { 0, 1, 0, -1 };
int y[4] = { -1, 0, 1, 0 };

int N, OUT = 0;
int map[499][499];

void tornado(int, int, int);
bool checkInside(int, int);

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	int startXPos = N / 2;
	int startYPos = N / 2;
	int dir = 0;
	int offset = 1;
	bool stop = false;
	while (true) {
		for (int i = 0; i < offset; i++) {
			if (startXPos == 0 && startYPos == 0) {
				stop = true;
				break;
			}
			if (!checkInside(startXPos, startYPos)) {
				break;
			}
			tornado(startXPos, startYPos, dir);
			startXPos += x[dir];
			startYPos += y[dir];
		}
		if (stop) {
			break;
		}

		dir = (dir + 1) % 4;
		for (int i = 0; i < offset; i++) {
			if (startXPos == 0 && startYPos == 0) {
				stop = true;
				break;
			}
			if (!checkInside(startXPos, startYPos)) {
				break;
			}
			tornado(startXPos, startYPos, dir);
			startXPos += x[dir];
			startYPos += y[dir];
		}
		if (stop) {
			break;
		}

		dir = (dir + 1) % 4;
		offset++;
	}

	cout << OUT;
	return 0;
}

void tornado(int startXPos, int startYPos, int dir) {
	int dirForward = dir, dirBackward = (dir + 2) % 4;
	int dirRight = (dir + 3) % 4, dirLeft = (dir + 1) % 4;
	int endXPos = startXPos + x[dirForward];
	int endYPos = startYPos + y[dirForward];
	int alphaXPos = endXPos + x[dirForward];
	int alphaYPos = endYPos + y[dirForward];
	int sandQuantity = 0;
	int sandTotalQuantity = map[endXPos][endYPos];

	int sandX = 0, sandY = 0;
	//1%
	sandQuantity = sandTotalQuantity / 100;
	sandX = startXPos + x[dirRight];
	sandY = startYPos + y[dirRight];
	if (checkInside(sandX, sandY)) {
		map[sandX][sandY] += sandQuantity;
	}
	else {
		OUT += sandQuantity;
	}
	map[endXPos][endYPos] -= sandQuantity;

	sandX = startXPos + x[dirLeft];
	sandY = startYPos + y[dirLeft];
	if (checkInside(sandX, sandY)) {
		map[sandX][sandY] += sandQuantity;
	}
	else {
		OUT += sandQuantity;
	}
	map[endXPos][endYPos] -= sandQuantity;

	//2%
	sandQuantity = sandTotalQuantity * 2 / 100;
	sandX = endXPos + x[dirRight] * 2;
	sandY = endYPos + y[dirRight] * 2;
	if (checkInside(sandX, sandY)) {
		map[sandX][sandY] += sandQuantity;
	}
	else {
		OUT += sandQuantity;
	}
	map[endXPos][endYPos] -= sandQuantity;

	sandX = endXPos + x[dirLeft] * 2;
	sandY = endYPos + y[dirLeft] * 2;
	if (checkInside(sandX, sandY)) {
		map[sandX][sandY] += sandQuantity;
	}
	else {
		OUT += sandQuantity;
	}
	map[endXPos][endYPos] -= sandQuantity;

	//5%
	sandQuantity = sandTotalQuantity * 5 / 100;
	sandX = endXPos + x[dirForward] * 2;
	sandY = endYPos + y[dirForward] * 2;
	if (checkInside(sandX, sandY)) {
		map[sandX][sandY] += sandQuantity;
	}
	else {
		OUT += sandQuantity;
	}
	map[endXPos][endYPos] -= sandQuantity;

	//7%
	sandQuantity = sandTotalQuantity * 7 / 100;
	sandX = endXPos + x[dirRight];
	sandY = endYPos + y[dirRight];
	if (checkInside(sandX, sandY)) {
		map[sandX][sandY] += sandQuantity;
	}
	else {
		OUT += sandQuantity;
	}
	map[endXPos][endYPos] -= sandQuantity;

	sandX = endXPos + x[dirLeft];
	sandY = endYPos + y[dirLeft];
	if (checkInside(sandX, sandY)) {
		map[sandX][sandY] += sandQuantity;
	}
	else {
		OUT += sandQuantity;
	}
	map[endXPos][endYPos] -= sandQuantity;

	//10%
	sandQuantity = sandTotalQuantity * 10 / 100;
	sandX = alphaXPos + x[dirRight];
	sandY = alphaYPos + y[dirRight];
	if (checkInside(sandX, sandY)) {
		map[sandX][sandY] += sandQuantity;
	}
	else {
		OUT += sandQuantity;
	}
	map[endXPos][endYPos] -= sandQuantity;

	sandX = alphaXPos + x[dirLeft];
	sandY = alphaYPos + y[dirLeft];
	if (checkInside(sandX, sandY)) {
		map[sandX][sandY] += sandQuantity;
	}
	else {
		OUT += sandQuantity;
	}
	map[endXPos][endYPos] -= sandQuantity;

	//alpha
	if (checkInside(alphaXPos, alphaYPos)) {
		map[alphaXPos][alphaYPos] += map[endXPos][endYPos];
		map[endXPos][endYPos] = 0;
	}
	else {
		OUT += map[endXPos][endYPos];
		map[endXPos][endYPos] = 0;
	}
}

bool checkInside(int xPos, int yPos) {
	if (xPos >= 0 && xPos < N && yPos >= 0 && yPos < N) {
		return true;
	}
	else {
		return false;
	}
}