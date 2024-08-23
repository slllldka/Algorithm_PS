#include <iostream>
#include <queue>
#include <utility>

#define max(a, b) (((a) > (b)) ? (a) : (b))

using namespace std;

int N, arr[1000], sum[1000];

int main() {
	int maxSum = 0;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	sum[0] = arr[0];

	for (int i = 1; i < N; i++) {
		maxSum = 0;
		for (int j = 0; j < i; j++) {
			if (arr[i] > arr[j]) {
				maxSum = max(maxSum, sum[j]);
			}
		}
		sum[i] = maxSum + arr[i];
	}

	maxSum = 0;
	for (int i = 0; i < N; i++) {
		maxSum = max(maxSum, sum[i]);
	}

	cout << maxSum;
	return 0;
}