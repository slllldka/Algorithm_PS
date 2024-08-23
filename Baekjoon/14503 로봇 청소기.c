#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N, M, arr[50][50], ret;
int rd[4] = { -1, 0, 1, 0 };
int cd[4] = { 0, 1, 0, -1 };
char visited[50][50];

void DFS(int r, int c, int d) {
	int newr, newc, idx;
	if (arr[r][c] == 0) {
		if (visited[r][c] == 0) {
			visited[r][c] = 1;
			ret++;
		}
	}

	if (d == 0) {
		// 3 -> 2 -> 1 -> 0
		for (int i = 3; i >= 0; i--) {
			idx = i;
			newr = r + rd[idx];
			newc = c + cd[idx];
			if (arr[newr][newc] == 0) {
				if (visited[newr][newc] == 0) {
					DFS(newr, newc, idx);
					return;
				}
			}
		}
		newr = r - rd[d];
		newc = c - cd[d];
		if (arr[newr][newc] == 0) {
			DFS(newr, newc, d);
		}
	}
	else if (d == 1) {
		// 0 -> 3 -> 2 -> 1
		for (int i = 3; i >= 0; i--) {
			idx = (i + 1) % 4;
			newr = r + rd[idx];
			newc = c + cd[idx];
			if (arr[newr][newc] == 0) {
				if (visited[newr][newc] == 0) {
					DFS(newr, newc, idx);
					return;
				}
			}
		}
		newr = r - rd[d];
		newc = c - cd[d];
		if (arr[newr][newc] == 0) {
			DFS(newr, newc, d);
		}
	}
	else if (d == 2) {
		// 1 -> 0 -> 3 -> 2
		for (int i = 3; i >= 0; i--) {
			idx = (i + 2) % 4;
			newr = r + rd[idx];
			newc = c + cd[idx];
			if (arr[newr][newc] == 0) {
				if (visited[newr][newc] == 0) {
					DFS(newr, newc, idx);
					return;
				}
			}
		}
		newr = r - rd[d];
		newc = c - cd[d];
		if (arr[newr][newc] == 0) {
			DFS(newr, newc, d);
		}
	}
	else if (d == 3) {
		// 2 -> 1 -> 0 -> 3
		for (int i = 3; i >= 0; i--) {
			idx = (i + 3) % 4;
			newr = r + rd[idx];
			newc = c + cd[idx];
			if (arr[newr][newc] == 0) {
				if (visited[newr][newc] == 0) {
					DFS(newr, newc, idx);
					return;
				}
			}
		}
		newr = r - rd[d];
		newc = c - cd[d];
		if (arr[newr][newc] == 0) {
			DFS(newr, newc, d);
		}
	}
}

int main() {
	int r, c, d;
	scanf("%d %d", &N, &M);
	scanf("%d %d %d", &r, &c, &d);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	ret = 0;
	DFS(r, c, d);
	printf("%d", ret);
}