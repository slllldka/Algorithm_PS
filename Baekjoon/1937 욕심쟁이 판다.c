#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))

typedef struct _d {
	int r, c;
	int num;
}Data;

int n, arr[500][500], day[500][500];
int rd[4] = { 1, 0, -1, 0 };
int cd[4] = { 0, 1, 0, -1 };
char v[500][500];

int DFS(int r, int c) {
	int newr, newc, ret, Max = 0;
	if (v[r][c] == 1) {
		return day[r][c];
	}
	else if (v[r][c] == 0) {
		v[r][c] = 1;
	}

	for (int i = 0; i < 4; i++) {
		newr = r + rd[i];
		newc = c + cd[i];
		if ((newr >= 0) && (newr < n) && (newc >= 0) && (newc < n)) {
			if (arr[r][c] < arr[newr][newc]) {
				if (v[newr][newc] == 1) {
					Max = max(Max, 1 + day[newr][newc]);
				}
				else if (v[newr][newc] == 0) {
					ret = DFS(newr, newc);
					Max = max(Max, ret + 1);
				}
			}
		}
	}

	if (Max == 0) {
		day[r][c] = 1;
		return 1;
	}
	else {
		ret = Max;
		day[r][c] = ret;
		return ret;
	}
}

int main() {
	int Max = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (v[i][j] == 0) {
				DFS(i, j);
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			Max = max(Max, day[i][j]);
		}
	}
	printf("%d", Max);
}