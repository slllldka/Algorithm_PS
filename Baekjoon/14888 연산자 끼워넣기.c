#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

int N, arr[11];
int Plus, Minus, Multiple, Divide;
int Max = INT_MIN, Min = INT_MAX;

void Find(int num, int idx, char op, int plus, int minus, int multiple, int divide) {
	int result = 0;
	if (idx == 0) {
		result = arr[idx];
	}
	else {
		if (op == '+') {
			result = num + arr[idx];
		}
		else if (op == '-') {
			result = num - arr[idx];
		}
		else if (op == '*') {
			result = num * arr[idx];
		}
		else if (op == '/') {
			result = num / arr[idx];
		}
	}

	if ((plus == 0) && (minus == 0) && (multiple == 0) && (divide == 0)) {
		Min = min(Min, result);
		Max = max(Max, result);
		return;
	}
	else {
		if (plus > 0) {
			Find(result, idx + 1, '+', plus - 1, minus, multiple, divide);
		}
		if (minus > 0) {
			Find(result, idx + 1, '-', plus, minus - 1, multiple, divide);
		}
		if (multiple > 0) {
			Find(result, idx + 1, '*', plus, minus, multiple - 1, divide);
		}
		if (divide > 0) {
			Find(result, idx + 1, '/', plus, minus, multiple, divide - 1);
		}
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}
	scanf("%d %d %d %d", &Plus, &Minus, &Multiple, &Divide);

	Find(0, 0, 0, Plus, Minus, Multiple, Divide);
	printf("%d\n%d", Max, Min);
	return 0;
}