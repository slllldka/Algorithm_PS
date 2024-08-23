#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _d {
	int r, c;
}Data;

typedef struct _dice {
	int top, bottom, right, left, front, back;
}Dice;

int arr[20][20], move[1000];
int N, M, K, set = 0;
Data pos;
Dice dice;

void East() {
	pos.c++;
	if ((pos.r < 0) || (pos.r >= N) || (pos.c < 0) || (pos.c >= M)) {
		pos.c--;
		set = -1;
		return;
	}
	int temp = dice.top;
	dice.top = dice.left;
	dice.left = dice.bottom;
	dice.bottom = dice.right;
	dice.right = temp;
}
void West() {
	pos.c--;
	if ((pos.r < 0) || (pos.r >= N) || (pos.c < 0) || (pos.c >= M)) {
		pos.c++;
		set = -1;
		return;
	}
	int temp = dice.top;
	dice.top = dice.right;
	dice.right = dice.bottom;
	dice.bottom = dice.left;
	dice.left = temp;
}
void South() {
	pos.r++;
	if ((pos.r < 0) || (pos.r >= N) || (pos.c < 0) || (pos.c >= M)) {
		pos.r--;
		set = -1;
		return;
	}
	int temp = dice.top;
	dice.top = dice.back;
	dice.back = dice.bottom;
	dice.bottom = dice.front;
	dice.front = temp;

}
void North() {
	pos.r--;
	if ((pos.r < 0) || (pos.r >= N) || (pos.c < 0) || (pos.c >= M)) {
		pos.r++;
		set = -1;
		return;
	}
	int temp = dice.top;
	dice.top = dice.front;
	dice.front = dice.bottom;
	dice.bottom = dice.back;
	dice.back = temp;
}

int main() {
	int row = 0, column = 0;
	dice.top = 0;
	dice.bottom = 0;
	dice.right = 0;
	dice.left = 0;
	dice.front = 0;
	dice.back = 0;
	scanf("%d %d %d %d %d", &N, &M, &pos.r, &pos.c, &K);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	for (int i = 0; i < K; i++) {
		scanf("%d", move + i);
	}

	for (int i = 0; i < K; i++) {
		set = 0;
		if (move[i] == 1) {
			East();
		}
		else if (move[i] == 2) {
			West();
		}
		else if (move[i] == 3) {
			North();
		}
		else if (move[i] == 4) {
			South();
		}

		if (set == -1) {
			continue;
		}

		if (arr[pos.r][pos.c] == 0) {
			arr[pos.r][pos.c] = dice.bottom;
		}
		else {
			dice.bottom = arr[pos.r][pos.c];
			arr[pos.r][pos.c] = 0;
		}
		printf("%d\n", dice.top);
	}
}