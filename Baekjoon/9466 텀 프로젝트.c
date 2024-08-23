#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char v[100001];
int arr[100001], number[100001], ret;

void DFS(int idx, int num) {
	int next, i;
	if (v[idx] == 1) {
		return;
	}
	else if (v[idx] == 0) {
		v[idx] = 1;
		number[num] = idx;
	}
	
	next = arr[idx];
	if (v[next] == 0) {
		DFS(next, num + 1);
	}
	else {
		for (i = 1; i <= num; i++) {
			if (next == number[i]) {
				ret += num - i + 1;
				return;
			}
		}
	}
}

int main() {
	int T, n;
	int* output;
	scanf("%d", &T);
	output = (int*)malloc(sizeof(int) * T);
	for (int i = 0; i < T; i++) {
		scanf("%d", &n);
		for (int j = 1; j <= n; j++) {
			scanf("%d", &arr[j]);
		}

		memset(v, 0, sizeof(char) * sizeof(v));
		ret = 0;
		for (int j = 1; j <= n; j++) {
			if (v[j] == 0) {
				DFS(j, 1);
			}
		}
		output[i] = n - ret;
	}
	
	for (int i = 0; i < T; i++) {
		printf("%d\n", output[i]);
	}
	free(output);
	return 0;
}