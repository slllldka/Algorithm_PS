#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct _time {
	int start;
	int end;
}Time;

void merge(Time arr[], int s, int m, int e) {
	Time* arr2 = (Time*)malloc(sizeof(Time) * (e - s + 1));
	int i = s;
	int j = m + 1;
	int k = 0;

	while (i <= m && j <= e) {
		if ((arr[i].end < arr[j].end) || ((arr[i].end == arr[j].end) && (arr[i].start <= arr[j].start))) {
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
void mergesort(Time arr[], int s, int e) {
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
	int n;
	int endtime = 0;
	int count = 0;
	int c;
	int i;
	scanf("%d", &n);

	Time* tptr;
	tptr = (Time*)malloc(sizeof(Time) * n);

	for (int j = 0; j < n; j++) {
		scanf("%d %d", &(tptr[j].start), &(tptr[j].end));
	}
	
	mergesort(tptr, 0, n - 1);
	i = 0;
	while (1) {
		c = -1;
		for (int j = i; j < n; j++) {
			//시작시간 >= endtime end값 최소
			if (tptr[j].start >= endtime) {
				c = j;
				j++;
				i = j;
				break;
			}
		}
		if (c == -1) {
			break;
		}
		else {
			endtime = tptr[c].end;
			count++;
		}
	}
	
	printf("%d", count);
}