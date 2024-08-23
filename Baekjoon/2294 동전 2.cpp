#include <iostream>
#include <cstring>

#define min(a, b) (((a) < (b)) ? (a) : (b))

using namespace std;

int n, k;
int coins[100];
int arr[10001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> coins[i];
	}

	for (int i = 0; i <= k; i++) {
		arr[i] = 100000;
	}

	for (int i = 0; i < n; i++) {
		for (int j = coins[i]; j <= k; j++) {
			if (j == coins[i]) {
				arr[j] = 1;
			}
			else {
				arr[j] = min(arr[j], arr[j - coins[i]] + 1);
			}
		}

	}

	if (arr[k] < 100000) {
		cout << arr[k];
	}
	else {
		cout << -1;
	}

	return 0;
}