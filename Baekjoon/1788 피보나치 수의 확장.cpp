#include <iostream>

using namespace std;

int N;
long long* negative, * positive;
bool* checkNegative, * checkPositive;

long long fibonacci(int);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	negative = new long long[1000001];
	positive = new long long[1000001];
	negative[1] = 1;
	negative[2] = -1;
	positive[0] = 0;
	positive[1] = 1;

	checkNegative = new bool[1000001];
	checkPositive = new bool[1000001];
	for (int i = 0; i < 1000001; i++) {
		checkNegative[i] = false;
		checkPositive[i] = false;
	}
	checkNegative[1] = true;
	checkNegative[2] = true;
	checkPositive[0] = true;
	checkPositive[1] = true;

	
	cin >> N;
	long long result = fibonacci(N);
	if (result > 0) {
		cout << 1 << '\n';
		cout << result;
	}
	else if (result == 0) {
		cout << 0 << '\n';
		cout << 0;
	}
	else {
		cout << -1 << '\n';
		cout << -result;
	}

	delete[] negative;
	delete[] positive;
	delete[] checkNegative;
	delete[] checkPositive;

	return 0;
}

long long fibonacci(int n) {
	if (n >= 0) {
		if (checkPositive[n]) {
			return positive[n];
		}
		else {
			positive[n] = (fibonacci(n - 1) + fibonacci(n - 2)) % 1000000000;
			checkPositive[n] = true;
			return positive[n];
		}
	}
	else {
		if (checkNegative[-n]) {
			return negative[-n];
		}
		else {
			negative[-n] = fibonacci(n + 2) - fibonacci(n + 1);
			if (negative[-n] >= 0) {
				negative[-n] %= 1000000000;
			}
			else {
				negative[-n] *= -1;
				negative[-n] %= 1000000000;
				negative[-n] *= -1;
			}
			checkNegative[-n] = true;
			return negative[-n];
		}
	}
}