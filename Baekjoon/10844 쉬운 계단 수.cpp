#include <iostream>

using namespace std;

long long N, endWith[101][10];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	endWith[1][0] = 0;
	endWith[1][1] = 1;
	endWith[1][2] = 1;
	endWith[1][3] = 1;
	endWith[1][4] = 1;
	endWith[1][5] = 1;
	endWith[1][6] = 1;
	endWith[1][7] = 1;
	endWith[1][8] = 1;
	endWith[1][9] = 1;

	for (int i = 2; i <= N; i++) {
		endWith[i][0] = (endWith[i - 1][1]) % 1000000000;
		endWith[i][1] = (endWith[i - 1][0] + endWith[i - 1][2]) % 1000000000;
		endWith[i][2] = (endWith[i - 1][1] + endWith[i - 1][3]) % 1000000000;
		endWith[i][3] = (endWith[i - 1][2] + endWith[i - 1][4]) % 1000000000;
		endWith[i][4] = (endWith[i - 1][3] + endWith[i - 1][5]) % 1000000000;
		endWith[i][5] = (endWith[i - 1][4] + endWith[i - 1][6]) % 1000000000;
		endWith[i][6] = (endWith[i - 1][5] + endWith[i - 1][7]) % 1000000000;
		endWith[i][7] = (endWith[i - 1][6] + endWith[i - 1][8]) % 1000000000;
		endWith[i][8] = (endWith[i - 1][7] + endWith[i - 1][9]) % 1000000000;
		endWith[i][9] = (endWith[i - 1][8]) % 1000000000;
	}

	long long sum = 0;
	for (int i = 0; i < 10; i++) {
		sum += endWith[N][i];
	}
	cout << sum % 1000000000;

	return 0;
}