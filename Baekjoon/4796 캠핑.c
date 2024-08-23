#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
	int L, P, V, count;
	int* arr = (int*)malloc(sizeof(int));
	count = 0;
	while (1) {
		scanf("%d %d %d", &L, &P, &V);
		if ((L == 0) && (P == 0) && (V == 0)) {
			break;
		}
		if (count > 0){
			arr = (int*)realloc(arr, sizeof(int) * (count + 1));
		}
		arr[count] = L * (V / P);
		if (V % P > L) {
			arr[count] += L;
		}
		else {
			arr[count] += V % P;
		}
		count++;
	}
	
	for (int i = 0; i < count; i++) {
		printf("Case %d: %d\n", i + 1, arr[i]);
	}
	
	free(arr);
	return 0;
}