#include <iostream>
#include <cstring>
#include <queue>
#include <tuple>

#define max(a, b) (((a) > (b)) ? (a) : (b))

using namespace std;

typedef tuple<int, int, int, int> i4;

int arr[100][100][100];
int M, N, H, Day = 0;

int HD[] = {1, -1, 0, 0, 0, 0};
int ND[] = {0, 0, 1, -1, 0, 0};
int MD[] = {0, 0, 0, 0, 1, -1};

bool CheckRange(int _h, int _n, int _m) {
	if (_h >= 0 && _h < H && _n >= 0 && _n < N && _m >= 0 && _m < M) {
		return true;
	}
	else {
		return false;
	}
}

void Push(queue<i4>& ref, i4& _cur) {
	int _h = get<0>(_cur);
	int _n = get<1>(_cur);
	int _m = get<2>(_cur);
	int _day = get<3>(_cur);
	for (int i = 0; i < 6; i++) {
		if (CheckRange(_h + HD[i], _n + ND[i], _m + MD[i])) {
			if (arr[_h + HD[i]][_n + ND[i]][_m + MD[i]] == 0) {
				ref.push(i4(_h + HD[i], _n + ND[i], _m + MD[i], _day + 1));
				arr[_h + HD[i]][_n + ND[i]][_m + MD[i]] = 1;
			}
		}
	}
}

bool CheckTomato() {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				if (arr[i][j][k] == 0) {
					return false;
				}
			}
		}
	}

	return true;
}

bool BFS() {
	queue<i4> q;
	i4 temp;

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				if (arr[i][j][k] == 1) {
					q.push(i4(i, j, k, 0));
				}
			}
		}
	}

	while (!q.empty()) {
		temp = q.front();
		q.pop();
		Day = max(Day, get<3>(temp));

		Push(q, temp);
	}

	return CheckTomato();
}

int main() {
	memset(arr, 0, sizeof(arr));
	cin >> M >> N >> H;
	
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				cin >> arr[i][j][k];
			}
		}
	}

	if (BFS()) {
		cout << Day;
	}
	else {
		cout << -1;
	}

	return 0;
}