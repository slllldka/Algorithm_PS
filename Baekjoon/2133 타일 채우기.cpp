#include <iostream>
#include <cstring>

using namespace std;

int N;
int arr[31];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	
	arr[0] = 1;
	for (int i = 2; i <= 30; i += 2) {
		arr[i] = 0;
		arr[i] += arr[i - 2] * 3;
		for (int j = i - 4; j >= 0; j -= 2) {
			arr[i] += arr[j] * 2;
		}
	}

	cout << arr[N];

	return 0;
}