#include <iostream>
#include <cstring>
#include <queue>
#include <list>
#include <utility>
#include <tuple>

using namespace std;

typedef pair<int, int> i2;
typedef tuple<int, int, i2, list<i2>> blockType;


int x[4] = { 0, 1, 0, -1 };
int y[4] = { 1, 0, -1, 0 };

int temp[20];

int N, M, score = 0;
int map[20][20];

bool visit[20][20];

queue<i2> q;
list<i2> blockGroup;
blockType biggestBlock;

bool findBiggestBlock();
void removeBlock();
void gravity();
void rotateCounterClockwise(int, int, int);

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
	
	while (findBiggestBlock()) {
		removeBlock();
		gravity();
		rotateCounterClockwise(0, 0, N);
		gravity();
	}

	cout << score;

	return 0;
}

bool findBiggestBlock() {
	//블록을 찾고 그 블록에서 기준 블록을 찾고 기준 블록끼리 비교
	int color = 0;
	int size = 0, rainbow = 0;
	i2 referenceBlock = i2(N, N);
	biggestBlock = blockType(0, 0, i2(0, 0), list<i2>());
	memset(visit, false, sizeof(visit));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] > 0 && !visit[i][j]) {
				size = 0;
				rainbow = 0;
				q = queue<i2>();
				blockGroup = list<i2>();
				color = map[i][j];
				referenceBlock = i2(i, j);
				q.push(i2(i, j));
				blockGroup.push_back(i2(i, j));
				visit[i][j] = true;
				size++;
				while (!q.empty()) {
					i2 data = q.front();
					q.pop();

					int newX = 0, newY = 0;
					for (int k = 0; k < 4; k++) {
						newX = data.first + x[k];
						newY = data.second + y[k];
						if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
							if (!visit[newX][newY]) {
								if (map[newX][newY] == 0) {
									rainbow++;
									q.push(i2(newX, newY));
									blockGroup.push_back(i2(newX, newY));
									visit[newX][newY] = true;
									size++;
								}
								else if (map[newX][newY] == color) {
									if (newX < referenceBlock.first) {
										referenceBlock = i2(newX, newY);
									}
									else if (newX == referenceBlock.first) {
										if (newY < referenceBlock.second) {
											referenceBlock = i2(newX, newY);
										}
									}
									q.push(i2(newX, newY));
									blockGroup.push_back(i2(newX, newY));
									visit[newX][newY] = true;
									size++;
								}
							}
						}
					}
				}

				if (size > 1) {
					int biggestSize = get<0>(biggestBlock);
					int biggestRainbow = get<1>(biggestBlock);
					i2 biggestReferenceBlock = get<2>(biggestBlock);
					if (size > biggestSize) {
						biggestBlock = blockType(size, rainbow, referenceBlock, blockGroup);
					}
					else if (size == biggestSize) {
						if (rainbow > biggestRainbow) {
							biggestBlock = blockType(size, rainbow, referenceBlock, blockGroup);
						}
						else if (rainbow == biggestRainbow) {
							if (referenceBlock.first > biggestReferenceBlock.first) {
								biggestBlock = blockType(size, rainbow, referenceBlock, blockGroup);
							}
							else if (referenceBlock.first == biggestReferenceBlock.first) {
								if (referenceBlock.second > biggestReferenceBlock.second) {
									biggestBlock = blockType(size, rainbow, referenceBlock, blockGroup);
								}
							}
						}
					}

					for (i2 data : get<3>(biggestBlock)) {
						if (map[data.first][data.second] == 0) {
							visit[data.first][data.second] = false;
						}
					}
				}
			}
		}
	}

	if (get<0>(biggestBlock) < 1) {
		return false;
	}
	else {
		return true;
	}
}
void removeBlock() {
	int size = get<0>(biggestBlock);
	score += size * size;
	for (i2 data : get<3>(biggestBlock)) {
		map[data.first][data.second] = -2;
	}
}
void gravity() {
	int height = 0;
	for (int i = N - 2; i >= 0; i--) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] > -1) {
				height = 1;
				while (true) {
					if ((i + height) < N) {
						if (map[i + height][j] != -2) {
							break;
						}
					}
					else {
						break;
					}
					height++;
				}
				height--;
				if (height > 0) {
					map[i + height][j] = map[i][j];
					map[i][j] = -2;
				}
			}
		}
	}
}
void rotateCounterClockwise(int xPos, int yPos, int len) {
	if (len > 1) {
		i2 prev, next;
		prev = i2(xPos, yPos);
		next = i2(xPos + x[0] * (len - 1), yPos + y[0] * (len - 1));
		for (int i = 0; i < len - 1; i++) {
			temp[i] = map[prev.first][prev.second + i];
		}

		for (int i = 0; i < 4; i++) {
			if (i < 3) {
				for (int j = 0; j < len - 1; j++) {
					map[prev.first + x[i] * j][prev.second + y[i] * j]
						= map[next.first + x[(i + 1) % 4] * j][next.second + y[(i + 1) % 4] * j];
				}
			}
			else {
				for (int j = 0; j < len - 1; j++) {
					map[prev.first + x[i] * j][prev.second + y[i] * j]
						= temp[j];
				}
			}
			prev = next;
			next = i2(next.first + x[(i + 1) % 4] * (len - 1), next.second + y[(i + 1) % 4] * (len - 1));
		}
		rotateCounterClockwise(xPos + 1, yPos + 1, len - 2);
	}
}