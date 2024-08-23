#include <iostream>
#include <cstring>

using namespace std;

int N, M, T;

int discs[50][50];
int alive[50][50];
int starts[50], x[50], d[50], k[50];

char deleted;

void rotate_discs(int, int, int);
void check_if_same(int, int, int);
void find_same_nums(int);
void plus_minus();
void rotate();
int sum();
void print_discs();


int main() {
	cin >> N >> M >> T;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int num = 0;
			cin >> num;
			discs[i][j] = num;
		}
		starts[i] = 0;
	}

	for (int i = 0; i < T; i++) {
		int x_i = 0, d_i = 0, k_i = 0;
		cin >> x_i >> d_i >> k_i;
		x[i] = x_i;
		d[i] = d_i;
		k[i] = k_i;
	}

	rotate();
	cout << sum();

	return 0;
}

void rotate_discs(int x_i, int d_i, int k_i) {
	for (int i = x_i - 1; i < N; i += x_i) {
		if (d_i == 0) {
			starts[i] = (starts[i] + M - k_i) % M;
		}
		else if (d_i == 1) {
			starts[i] = (starts[i] + k_i) % M;
		}
	}
}

void check_if_same(int round, int disc_num, int idx) {
	int num_idx = (starts[disc_num] + idx) % M;
	int num = discs[disc_num][num_idx];
	int alive_num = 0;

	if (alive[disc_num][num_idx] > 0 && alive[disc_num][num_idx] < round) {
		return;
	}

	if (disc_num - 1 >= 0) {
		alive_num = alive[disc_num - 1][(starts[disc_num - 1] + idx) % M];
		if (alive_num == 0 || alive_num >= round) {
			if (discs[disc_num - 1][(starts[disc_num - 1] + idx) % M] == num) {
				alive[disc_num][num_idx] = round;
				deleted = 1;
			}
		}
	}
	if (disc_num + 1 < N) {
		alive_num = alive[disc_num + 1][(starts[disc_num + 1] + idx) % M];
		if (alive_num == 0 || alive_num >= round) {
			if (discs[disc_num + 1][(starts[disc_num + 1] + idx) % M] == num) {
				alive[disc_num][num_idx] = round;
				deleted = 1;
			}
		}
	}

	alive_num = alive[disc_num][(num_idx + 1) % M];
	if (alive_num == 0 || alive_num >= round) {
		if (discs[disc_num][(num_idx + 1) % M] == num) {
			alive[disc_num][num_idx] = round;
			deleted = 1;
		}
	}

	alive_num = alive[disc_num][(num_idx + M - 1) % M];
	if (alive_num == 0 || alive_num >= round) {
		if (discs[disc_num][(num_idx + M - 1) % M] == num) {
			alive[disc_num][num_idx] = round;
			deleted = 1;
		}
	}
}

void find_same_nums(int round) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			check_if_same(round, i, j);
		}
	}
}

void plus_minus() {
	if (deleted == 0) {
		double avg = 0;
		int count = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (alive[i][j] == 0) {
					avg += discs[i][j];
					count++;
				}
			}
		}
		avg /= count;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (alive[i][j] == 0) {
					if (discs[i][j] > avg) {
						discs[i][j]--;
					}
					else if (discs[i][j] < avg) {
						discs[i][j]++;
					}
				}
			}
		}
	}
}

void rotate() {
	for (int i = 0; i < T; i++) {
		deleted = 0;
		rotate_discs(x[i], d[i], k[i]);
		find_same_nums(i+1);
		plus_minus();
	}
}

int sum() {
	int res = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (alive[i][j] == 0) {
				res += discs[i][j];
			}
		}
	}

	return res;
}

void print_discs() {
	for (int j = 0; j < N; j++) {
		for (int k = 0; k < M; k++) {
			if (alive[j][(starts[j] + k) % M] == 0) {
				cout << discs[j][(starts[j] + k) % M];
			}
			else {
				cout << "x";
			}
		}
		cout << endl;
	}
	cout << endl;
}