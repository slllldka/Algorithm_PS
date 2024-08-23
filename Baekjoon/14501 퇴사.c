#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))

int N, T[16], P[16], S[17];

void Go(int d, int sum) {
	if (S[d - 1] > sum) {
		return;
	}
	else {
		S[d - 1] = sum;
	}
	if (d + T[d] - 1 < N) {
		Go(d + T[d], sum + P[d]);
	}
	else if (d + T[d] - 1 == N) {
		S[N + 1] = max(sum + P[d], S[N + 1]);
	}
	else {
		S[N + 1] = max(sum, S[N + 1]);
	}
	if ((d + 1 <= N) && (T[d] > 1)) {
		Go(d + 1, sum);
	}

}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &T[i], &P[i]);
	}
	Go(1, 0);
	printf("%d", S[N + 1]);
}