#include <iostream>
#include <utility>

#define max(a, b) (((a) > (b)) ? (a) : (b))

using namespace std;

typedef pair<int, int> i2;

int N, arr[1000];
i2 lengthArr[1000];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	lengthArr[0] = i2(1, 0);
	for (int i = 1; i < N; i++) {
		int maxLength = 0, maxIdx = -1;
		for (int j = 0; j < i; j++) {
			if (arr[j] < arr[i]) {
				if (lengthArr[j].first > maxLength) {
					maxLength = lengthArr[j].first;
					maxIdx = j;
				}
			}
		}
		lengthArr[i] = i2(maxLength + 1, maxIdx);
	}
	
	int maxLength = 0, maxIdx = 0;
	for (int i = 0; i < N; i++) {
		if (lengthArr[i].first > maxLength) {
			maxLength = lengthArr[i].first;
			maxIdx = i;
		}
	}

	int* newArr = new int[maxLength];
	int idx = maxIdx;
	for (int i = 1; i <= maxLength; i++) {
		newArr[maxLength - i] = arr[idx];
		idx = lengthArr[idx].second;
	}

	cout << maxLength << '\n';
	for (int i = 0; i < maxLength; i++) {
		cout << newArr[i] << ' ';
	}

	delete[] newArr;

	return 0;
}