#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N, arr[1000000], B, C;

int main() {
	int quo, mod;
	unsigned long long total = 0;

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
	scanf("%d %d", &B, &C);

	for (int i = 0; i < N; i++) {
		total++;
		arr[i] -= B;
		if (arr[i] > 0) {
			quo = arr[i] / C;
			mod = arr[i] % C;
			if (mod == 0) {
				total += quo;
			}
			else {
				total += quo + 1;
			}
		}
	}

	printf("%llu", total);
	return 0;
}