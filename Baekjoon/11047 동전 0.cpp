#include <iostream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K, arr[10], quotient = 0, sum = 0, result = 0;
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		cin >> arr[(N - 1) - i];
	}

	for (int i = 0; i < N; i++) {
		quotient = (K - sum) / arr[i];
		result += quotient;
		sum += arr[i] * quotient;
		if (sum == K) {
			break;
		}
	}
	cout << result;

	return 0;
}