#include <iostream>

#define min(a, b) (((a) < (b)) ? (a) : (b))

using namespace std;

int arr[100000];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, S, sum = 0, len = 100001, left = 0, right = 0;
	cin >> N >> S;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	sum = arr[0];
	for (left = 0; left < N;) {
		if (sum >= S) {
			len = min(len, (right - left + 1));
			sum -= arr[left];
			left++;
		}
		else {
			right++;
			if (right >= N) {
				break;
			}
			else {
				sum += arr[right];
			}
		}
	}

	if (len == 100001) {
		cout << 0;
	}
	else {
		cout << len;
	}

	return 0;
}