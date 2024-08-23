#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int N, arr[16][16], num = 0;

//d = 0: east, d = 1: southeast, d = 2: south
void DFS(int r1, int c1, int r2, int c2, int d) {
	if ((r2 == N - 1) && (c2 == N - 1)) {
		num++;
		return;
	}
	if (d == 0) {
		if ((c2 + 1 < N) && (arr[r2][c2 + 1] == 0)) {
			DFS(r2, c2, r2, c2 + 1, 0);
		}
		if ((r2 + 1 < N) && (c2 + 1 < N) && (arr[r2 + 1][c2 + 1] == 0) && (arr[r2][c2 + 1] == 0) && (arr[r2 + 1][c2] == 0)) {
			DFS(r2, c2, r2 + 1, c2 + 1, 1);
		}
	}
	else if (d == 1) {
		if ((r2 + 1 < N) && (arr[r2 + 1][c2] == 0)) {
			DFS(r2, c2, r2 + 1, c2, 2);
		}
		if ((c2 + 1 < N) && (arr[r2][c2 + 1] == 0)) {
			DFS(r2, c2, r2, c2 + 1, 0);
		}
		if ((r2 + 1 < N) && (c2 + 1 < N) && (arr[r2 + 1][c2 + 1] == 0) && (arr[r2][c2 + 1] == 0) && (arr[r2 + 1][c2] == 0)) {
			DFS(r2, c2, r2 + 1, c2 + 1, 1);
		}
	}
	else if (d == 2) {
		if ((r2 + 1 < N) && (arr[r2 + 1][c2] == 0)) {
			DFS(r2, c2, r2 + 1, c2, 2);
		}
		if ((r2 + 1 < N) && (c2 + 1 < N) && (arr[r2 + 1][c2 + 1] == 0) && (arr[r2][c2 + 1] == 0) && (arr[r2 + 1][c2] == 0)) {
			DFS(r2, c2, r2 + 1, c2 + 1, 1);
		}
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	DFS(0, 0, 0, 1, 0);
	printf("%d", num);
	return 0;
}