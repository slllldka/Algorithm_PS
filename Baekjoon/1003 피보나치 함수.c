#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arr0[41];
int arr1[41];

void fibonacci(int n) {
	if (n == 0) {
		arr0[n] = 1;
		arr1[n] = 0;
	}
	else if (n == 1) {
		arr0[n] = 0;
		arr1[n] = 1;
	}
	else if ((arr0[n] == -1) && (arr1[n] == -1)) {
		fibonacci(n - 1);
		fibonacci(n - 2);
		arr0[n] = arr0[n - 1] + arr0[n - 2];
		arr1[n] = arr1[n - 1] + arr1[n - 2];
	}
}

int main() {
	int T, N;
	char** str;
	scanf("%d", &T);
	str = (char**)malloc(sizeof(char*) * T);
	memset(arr0, -1, sizeof(int) * 41);
	memset(arr1, -1, sizeof(int) * 41);
	for (int i = 0; i < T; i++) {
		scanf("%d", &N);
		str[i] = (char*)malloc(sizeof(char) * 20);
		fibonacci(N);
		sprintf(str[i], "%d %d\n", arr0[N], arr1[N]);
	}

	for (int i = 0; i < T; i++) {
		printf("%s", str[i]);
		free(str[i]);
	}
	free(str);
	return 0;
}