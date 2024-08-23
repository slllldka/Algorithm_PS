#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int M, N, ret;
int nd[4] = { 1, 0, -1, 0 };
int md[4] = { 0, 1, 0, -1 };
char arr[50][50], visited[50][50];

void DFS(int n, int m) {
	int newn, newm;
	if (arr[n][m] == 0) {
		return;
	}
	if (visited[n][m] == 1) {
		return;
	}
	else if (visited[n][m] == 0) {
		visited[n][m] = 1;
	}

	for (int i = 0; i < 4; i++) {
		newn = n + nd[i];
		newm = m + md[i];
		if ((newn >= 0) && (newn < N) && (newm >= 0) && (newm < M)) {
			if ((arr[newn][newm] == 1) && (visited[newn][newm] == 0)) {
				DFS(newn, newm);
			}
		}
	}
}

int main() {
	int T, K, x, y;
	int* output;
	scanf("%d", &T);
	output = (int*)malloc(sizeof(int) * T);

	for (int i = 0; i < T; i++) {
		scanf("%d %d %d", &M, &N, &K);
		ret = 0;
		memset(arr, 0, sizeof(char) * 2500);
		memset(visited, 0, sizeof(char) * 2500);
		for (int j = 0; j < K; j++) {
			scanf("%d %d", &x, &y);
			arr[y][x] = 1;
		}

		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				if ((arr[j][k] == 1) && (visited[j][k] == 0)) {
					DFS(j, k);
					ret++;
				}
			}
		}
		output[i] = ret;
	}

	for (int i = 0; i < T; i++) {
		printf("%d\n", output[i]);
	}
	free(output);
	return 0;
}