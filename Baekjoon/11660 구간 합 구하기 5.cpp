#include <iostream>
#include <cstring>

using namespace std;

int N, M;
int arr[1024][1024];
int sum[1024][1024];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
			for (int k = j; k < N; k++) {
				sum[i][k] += arr[i][j];
			}
		}
	}

	int x1, y1, x2, y2, result;
	for (int i = 0; i < M; i++) {
		cin >> x1 >> y1 >> x2 >> y2;
		x1--;
		y1--;
		x2--;
		y2--;

		result = 0;
		for (int j = x1; j <= x2; j++) {
			if (y1 >= 1) {
				result += (sum[j][y2] - sum[j][y1 - 1]);
			}
			else {
				result += sum[j][y2];
			}
		}
		cout << result << '\n';
	}
	
	return 0;
}