#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct _d {
	int r, c;
}Data;

char v[50][50];
int N, L, R, arr[50][50];
int count, sum;
int rd[4] = { 1, 0, -1, 0 };
int cd[4] = { 0, 1, 0, -1 };
Data data[2500];

void DFS(int r, int c) {
	Data pos;
	int newr, newc, dif;
	if (v[r][c] == 1) {
		return;
	}
	else if (v[r][c] == 0) {
		v[r][c] = 1;
	}

	pos.r = r;
	pos.c = c;
	data[count] = pos;
	count++;
	sum += arr[r][c];

	for (int i = 0; i < 4; i++) {
		newr = r + rd[i];
		newc = c + cd[i];
		if (newr >= 0 && newr < N && newc >= 0 && newc < N) {
			dif = abs(arr[r][c] - arr[newr][newc]);
			if ((dif >= L) && (dif <= R) && (v[newr][newc] == 0)) {
				DFS(newr, newc);
			}
		}
	}
}

int main() {
	int ret, output;
	scanf("%d %d %d", &N, &L, &R);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	output = 0;
	while (1) {
		ret = -1;
		memset(v, 0, sizeof(char) * 2500);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (v[i][j] == 0) {
					count = 0;
					sum = 0;
					DFS(i, j);
					if (count > 1) {
						ret = 1;
						for (int k = 0; k < count; k++) {
							arr[data[k].r][data[k].c] = sum / count;
						}
					}
				}
			}
		}
		if (ret == -1) {
			break;
		}
		else if (ret == 1) {
			output++;
		}
	}

	printf("%d", output);
	return 0;
}