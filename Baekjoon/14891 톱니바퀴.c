#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

char one[9], two[9], three[9], four[9];
char r1, l2, r2, l3, r3, l4;
int s1, s2, s3, s4;
int K;

void Left(int s, int d) {
	if (s == 2) {
		if (r1 == l2) {
			return;
		}
		else {
			if (d == 1) {
				s1 = (s1 + 1) % 8;
			}
			else if (d == -1) {
				s1 = (s1 + 7) % 8;
			}
			return;
		}
	}
	else if (s == 3) {
		if (r2 == l3) {
			return;
		}
		else {
			if (d == 1) {
				s2 = (s2 + 1) % 8;
			}
			else if (d == -1) {
				s2 = (s2 + 7) % 8;
			}
			Left(s - 1, d * (-1));
		}
	}
	else if (s == 4) {
		if (r3 == l4) {
			return;
		}
		else {
			if (d == 1) {
				s3 = (s3 + 1) % 8;
			}
			else if (d == -1) {
				s3 = (s3 + 7) % 8;
			}
			Left(s - 1, d * (-1));
		}
	}
}
void Right(int s, int d) {
	if (s == 1) {
		if (r1 == l2) {
			return;
		}
		else {
			if (d == 1) {
				s2 = (s2 + 1) % 8;
			}
			else if (d == -1) {
				s2 = (s2 + 7) % 8;
			}
			Right(s + 1, d * (-1));
		}
	}
	else if (s == 2) {
		if (r2 == l3) {
			return;
		}
		else {
			if (d == 1) {
				s3 = (s3 + 1) % 8;
			}
			else if (d == -1) {
				s3 = (s3 + 7) % 8;
			}
			Right(s + 1, d * (-1));
		}
	}
	else if (s == 3) {
		if (r3 == l4) {
			return;	
		}
		else {
			if (d == 1) {
				s4 = (s4 + 1) % 8;
			}
			else if (d == -1) {
				s4 = (s4 + 7) % 8;
			}
			return;
		}
	}
}

int main() {
	int start, direction;
	fgets(one, 9, stdin);
	getchar();
	fgets(two, 9, stdin);
	getchar();
	fgets(three, 9, stdin);
	getchar();
	fgets(four, 9, stdin);
	getchar();

	scanf("%d", &K);

	s1 = 0;
	s2 = 0;
	s3 = 0;
	s4 = 0;
	for (int i = 0; i < K; i++) {
		r1 = one[(s1 + 2) % 8];
		l2 = two[(s2 + 6) % 8];
		r2 = two[(s2 + 2) % 8];
		l3 = three[(s3 + 6) % 8];
		r3 = three[(s3 + 2) % 8];
		l4 = four[(s4 + 6) % 8];

		scanf("%d %d", &start, &direction);

		if (start == 1) {
			if (direction == 1) {
				s1 = (s1 + 7) % 8;
			}
			else if (direction == -1) {
				s1 = (s1 + 1) % 8;
			}
		}
		else if (start == 2) {
			if (direction == 1) {
				s2 = (s2 + 7) % 8;
			}
			else if (direction == -1) {
				s2 = (s2 + 1) % 8;
			}
		}
		else if (start == 3) {
			if (direction == 1) {
				s3 = (s3 + 7) % 8;
			}
			else if (direction == -1) {
				s3 = (s3 + 1) % 8;
			}
		}
		else if (start == 4) {
			if (direction == 1) {
				s4 = (s4 + 7) % 8;
			}
			else if (direction == -1) {
				s4 = (s4 + 1) % 8;
			}
		}

		if (start > 1) {
			Left(start, direction);
		}
		if (start < 4) {
			Right(start, direction);
		}
	}

	printf("%d", one[s1] + two[s2] * 2 + three[s3] * 4 + four[s4] * 8 - '0' * 15);
	return 0;
}