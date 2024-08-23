#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void merge(int arr1[], int s, int m, int e) {
	int* arr2 = (int*)malloc(sizeof(int) * (e - s + 1));
	int i, j, k;
	i = s;
	j = m + 1;
	k = 0;
	while (i <= m && j <= e) {
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
	int sum;
	int i;
	int j;
	int k;
	int* arr1;
	int* arr2;
	scanf("%d", &N);
	arr1 = (int*)malloc(sizeof(int) * N);
	arr2 = (int*)malloc(sizeof(int) * (N - 1));
	for (i = 0; i < N; i++) {
		scanf("%d", arr1 + i);
	}
	mergesort(arr1, 0, N - 1);

	sum = 0;
	i = 0;
	j = 0;
	k = 0;
	while (1) {
		// 2/0, 2/1, 2/2, 1/1, 1/2, 0/2, 종료조건: 0/1
		if (N == 1) {
			break;
		}
		else if ((i < N - 1) && (j == 0)) {
			arr2[j] = arr1[i] + arr1[i + 1];
			sum += arr2[j];
			i += 2;
			j++;
		}
		else if ((i < N - 1) && (j - k == 1)) {
			if (arr1[i + 1] <= arr2[k]) {
				arr2[j] = arr1[i] + arr1[i + 1];
				sum += arr2[j];
				i += 2;
				j++;
			}
			else {
				arr2[j] = arr1[i] + arr2[k];
				sum += arr2[j];
				i++;
				j++;
				k++;
			}
		}
		else if ((i < N - 1) && (j - k >= 2)) {
			if (arr1[i + 1] <= arr2[k]) {
				arr2[j] = arr1[i] + arr1[i + 1];
				sum += arr2[j];
				i += 2;
				j++;
			}
			else if ((arr2[k] < arr1[i + 1]) && (arr1[i] <= arr2[k + 1])) {
				arr2[j] = arr1[i] + arr2[k];
				sum += arr2[j];
				i++;
				j++;
				k++;
			}
			else if (arr2[k] < arr1[i]) {
				arr2[j] = arr2[k] + arr2[k + 1];
				sum += arr2[j];
				j++;
				k += 2;
			}
		}
		else if ((i == N - 1) && (j - k == 1)) {
			arr2[j] = arr1[i] + arr2[k];
			sum += arr2[j];
			i++;
			j++;
			k++;
		}
		else if ((i == N - 1) && (j - k >= 2)) {
			if (arr1[i] <= arr2[k + 1]) {
				arr2[j] = arr1[i] + arr2[k];
				sum += arr2[j];
				i++;
				j++;
				k++;
			}
			else {
				arr2[j] = arr2[k] + arr2[k + 1];
				sum += arr2[j];
				j++;
				k += 2;
			}
		}
		else if ((i == N) && (j - k >= 2)) {
			arr2[j] = arr2[k] + arr2[k + 1];
			sum += arr2[j];
			j++;
			k += 2;
		}
		else if ((i == N) && (j - k == 1)) {
			break;
		}

	}
	printf("%d", sum);
	free(arr1);
	free(arr2);
	return 0;
}