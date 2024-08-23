#include <iostream>
#include <cstring>

using namespace std;

int T, N, M;
int price[20];
int arr[10001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> N;
		memset(arr, 0, sizeof(arr));
		arr[0] = 1;
		for (int i = 0; i < N; i++) {
			cin >> price[i];
		}
		cin >> M;

		for (int i = 0; i < N; i++) {
			for (int j = price[i]; j <= M; j++) {
				arr[j] += arr[j - price[i]];
			}
		}

		cout << arr[M] << '\n';
	}
	
	return 0;
}