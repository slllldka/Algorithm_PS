#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))

int N, M, arr[500][500];
int Max = 0;

void t1(int r, int c) {
	int sum;
	if (c + 3 < M) {
		sum = arr[r][c] + arr[r][c + 1] + arr[r][c + 2] + arr[r][c + 3];
		Max = max(Max, sum);
	}
}
void t2(int r, int c) {
	int sum;
	if (r + 3 < N) {
		sum = arr[r][c] + arr[r + 1][c] + arr[r + 2][c] + arr[r + 3][c];
		Max = max(Max, sum);
	}
}
void t3(int r, int c) {
	int sum;
	if ((r + 1 < N) && (c + 1 < M)) {
		sum = arr[r][c] + arr[r + 1][c] + arr[r][c + 1] + arr[r + 1][c + 1];
		Max = max(Max, sum);
	}
}
void t4(int r, int c) {
	int sum;
	if ((r + 2 < N) && (c + 1 < M)) {
		sum = arr[r][c] + arr[r + 1][c] + arr[r + 2][c] + arr[r + 2][c + 1];
		Max = max(Max, sum);
	}
}
void t5(int r, int c) {
	int sum;
	if ((r + 1 < N) && (c + 2 < M)) {
		sum = arr[r][c] + arr[r + 1][c] + arr[r][c + 1] + arr[r][c + 2];
		Max = max(Max, sum);
	}
}
void t6(int r, int c) {
	int sum;
	if ((r + 2 < N) && (c + 1 < M)) {
		sum = arr[r][c] + arr[r][c + 1] + arr[r + 1][c + 1] + arr[r + 2][c + 1];
		Max = max(Max, sum);
	}
}
void t7(int r, int c) {
	int sum;
	if ((r - 1 >= 0) && (c + 2) < M) {
		sum = arr[r][c] + arr[r][c + 1] + arr[r][c + 2] + arr[r - 1][c + 2];
		Max = max(Max, sum);
	}
}
void t8(int r, int c) {
	int sum;
	if ((r - 2 >= 0) && (c + 1 < M)) {
		sum = arr[r][c] + arr[r][c + 1] + arr[r - 1][c + 1] + arr[r - 2][c + 1];
		Max = max(Max, sum);
	}
}
void t9(int r, int c) {
	int sum;
	if ((r + 1 < N) && (c + 2 < M)) {
		sum = arr[r][c] + arr[r + 1][c] + arr[r + 1][c + 1] + arr[r + 1][c + 2];
		Max = max(Max, sum);
	}
}
void t10(int r, int c) {
	int sum;
	if ((r + 2 < N) && (c + 1 < M)) {
		sum = arr[r][c] + arr[r + 1][c] + arr[r + 2][c] + arr[r][c + 1];
		Max = max(Max, sum);
	}
}
void t11(int r, int c) {
	int sum;
	if ((r + 1 < N) && (c + 2 < M)) {
		sum = arr[r][c] + arr[r][c + 1] + arr[r][c + 2] + arr[r + 1][c + 2];
		Max = max(Max, sum);
	}
}
void t12(int r, int c) {
	int sum;
	if ((r + 2 < N) && (c + 1 < M)) {
		sum = arr[r][c] + arr[r + 1][c] + arr[r + 1][c + 1] + arr[r + 2][c + 1];
		Max = max(Max, sum);
	}
}
void t13(int r, int c) {
	int sum;
	if ((r - 1 >= 0) && (c + 2 < M)) {
		sum = arr[r][c] + arr[r][c + 1] + arr[r - 1][c + 1] + arr[r - 1][c + 2];
		Max = max(Max, sum);
	}
}
void t14(int r, int c) {
	int sum;
	if ((r - 1 >= 0) && (r + 1 < N) && (c + 1 < M)) {
		sum = arr[r][c] + arr[r + 1][c] + arr[r][c + 1] + arr[r - 1][c + 1];
		Max = max(Max, sum);
	}
}
void t15(int r, int c) {
	int sum;
	if ((r + 1 < N) && (c + 2 < M)) {
		sum = arr[r][c] + arr[r][c + 1] + arr[r + 1][c + 1] + arr[r + 1][c + 2];
		Max = max(Max, sum);
	}
}
void t16(int r, int c) {
	int sum;
	if ((r + 1 < N) && (c + 2 < M)) {
		sum = arr[r][c] + arr[r][c + 1] + arr[r + 1][c + 1] + arr[r][c + 2];
		Max = max(Max, sum);
	}
}
void t17(int r, int c) {
	int sum;
	if ((r - 1 >= 0) && (r + 1 < N) && (c + 1 < M)) {
		sum = arr[r][c] + arr[r][c + 1] + arr[r - 1][c + 1] + arr[r + 1][c + 1];
		Max = max(Max, sum);
	}
}
void t18(int r, int c) {
	int sum;
	if ((r - 1 >= 0) && (c + 2 < M)) {
		sum = arr[r][c] + arr[r][c + 1] + arr[r - 1][c + 1] + arr[r][c + 2];
		Max = max(Max, sum);
	}
}
void t19(int r, int c) {
	int sum;
	if ((r + 2 < N && (c + 1 < M))) {
		sum = arr[r][c] + arr[r + 1][c] + arr[r + 2][c] + arr[r + 1][c + 1];
		Max = max(Max, sum);
	}
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			t1(i, j);
			t2(i, j);
			t3(i, j);
			t4(i, j);
			t5(i, j);
			t6(i, j);
			t7(i, j);
			t8(i, j);
			t9(i, j);
			t10(i, j);
			t11(i, j);
			t12(i, j);
			t13(i, j);
			t14(i, j);
			t15(i, j);
			t16(i, j);
			t17(i, j);
			t18(i, j);
			t19(i, j);
		}
	}
	printf("%d", Max);
	return 0;
}