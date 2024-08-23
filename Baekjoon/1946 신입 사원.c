#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct _rank {
	int doc;
	int iv;
}Rank;

void merge(Rank arr[], int s, int m, int e) {
	Rank* arr2 = (Rank*)malloc(sizeof(Rank) * (e - s + 1));
	int i = s;
	int j = m + 1;
	int k = 0;

	while (i <= m && j <= e) {
		if ((arr[i].doc < arr[j].doc)) {
			arr2[k] = arr[i];
			i++;
			k++;
		}
		else {
			arr2[k] = arr[j];
			j++;
			k++;
		}
	}

	while (i <= m) {
		arr2[k] = arr[i];
		i++;
		k++;
	}
	while (j <= e) {
		arr2[k] = arr[j];
		j++;
		k++;
	}
	k--;

	while (k >= 0) {
		arr[s + k] = arr2[k];
		k--;
	}
	free(arr2);
}
void mergesort(Rank arr[], int s, int e) {
	if (s < e) {
		int m = (s + e) / 2;
		mergesort(arr, s, m);
		mergesort(arr, m + 1, e);
		merge(arr, s, m, e);
	}
	else
		return;
}

int main() {
	int T;
	int N;
	int k;
	int count;
	int iv;
	scanf("%d", &T);
	Rank** Tptr = (Rank**)malloc(sizeof(Rank*) * T);
	int* num = (int*)malloc(sizeof(int) * T);
	for (int i = 0; i < T; i++) {
		scanf("%d", &N);
		num[i] = N;
		Tptr[i] = (Rank*)malloc(sizeof(Rank) * N);
		for (int j = 0; j < N; j++) {
			scanf("%d %d", &Tptr[i][j].doc, &Tptr[i][j].iv);
		}
		mergesort(Tptr[i], 0, num[i] - 1);
	}

	for (int i = 0; i < T; i++) {
		count = 1;
		iv = Tptr[i][0].iv;
		for (int j = 1; j < num[i]; j++) {
			if (Tptr[i][j].iv < iv) {
				count++;
				iv = Tptr[i][j].iv;
			}
		}
		printf("%d\n", count);
	}

	for (int i = 0; i < T; i++) {
		free(Tptr[i]);
	}
	free(Rank);
	free(num);

	return 0;
}