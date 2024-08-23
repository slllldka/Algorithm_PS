#include <iostream>
#include <queue>
#include <utility>
#include <cstring>

using namespace std;

typedef pair<int, int> i2;

int x[4] = { -1, 1, 0, 0 };
int y[4] = { 0, 0, 1, -1 };

const int Up = 0, Down = 1, Right = 2, Left = 3, Front = 4, Behind = 5;

int score = 0;
int diceX = 0, diceY = 0, diceDir = Right;
int dice[6] = { 1, 6, 3, 4, 5, 2 }; // Up, Down, Right, Left, Front, Behind
int N, M, K, map[20][20];

bool visit[20][20];
queue<i2> q;

void moveDiceRight();
void moveDiceDown();
void moveDiceLeft();
void moveDiceUp();

int main() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	int newX = 0, newY = 0;
	for (int i = 0; i < K; i++) {
		newX = diceX + x[diceDir];
		newY = diceY + y[diceDir];
		if (newX >= 0 && newX < N && newY >= 0 && newY < M) {
			if (diceDir == Up) {
				moveDiceUp();
			}
			else if (diceDir == Down) {
				moveDiceDown();
			}
			else if (diceDir == Right) {
				moveDiceRight();
			}
			else if (diceDir == Left) {
				moveDiceLeft();
			}
		}
		else {
			if (diceDir == Up) {
				diceDir = Down;
				moveDiceDown();
			}
			else if (diceDir == Down) {
				diceDir = Up;
				moveDiceUp();
			}
			else if (diceDir == Right) {
				diceDir = Left;
				moveDiceLeft();
			}
			else if (diceDir == Left) {
				diceDir = Right;
				moveDiceRight();
			}
		}

		int count = 0;
		q = queue<i2>();
		memset(visit, false, sizeof(visit));
		count++;
		visit[diceX][diceY] = true;
		q.push(i2(diceX, diceY));
		while (!q.empty()) {
			i2 data = q.front();
			q.pop();
			for (int j = 0; j < 4; j++) {
				newX = data.first + x[j];
				newY = data.second + y[j];
				if (newX >= 0 && newX < N && newY >= 0 && newY < M) {
					if (!visit[newX][newY] && (map[diceX][diceY] == map[newX][newY])) {
						count++;
						visit[newX][newY] = true;
						q.push(i2(newX, newY));
					}
				}
			}
		}
		score += map[diceX][diceY] * count;

		if (dice[Down] > map[diceX][diceY]) {
			if (diceDir == Up) {
				diceDir = Right;
			}
			else if (diceDir == Right) {
				diceDir = Down;
			}
			else if (diceDir == Down) {
				diceDir = Left;
			}
			else if (diceDir == Left) {
				diceDir = Up;
			}
		}
		else if (dice[Down] < map[diceX][diceY]) {
			if (diceDir == Up) {
				diceDir = Left;
			}
			else if (diceDir == Left) {
				diceDir = Down;
			}
			else if (diceDir == Down) {
				diceDir = Right;
			}
			else if (diceDir == Right) {
				diceDir = Up;
			}
		}
	}

	cout << score;
	return 0;
}

void moveDiceRight() {
	int temp = dice[Up];
	dice[Up] = dice[Left];
	dice[Left] = dice[Down];
	dice[Down] = dice[Right];
	dice[Right] = temp;
	diceY++;
}
void moveDiceDown() {
	int temp = dice[Up];
	dice[Up] = dice[Behind];
	dice[Behind] = dice[Down];
	dice[Down] = dice[Front];
	dice[Front] = temp;
	diceX++;
}
void moveDiceLeft() {
	int temp = dice[Up];
	dice[Up] = dice[Right];
	dice[Right] = dice[Down];
	dice[Down] = dice[Left];
	dice[Left] = temp;
	diceY--;
}
void moveDiceUp() {
	int temp = dice[Up];
	dice[Up] = dice[Front];
	dice[Front] = dice[Down];
	dice[Down] = dice[Behind];
	dice[Behind] = temp;
	diceX--;
}