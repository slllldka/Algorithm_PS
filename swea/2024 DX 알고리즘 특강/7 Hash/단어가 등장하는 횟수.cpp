#include <iostream>

using namespace std;

int pi[100000];

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T, count, idx;
	string B, S;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> B;
		cin >> S;
		count = 0;
		pi[0] = 0;
		idx = 0;
		for (int i = 1; i < S.length(); i++) {
			if (S[i] == S[idx]) {
				idx++;
				pi[i] = idx;
			}
			else{
				if (idx > 0) {
					i--;
					idx = pi[idx - 1];
				}
				else {
					pi[i] = 0;
				}
			}
		}

		idx = 0;
		for (int i = 0; i < B.length(); i++) {
			if (B[i] == S[idx]) {
				idx++;
				if (idx == S.length()) {
					count++;
					idx = pi[idx - 1];
				}
			}
			else {
				if (idx > 0) {
					i--;
					idx = pi[idx - 1];
				}
			}
		}

		cout << '#' << t << ' ' << count << '\n';
	}
	return 0;
}