#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int visited[500][500];
int M, N, arr[500][500];
int rd[4] = { 1, 0, -1, 0 };
int cd[4] = { 0, 1, 0, -1 };
int H = 0;

void DFS(int sr, int sc) {
	int current = H;
	if ((sr == M - 1) && (sc == N - 1)) {
		H++;
		return;
	}

	if (visited[sr][sc] == -1) {
		return;
	}
	else if (visited[sr][sc] > 0) {
		H += visited[sr][sc];
		return;
	}

	int newr, newc;
	for (int i = 0; i < 4; i++) {
		newr = sr + rd[i];
		newc = sc + cd[i];
		if ((newr >= 0) && (newr < M) && (newc >= 0) && (newc < N)) {
			if (arr[sr][sc] > arr[newr][newc]) {
				DFS(newr, newc);
			}
		}
	}
	if (current < H) {
		visited[sr][sc] = H - current;
	}
	else {
		visited[sr][sc] = -1;
	}
}

int main() {
	scanf("%d %d", &M, &N);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	DFS(0, 0);
	printf("%d", H);
	return 0;
}