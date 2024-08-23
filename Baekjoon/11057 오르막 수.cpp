#include <iostream>
#include <utility>
#include <cstring>

using namespace std;

long long N;
long long num[1001][10];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;

	memset(num, 0, sizeof(num));
	for (int i = 0; i < 10; i++) {
		num[1][i] = 1;
	}

	for (int i = 2; i <= N; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = j; k < 10; k++) {
				num[i][k] += num[i - 1][j];
				num[i][k] %= 10007;
			}
		}
	}

	long long sum = 0;
	for (int i = 0; i < 10; i++) {
		sum += num[N][i];
		sum %= 10007;
	}

	cout << sum << '\n';
	return 0;
}