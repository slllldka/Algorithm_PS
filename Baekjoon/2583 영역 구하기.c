#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char visited[100][100];
int M, N, K, arr[100][100], output[5000];
int rd[4] = { 1, 0, -1, 0 };
int cd[4] = { 0, 1, 0, -1 };
int area;

void merge(int arr[], int s, int m, int e) {
	int* temp = (int*)malloc(sizeof(int) * (e - s + 1));
	int i = s;
	int j = m + 1;
	int k = 0;
	while ((i <= m) && (j <= e)) {
		if (arr[i] <= arr[j]) {
			temp[k] = arr[i];
			i++;
			k++;
		}
		else {
			temp[k] = arr[j];
			j++;
			k++;
		}
	}
	while (i <= m) {
		temp[k] = arr[i];
		i++;
		k++;
	}
	while (j <= e) {
		temp[k] = arr[j];
		j++;
		k++;
	}

	k--;
	for (; k >= 0; k--) {
		arr[s + k] = temp[k];
	}
	free(temp);
}
void mergesort(int arr[], int s, int e) {
	if (s < e) {
		int m = (s + e) / 2;
		mergesort(arr, s, m);
		mergesort(arr, m + 1, e);
		merge(arr, s, m, e);
	}
}

void DFS(int r, int c) {
	int newr, newc;
	if (visited[r][c] == 1) {
		return;
	}
	else if (visited[r][c] == 0) {
		visited[r][c] = 1;
		area++;
	}

	for (int i = 0; i < 4; i++) {
		newr = r + rd[i];
		newc = c + cd[i];
		if ((newr >= 0) && (newr < M) && (newc >= 0) && (newc < N)) {
			if ((arr[newr][newc] == 0) && (visited[newr][newc] == 0)) {
				DFS(newr, newc);
			}
		}
	}
}

int main() {
	int a, b, c, d;
	int count = 0;
	scanf("%d %d %d", &M, &N, &K);
	for (int i = 0; i < K; i++) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		for (int j = b; j < d; j++) {
			for (int k = a; k < c; k++) {
				if (arr[j][k] == 0) {
					arr[j][k] = 1;
				}
			}
		}
	}

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if ((arr[i][j] == 0) && (visited[i][j] == 0)) {
				area = 0;
				DFS(i, j);
				output[count] = area;
				count++;
			}
		}
	}
	mergesort(output, 0, count - 1);

	printf("%d\n", count);
	for (int i = 0; i < count; i++) {
		printf("%d ", output[i]);
	}
	return 0;
}