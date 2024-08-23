#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define MAX 1000

int R, C;
char arr[20][21];
char v[20][20];
char alpha[400];
int value[20][20];

typedef struct _d {
	int r, c;
	int num;
}Data;

typedef struct _q {
	int f, r;
	Data* data;
}Queue;

void Initqueue(Queue* p) {
	p->f = 0;
	p->r = 0;
	p->data = (Data*)malloc(sizeof(Data) * MAX);
}
void Enqueue(Queue* p, Data item) {
	if (p->f == (p->r + 1) % MAX) {
		exit(1);
	}
	p->data[p->r] = item;
	(p->r)++;
}
Data Peek(Queue* p) {
	if (p->f == p->r) {
		exit(1);
	}
	return p->data[p->f];
}
void Dequeue(Queue* p) {
	if (p->f == p->r) {
		exit(1);
	}
	(p->f)++;
}

int BFS() {
	Queue q;
	Data data;
	int i, r, c, num, m = 0;
	Initqueue(&q);
	data.r = 0;
	data.c = 0;
	data.num = 1;
	value[0][0] = 1;
	alpha[0] = arr[0][0];
	Enqueue(&q, data);

	while (q.f != q.r) {
		data = Peek(&q);
		Dequeue(&q);
		r = data.r;
		c = data.c;
		num = data.num;

		if (v[r][c] == 1) {
			continue;
		}
		else {
			v[r][c] = 1;
		}

		//R 증가
		if (r + 1 >= 0 && r + 1 <= R - 1) {
			if (v[r + 1][c] == 0) {
				data.r = r + 1;
				data.c = c;
				data.num = num + 1;
				for (i = 0; i < num; i++) {
					if (alpha[i] == arr[r + 1][c]) {
						m = max(m, num);
						break;
					}
				}
				if (i == num) {
					if (value[r + 1][c] <= num + 1) {
						value[r + 1][c] = num + 1;
						alpha[num] = arr[r + 1][c];
						Enqueue(&q, data);
					}
				}
			}
		}
		//R 감소
		if (r - 1 >= 0 && r - 1 <= R - 1) {
			if (v[r - 1][c] == 0) {
				data.r = r - 1;
				data.c = c;
				data.num = num + 1;
				for (i = 0; i < num; i++) {
					if (alpha[i] == arr[r - 1][c]) {
						m = max(m, num);
						break;
					}
				}
				if (i == num) {
					if (value[r - 1][c] <= num + 1) {
						value[r - 1][c] = num + 1;
						alpha[num] = arr[r - 1][c];
						Enqueue(&q, data);
					}
				}
			}
		}
		//C 증가
		if (c + 1 >= 0 && c + 1 <= C - 1) {
			if (v[r][c + 1] == 0) {
				data.r = r;
				data.c = c + 1;
				data.num = num + 1;
				for (i = 0; i < num; i++) {
					if (alpha[i] == arr[r][c + 1]) {
						m = max(m, num);
						break;
					}
				}
				if (i == num) {
					if (value[r][c + 1] <= num + 1) {
						value[r][c + 1] = num + 1;
						alpha[num] = arr[r][c + 1];
						Enqueue(&q, data);
					}
				}
			}
		}
		//C 감소
		if (c - 1 >= 0 && c - 1 <= C - 1) {
			if (v[r][c - 1] == 0) {
				data.r = r;
				data.c = c - 1;
				data.num = num + 1;
				for (i = 0; i < num; i++) {
					if (alpha[i] == arr[r][c - 1]) {
						m = max(m, num);
						break;
					}
				}
				if (i == num) {
					if (value[r][c - 1] <= num + 1) {
						value[r][c - 1] = num + 1;
						alpha[num] = arr[r][c - 1];
						Enqueue(&q, data);
					}
				}
			}
		}
		v[r][c] = 0;
	}
	return m;
}

int main() {
	int ret;
	scanf("%d %d", &R, &C);
	while (getchar() != '\n');
	for (int i = 0; i < R; i++) {
		fgets(arr[i], C + 1, stdin);
		while (getchar() != '\n');
	}

	ret = BFS();
	printf("%d", ret);
	return 0;
}