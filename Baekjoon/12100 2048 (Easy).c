#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))

int N, Max = 0;

void Left(int** src, int** dst) {
	int f, count;
	for (int i = 0; i < N; i++) {
		f = 0;
		count = 0;
		for (int j = 0; j < N; j++) {
			if ((f == 0) && (src[i][j] != 0)) {
				f = src[i][j];
			}
			else if ((f != 0) && (src[i][j] != 0)) {
				if (f == src[i][j]) {
					dst[i][count] = f * 2;
					Max = max(Max, f * 2);
					count++;
					f = 0;
				}
				else {
					dst[i][count] = f;
					Max = max(Max, f);
					count++;
					f = src[i][j];
				}
			}
		}
		if (f != 0) {
			dst[i][count] = f;
			Max = max(Max, f);
			count++;
		}
		for (; count < N; count++) {
			dst[i][count] = 0;
		}
	}
}
void Right(int** src, int** dst) {
	int f, count;
	for (int i = 0; i < N; i++) {
		f = 0;
		count = 0;
		for (int j = 0; j < N; j++) {
			if ((f == 0) && (src[i][N - 1 - j] != 0)) {
				f = src[i][N - 1 - j];
			}
			else if ((f != 0) && (src[i][N - 1 - j] != 0)) {
				if (f == src[i][N - 1 - j]) {
					dst[i][N - 1 - count] = f * 2;
					Max = max(Max, f * 2);
					count++;
					f = 0;
				}
				else {
					dst[i][N - 1 - count] = f;
					Max = max(Max, f);
					count++;
					f = src[i][N - 1 - j];
				}
			}
		}
		if (f != 0) {
			dst[i][N - 1 - count] = f;
			Max = max(Max, f);
			count++;
		}
		for (; count < N; count++) {
			dst[i][N - 1 - count] = 0;
		}
	}
}
void Up(int** src, int** dst) {
	int f, count;
	for (int i = 0; i < N; i++) {
		f = 0;
		count = 0;
		for (int j = 0; j < N; j++) {
			if ((f == 0) && (src[j][i] != 0)) {
				f = src[j][i];
			}
			else if ((f != 0) && (src[j][i] != 0)) {
				if (f == src[j][i]) {
					dst[count][i] = f * 2;
					Max = max(Max, f * 2);
					count++;
					f = 0;
				}
				else {
					dst[count][i] = f;
					Max = max(Max, f);
					count++;
					f = src[j][i];
				}
			}
		}
		if (f != 0) {
			dst[count][i] = f;
			Max = max(Max, f);
			count++;
		}
		for (; count < N; count++) {
			dst[count][i] = 0;
		}
	}
}
void Down(int** src, int** dst) {
	int f, count;
	for (int i = 0; i < N; i++) {
		f = 0;
		count = 0;
		for (int j = 0; j < N; j++) {
			if ((f == 0) && (src[N - 1 - j][i] != 0)) {
				f = src[N - 1 - j][i];
			}
			else if ((f != 0) && (src[N - 1 - j][i] != 0)) {
				if (f == src[N - 1 - j][i]) {
					dst[N - 1 - count][i] = f * 2;
					Max = max(Max, f * 2);
					count++;
					f = 0;
				}
				else {
					dst[N - 1 - count][i] = f;
					Max = max(Max, f);
					count++;
					f = src[N - 1 - j][i];
				}
			}
		}
		if (f != 0) {
			dst[N - 1 - count][i] = f;
			Max = max(Max, f);
			count++;
		}
		for (; count < N; count++) {
			dst[N - 1 - count][i] = 0;
		}
	}
}

void DFS(int** arr, int num) {
	if (num == 5) {
		return;
	}
	int** src, ** dst;
	src = (int**)malloc(sizeof(int*) * N);
	dst = (int**)malloc(sizeof(int*) * N);
	for (int i = 0; i < N; i++) {
		src[i] = (int*)malloc(sizeof(int) * N);
		dst[i] = (int*)malloc(sizeof(int) * N);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			src[i][j] = arr[i][j];
		}
	}

	Left(src, dst);
	DFS(dst, num + 1);
	Right(src, dst);
	DFS(dst, num + 1);
	Up(src, dst);
	DFS(dst, num + 1);
	Down(src, dst);
	DFS(dst, num + 1);

	for (int i = 0; i < N; i++) {
		free(src[i]);
		free(dst[i]);
	}
	free(src);
	free(dst);
}

int main() {
	int** start;
	scanf("%d", &N);
	
	start = (int**)malloc(sizeof(int*) * N);
	for (int i = 0; i < N; i++) {
		start[i] = (int*)malloc(sizeof(int) * N);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &start[i][j]);
		}
	}

	DFS(start, 0);
	printf("%d", Max);
	
	for (int i = 0; i < N; i++) {
		free(start[i]);
	}
	free(start);
	return 0;
}