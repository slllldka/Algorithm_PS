#include <iostream>
#include <cstring>

using namespace std;

int R, C, T;
int A[50][50];
int dirty[50][50];

int rd[4] = { 1, 0, -1, 0 };
int cd[4] = { 0, 1, 0, -1 };

int cleaner_first_r = -1, cleaner_first_c = 0, cleaner_second_r = -1, cleaner_second_c = 0;

void Diffusion();
void Cleaner();

int main() {
	int result = 0;
	cin >> R >> C >> T;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> A[i][j];
			if (A[i][j] == -1) {
				if (cleaner_first_r == -1) {
					cleaner_first_r = i;
				}
				else {
					cleaner_second_r = i;
				}
			}
		}
	}

	for (int i = 0; i < T; i++) {
		Diffusion();
		Cleaner();
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (A[i][j] != -1) {
				result += A[i][j];
			}
		}
	}

	cout << result;

	return 0;
}

void Diffusion() {
	memset(dirty, 0, sizeof(dirty));
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (A[i][j] >= 5) {
				int amount = A[i][j] / 5;
				for (int k = 0; k < 4; k++) {
					int new_r = i + rd[k];
					int new_c = j + cd[k];
					if (new_r >= 0 && new_r < R && new_c >= 0 && new_c < C) {
						if (A[new_r][new_c] != -1) {
							dirty[new_r][new_c] += amount;
							dirty[i][j] -= amount;
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			A[i][j] += dirty[i][j];
		}
	}
}
void Cleaner() {
	int r, c;
	//first
	r = cleaner_first_r;
	c = cleaner_first_c;
	while (r > 0) {
		r--;
		if (A[r + 1][c] != -1) {
			A[r + 1][c] = A[r][c];
		}
	}
	while (c < C - 1) {
		c++;
		if (A[r][c - 1] != -1) {
			A[r][c - 1] = A[r][c];
		}
	}
	while (r < cleaner_first_r) {
		r++;
		if (A[r - 1][c] != -1) {
			A[r - 1][c] = A[r][c];
		}
	}
	while (c > 0) {
		c--;
		if (A[r][c + 1] != -1) {
			if (A[r][c] == -1) {
				A[r][c + 1] = 0;
			}
			else {
				A[r][c + 1] = A[r][c];
			}
		}
	}

	//second
	r = cleaner_second_r;
	c = cleaner_second_c;
	while (r < R - 1) {
		r++;
		if (A[r - 1][c] != -1) {
			A[r - 1][c] = A[r][c];
		}
	}
	while (c < C - 1) {
		c++;
		if (A[r][c - 1] != -1) {
			A[r][c - 1] = A[r][c];
		}
	}
	while (r > cleaner_second_r) {
		r--;
		if (A[r + 1][c] != -1) {
			A[r + 1][c] = A[r][c];
		}
	}
	while (c > 0) {
		c--;
		if (A[r][c + 1] != -1) {
			if (A[r][c] == -1) {
				A[r][c + 1] = 0;
			}
			else {
				A[r][c + 1] = A[r][c];
			}
		}
	}
}