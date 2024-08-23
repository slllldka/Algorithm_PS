#include <iostream>

using namespace std;

int arr[10000];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M;
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	int left = 0, right = 0, sum = arr[0], count = 0;
	for (; left < N;) {
		if (sum == M) {
			count++;

			sum -= arr[left];
			left++;
			right++;
			if (right >= N) {
				break;
			}
			else {
				sum += arr[right];
			}
		}
		else if (sum > M) {
			sum -= arr[left];
			left++;
		}
		else if (sum < M) {
			right++;

			if (right >= N) {
				break;
			}
			else {
				sum += arr[right];
			}
		}
	}

	cout << count;

	return 0;
}