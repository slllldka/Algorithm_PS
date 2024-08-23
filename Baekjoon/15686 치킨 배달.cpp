#include <iostream>
#include <queue>
#include <tuple>
#include <cstring>

#define min(a, b) (((a) < (b)) ? (a) : (b))

using namespace std;

int N, M, house_num = 0, Min = -1;
int map[50][50];
typedef tuple<int, int> i2;
vector<i2> house;

int choose[13];
int row_vector[4] = { 1, 0, -1, 0 };
int column_vector[4] = { 0, 1, 0, -1 };

int Chicken_Distance(i2);
void Combination(int, int);

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) {
				house_num++;
				house.push_back(i2(i, j));
			}
		}
	}
	
	Combination(0, M);
	cout << Min;
}

int Chicken_Distance(i2 location) {
	int result = 10000;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 3) {
				int rd = abs(get<1>(location) - j);
				int cd = abs(get<0>(location) - i);
				result = min(result, rd + cd);
			}
		}
	}

	return result;
}

void Combination(int index, int num) {
	if (num == 0) {
		int result = 0;
		for (int i = 0; i < M; i++) {
			int row = choose[i] % N;
			int column = choose[i] / N;
			map[row][column] = 3;
		}

		for (int i = 0; i < house_num; i++) {
			result += Chicken_Distance(house[i]);
		}

		if (Min == -1) {
			Min = result;
		}
		else {
			Min = min(Min, result);
		}

		for (int i = 0; i < M; i++) {
			int row = choose[i] % N;
			int column = choose[i] / N;
			map[row][column] = 2;
		}
	}
	else {
		for (int i = index; i < N * N; i++) {
			int row = i % N;
			int column = i / N;
			if (map[row][column] == 2) {
				choose[M - num] = i;
				Combination(i + 1, num - 1);
			}
		}
	}
}