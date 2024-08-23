#include <iostream>

#define max(a, b) (((a) > (b)) ? (a) : (b))

using namespace std;

int N, *timeArr, *payArr;
long long *sum;


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	timeArr = new int[1500001];
	payArr = new int[1500001];
	sum = new long long[1500001];

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> timeArr[i] >> payArr[i];
	}

	long long maxSum = 0;
	sum[0] = 0;
	for (int i = 0; i < N; i++) {
		maxSum = max(maxSum, sum[i]);
		if (i + timeArr[i] <= N) {
			sum[i + timeArr[i]] = max(sum[i + timeArr[i]], maxSum + payArr[i]);
		}
	}

	cout << max(maxSum, sum[N]);

	return 0;
}