#include <iostream>
#include <tuple>
#include <list>
#include <algorithm>

#define min(a, b) a < b ? a : b

using namespace std;

typedef tuple<int, int, int> i3;

int N, M, K, minSum = 2147483647;
int inputMap[50][50];
int map[50][50];
int temp[50][50];

i3 rotation[6];

list<int> permuList;

void rotateArray(i3);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int r, c, s;
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> inputMap[i][j];
		}
	}

	for (int i = 0; i < K; i++) {
		cin >> r >> c >> s;
		rotation[i] = i3(r, c, s);
		permuList.push_back(i);
	}

	do {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				map[i][j] = inputMap[i][j];
			}
		}

		for (int idx : permuList) {
			rotateArray(rotation[idx]);
		}

		int sum = 0;
		for (int i = 0; i < N; i++) {
			sum = 0;
			for (int j = 0; j < M; j++) {
				sum += map[i][j];
			}
			minSum = min(minSum, sum);
		}

	} while (next_permutation(permuList.begin(), permuList.end()));

	cout << minSum;

	return 0;
}

void rotateArray(i3 info) {
	int r, c, s;
	tie(r, c, s) = info;
	r--;
	c--;

	for (int i = -s; i <= s; i++) {
		for (int j = -s; j <= s; j++) {
			if (i == 0 && j == 0) {
				temp[r][c] = map[r][c];
			}
			else {
				if (j >= i && j < -i) {
					temp[r + i][c + j + 1] = map[r + i][c + j];
				}
				else if (j > i && j >= -i) {
					temp[r + i + 1][c + j] = map[r + i][c + j];
				}
				else if (j <= i && j > -i) {
					temp[r + i][c + j - 1] = map[r + i][c + j];
				}
				else if (j < i && j <= -i) {
					temp[r + i - 1][c + j] = map[r + i][c + j];
				}
			}
		}
	}

	for (int i = -s; i <= s; i++) {
		for (int j = -s; j <= s; j++) {
			map[r + i][c + j] = temp[r + i][c + j];
		}
	}
}