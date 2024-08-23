#include <iostream>
#include <utility>
#include <cstring>

using namespace std;

int n, k;
int price[100];
int num[10001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> price[i];
	}

	num[0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = price[i]; j <= k; j++) {
			num[j] += num[j - price[i]];
		}
	}

	cout << num[k];
	
	return 0;
}