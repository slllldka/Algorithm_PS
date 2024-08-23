#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))

int N, arr[21][21], start[10], link[10];
int Min = 100000;

int dif() {
	int ss = 0, ls = 0, ret;
	for (int i = 0; i < N / 2; i++) {
		for (int j = 0; j < N / 2; j++) {
			if (start[i] != start[j]) {
				ss += arr[start[i]][start[j]];
			}
			if (link[i] != link[j]) {
				ls += arr[link[i]][link[j]];
			}
		}
	}

	ret = abs(ss - ls);
	return ret;
}

void team(int idx, int s, int l) {
	if ((s == N / 2) && (l == N / 2)) {
		Min = min(Min, dif());
	}
	else {
		if (s < N / 2) {
			start[s] = idx;
			team(idx + 1, s + 1, l);
		}
		if (l < N / 2) {
			link[l] = idx;
			team(idx + 1, s, l + 1);
		}
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	start[0] = 1;

	team(2, 1, 0);
	printf("%d", Min);
	return 0;
}