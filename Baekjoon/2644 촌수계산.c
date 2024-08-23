#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct _d {
	int v;
	int num;
}Data;

typedef struct _q {
	int f, r;
	Data arr[MAX];
}Queue;

typedef struct _n {
	int v;
	struct _n* next;
}Node;

typedef struct _g {
	int num;
	Node** heads;
}Graph;

char visited[100];
int start, end, ret = -1;
Graph g;

void InitQueue(Queue* p);
void Enqueue(Queue* p, Data item);
Data Peek(Queue* p);
void Dequeue(Queue* p);

void InitGraph(Graph* p, int num);
void DestroyGraph(Graph* p);
void AddEdge(Graph* p, int s, int e);

void BFS();

int main() {
	int n, m, src, dst;
	scanf("%d", &n);
	InitGraph(&g, n);
	scanf("%d %d", &start, &end);
	start--;
	end--;
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &src, &dst);
		AddEdge(&g, src - 1, dst - 1);
	}
	BFS();
	DestroyGraph(&g);
	printf("%d", ret);
	return 0;
}

void InitQueue(Queue* p) {
	p->f = 0;
	p->r = 0;
}
void Enqueue(Queue* p, Data item) {
	if (p->f == (p->r + 1) % MAX) {
		exit(1);
	}
	p->arr[p->r] = item;
	(p->r)++;
}
Data Peek(Queue* p) {
	if (p->f == p->r) {
		exit(1);
	}
	return p->arr[p->f];
}
void Dequeue(Queue* p) {
	if (p->f == p->r) {
		exit(1);
	}
	(p->f)++;
}

void InitGraph(Graph* p, int num) {
	p->num = num;
	p->heads = (Node**)malloc(sizeof(Node*) * num);
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
void AddEdge(Graph* p, int s, int e) {
	Node* newnode1, * newnode2, * cur;

	newnode1 = (Node*)malloc(sizeof(Node));
	newnode1->v = s;
	newnode1->next = NULL;
	cur = p->heads[e];
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = newnode1;

	newnode2 = (Node*)malloc(sizeof(Node));
	newnode2->v = e;
	newnode2->next = NULL;
	cur = p->heads[s];
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = newnode2;
}

void BFS() {
	Data data;
	Queue q;
	Node* cur;
	int v, num;
	data.v = start;
	data.num = 0;
	InitQueue(&q);
	Enqueue(&q, data);
	while (q.f != q.r) {
		data = Peek(&q);
		Dequeue(&q);
		v = data.v;
		num = data.num;
		if (visited[v] == 1) {
			continue;
		}
		else {
			visited[v] = 1;
		}

		cur = g.heads[v]->next;
		while (cur != NULL) {
			if (visited[cur->v] == 0) {
				if (cur->v == end) {
					ret = num + 1;
					break;
				}
				data.v = cur->v;
				data.num = num + 1;
				Enqueue(&q, data);
			}
			cur = cur->next;
		}
	}
}