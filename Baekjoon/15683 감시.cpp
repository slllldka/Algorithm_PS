#include <iostream>
#include <cstring>
#include <vector>
#include <tuple>

#define min(a, b) (((a) < (b)) ? (a) : (b))

using namespace std;

typedef tuple<int, int, int> i3;

vector<i3> vi3;

int N, M;
int Office[8][8];
int Min = 64;

void ND(int, int, int, int);
void MD(int, int, int, int);
void Back(int);
void Minimum();
void Recursive1(int);
void Recursive2(int);


int main() {
	memset(Office, -1, sizeof(Office));
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> Office[i][j];
			if (Office[i][j] >= 1 && Office[i][j] <= 5) {
				vi3.push_back(i3(i, j, Office[i][j]));
			}
		}
	}

	Recursive2(0);
	cout << Min;
}

void ND(int sign, int _n, int _m, int idx) {
	int newn = _n + sign;
	while (newn >= 0 && newn < N) {
		if (Office[newn][_m] == 0) {
			Office[newn][_m] = idx + 10;
		}
		else if (Office[newn][_m] == 6) {
			break;
		}
		newn += sign;
	}
}
void MD(int sign, int _n, int _m, int idx) {
	int newm = _m + sign;
	while (newm >= 0 && newm < M) {
		if (Office[_n][newm] == 0) {
			Office[_n][newm] = idx + 10;
		}
		else if (Office[_n][newm] == 6) {
			break;
		}
		newm += sign;
	}
}

void Back(int idx) {
	if (idx >= 0) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (Office[i][j] == idx + 10) {
					Office[i][j] = 0;
				}
			}
		}
	}
}

void Minimum() {
	int num = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (Office[i][j] == 0) {
				num++;
			}
		}
	}

	Min = min(Min, num);
}

void Recursive1(int idx) {
	int _n = get<0>(vi3[idx]);
	int _m = get<1>(vi3[idx]);
	int cctv = get<2>(vi3[idx]);

	if (cctv == 1) {
		ND(1, _n, _m, idx);
		Recursive2(idx + 1);

		MD(1, _n, _m, idx);
		Recursive2(idx + 1);

		ND(-1, _n, _m, idx);
		Recursive2(idx + 1);

		MD(-1, _n, _m, idx);
		Recursive2(idx + 1);
	}
	else if (cctv == 2) {
		ND(1, _n, _m, idx);
		ND(-1, _n, _m, idx);
		Recursive2(idx + 1);

		MD(1, _n, _m, idx);
		MD(-1, _n, _m, idx);
		Recursive2(idx + 1);
	}
	else if (cctv == 3) {
		ND(1, _n, _m, idx);
		MD(1, _n, _m, idx);
		Recursive2(idx + 1);

		ND(1, _n, _m, idx);
		MD(-1, _n, _m, idx);
		Recursive2(idx + 1);

		ND(-1, _n, _m, idx);
		MD(-1, _n, _m, idx);
		Recursive2(idx + 1);

		ND(-1, _n, _m, idx);
		MD(1, _n, _m, idx);
		Recursive2(idx + 1);
	}
	else if (cctv == 4) {
		MD(-1, _n, _m, idx);
		ND(-1, _n, _m, idx);
		MD(1, _n, _m, idx);
		Recursive2(idx + 1);

		ND(-1, _n, _m, idx);
		MD(1, _n, _m, idx);
		ND(1, _n, _m, idx);
		Recursive2(idx + 1);

		MD(1, _n, _m, idx);
		ND(1, _n, _m, idx);
		MD(-1, _n, _m, idx);
		Recursive2(idx + 1);

		ND(1, _n, _m, idx);
		MD(-1, _n, _m, idx);
		ND(-1, _n, _m, idx);
		Recursive2(idx + 1);
	}
	else if (cctv == 5) {
		ND(1, _n, _m, idx);
		MD(1, _n, _m, idx);
		ND(-1, _n, _m, idx);
		MD(-1, _n, _m, idx);
		Recursive2(idx + 1);
	}

}

void Recursive2(int idx) {
	if (idx == vi3.size()) {
		Minimum();
	}
	else {
		Recursive1(idx);
	}
	Back(idx - 1);
}