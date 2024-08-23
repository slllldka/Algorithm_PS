#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
	int n;
	int five = -1;
	int three;
	scanf("%d", &n);

	for (int i = 0;; i++) {
		if ((5 * i <= n) && ((n - 5 * i) % 3 == 0)) {
			five = i;
		}
		else if (5 * i > n) {
			break;
		}
	}
	if (five != -1) {
		three = (n - five * 5) / 3;
		printf("%d", five + three);
	}
	else {
		printf("-1");
	}
	return 0;
}