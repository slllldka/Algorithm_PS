#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int L, C, v, c;
char* arr;

void Combination(char* ptr, int r, int idx1, int idx2) {
	if (r > 0) {
		for (int i = idx1; i < C - r + 1; i++) {
			ptr[idx2] = arr[i];
			Combination(ptr, r - 1, i + 1, idx2 + 1);
		}
	}
	else {
		v = 0;
		c = 0;
		for (int i = 0; i < L; i++) {
			if (ptr[i] == 'a' || ptr[i] == 'e' || ptr[i] == 'i' || ptr[i] == 'o' || ptr[i] == 'u') {
				v++;
			}
			else {
				c++;
			}
		}
		if (v >= 1 && c >= 2) {
			for (int i = 0; i < L; i++) {
				cout << ptr[i];
			}
			puts("");
		}
	}
}

int main() {
	char* ptr;
	cin >> L >> C;
	arr = new char[C];
	ptr = new char[C];
	for (int i = 0; i < C; i++) {
		cin >> arr[i];
	}
	sort(arr, arr + C);

	Combination(ptr, L, 0, 0);
	delete[]arr;
	delete[]ptr;
	return 0;
}