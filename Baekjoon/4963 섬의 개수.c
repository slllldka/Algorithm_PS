#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char v[50][50];
int w, h, arr[50][50];
int rd[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
int cd[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };

void DFS(int r, int c) {
	int newr, newc;
	if (arr[r][c] == 0) {
		return;
	}
	if (v[r][c] == 1) {
		return;
	}
	else if (v[r][c] == 0) {
		v[r][c] = 1;
	}

	for (int i = 0; i < 8; i++) {
		newr = r + rd[i];
		newc = c + cd[i];
		if ((newr >= 0) && (newr < h) && (newc >= 0) && (newc < w)) {
			if ((v[newr][newc] == 0) && (arr[newr][newc] == 1)) {
				DFS(newr, newc);
			}
		}
	}
}

int main() {
	int num, count = 0;
	int* output = (int*)malloc(sizeof(int) * 1);
	while (1) {
		num = 0;
		scanf("%d %d", &w, &h);

		if ((w == 0) && (h == 0)) {
			break;
		}

		if (count > 0) {
			output = realloc(output, sizeof(int) * (1 + count));
		}

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				scanf("%d", &arr[i][j]);
			}
		}

		memset(v, 0, sizeof(char) * 50 * 50);
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (arr[i][j] == 1) {
					if (v[i][j] == 0) {
						DFS(i, j);
						num++;
					}
				}
			}
		}
		output[count] = num;
		count++;
	}

	for (int i = 0; i < count; i++) {
		printf("%d\n", output[i]);
	}
	free(output);
	return 0;
}