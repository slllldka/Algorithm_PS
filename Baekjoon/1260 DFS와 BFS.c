#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20000

typedef struct _stack {
	int data[MAX];
	int top;
}Stack;

typedef struct _queue {
	int data[MAX];
	int s, e;
}Queue;

typedef struct _node {
	int item;
	struct _node* next;
}Node;

typedef struct _graph {
	int num;
	Node** heads;
}Graph;

typedef struct _pq {
	int num;
	int heap[MAX + 1];
}PQ;

void Initstack(Stack* p) {
	p->top = -1;
}

void Push(Stack* p, int item) {
	if (p->top == MAX - 1) {
		exit(1);
	}
	(p->top)++;
	p->data[p->top] = item;
}

void Pop(Stack* p) {
	if (p->top == -1) {
		exit(1);
	}
	(p->top)--;
}

int SPeek(Stack* p) {
	if (p->top == -1) {
		exit(1);
	}
	return p->data[p->top];
}

void Initqueue(Queue* p) {
	p->s = 0;
	p->e = 0;
}

void Enqueue(Queue* p, int item) {
	if (p->s == (p->e + 1) % MAX) {
		exit(1);
	}
	p->data[p->e] = item;
	p->e = (p->e + 1) % MAX;
}

void Dequeue(Queue* p) {
	if (p->s == p->e) {
		exit(1);
	}
	p->s = (p->s + 1) % MAX;
}

int QPeek(Queue* p) {
	if (p->s == p->e) {
		exit(1);
	}
	return p->data[p->s];
}

void Initheap(PQ* p) {
	p->num = 0;
}

int HPC(PQ* p, int idx) {
	if (p->num < 2 * idx) {
		return 0;
	}
	else if (p->num == 2 * idx) {
		return 2 * idx;
	}
	else if (p->heap[2 * idx] >= p->heap[2 * idx + 1]) {
		return 2 * idx;
	}
	else if (p->heap[2 * idx] < p->heap[2 * idx + 1]) {
		return 2 * idx + 1;
	}
}

int LPC(PQ* p, int idx) {
	if (p->num < 2 * idx) {
		return 0;
	}
	else if (p->num == 2 * idx) {
		return 2 * idx;
	}
	else if (p->heap[2 * idx] >= p->heap[2 * idx + 1]) {
		return 2 * idx + 1;
	}
	else if (p->heap[2 * idx] < p->heap[2 * idx + 1]) {
		return 2 * idx;
	}
}

void MAXInsert(PQ* p, int data) {
	if (p->num == MAX) {
		exit(1);
	}
	(p->num)++;
	int idx = p->num;
	while (idx > 1) {
		if (p->heap[idx / 2] < data) {
			p->heap[idx] = p->heap[idx / 2];
			idx /= 2;
		}
		else {
			break;
		}
	}
	p->heap[idx] = data;
}

void MINInsert(PQ* p, int data) {
	if (p->num == MAX) {
		exit(1);
	}
	(p->num)++;
	int idx = p->num;
	while (idx > 1) {
		if (p->heap[idx / 2] > data) {
			p->heap[idx] = p->heap[idx / 2];
			idx /= 2;
		}
		else {
			break;
		}
	}
	p->heap[idx] = data;
}

int MAXDelete(PQ* p) {
	if (p->num == 0) {
		exit(1);
	}
	int ret = p->heap[1];
	int last = p->heap[p->num];
	p->num--;
	int idx = 1;
	int hpc;
	while (1) {
		hpc = HPC(p, idx);
		if (hpc == 0) {
			break;
		}
		else if (p->heap[hpc] > last) {
			p->heap[idx] = p->heap[hpc];
			idx = hpc;
		}
		else {
			break;
		}
	}
	p->heap[idx] = last;
	return ret;
}

int MINDelete(PQ* p) {
	if (p->num == 0) {
		exit(1);
	}
	int ret = p->heap[1];
	int last = p->heap[p->num];
	p->num--;
	int idx = 1;
	int lpc;
	while (1) {
		lpc = LPC(p, idx);
		if (lpc == 0) {
			break;
		}
		else if (p->heap[lpc] < last) {
			p->heap[idx] = p->heap[lpc];
			idx = lpc;
		}
		else {
			break;
		}
	}
	p->heap[idx] = last;
	return ret;
}

void CreateGraph(Graph* p, int num) {
	p->num = num;
	p->heads = (Node**)malloc(sizeof(Node*) * num);
	for (int i = 0; i < num; i++) {
		p->heads[i] = (Node*)malloc(sizeof(Node));
		p->heads[i]->next = NULL;
	}
}
void DestroyGraph(Graph* p) {
	if (p->num == 0) {
		exit(1);
	}
	Node* cur;
	Node* temp;
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
	Node* newnode1 = (Node*)malloc(sizeof(Node));
	Node* newnode2 = (Node*)malloc(sizeof(Node));
	Node* cur = p->heads[s];
	newnode1->item = e;
	newnode1->next = NULL;
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = newnode1;

	cur = p->heads[e];
	newnode2->item = s;
	newnode2->next = NULL;
	while (cur->next != NULL) {
		cur = cur->next;
	}
	cur->next = newnode2;
}

void BFS(Graph* p, int V) {
	Queue q;
	PQ pq;
	char* v = (char*)malloc(sizeof(char) * p->num);
	int m;
	for (int i = 0; i < p->num; i++) {
		v[i] = '0';
	}
	Initqueue(&q);
	Enqueue(&q, V);

	while (q.s != q.e) {
		Node* cur;
		int node = QPeek(&q);
		Dequeue(&q);

		if (v[node] == '1') {
			continue;
		}
		else {
			v[node] = '1';
			printf("%d ", node + 1);
		}

		Initheap(&pq);
		cur = p->heads[node]->next;
		while (cur != NULL) {
			if (v[cur->item] == '0') {
				MINInsert(&pq, cur->item);
			}
			cur = cur->next;
		}
		while (pq.num > 0) {
			m = MINDelete(&pq);
			Enqueue(&q, m);
		}
	}
}

void DFS(Graph* p, int V) {
	Stack s;
	PQ pq;
	char* v = (char*)malloc(sizeof(char) * p->num);
	int m;
	for (int i = 0; i < p->num; i++) {
		v[i] = '0';
	}
	Initstack(&s);
	Push(&s, V);
	while (s.top != -1) {
		Node* cur;
		int node = SPeek(&s);
		Pop(&s);

		if (v[node] == '1') {
			continue;
		}
		else {
			v[node] = '1';
			printf("%d ", node + 1);
		}
		
		Initheap(&pq);
		cur = p->heads[node]->next;
		while (cur != NULL) {
			if (v[cur->item] == '0') {
				MAXInsert(&pq, cur->item);
			}
			cur = cur->next;
		}
		while (pq.num > 0) {
			m = MAXDelete(&pq);
			Push(&s, m);
		}
	}
}

int main() {
	Graph g;
	int N;
	int M;
	int V;
	int s, e;
	scanf("%d %d %d", &N, &M, &V);
	CreateGraph(&g, N);
	V--;
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &s, &e);
		s--;
		e--;
		AddEdge(&g, s, e);
	}
	DFS(&g, V);
	puts("");
	BFS(&g, V);
	DestroyGraph(&g);
	return 0;
}