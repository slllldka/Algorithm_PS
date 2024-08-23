#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
		else {
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
	int N;
	int* arr;
	int m = 0;
	int z = 0;
	int p = 0;
	int sum = 0;
	scanf("%d", &N);
	arr = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}
	mergesort(arr, 0, N - 1);

	for (int i = 0; i < N; i++) {
		if (arr[i] < 0) {
			m++;
		}
		else if (arr[i] == 0) {
			z++;
		}
		else if (arr[i] > 0) {
			p++;
		}
	}

	//양수
	for (int i = N - 1; i >= m + z;) {
		if (i == m + z) {
			sum += arr[m + z];
			break;
		}
		else if (arr[i] * arr[i - 1] > arr[i] + arr[i - 1]) {
			sum += arr[i] * arr[i - 1];
			i -= 2;
		}
		else if (arr[i] * arr[i - 1] <= arr[i] + arr[i - 1]) {
			sum += arr[i];
			i--;
		}
	}

	//음수와 0
	if (m % 2 == 0) {
		for (int i = 0; i < m; i += 2) {
			sum += arr[i] * arr[i + 1];
		}
	}
	else if ((m % 2 == 1) && (z == 0)) {
		for (int i = 0; i < m - 1; i += 2) {
			sum += arr[i] * arr[i + 1];
		}
		sum += arr[m - 1];
	}
	else if ((m % 2 == 1) && (z > 0)) {
		for (int i = 0; i < m - 1; i += 2) {
			sum += arr[i] * arr[i + 1];
		}
	}

	printf("%d", sum);
	free(arr);
	return 0;
}