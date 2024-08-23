#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a, b) (((a) > (b)) ? (a) : (b))

typedef struct _data {
	int v;
	int c;
}Data;

int* arr;
Data* x1;
Data* x2;
int* y;

void Function(int n) {
	if ((x1[n].v != -1) && (x2[n].v != -1) && (y[n] != -1)) {
		return;
	}
	else if (n == 1) {
		x1[1].c = 1;
		x1[1].v = arr[1];
		x2[1].c = 2;
		x2[1].v = -100;
		y[1] = 0;
	}
	else if (n == 2) {
		x1[2].c = 1;
		x1[2].v = arr[2];
		x2[2].c = 2;
		x2[2].v = arr[1] + arr[2];
		y[2] = arr[1];
	}
	else {
		Function(n - 1);
		Function(n - 2);
		x1[n].c = 1;
		x2[n].c = 2;
		//x1
		if (max(max(x1[n - 2].v, x2[n - 2].v), max(y[n - 1], y[n - 2])) == x1[n - 2].v) {
			x1[n].v = x1[n - 2].v + arr[n];
		}
		else if (max(max(x1[n - 2].v, x2[n - 2].v), max(y[n - 1], y[n - 2])) == x2[n - 2].v) {
			x1[n].v = x2[n - 2].v + arr[n];
		}
		else if (max(max(x1[n - 2].v, x2[n - 2].v), max(y[n - 1], y[n - 2])) == y[n - 1]) {
			x1[n].v = y[n - 1] + arr[n];
		}
		else if (max(max(x1[n - 2].v, x2[n - 2].v), max(y[n - 1], y[n - 2])) == y[n - 2]) {
			x1[n].v = y[n - 2] + arr[n];
		}
		//x2:x1(n-1), y(n-2)
		if (x1[n - 1].v >= y[n - 2] + arr[n - 1]) {
			x2[n].v = x1[n - 1].v + arr[n];
		}
		else {
			x2[n].v = y[n - 2] + arr[n - 1] + arr[n];
		}
		//y
		y[n] = max(max(max(x1[n - 1].v, x1[n - 2].v), max(x2[n - 1].v, x2[n - 2].v)), max(y[n - 1], y[n - 2]));
	}
}

int main() {
	int n;
	scanf("%d", &n);
	arr = (int*)malloc(sizeof(int) * (n+1));
	x1 = (Data*)malloc(sizeof(Data) * (n+1));
	x2 = (Data*)malloc(sizeof(Data) * (n + 1));
	y = (int*)malloc(sizeof(int) * (n+1));
	
	for (int i = 1; i <= n; i++) {
		scanf("%d", arr + i);
		x1[i].v = -1;
		x2[i].v = -1;
		y[i] = -1;
	}

	Function(n);
	printf("%d", max(max(x1[n].v, x2[n].v), y[n]));

	free(arr);
	free(x1);
	free(x2);
	free(y);
	return 0;
}