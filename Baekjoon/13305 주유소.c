#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
	long N;
	long price = 0;
	long ppl;
	long* dp;
	long* pp;

	scanf("%d", &N);

	dp = (long*)malloc(sizeof(long) * (N - 1));
	pp = (long*)malloc(sizeof(long) * N);
	for (int i = 0; i < N - 1; i++) {
		scanf("%d", &dp[i]);
	}
	for (int i = 0; i < N; i++) {
		scanf("%d", &pp[i]);
	}

	ppl = pp[0];
	for (int i = 0; i < N - 1; i++) {
		if (ppl > pp[i + 1]) {
			price += dp[i] * ppl;
			ppl = pp[i + 1];
		}
		else {
			price += dp[i] * ppl;
		}
	}

	printf("%ld", price);
}