#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

int N, M, arr[300][300];
int rd[4] = { 1, 0, -1, 0 };
int cd[4] = { 0, 1, 0, -1 };
char visited[300][300], notzero[300][300];

void DFS(int r, int c) {
	int newr;
	int newc;
	if (arr[r][c] == 0) {
		return;
	}
	if (visited[r][c] == 1) {
		return;
	}
	else if (visited[r][c] == 0) {
		visited[r][c] = 1;
	}

	for (int i = 0; i < 4; i++) {
		newr = r + rd[i];
		newc = c + cd[i];
		if ((newr >= 0) && (newr <= N - 1) && (newc >= 0) && (newc <= M - 1)) {
			if (notzero[newr][newc] > 0) {
				if (visited[newr][newc] == 0) {
					DFS(newr, newc);
				}
			}
			else if (notzero[newr][newc] == 0) {
				if (arr[r][c] > 0) {
					arr[r][c]--;
				}
			}
		}
	}
}

void DFS2(int r, int c) {
	int newr;
	int newc;
	if (arr[r][c] == 0) {
		return;
	}
	if (visited[r][c] == 1) {
		return;
	}
	else if (visited[r][c] == 0) {
		visited[r][c] = 1;
	}

	for (int i = 0; i < 4; i++) {
		newr = r + rd[i];
		newc = c + cd[i];
		if ((newr >= 0) && (newr <= N - 1) && (newc >= 0) && (newc <= M - 1)) {
			if (arr[newr][newc] > 0) {
				if (visited[newr][newc] == 0) {
					DFS2(newr, newc);
				}
			}
		}
	}
}

int main() {
	int count, zero;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	count = 0;
	while (1) {
		zero = 0;
		memset(visited, 0, sizeof(char) * 90000);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (arr[i][j] > 0) {
					zero = -1;
					DFS2(i, j);
					break;
				}
			}
			if (zero == -1) {
				break;
			}
		}

		if (zero == 0) {
			printf("0");
			return 0;
		}
		else if (zero == -1) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					if (arr[i][j] > 0) {
						if (visited[i][j] == 0) {
							printf("%d", count);
							return 0;
						}
					}
				}
			}
		}

		memset(visited, 0, sizeof(char) * 90000);
		memset(notzero, 0, sizeof(char) * 90000);
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (arr[i][j] > 0) {
					notzero[i][j] = 1;
				}
			}
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if ((arr[i][j] > 0) && (visited[i][j] == 0)) {
					DFS(i, j);
					break;
				}
			}
		}
		count++;
	}
}