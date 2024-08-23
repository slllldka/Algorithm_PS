#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char arr[101][101], visited[100][100];
char set;
int N;
int rd[4] = { 1, 0, -1, 0 };
int cd[4] = { 0, 1, 0, -1 };

void DFS(int r, int c) {
	int newr, newc;
	if (visited[r][c] == 1) {
		return;
	}
	else if (visited[r][c] == 0) {
		visited[r][c] = 1;
	}

	for (int i = 0; i < 4; i++) {
		newr = r + rd[i];
		newc = c + cd[i];
		if ((newr >= 0) && (newr < N) && (newc >= 0) && (newc < N)) {
			if ((arr[newr][newc] == set) && (visited[newr][newc] == 0)) {
				DFS(newr, newc);
			}
		}
	}
}

int main() {
	int area1, area2;
	scanf("%d", &N);
	while (getchar() != '\n');
	for (int i = 0; i < N; i++) {
		fgets(arr[i], N + 1, stdin);
		while (getchar() != '\n');
	}

	area1 = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visited[i][j] == 0) {
				set = arr[i][j];
				DFS(i, j);
				area1++;
			}
		}
	}

	memset(visited, 0, sizeof(char) * 10000);
	area2 = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (arr[i][j] == 'G') {
				arr[i][j] = 'R';
			}
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visited[i][j] == 0) {
				set = arr[i][j];
				DFS(i, j);
				area2++;
			}
		}
	}
	printf("%d %d", area1, area2);
	return 0;
}