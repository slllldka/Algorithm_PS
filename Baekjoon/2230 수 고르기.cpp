#include <iostream>
#include <algorithm>

using namespace std;

int arr[100000];

int difference(int n1, int n2) {
	return (n1 - n2);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	sort(arr, arr + N);
	
	int result = 2147483647, ret = 0;
	int right = 0;
	for (int left = 0; left < N;) {
		if ((ret = difference(arr[right], arr[left])) > M) {
			if (ret < result) {
				result = ret;
				left++;
				right++;
				if (right == N) {
					right--;
				}
			}
			else {
				left++;
				if (left > right) {
					left = right;
				}
			}
		}
		else if (ret == M) {
			cout << M;
			return 0;
		}
		else {
			right++;
			if (right == N) {
				cout << result;
				return 0;
			}
		}
	}

	return 0;
}