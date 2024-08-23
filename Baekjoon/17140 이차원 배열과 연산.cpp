#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>

#define max(a, b) (((a) > (b)) ? (a) : (b))

using namespace std;

typedef pair<int, int> i2;

struct compare {
	bool operator()(i2 a, i2 b) {
		if (a.second > b.second) {
			return true;
		}
		else if (a.second < b.second) {
			return false;
		}
		else {
			if (a.first > b.first) {
				return true;
			}
			else {
				return false;
			}
		}
	}
};


typedef priority_queue<i2, deque<i2>, compare> pq;

int r, c, k;
int R_len, C_len;
int A[100][100];
int Arr[101];

void R();
void C();

int main() {
	R_len = 3;
	C_len = 3;
	cin >> r >> c >> k;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> A[i][j];
		}
	}

	for (int i = 0; i < 100; i++) {
		if (A[r - 1][c - 1] == k) {
			cout << i;
			return 0;
		}

		if (R_len >= C_len) {
			R();
		}
		else {
			C();
		}
	}

	if (A[r - 1][c - 1] == k) {
		cout << 100;
	}
	else {
		cout << -1;
	}
	return 0;
}

void R() {
	int max = 0;
	for (int i = 0; i < R_len; i++) {
		memset(Arr, 0, sizeof(Arr));
		for (int j = 0; j < C_len; j++) {
			if (A[i][j] != 0) {
				Arr[A[i][j]]++;
			}
		}

		pq temp;
		for (int j = 1; j < 101; j++) {
			if (Arr[j] > 0) {
				temp.push(i2(j, Arr[j]));
			}
			if (temp.size() == 50) {
				break;
			}
		}
		
		int idx = 0;
		while (!temp.empty()) {
			i2 cur = temp.top();
			temp.pop();
			A[i][idx++] = cur.first;
			A[i][idx++] = cur.second;
		}

		max = max(max, idx);
		while (idx < 100) {
			A[i][idx++] = 0;
		}
	}

	if (max > 100) {
		C_len = 100;
	}
	else {
		C_len = max;
	}
}
void C() {
	int max = 0;
	for (int i = 0; i < C_len; i++) {
		memset(Arr, 0, sizeof(Arr));
		for (int j = 0; j < 100; j++) {
			if (A[j][i] != 0) {
				Arr[A[j][i]]++;
			}
		}

		pq temp;
		for (int j = 1; j < 101; j++) {
			if (Arr[j] > 0) {
				temp.push(i2(j, Arr[j]));
			}
			if (temp.size() == 50) {
				break;
			}
		}

		int idx = 0;
		while (!temp.empty()) {
			i2 cur = temp.top();
			temp.pop();
			A[idx++][i] = cur.first;
			A[idx++][i] = cur.second;
		}

		max = max(max, idx);
		while (idx < 100) {
			A[idx++][i] = 0;
		}
	}

	if (max > 100) {
		R_len = 100;
	}
	else {
		R_len = max;
	}
}