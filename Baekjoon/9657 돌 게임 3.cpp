#include <iostream>
#include <cstring>

using namespace std;

const bool SK = true, CY = false;

int N;
bool whoWins[1001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	whoWins[1] = SK;
	whoWins[2] = CY;
	whoWins[3] = SK;
	whoWins[4] = SK;
	whoWins[5] = SK;
	whoWins[6] = SK;
	for (int i = 7; i <= N; i++) {
		if (whoWins[i - 1] == SK && whoWins[i - 3] == SK && whoWins[i - 4] == SK) {
			whoWins[i] = CY;
		}
		else {
			whoWins[i] = SK;
		}
	}

	if (whoWins[N]) {
		cout << "SK";
	}
	else {
		cout << "CY";
	}

	return 0;
}