#include <iostream>

#define max(a, b) (((a) > (b)) ? (a) : (b))

using namespace std;

int N;
int price[1001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> price[i];
	}
	
	int maxSum;
	for (int i = 2; i <= N; i++) {
		maxSum = 0;
		for (int j = i - 1; (double)j >= (double)i / 2; j--) {
			maxSum = max(maxSum, price[j] + price[i - j]);
		}
		price[i] = max(price[i], maxSum);
	}

	cout << price[N];

	return 0;
}