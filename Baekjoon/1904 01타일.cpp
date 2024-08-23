#include <iostream>

using namespace std;

int N;
long long* endWithOne;
long long* endWithZero;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	endWithOne = new long long[N + 1];
	endWithOne[1] = 1;
	if (N >= 2) {
		endWithOne[2] = 1;
	}

	endWithZero = new long long[N + 1];
	endWithZero[1] = 0;
	if (N >= 2) {
		endWithZero[2] = 1;
	}

	for (int i = 3; i <= N; i++) {
		endWithOne[i] = (endWithOne[i - 1] + endWithZero[i - 1]) % 15746;
		endWithZero[i] = (endWithOne[i - 2] + endWithZero[i - 2]) % 15746;
	}

	cout << (endWithOne[N] + endWithZero[N]) % 15746;

	delete[] endWithOne;
	delete[] endWithZero;
	
	return 0;
}