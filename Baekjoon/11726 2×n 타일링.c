#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arr[1001];

int Function(int N) {
	int ret;
	if (arr[N] != -1) {
		return arr[N];
	}
	else if (N == 1) {
		arr[N] = 1;
		return 1;
	}
	else if (N == 2) {
		arr[N] = 2;
		return 2;
	}
	else {
		ret = (Function(N - 1) + Function(N - 2)) % 10007;
		arr[N] = ret;
		return ret;
	}
}
int main() {
	int n;
	scanf("%d", &n);
	memset(arr, -1, sizeof(int) * 1001);
	printf("%d", Function(n));
	return 0;
}