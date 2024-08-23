#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _jewel {
	int M;
	int V;
}Jewel;

typedef struct _pqueue {
	Jewel* MAXHEAP;
	int num;
}PQueue;
void Initialize(PQueue* p) {
	p->MAXHEAP = (Jewel*)malloc(sizeof(Jewel) * (300001));
	p->num = 0;
}
int HPC(PQueue* p, int parent) {
	if (p->num < parent * 2) {
		return 0;
	}
	else if (p->num < parent * 2 + 1) {
		return parent * 2;
	}
	else if (p->MAXHEAP[parent * 2].V >= p->MAXHEAP[parent * 2 + 1].V) {
		return parent * 2;
	}
	else {
		return parent * 2 + 1;
	}
}
void Insert(PQueue* p, Jewel item) {
	if (p->num == 300000) {
		exit(1);
	}
	(p->num)++;
	int idx = p->num;
	while (idx > 1) {
		if (p->MAXHEAP[idx / 2].V < item.V) {
			p->MAXHEAP[idx] = p->MAXHEAP[idx / 2];
			idx /= 2;
		}
		else {
			break;
		}
	}
	p->MAXHEAP[idx] = item;
}
int Delete(PQueue* p) {
	if (p->num == 0) {
		exit(1);
	}
	int ret = p->MAXHEAP[1].V;
	int idx = 1;
	Jewel last = p->MAXHEAP[p->num];
	int hpc;
	while (1) {
		hpc = HPC(p, idx);
		if (hpc == 0) {
			break;
		}
		else if (p->MAXHEAP[hpc].V > last.V) {
			p->MAXHEAP[idx] = p->MAXHEAP[hpc];
			idx = hpc;
		}
		else {
			break;
		}
	}
	p->MAXHEAP[idx] = last;
	(p->num)--;
	return ret;
}

void merge(Jewel arr1[], int s, int m, int e) {
	Jewel* arr2 = (Jewel*)malloc(sizeof(Jewel) * (e - s + 1));
	int i = s;
	int j = m + 1;
	int k = 0;
	while ((i <= m) && (j <= e)) {
		if (arr1[i].M <= arr1[j].M) {
			arr2[k] = arr1[i];
			i++;
			k++;
		}
		else if (arr1[j].M < arr1[i].M) {
			arr2[k] = arr1[j];
			j++;
			k++;
		}
	}
	if (i == m + 1) {
		for (; j <= e; j++) {
			arr2[k] = arr1[j];
			k++;
		}
	}
	else if (j == e + 1) {
		for (; i <= m; i++) {
			arr2[k] = arr1[i];
			k++;
		}
	}
	
	k--;
	for (; k >= 0; k--) {
		arr1[k + s] = arr2[k];
	}
	free(arr2);
}
void mergesort(Jewel arr1[], int s, int e) {
	int m;
	if (s < e) {
		m = (s + e) / 2;
		mergesort(arr1, s, m);
		mergesort(arr1, m + 1, e);
		merge(arr1, s, m, e);
	}
}
void merge1(int arr1[], int s, int m, int e) {
	int* arr2 = (int*)malloc(sizeof(int) * (e - s + 1));
	int i = s;
	int j = m + 1;
	int k = 0;
	while ((i <= m) && (j <= e)) {
		if (arr1[i] <= arr1[j]) {
			arr2[k] = arr1[i];
			i++;
			k++;
		}
		else if (arr1[j] < arr1[i]) {
			arr2[k] = arr1[j];
			j++;
			k++;
		}
	}
	if (i == m + 1) {
		for (; j <= e; j++) {
			arr2[k] = arr1[j];
			k++;
		}
	}
	else if (j == e + 1) {
		for (; i <= m; i++) {
			arr2[k] = arr1[i];
			k++;
		}
	}

	k--;
	for (; k >= 0; k--) {
		arr1[k + s] = arr2[k];
	}
	free(arr2);
}
void mergesort1(int arr1[], int s, int e) {
	int m;
	if (s < e) {
		m = (s + e) / 2;
		mergesort1(arr1, s, m);
		mergesort1(arr1, m + 1, e);
		merge1(arr1, s, m, e);
	}
}
int main() {
	long long sum;
	int N, K, num;
	int n;
	Jewel* MV;
	int* C;
	PQueue pqueue;
	scanf("%d %d", &N, &K);
	Initialize(&pqueue);

	MV = (Jewel*)malloc(sizeof(Jewel) * N);
	C = (int*)malloc(sizeof(int) * K);

	for (int i = 0; i < N; i++) {
		scanf("%d %d", &MV[i].M, &MV[i].V);
	}
	for (int i = 0; i < K; i++) {
		scanf("%d", C + i);
	}
	
	mergesort(MV, 0, N - 1);
	mergesort1(C, 0, K - 1);

	n = 0;
	sum = 0;
	num = 0;
	for (int i = 0; i < K; i++) {
		for (; n < N; n++) {
			if (MV[n].M <= C[i]) {
				Insert(&pqueue, MV[n]);
				num++;
			}
			else {
				break;
			}
		}
		if (num != 0) {
			sum += Delete(&pqueue);
			num--;
		}
	}

	printf("%lld", sum);
	
	free(MV);
	free(C);
	free(pqueue.MAXHEAP);
	return 0;
}