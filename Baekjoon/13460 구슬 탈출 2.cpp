#include <iostream>

#define min(a, b) (((a) < (b)) ? (a) : (b))

using namespace std;

int M, N;
char map[10][11];
int position[10][10][10][10];
int Min = 11;

void Left(int, int, int, int, int);
void Right(int, int, int, int, int);
void Up(int, int, int, int, int);
void Down(int, int, int, int, int);
void DFS(int, int, int, int, int);

int main() {
	int R0 = -1;
	int R1 = -1;
	int B0 = -1;
	int B1 = -1;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> map[i];
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 10; k++) {
				for (int l = 0; l < 10; l++) {
					position[i][j][k][l] = 10;
				}
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 'R') {
				R0 = i;
				R1 = j;
			}
			else if (map[i][j] == 'B') {
				B0 = i;
				B1 = j;
			}
		}
	}

	DFS(R0, R1, B0, B1, 0);

	if (Min > 10) {
		cout << -1;
	}
	else {
		cout << Min;
	}
	return 0;
}

void Left(int _R0, int _R1, int _B0, int _B1, int _num) {
	int R0 = _R0;
	int R1 = _R1;
	int B0 = _B0;
	int B1 = _B1;
	int num = _num + 1;
	bool Red = false;
	bool Blue = false;

	if (R0 == B0) {
		if (R1 < B1) {
			while (map[R0][R1 - 1] != '#') {
				R1--;
				if (map[R0][R1] == 'O') {
					Red = true;
					break;
				}
			}
			while ((((B1 - 1) != R1) || Red) && (map[B0][B1 - 1] != '#')) {
				B1--;
				if (map[B0][B1] == 'O') {
					Blue = true;
					break;
				}
			}
		}
		else if (B1 < R1) {
			while (map[B0][B1 - 1] != '#') {
				B1--;
				if (map[B0][B1] == 'O') {
					Blue = true;
					break;
				}
			}
			while ((((R1 - 1) != B1) || Blue) && (map[R0][R1 - 1] != '#')) {
				R1--;
				if (map[R0][R1] == 'O') {
					Red = true;
					break;
				}
			}
		}
	}
	else {
		while (map[R0][R1 - 1] != '#') {
			R1--;
			if (map[R0][R1] == 'O') {
				Red = true;
				break;
			}
		}
		while (map[B0][B1 - 1] != '#') {
			B1--;
			if (map[B0][B1] == 'O') {
				Blue = true;
				break;
			}
		}
	}

	if (!Red && !Blue) {
		DFS(R0, R1, B0, B1, num);
	}
	else if (Red && !Blue) {
		Min = min(Min, num);
	}
}
void Right(int _R0, int _R1, int _B0, int _B1, int _num) {
	int R0 = _R0;
	int R1 = _R1;
	int B0 = _B0;
	int B1 = _B1;
	int num = _num + 1;
	bool Red = false;
	bool Blue = false;

	if (R0 == B0) {
		if (R1 > B1) {
			while (map[R0][R1 + 1] != '#') {
				R1++;
				if (map[R0][R1] == 'O') {
					Red = true;
					break;
				}
			}
			while ((((B1 + 1) != R1) || Red) && (map[B0][B1 + 1] != '#')) {
				B1++;
				if (map[B0][B1] == 'O') {
					Blue = true;
					break;
				}
			}
		}
		else if (B1 > R1) {
			while (map[B0][B1 + 1] != '#') {
				B1++;
				if (map[B0][B1] == 'O') {
					Blue = true;
					break;
				}
			}
			while ((((R1 + 1) != B1) || Blue) && (map[R0][R1 + 1] != '#')) {
				R1++;
				if (map[R0][R1] == 'O') {
					Red = true;
					break;
				}
			}
		}
	}
	else {
		while (map[R0][R1 + 1] != '#') {
			R1++;
			if (map[R0][R1] == 'O') {
				Red = true;
				break;
			}
		}
		while (map[B0][B1 + 1] != '#') {
			B1++;
			if (map[B0][B1] == 'O') {
				Blue = true;
				break;
			}
		}
	}

	if (!Red && !Blue) {
		DFS(R0, R1, B0, B1, num);
	}
	else if (Red && !Blue) {
		Min = min(Min, num);
	}
}
void Up(int _R0, int _R1, int _B0, int _B1, int _num) {
	int R0 = _R0;
	int R1 = _R1;
	int B0 = _B0;
	int B1 = _B1;
	int num = _num + 1;
	bool Red = false;
	bool Blue = false;

	if (R1 == B1) {
		if (R0 < B0) {
			while (map[R0 - 1][R1] != '#') {
				R0--;
				if (map[R0][R1] == 'O') {
					Red = true;
					break;
				}
			}
			while ((((B0 - 1) != R0) || Red) && (map[B0 - 1][B1] != '#')) {
				B0--;
				if (map[B0][B1] == 'O') {
					Blue = true;
					break;
				}
			}
		}
		else if (B0 < R0) {
			while (map[B0 - 1][B1] != '#') {
				B0--;
				if (map[B0][B1] == 'O') {
					Blue = true;
					break;
				}
			}
			while ((((R0 - 1) != B0) || Blue) && (map[R0 - 1][R1] != '#')) {
				R0--;
				if (map[R0][R1] == 'O') {
					Red = true;
					break;
				}
			}
		}
	}
	else {
		while (map[R0 - 1][R1] != '#') {
			R0--;
			if (map[R0][R1] == 'O') {
				Red = true;
				break;
			}
		}
		while (map[B0 - 1][B1] != '#') {
			B0--;
			if (map[B0][B1] == 'O') {
				Blue = true;
				break;
			}
		}
	}

	if (!Red && !Blue) {
		DFS(R0, R1, B0, B1, num);
	}
	else if (Red && !Blue) {
		Min = min(Min, num);
	}
}
void Down(int _R0, int _R1, int _B0, int _B1, int _num) {
	int R0 = _R0;
	int R1 = _R1;
	int B0 = _B0;
	int B1 = _B1;
	int num = _num + 1;
	bool Red = false;
	bool Blue = false;

	if (R1 == B1) {
		if (R0 > B0) {
			while (map[R0 + 1][R1] != '#') {
				R0++;
				if (map[R0][R1] == 'O') {
					Red = true;
					break;
				}
			}
			while ((((B0 + 1) != R0) || Red) && (map[B0 + 1][B1] != '#')) {
				B0++;
				if (map[B0][B1] == 'O') {
					Blue = true;
					break;
				}
			}
		}
		else if (B0 > R0) {
			while (map[B0 + 1][B1] != '#') {
				B0++;
				if (map[B0][B1] == 'O') {
					Blue = true;
					break;
				}
			}
			while ((((R0 + 1) != B0) || Blue) && (map[R0 + 1][R1] != '#')) {
				R0++;
				if (map[R0][R1] == 'O') {
					Red = true;
					break;
				}
			}
		}
	}
	else {
		while (map[R0 + 1][R1] != '#') {
			R0++;
			if (map[R0][R1] == 'O') {
				Red = true;
				break;
			}
		}
		while (map[B0 + 1][B1] != '#') {
			B0++;
			if (map[B0][B1] == 'O') {
				Blue = true;
				break;
			}
		}
	}

	if (!Red && !Blue) {
		DFS(R0, R1, B0, B1, num);
	}
	else if (Red && !Blue) {
		Min = min(Min, num);
	}
}
void DFS(int R0, int R1, int B0, int B1, int num) {
	if (position[R0][R1][B0][B1] > num && num < 10) {
		position[R0][R1][B0][B1] = num;
		Left(R0, R1, B0, B1, num);
		Right(R0, R1, B0, B1, num);
		Up(R0, R1, B0, B1, num);
		Down(R0, R1, B0, B1, num);
	}
}