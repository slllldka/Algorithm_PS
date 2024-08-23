#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

int N, arr[100][100], exist[101], s, Min, Max;
int rd[4] = { 1, 0 ,-1, 0 };
int cd[4] = { 0, 1, 0, -1 };
char visited[100][100];

void DFS(int r, int c) {
	int newr;
	int newc;

	if (visited[r][c] == 1) {
		return;
	}
	else {
		visited[r][c] = 1;
	}

	for (int i = 0; i < 4; i++) {
		newr = r + rd[i];
		newc = c + cd[i];
		if ((newr >= 0) && (newr <= N - 1) && (newc >= 0) && (newc <= N - 1)) {
			if (arr[newr][newc] > s) {
				if (visited[newr][newc] == 0) {
					DFS(newr, newc);
				}
			}
		}
	}
}

int main() {
	int area, Maxarea;
	Min = 100;
	Max = 1;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &arr[i][j]);
			exist[arr[i][j]] = 1;
			Min = min(Min, arr[i][j]);
			Max = max(Max, arr[i][j]);
		}
	}

	Maxarea = 1;
	for (s = Min; s <= Max; s++) {
		if (exist[s] == 1) {
			area = 0;
			memset(visited, 0, sizeof(char) * 100 * 100);
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if ((arr[i][j] > s) && (visited[i][j] == 0)) {
						DFS(i, j);
						area++;
					}
				}
			}
			Maxarea = max(Maxarea, area);
		}
	}
	printf("%d", Maxarea);
	return 0;
}