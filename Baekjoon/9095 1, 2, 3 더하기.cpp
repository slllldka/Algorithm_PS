#include <iostream>
#include <cmath>

using namespace std;

int memory[11];

int getSumNum(int);

int main() {
	memory[1] = 1;
	memory[2] = 2;
	memory[3] = 4;
	
	int T, n;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> n;
		cout << getSumNum(n) << endl;
	}

	return 0;
}

int getSumNum(int n) {
	if (n <= 3) {
		return memory[n];
	}
	else if (memory[n] != 0) {
		return memory[n];
	}
	else {
		return getSumNum(n - 1) + getSumNum(n - 2) + getSumNum(n - 3);
	}
}