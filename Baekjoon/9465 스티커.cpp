#include <iostream>
#include <utility>

#define max1(a, b) (((a) > (b)) ? (a) : (b))
#define max2(a, b, c) max1(max1(a, b), c)

using namespace std;

typedef pair<int, int> i2;

int T, N;
int score[2][100001];
int maxScore[3][100001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> N;
		for (int j = 0; j < 2; j++) {
			for (int k = 1; k <= N; k++) {
				cin >> score[j][k];
			}
		}

		maxScore[0][1] = score[0][1];
		maxScore[1][1] = score[1][1];
		maxScore[2][1] = 0;

		for (int j = 2; j <= N; j++) {
			maxScore[0][j] = max1(maxScore[1][j - 1], maxScore[2][j - 1]) + score[0][j];
			maxScore[1][j] = max1(maxScore[0][j - 1], maxScore[2][j - 1]) + score[1][j];
			maxScore[2][j] = max2(maxScore[0][j - 1], maxScore[1][j - 1], maxScore[2][j - 1]);
		}

		cout << max2(maxScore[0][N], maxScore[1][N], maxScore[2][N]) << '\n';
	}

	return 0;
}