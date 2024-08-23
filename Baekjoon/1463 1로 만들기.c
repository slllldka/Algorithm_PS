#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int* arr;
int minimum(int f, int s, int t) {
	if ((f <= s) && (f <= t)) {
		return f;
	}
	else if ((s <= f) && (s <= t)) {
		return s;
	}
	else if ((t <= f) && (t <= s)) {
		return t;
	}
}
int Function(int N) {
	int ret;
	if (arr[N] != -1) {
		return arr[N];
	}
	else if (N == 1) {
		arr[N] = 0;
		return 0;
	}
	else if (N == 2 || N == 3) {
		arr[N] = 1;
		return 1;
	}
	else {
		if (N % 3 == 0) {
			if (N % 2 == 0) {
				ret = minimum(Function(N / 3), Function(N / 2), Function(N - 1)) + 1;
				arr[N] = ret;
				return ret;
			}
			else {
				ret = minimum(Function(N / 3), Function(N - 1), 1000001) + 1;
				arr[N] = ret;
				return ret;
			}
		}
		else if (N % 2 == 0) {
			ret = minimum(Function(N / 2), Function(N - 1), 1000001) + 1;
			arr[N] = ret;
			return ret;
		}
		else {
			ret = Function(N - 1) + 1;
			arr[N] = ret;
			return ret;
		}
	}
}
int main() {
	int N, count;
	scanf("%d", &N);
	arr = (int*)malloc(sizeof(int) * (N + 1));
	memset(arr, -1, sizeof(int) * (N + 1));
	count = Function(N);
	printf("%d", count);
	free(arr);
	return 0;
}