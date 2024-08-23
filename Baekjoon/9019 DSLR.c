#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100000

char v[10000], back2[10000];
int start, end, length, back1[10000];

typedef struct _d {
	int reg, num, src;
	char dslr;
}Data;

typedef struct _q {
	int f, r;
	Data data[MAX];
}Queue;

void Initqueue(Queue* p) {
	p->f = 0;
	p->r = 0;
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

int D(int n) {
	int ret = 2 * n;
	if (ret > 9999) {
		return ret % 10000;
	}
	else {
		return ret;
	}
}
int S(int n) {
	int ret = n;
	if (ret == 0) {
		return 9999;
	}
	else {
		return ret - 1;
	}
}
int L(int n) {
	int d1, d2, d3, d4, temp, ret;
	d1 = n / 1000;
	d2 = (n - d1 * 1000) / 100;
	d3 = (n - d1 * 1000 - d2 * 100) / 10;
	d4 = (n - d1 * 1000 - d2 * 100 - d3 * 10);
	temp = d1;
	d1 = d2;
	d2 = d3;
	d3 = d4;
	d4 = temp;
	ret = d1 * 1000 + d2 * 100 + d3 * 10 + d4;
	return ret;
}
int R(int n) {
	int d1, d2, d3, d4, temp, ret;
	d1 = n / 1000;
	d2 = (n - d1 * 1000) / 100;
	d3 = (n - d1 * 1000 - d2 * 100) / 10;
	d4 = (n - d1 * 1000 - d2 * 100 - d3 * 10);
	temp = d4;
	d4 = d3;
	d3 = d2;
	d2 = d1;
	d1 = temp;
	ret = d1 * 1000 + d2 * 100 + d3 * 10 + d4;
	return ret;
}

int BFS() {
	int reg, num, d, s, l, r;
	Data data;
	Queue q;
	data.reg = start;
	data.num = 0;
	Initqueue(&q);
	Enqueue(&q, data);

	while (q.f != q.r) {
		data = Peek(&q);
		Dequeue(&q);
		reg = data.reg;
		num = data.num;

		if (v[reg] == 1) {
			continue;
		}
		else if (v[reg] == 0) {
			v[reg] = 1;
			back1[reg] = data.src;
			back2[reg] = data.dslr;
		}

		d = D(reg);
		s = S(reg);
		l = L(reg);
		r = R(reg);
		if (d == end) {
			length = num + 1;
			back1[d] = reg;
			back2[d] = 'D';
			return d;
		}
		else {
			if (v[d] == 0) {
				data.reg = d;
				data.num = num + 1;
				data.src = reg;
				data.dslr = 'D';
				Enqueue(&q, data);
			}
		}
		if (s == end) {
			length = num + 1;
			back1[s] = reg;
			back2[s] = 'S';
			return s;
		}
		else {
			if (v[s] == 0) {
				data.reg = s;
				data.num = num + 1;
				data.src = reg;
				data.dslr = 'S';
				Enqueue(&q, data);
			}
		}
		if (l == end) {
			length = num + 1;
			back1[l] = reg;
			back2[l] = 'L';
			return l;
		}
		else {
			if (v[l] == 0) {
				data.reg = l;
				data.num = num + 1;
				data.src = reg;
				data.dslr = 'L';
				Enqueue(&q, data);
			}
		}
		if (r == end) {
			length = num + 1;
			back1[r] = reg;
			back2[r] = 'R';
			return r;
		}
		else {
			if (v[r] == 0) {
				data.reg = r;
				data.num = num + 1;
				data.src = reg;
				data.dslr = 'R';
				Enqueue(&q, data);
			}
		}
	}
}

int main() {
	char** output;
	int T, ret;
	scanf("%d", &T);
	output = (char**)malloc(sizeof(char*) * T);
	for (int i = 0; i < T; i++) {
		scanf("%d %d", &start, &end);
		memset(v, 0, sizeof(char) * 10000);
		memset(back1, 0, sizeof(int) * 10000);
		memset(back2, 0, sizeof(char) * 10000);
		ret = BFS();
		output[i] = (char*)malloc(sizeof(char) * (length + 1));
		for (int j = length - 1; j >= 0; j--) {
			output[i][j] = back2[ret];
			ret = back1[ret];
		}
		output[i][length] = '\0';
	}

	for (int i = 0; i < T; i++) {
		printf("%s\n", output[i]);
		free(output[i]);
	}
	free(output);
	return 0;
}