#include <iostream>
#include <utility>

using namespace std;

long long num[1000001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	num[1] = 1;
	num[2] = 2;
	num[3] = 4;

	for (int i = 4; i <= 1000000; i++) {
		num[i] = (num[i - 1] + num[i - 2] + num[i - 3]) % 1000000009;
	}

	int T, n;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> n;
		cout << num[n] << '\n';
	}

	return 0;
}