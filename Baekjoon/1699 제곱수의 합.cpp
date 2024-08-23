#include <iostream>
#include <cmath>

#define min(a, b) (((a) < (b)) ? (a) : (b))

using namespace std;

int N;
int arr[100001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> N;

	for (int i = 1; i <= N; i++) {
		arr[i] = 100000;
	}

	arr[1] = 1;
	int squareRoot = 0;
	for (int i = 2; i <= N; i++) {
		squareRoot = sqrt(i);
		if (squareRoot * squareRoot == i) {
			arr[i] = 1;
		}
		else {
			for (int j = 1; j <= squareRoot; j++) {
				arr[i] = min(arr[i], arr[i - j * j] + 1);
			}
		}
	}

	cout << arr[N];

	return 0;
}