#include <iostream>

using namespace std;

int N, M, H;
int A[3], B[3];
int horizontal[32][10];
bool result = false;

bool Test(int);
int Ride_Ladder(int);

int main() {
	int a, b, num = 0;
	cin >> N >> M >> H;
	for (int i = 0; i < H + 2; i++) {
		for (int j = 0; j < N; j++) {
			horizontal[i][j] = 0;
		}
	}
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		horizontal[a][b - 1] = b;
		horizontal[a][b] = b;
	}

	//0
	if (Test(0)) {
		cout << 0;
		return 0;
	}

	//1
	for (int i = 0; i < (N - 1) * H; i++) {
		int row0 = i % H + 1;
		int column0 = i / H;
		if (!horizontal[row0][column0] && !horizontal[row0][column0 + 1]) {
			A[0] = row0;
			B[0] = column0;
			if (Test(1)) {
				cout << 1;
				return 0;
			}
		}
	}

	//2
	for (int i = 0; i < (N - 1) * H; i++) {
		int row0 = i % H + 1;
		int column0 = i / H;
		if (!horizontal[row0][column0] && !horizontal[row0][column0 + 1]) {
			A[0] = row0;
			B[0] = column0;
			for (int j = i + 1; j < (N - 1) * H; j++) {
				int row1 = j % H + 1;
				int column1 = j / H;
				if (!horizontal[row1][column1] && !horizontal[row1][column1 + 1]) {
					if ((row0 != row1) || (column1 != column0 + 1)) {
						A[1] = row1;
						B[1] = column1;
						if (Test(2)) {
							cout << 2;
							return 0;
						}
					}
				}
			}
		}

	}


	//3
	for (int i = 0; i < (N - 1) * H; i++) {
		int row0 = i % H + 1;
		int column0 = i / H;
		if (!horizontal[row0][column0] && !horizontal[row0][column0 + 1]) {
			A[0] = row0;
			B[0] = column0;
			for (int j = i + 1; j < (N - 1) * H; j++) {
				int row1 = j % H + 1;
				int column1 = j / H;
				if (!horizontal[row1][column1] && !horizontal[row1][column1 + 1]) {
					if ((row0 != row1) || (column1 != column0 + 1)) {
						A[1] = row1;
						B[1] = column1;
						for (int k = j + 1; k < (N - 1) * H; k++) {
							int row2 = k % H + 1;
							int column2 = k / H;
							if (!horizontal[row2][column2] && !horizontal[row2][column2 + 1]) {
								if (((row0 != row2) || (column2 != column0 + 1)) && ((row1 != row2) || (column2 != column1 + 1))) {
									A[2] = row2;
									B[2] = column2;
									if (Test(3)) {
										cout << 3;
										return 0;
									}
								}
							}
						}
					}
				}
			}
		}

	}

	cout << -1;
	return 0;

}

bool Test(int num) {
	bool result = true;
	for (int i = 0; i < num; i++) {
		horizontal[A[i]][B[i]] = B[i] + 1;
		horizontal[A[i]][B[i] + 1] = B[i] + 1;
	}

	for (int i = 0; i < N; i++) {
		if (i != Ride_Ladder(i)) {
			result = false;
			break;
		}
	}

	for (int i = 0; i < num; i++) {
		horizontal[A[i]][B[i]] = 0;
		horizontal[A[i]][B[i] + 1] = 0;
	}

	return result;
}

int Ride_Ladder(int column) {
	int result = column;

	for (int i = 0; i < H + 2; i++) {
		if (horizontal[i][result]) {
			if (result > 0) {
				if (horizontal[i][result - 1] == result) {
					result--;
					continue;
				}
			}
			if (result < N - 1) {
				if (horizontal[i][result + 1] == result + 1) {
					result++;
					continue;
				}
			}
		}
	}

	return result;
}