#include <iostream>
#include <cstring>

using namespace std;

int N;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> N;

	if (N % 2 == 1) {
		cout << "SK";
	}
	else {
		cout << "CY";
	}

	return 0;
}