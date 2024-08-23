#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K;

int arr[10][10];
int p2[20], p3[20];

vector<int> p[3];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int input = 0;

	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		p[0].push_back(i);
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}

	for (int i = 0; i < 20; i++) {
		cin >> input;
		p[1].push_back(input);
	}
	for (int i = 0; i < 20; i++) {
		cin >> input;
		p[2].push_back(input);
	}

	do {
		int p1 = 0, p2 = 1;
		int pIdx[3] = { 0, 0, 0 };
		int pWin[3] = { 0, 0, 0 };
		bool p1Wins = false;

		while (true) {
			if (arr[p[p1][pIdx[p1]]][p[p2][pIdx[p2]]] == 0) {
				p1Wins = false;
			}
			else if (arr[p[p1][pIdx[p1]]][p[p2][pIdx[p2]]] == 1) {
				if (p1 < p2) {
					p1Wins = false;
				}
				else {
					p1Wins = true;
				}
			}
			else if (arr[p[p1][pIdx[p1]]][p[p2][pIdx[p2]]] == 2) {
				p1Wins = true;
			}


			pIdx[p1]++;
			pIdx[p2]++;

			if (p1Wins) {
				pWin[p1]++;
			}
			else {
				pWin[p2]++;
			}

			if (pWin[0] == K) {
				cout << 1;
				return 0;
			}
			else if (pWin[1] == K) {
				break;
			}
			else if (pWin[2] == K) {
				break;
			}

			if (pIdx[0] >= N) {
				break;
			}
			else if (pIdx[1] >= 20) {
				break;
			}
			else if (pIdx[2] >= 20) {
				break;
			}

			if (p1 == 0 && p2 == 1) {
				if (p1Wins) {
					p1 = 0;
					p2 = 2;
				}
				else {
					p1 = 1;
					p2 = 2;
				}
			}
			else if (p1 == 1 && p2 == 0) {
				if (p1Wins) {
					p1 = 1;
					p2 = 2;
				}
				else {
					p1 = 0;
					p2 = 2;
				}
			}
			else if (p1 == 0 && p2 == 2) {
				if (p1Wins) {
					p1 = 0;
					p2 = 1;
				}
				else {
					p1 = 2;
					p2 = 1;
				}
			}
			else if (p1 == 2 && p2 == 0) {
				if (p1Wins) {
					p1 = 2;
					p2 = 1;
				}
				else {
					p1 = 0;
					p2 = 1;
				}
			}
			else if (p1 == 1 && p2 == 2) {
				if (p1Wins) {
					p1 = 1;
					p2 = 0;
				}
				else {
					p1 = 2;
					p2 = 0;
				}
			}
			else if (p1 == 2 && p2 == 1) {
				if (p1Wins) {
					p1 = 2;
					p2 = 0;
				}
				else {
					p1 = 1;
					p2 = 0;
				}
			}
		}
	} while (next_permutation(p[0].begin(), p[0].end()));

	cout << 0;

	return 0;
}