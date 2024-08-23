#include <iostream>
#include <utility>

#define max(a, b) (((a) > (b)) ? (a) : (b))

using namespace std;

int T, W, *arr;
int* prevNum, * curNum;

int getPos(int);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T >> W;
	arr = new int[T];
	for (int i = 0; i < T; i++) {
		cin >> arr[i];
	}

	prevNum = new int[W + 1];
	curNum = new int[W + 1];
	for (int i = 0; i <= W; i++) {
		prevNum[i] = -1;
		curNum[i] = -1;
	}

	prevNum[0] = ((arr[0] == 1) ? 1 : 0);
	prevNum[1] = ((arr[0] == 2) ? 1 : 0);

	for (int i = 1; i < T; i++) {
		for (int j = 0; j <= W; j++) {
			if (prevNum[j] == -1) {
				break;
			}
			else {
				if (arr[i] == getPos(j)) {
					curNum[j] = max(curNum[j], prevNum[j] + 1);
					if (j + 1 <= W) {
						curNum[j + 1] = max(curNum[j + 1], prevNum[j]);
					}
				}
				else {
					curNum[j] = max(curNum[j], prevNum[j]);
					if (j + 1 <= W) {
						curNum[j + 1] = max(curNum[j + 1], prevNum[j] + 1);
					}
				}
			}
		}

		for (int j = 0; j <= W; j++) {
			prevNum[j] = curNum[j];
			curNum[j] = -1;
		}
	}

	int maxPlum = 0;
	for (int i = 0; i <= W; i++) {
		maxPlum = max(maxPlum, prevNum[i]);
	}
	cout << maxPlum;

	delete[] arr;
	delete[] prevNum;
	delete[] curNum;

	return 0;
}

int getPos(int w) {
	return 1 + (w % 2);
}