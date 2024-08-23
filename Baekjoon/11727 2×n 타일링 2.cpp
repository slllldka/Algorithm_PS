#include <iostream>

using namespace std;

long long N, arr[1001];

long long getNth(long long);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	arr[1] = 1;
	arr[2] = 3;

	cout << getNth(N) % 10007;

	return 0;
}

long long getNth(long long num) {
	if (arr[num] != 0) {
		return arr[num];
	}
	else {
		arr[num] = (getNth(num - 2) * 2 + (getNth(num - 1))) % 10007;
		return arr[num];
	}
}