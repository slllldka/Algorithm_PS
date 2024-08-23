#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a, b) (((a) > (b)) ? (a) : (b))

int main() {
	int i, n, sum;
	int* arr1;
	int* arr2;
	scanf("%d", &n);
	arr1 = (int*)malloc(sizeof(int) * n);
	arr2 = (int*)malloc(sizeof(int) * n);
	memset(arr2, 0, sizeof(int) * n);
	for (i = 0; i < n; i++) {
		scanf("%d", arr1 + i);
	}

	arr2[0] = arr1[0];
	for (i = 1; i < n; i++) {
		arr2[i] = max(arr2[i - 1] + arr1[i], arr1[i]);
	}

	sum = arr2[0];
	for (i = 1; i < n; i++) {
		sum = max(sum, arr2[i]);
	}
	printf("%d", sum);
	free(arr1);
	free(arr2);
	return 0;
}