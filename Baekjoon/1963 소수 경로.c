#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 9999

char visited[10000], Isprime[10000];
int target;

typedef struct _d {
	int prime, num;
}Data;

typedef struct _q {
	int f, r;
	Data data[MAX];
}Queue;

void Initqueue(Queue* p) {
	p->f = p->r = 0;
}
void Enqueue(Queue* p, Data item) {
	if (p->f == (p->r + 1) % MAX) {
		exit(1);
	}
	p->data[p->r] = item;
	p->r = (p->r + 1) % MAX;
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
	p->f = (p->f + 1) % MAX;
}

int CheckPrime(int n) {
	if (Isprime[n] == 1) {
		return 0;
	}
	else if (Isprime[n] == 2) {
		return 1;
	}
	else {
		for (int i = 2; i <= n / 2; i++) {
			if (n % i == 0) {
				Isprime[n] = 1;
				return 0;
			}
		}
		Isprime[n] = 2;
		return 1;
	}
}

int ChangeNumber(int n, int idx, int ch) {
	int one, two, three, four, ret;
	one = n % 10;
	two = (n % 100) / 10;
	three = (n % 1000) / 100;
	four = n / 1000;
	if (idx == 1) {
		ret = n - one + ch;
		return ret;
	}
	else if (idx == 2) {
		ret = n - two * 10 + ch * 10;
		return ret;
	}
	else if (idx == 3) {
		ret = n - three * 100 + ch * 100;
		return ret;
	}
	else if (idx == 4) {
		ret = n - four * 1000 + ch * 1000;
		return ret;
	}
}

int BFS(int start) {
	int prime, num;
	Queue q;
	Data data;
	Initqueue(&q);
	data.prime = start;
	data.num = 0;
	Enqueue(&q, data);
	memset(visited, 0, sizeof(visited));

	while (q.f != q.r) {
		data = Peek(&q);
		Dequeue(&q);
		prime = data.prime;
		num = data.num;
		data.num++;

		if (visited[prime] == 1) {
			continue;
		}

		if (prime == target) {
			return num;
		}

		visited[prime] = 1;

		for (int i = 0; i <= 9; i++) {
			if (i > 0) {
				data.prime = ChangeNumber(prime, 4, i);
				if (CheckPrime(data.prime) == 1) {
					if (visited[data.prime] == 0) {
						Enqueue(&q, data);
					}
				}
			}
			data.prime = ChangeNumber(prime, 3, i);
			if (CheckPrime(data.prime) == 1) {
				if (visited[data.prime] == 0) {
					Enqueue(&q, data);
				}
			}
			data.prime = ChangeNumber(prime, 2, i);
			if (CheckPrime(data.prime) == 1) {
				if (visited[data.prime] == 0) {
					Enqueue(&q, data);
				}
			}
			data.prime = ChangeNumber(prime, 1, i);
			if (CheckPrime(data.prime) == 1) {
				if (visited[data.prime] == 0) {
					Enqueue(&q, data);
				}
			}
		}
	}
	return -1;
}

int main() {
	int T, start, * output;
	scanf("%d", &T);
	output = (int*)malloc(sizeof(int) * T);
	for (int i = 0; i < T; i++) {
		scanf("%d %d", &start, &target);
		output[i] = BFS(start);
	}

	for (int i = 0; i < T; i++) {
		if (output[i] == -1) {
			printf("Impossible\n");
		}
		else {
			printf("%d\n", output[i]);
		}
	}
	free(output);
	return 0;
}