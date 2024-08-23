#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a,b) (((a) > (b)) ? (a) : (b))
int arr[301];

typedef struct _score {
	int s;
	int c;
}Score;

Score x[301];
Score y[301];

void Function(int n) {
	if ((x[n].s != -1) && (y[n].s != -1)) {
		return;
	}
	else if (n == 1) {
		x[1].s = arr[1];
		x[1].c = 1;
		y[1].s = -2;
		y[1].c = -2;
	}
	else if (n == 2) {
		x[2].s = arr[1] + arr[2];
		x[2].c = 2;
		y[2].s = arr[2];
		y[2].c = 1;
	}
	else if (n > 2) {
		Function(n - 1);
		Function(n - 2);
		if (y[n - 1].s == -2) {
			x[n].s = x[n - 1].s + arr[n];
			x[n].c = (x[n - 1].c) + 1;
		}
		else if (x[n - 1].c == 2) {
			x[n].s = y[n - 1].s + arr[n];
			x[n].c = (y[n - 1].c) + 1;
		}
		else {
			if (x[n - 1].s > y[n - 1].s) {
				x[n].s = x[n - 1].s + arr[n];
				x[n].c = (x[n - 1].c) + 1;
			}
			else {
				x[n].s = y[n - 1].s + arr[n];
				x[n].c = (y[n - 1].c) + 1;
			}
		}

		if (y[n - 2].s == -2) {
			y[n].s = x[n - 2].s + arr[n];
			y[n].c = 1;
		}
		else {
			if (x[n - 2].s > y[n - 2].s) {
				y[n].s = x[n - 2].s + arr[n];
				y[n].c = 1;
			}
			else {
				y[n].s = y[n - 2].s + arr[n];
				y[n].c = 1;
			}
		}
	}

}

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		x[i].s = -1;
		y[i].s = -1;
	}
	Function(n);
	printf("%d", max(x[n].s, y[n].s));
	return 0;
}