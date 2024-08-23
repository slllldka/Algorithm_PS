#include <iostream>
#include <queue>

using namespace std;

typedef deque<int> vi;

int N, M, K;
int map[10][10];
int A[10][10];

int rd[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int cd[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

vi trees[10][10];

void Spring();
void Fall();
void Winter();

int main() {
	int x, y, z, result = 0;
	cin >> N >> M >> K;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> A[i][j];
			map[i][j] = 5;
		}
	}

	for (int i = 0; i < M; i++) {
		cin >> x >> y >> z;
		trees[x - 1][y - 1].push_back(z);
	}

	for (int i = 0; i < K; i++) {
		Spring();
		Fall();
		Winter();
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			result += trees[i][j].size();
		}
	}

	cout << result;

	return 0;
}

void Spring() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int food = 0;
			int size = trees[i][j].size();
			for (int k = 0; k < size; k++) {
				int age = trees[i][j].front();
				trees[i][j].pop_front();
				if (map[i][j] >= age) {
					map[i][j] -= age;
					trees[i][j].push_back(age + 1);
				}
				else {
					food += age / 2;
				}
			}
			map[i][j] += food;
		}
	}
}
void Fall() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int size = trees[i][j].size();
			for (int k = 0; k < size; k++) {
				if (trees[i][j][k] % 5 == 0) {
					for (int l = 0; l < 8; l++) {
						int new_r = i + rd[l];
						int new_c = j + cd[l];
						if (new_r >= 0 && new_r < N && new_c >= 0 && new_c < N) {
							trees[new_r][new_c].push_front(1);
						}
					}
				}
			}
		}
	}
}
void Winter() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] += A[i][j];
		}
	}
}