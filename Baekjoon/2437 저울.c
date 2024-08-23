#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void merge(int arr1[], int s, int m, int e) {
	int* arr2 = (int*)malloc(sizeof(int) * (e - s + 1));
	int i = s;
	int j = m + 1;
	int k = 0;
	while ((i <= m) && (j <= e)) {
		if (arr1[i] <= arr1[j]) {
			arr2[k] = arr1[i];
			i++;
			k++;
		}
		else if (arr1[j] <= arr1[i]) {
			arr2[k] = arr1[j];
			j++;
			k++;
		}
	}
	if (i == m + 1) {
		for (; j <= e; j++) {
			arr2[k] = arr1[j];
			k++;
		}
	}
	else if (j == e + 1) {
		for (; i <= m; i++) {
			arr2[k] = arr1[i];
			k++;
		}
	}
	
	k--;
	for (; k >= 0; k--) {
		arr1[k + s] = arr2[k];
	}
	free(arr2);
}
void mergesort(int arr1[], int s, int e) {
	int m;
	if (s < e) {
		m = (s + e) / 2;
		mergesort(arr1, s, m);
		mergesort(arr1, m + 1, e);
		merge(arr1, s, m, e);
	}
}

int main() {
	int N, sum;
	int* arr;
	scanf("%d", &N);
	arr = (int*)malloc(sizeof(int) * N);
	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	mergesort(arr, 0, N - 1);
	if (arr[0] != 1) {
		printf("1");
		free(arr);
		return 0;
	}
	
	sum = 0;
	for (int i = 0; i < N; i++) {
		if (arr[i] - 1 <= sum) {
			sum += arr[i];
		}
		else if (arr[i] - 1 > sum) {
			printf("%d", sum + 1);
			free(arr);
			return 0;
		}
	}
	printf("%d", sum + 1);
	free(arr);
	return 0;
}