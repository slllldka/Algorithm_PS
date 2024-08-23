#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, arr[50][10];
vector<int> order = { 2, 3, 4, 5, 6, 7, 8, 9 };

int startGame();

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 1; j <= 9; j++) {
			cin >> arr[i][j];
		}
	}

	int maxScore = 0, ret;
	do {
		order.insert(order.begin() + 3, 1);
		ret = startGame();
		maxScore = maxScore > ret ? maxScore : ret;
		order.erase(order.begin() + 3);
	} while (next_permutation(order.begin(), order.end()));

	cout << maxScore;

	return 0;
}

int startGame() {
	int score = 0, outCount = 0, currentHitter = 0;
	bool base[3] = { false, false, false};
	for (int i = 0; i < N; i++) {
		outCount = 0;
		base[0] = false;
		base[1] = false;
		base[2] = false;
		while (outCount < 3) {
			if (arr[i][order[currentHitter]] == 0) {
				outCount++;
			}
			else if (arr[i][order[currentHitter]] == 1) {
				for (int j = 2; j >= 0; j--) {
					if (base[j]) {
						base[j] = false;
						if (j >= 2) {
							score++;
						}
						else {
							base[j + 1] = true;
						}
					}
				}
				base[0] = true;
			}
			else if (arr[i][order[currentHitter]] == 2) {
				for (int j = 2; j >= 0; j--) {
					if (base[j]) {
						base[j] = false;
						if (j >= 1) {
							score++;
						}
						else {
							base[j + 2] = true;
						}
					}
				}
				base[1] = true;
			}
			else if (arr[i][order[currentHitter]] == 3) {
				for (int j = 2; j >= 0; j--) {
					if (base[j]) {
						base[j] = false;
						score++;
					}
				}
				base[2] = true;
			}
			else if (arr[i][order[currentHitter]] == 4) {
				int runner = 0;
				for (int j = 0; j < 3; j++) {
					if (base[j]) {
						runner++;
					}
				}
				score += (runner + 1);
				base[0] = false;
				base[1] = false;
				base[2] = false;
			}
			currentHitter = (currentHitter + 1) % 9;
		}
	}

	return score;
}