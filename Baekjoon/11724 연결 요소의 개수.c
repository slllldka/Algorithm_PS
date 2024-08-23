#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char visited[1001];
int N, M, arr[1001][1001];

void DFS(int start) {
	if (visited[start] == 1) {
		return;
	}
	else if (visited[start] == 0) {
		visited[start] = 1;
	}

	for (int i = 1; i <= N; i++) {
		if (arr[start][i] == 1) {
			if (visited[i] == 0) {
				DFS(i);
			}
		}
	}
}

int main() {
	int num = 0;
	int u, v;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &u, &v);
		arr[u][v] = 1;
		arr[v][u] = 1;
	}

	for (int i = 1; i <= N; i++) {
		if (visited[i] == 0) {
			DFS(i);
			num++;
		}
	}
	printf("%d", num);
	return 0;
}