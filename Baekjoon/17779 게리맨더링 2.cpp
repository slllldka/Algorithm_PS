#include <iostream>

using namespace std;

int N;

int city[20][20];

int get_difference(int, int, int, int);
bool available_separating(int, int, int, int);

int main() {
	int Min = 50000;

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> city[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 1; k <= j; k++) {
				for (int l = 1; l < N - j; l++) {
					if (available_separating(i, j, k, l)) {
						int diff = get_difference(i, j, k, l);
						Min = Min > diff ? diff : Min;
					}
				}
			}
		}
	}

	cout << Min;

	return 0;
}

int get_difference(int x, int y, int d1, int d2) {
	int district[5] = { 0, 0, 0, 0, 0 };
	int max = 0, min = 50000;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if ((i + j) >= (x + y) && (i + j) <= (x + y + 2 * d2) && (j - i) >= (y - x - 2 * d1) && (j - i) <= (y - x)) {
				district[4] += city[i][j];
			}
			else if (i >= 0 && i < (x + d1) && j >= 0 && j <= y) {
				district[0] += city[i][j];
			}
			else if (i >= 0 && i <= (x + d2) && j > y && j < N) {
				district[1] += city[i][j];
			}
			else if (i >= (x + d1) && i < N && j >= 0 && j < (y - d1 + d2)) {
				district[2] += city[i][j];
			}
			else if (i > (x + d2) && i < N && j >= (y - d1 + d2) && j < N) {
				district[3] += city[i][j];
			}
		}
	}

	for (int i = 0; i < 5; i++) {
		min = min > district[i] ? district[i] : min;
		max = max > district[i] ? max : district[i];
	}

	return max - min;
}

bool available_separating(int x, int y, int d1, int d2) {
	if (x < 0 || x >= N || y < 0 || y >= N) {
		return false;
	}
	if ((x+d1) < 0 || (x+d1) >= N || (y-d1) < 0 || (y-d1) >= N) {
		return false;
	}
	if ((x+d2) < 0 || (x+d2) >= N || (y+d2) < 0 || (y+d2) >= N) {
		return false;
	}
	if ((x+d1+d2) < 0 || (x+d1+d2) >= N || (y-d1+d2) < 0 || (y-d1+d2) >= N) {
		return false;
	}

	return true;
}