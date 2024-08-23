#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <vector>
#include <tuple>

using namespace std;

typedef tuple<int, int, int> i3;
typedef tuple<int, int, int, int> i4;

int xVec[6] = {1, 0, 0, -1, 0, 0};
int yVec[6] = {0, 1, 0, 0, -1, 0};
int zVec[6] = {0, 0, 1, 0, 0, -1};

int*** maze;

int*** boards[4];
int** board0[5];
int** board90[5];
int** board180[5];
int** board270[5];

vector<int> boardOrder = { 0, 1, 2, 3, 4 };

bool visit[5][5][5];

void rotateBoards();
int solveMaze();
int solveMazeForPoints(i3, i3);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	maze = new int**[5];

	for (int i = 0; i < 5; i++) {
		board0[i] = new int* [5];
		board90[i] = new int* [5];
		board180[i] = new int* [5];
		board270[i] = new int* [5];
		for (int j = 0; j < 5; j++) {
			board0[i][j] = new int[5];
			board90[i][j] = new int[5];
			board180[i][j] = new int[5];
			board270[i][j] = new int[5];
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				cin >> board0[i][j][k];
			}
		}
	}

	rotateBoards();

	boards[0] = board0;
	boards[1] = board90;
	boards[2] = board180;
	boards[3] = board270;

	int result = -1, ret;
	do {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					for (int m = 0; m < 4; m++) {
						for (int n = 0; n < 4; n++) {
							maze[0] = boards[i][boardOrder[0]];
							maze[1] = boards[j][boardOrder[1]];
							maze[2] = boards[k][boardOrder[2]];
							maze[3] = boards[m][boardOrder[3]];
							maze[4] = boards[n][boardOrder[4]];

							ret = solveMaze();
							if (result == -1) {
								result = ret;
							}
							else {
								if (ret > 0) {
									result = result < ret ? result : ret;
								}
							}

							if (result == 12) {
								i = 4;
								j = 4;
								k = 4;
								m = 4;
								n = 4;
								break;
							}
						}
					}
				}
			}
		}

	} while (next_permutation(boardOrder.begin(), boardOrder.end()));

	cout << result << '\n';

	delete[] maze;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			delete[] board0[i][j];
			delete[] board90[i][j];
			delete[] board180[i][j];
			delete[] board270[i][j];
		}
		delete[] board0[i];
		delete[] board90[i];
		delete[] board180[i];
		delete[] board270[i];
	}

	return 0;
}

void rotateBoards() {
	//0 -> 90
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				board90[i][j][k] = board0[i][4 - k][j];
			}
		}
	}
	//90 -> 180
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				board180[i][j][k] = board90[i][4 - k][j];
			}
		}
	}
	//180 -> 270
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				board270[i][j][k] = board180[i][4 - k][j];
			}
		}
	}
}

int solveMaze() {
	int result = -1, ret;
	//(0, 0, 0) -> (4, 4, 4)
	ret = solveMazeForPoints(i3(0, 0, 0), i3(4, 4, 4));
	if (result == -1) {
		result = ret;
	}
	else {
		if (ret > 0) {
			result = result < ret ? result : ret;
		}
	}

	//(0, 4, 0) -> (4, 0, 4)
	ret = solveMazeForPoints(i3(0, 4, 0), i3(4, 0, 4));
	if (result == -1) {
		result = ret;
	}
	else {
		if (ret > 0) {
			result = result < ret ? result : ret;
		}
	}

	//(0, 0, 4) -> (4, 4, 0)
	ret = solveMazeForPoints(i3(0, 0, 4), i3(4, 4, 0));
	if (result == -1) {
		result = ret;
	}
	else {
		if (ret > 0) {
			result = result < ret ? result : ret;
		}
	}

	//(0, 4, 4) -> (4, 0, 0)
	ret = solveMazeForPoints(i3(0, 4, 4), i3(4, 0, 0));
	if (result == -1) {
		result = ret;
	}
	else {
		if (ret > 0) {
			result = result < ret ? result : ret;
		}
	}

	return result;
}

int solveMazeForPoints(i3 start, i3 end) {
	int result = -1;
	int startX, startY, startZ, endX, endY, endZ;
	tie(startX, startY, startZ) = start;
	tie(endX, endY, endZ) = end;
	queue<i4> q;
	q = queue<i4>();
	if (maze[startX][startY][startZ] == 1 && maze[endX][endY][endZ] == 1) {
		memset(visit, false, sizeof(visit));
		q.push(i4(startX, startY, startZ, 0));
		visit[startX][startY][startZ] = true;
		while (!q.empty()) {
			int x, y, z, d;
			tie(x, y, z, d) = q.front();
			q.pop();

			int newX, newY, newZ;
			for (int i = 0; i < 6; i++) {
				newX = x + xVec[i];
				newY = y + yVec[i];
				newZ = z + zVec[i];
				if (newX >= 0 && newX < 5
					&& newY >= 0 && newY < 5
					&& newZ >= 0 && newZ < 5) {
					if (maze[newX][newY][newZ] == 1 && !visit[newX][newY][newZ]) {
						if (newX == endX && newY == endY && newZ == endZ) {
							if (result == -1) {
								result = d + 1;
							}
							else {
								result = result < (d + 1) ? result : (d + 1);
							}
							return result;
						}
						else {
							visit[newX][newY][newZ] = true;
							q.push(i4(newX, newY, newZ, d + 1));
						}
					}
				}
			}
		}
	}

	return result;
}