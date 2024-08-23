#include <iostream>

using namespace std;

long long N, endWithZero[91], endWithOne[91];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	endWithZero[1] = 0;
	endWithOne[1] = 1;

	for (int i = 2; i <= N; i++) {
		endWithZero[i] = endWithZero[i - 1] + endWithOne[i - 1];
		endWithOne[i] = endWithZero[i - 1];
	}

	cout << endWithZero[N] + endWithOne[N];

	return 0;
}