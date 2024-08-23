#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int n;
	long long arr[91];
	scanf("%d", &n);
	arr[0] = 0;
	arr[1] = 1;
	for (int i = 2; i <= n; i++) {
		arr[i] = arr[i - 1] + arr[i - 2];
	}
	printf("%lld", arr[n]);
	return 0;
}