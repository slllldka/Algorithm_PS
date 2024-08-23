#include <iostream>
#include <list>
#include <utility>
#include <cstring>
#include <queue>

using namespace std;

using pii = pair<int, int>;

int x[4] = { 1, 0, -1, 0 };
int y[4] = { 0, 1, 0, -1 };

int N, M, arr[20][20], temp[20][20];
bool visit[20][20];

int bigSize, bigRainbow;
list<pii> bigBlocks;

bool findBlockGroup();
void gravitationalAction();
void rotateCounterClockwise();
void printArr();

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}

	int score = 0;
	while (findBlockGroup()) {
		score += bigSize * bigSize;
		for (pii e : bigBlocks) {
			arr[e.first][e.second] = -2;
		}
		gravitationalAction();
		rotateCounterClockwise();
		gravitationalAction();
	}

	cout << score;
	return 0;
}

bool findBlockGroup() {
	queue<pii> q;
	list<pii> blocks;
	int color = -1, size = 0, rainbow = 0;
	int newX, newY;
	pii data;
	bigSize = 0;
	bigRainbow = 0;
	bigBlocks = list<pii>();
	memset(visit, false, sizeof(visit));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!visit[i][j]) {
				if (arr[i][j] > 0) {
					visit[i][j] = true;
					blocks = list<pii>();
					blocks.push_back(pii(i, j));
					color = arr[i][j];
					size = 1;
					rainbow = 0;

					q = queue<pii>();
					q.push(pii(i, j));
					while (!q.empty()) {
						data = q.front();
						q.pop();
						for (int k = 0; k < 4; k++) {
							newX = data.first + x[k];
							newY = data.second + y[k];
							if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
								if (!visit[newX][newY]) {
									if (arr[newX][newY] == color) {
										visit[newX][newY] = true;
										size++;
										blocks.push_back(pii(newX, newY));
										q.push(pii(newX, newY));
									}
									else if (arr[newX][newY] == 0) {
										visit[newX][newY] = true;
										size++;
										rainbow++;
										blocks.push_back(pii(newX, newY));
										q.push(pii(newX, newY));
									}
								}
							}
						}
					}

					for (pii e : blocks) {
						if (arr[e.first][e.second] == 0) {
							visit[e.first][e.second] = false;
						}
					}

					if (size >= 2) {
						if (size > bigSize) {
							bigSize = size;
							bigRainbow = rainbow;
							bigBlocks = list<pii>(blocks);
						}
						else if (size == bigSize) {
							if (rainbow > bigRainbow) {
								bigSize = size;
								bigRainbow = rainbow;
								bigBlocks = list<pii>(blocks);
							}
							else if (rainbow == bigRainbow) {
								if (blocks.front().first > bigBlocks.front().first) {
									bigSize = size;
									bigRainbow = rainbow;
									bigBlocks = list<pii>(blocks);
								}
								else if (blocks.front().first == bigBlocks.front().first) {
									if (blocks.front().second > bigBlocks.front().second) {
										bigSize = size;
										bigRainbow = rainbow;
										bigBlocks = list<pii>(blocks);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	if (bigSize >= 2) {
		return true;
	}
	else {
		return false;
	}
}

void gravitationalAction() {
	int count;
	for (int i = N - 2; i >= 0; i--) {
		for (int j = 0; j < N; j++) {
			if (arr[i][j] != -1) {
				count = 1;
				while (i + count < N) {
					if (arr[i + count][j] == -2) {
						arr[i + count][j] = arr[i + count - 1][j];
						arr[i + count - 1][j] = -2;
						count++;
					}
					else {
						break;
					}
				}
			}
		}
	}
}

void rotateCounterClockwise() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			temp[i][j] = arr[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			arr[N - 1 - j][i] = temp[i][j];
		}
	}
}
void printArr(){
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << arr[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}