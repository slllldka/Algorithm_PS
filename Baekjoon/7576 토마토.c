#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define MAX 2000000
int* arr;
int M, N;

typedef struct _data {
	int node;
	int day;
}Data;

typedef struct _queue {
	Data data[MAX];
	int f, r;
}Queue;

typedef struct _node {
	int data;
	struct _node* next;
}Node;

typedef struct _graph {
	int num;
	Node** heads;
}Graph;

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

void CreateGraph(Graph* p, int num) {
	p->heads = (Node**)malloc(sizeof(Node*) * num);
	p->num = num;
	for (int i = 0; i < num; i++) {
		p->heads[i] = (Node*)malloc(sizeof(Node));
		p->heads[i]->next = NULL;
	}
}
void DestroyGraph(Graph* p) {
	Node* cur, * temp;
	for (int i = 0; i < p->num; i++) {
		cur = p->heads[i];
		while (cur != NULL) {
			temp = cur;
			cur = cur->next;
			free(temp);
		}
	}
	free(p->heads);
}
void AddEdge(Graph* p, int x, int y) {
	Node* newnode1, * newnode2, * cur;
	newnode1 = (Node*)malloc(sizeof(Node));
	newnode2 = (Node*)malloc(sizeof(Node));

	newnode1->data = y;
	newnode1->next = NULL;
	cur = p->heads[x];
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = newnode1;

	newnode2->data = x;
	newnode2->next = NULL;
	cur = p->heads[y];
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = newnode2;
}

void BFS(Graph* p) {
	Queue q;
	int* v = (int*)malloc(sizeof(int) * p->num);
	Data data;
	int node, day, m = 0;
	Node* cur;

	memset(v, 0, sizeof(int) * p->num);
	Initqueue(&q);

	for (int i = 0; i < M * N; i++) {
		if (arr[i] == 1) {
			data.day = 0;
			data.node = i;
			Enqueue(&q, data);
		}
	}

	while (q.f != q.r) {
		data = Peek(&q);
		node = data.node;
		day = data.day;
		Dequeue(&q);

		if (arr[node] == 0) {
			exit(1);
		}
		else if (v[node] == 1) {
			continue;
		}
		else {
			v[node] = 1;
			m = max(m, day);
			if (arr[node] == -1) {
				continue;
			}
		}

		cur = p->heads[node]->next;
		while (cur != NULL) {
			if (v[cur->data] == 0) {
				if (arr[cur->data] == -1) {
					data.node = cur->data;
					data.day = day;
					Enqueue(&q, data);
				}
				else if (arr[cur->data] == 0) {
					arr[cur->data] = 1;
					data.node = cur->data;
					data.day = day + 1;
					Enqueue(&q, data);
				}
			}
			cur = cur->next;
		}
	}
	for (int i = 0; i < M * N; i++) {
		if (arr[i] == 0) {
			printf("-1");
			return;
		}
	}
	printf("%d", m);
}

int main() {
	Graph g;
	scanf("%d %d", &M, &N);
	arr = (int*)malloc(sizeof(int) * M * N);
	for (int i = 0; i < M * N; i++) {
		scanf("%d", arr + i);
	}

	CreateGraph(&g, M * N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M - 1; j++) {
			AddEdge(&g, M * i + j, M * i + j + 1);
		}
	}
	
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N - 1; j++) {
			AddEdge(&g, i + M * j, i + M * (j + 1));
		}
	}
	BFS(&g);
	DestroyGraph(&g);
	free(arr);
	return 0;
}