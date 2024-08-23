#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

int y[1001];

int BS(int s, int e, int target) {
	if (s == e) {
		if (y[s] == target) {
			return s;
		}
		else if (y[s] < target) {
			return s + 1;
		}
		else {
			return s;
		}
	}
	else if (s + 1 == e) {
		if (target <= y[s]) {
			return s;
		}
		else if (target <= y[e]) {
			return e;
		}
		else {
			return e + 1;
		}
	}
	int m = (s + e) / 2;
	if (y[m] == target) {
		return m;
	}
	else if (y[m] < target) {
		return BS(m + 1, e, target);
	}
	else {
		return BS(s, m - 1, target);
	}
}

int main() {
	int idx, N, D = 0;
	int x[1001];
	for (int i = 1; i < 1001; i++) {
		y[i] = 1001;
	}
	x[0] = 0;
	y[0] = 0;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", x + i);
	}

	for (int i = 1; i <= N; i++) {
		idx = BS(0, D, x[i]);
		D = max(D, idx);
		y[idx] = min(y[idx], x[i]);
	}

	printf("%d", D);
	return 0;
}