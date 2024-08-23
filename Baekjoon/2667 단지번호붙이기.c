#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char arr[25][26];
char v[25][25];
int N, h;
int D[600];
int rd[4] = { 1, 0, -1, 0 };
int cd[4] = { 0, 1, 0, -1 };

void merge(int a[], int s, int m, int e) {
	int* b = (int*)malloc(sizeof(int) * (e - s + 1));
	int i = s;
	int j = m + 1;
	int k = 0;
	while ((i <= m) && (j <= e)) {
		if (a[i] <= a[j]) {
			b[k] = a[i];
			i++;
			k++;
		}
		else {
			b[k] = a[j];
			j++;
			k++;
		}
	}
	while (i <= m) {
		b[k] = a[i];
		i++;
		k++;
	}
	while(j <= e) {
		b[k] = a[j];
		j++;
		k++;
	}
	
	k--;
	for (int i = k; k >= 0; k--) {
		a[s + k] = b[k];
	}
	free(b);
}
void mergesort(int a[], int s, int e) {
	if (s < e) {
		int m = (s + e) / 2;
		mergesort(a, s, m);
		mergesort(a, m + 1, e);
		merge(a, s, m, e);
	}
}

void DFS(int r, int c) {
	if (arr[r][c] == '0') {
		return;
	}
	if (v[r][c] == 1) {
		return;
	}
	
	int nr, nc;
	v[r][c] = 1;
	h++;

	for (int i = 0; i < 4; i++) {
		nr = r + rd[i];
		nc = c + cd[i];
		if ((nr >= 0) && (nr <= N - 1) && (nc >= 0) && (nc <= N - 1)) {
			if (arr[nr][nc] == '1') {
				if (v[nr][nc] == 0) {
					DFS(nr, nc);
				}
			}
		}
	}
}

int main() {
	int count;
	scanf("%d", &N);
	while (getchar() != '\n');
	for (int i = 0; i < N; i++) {
		fgets(arr[i], N + 1, stdin);
		while (getchar() != '\n');
	}

	count = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if ((arr[i][j] == '1') && (v[i][j] == 0)) {
				h = 0;
				DFS(i, j);
				if (h > 0) {
					D[count] = h;
					count++;
				}
			}
		}
	}
	mergesort(D, 0, count - 1);
	printf("%d\n", count);
	for (int i = 0; i < count; i++) {
		printf("%d\n", D[i]);
	}
	return 0;
}