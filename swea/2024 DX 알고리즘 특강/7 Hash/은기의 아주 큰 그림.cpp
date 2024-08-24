#include <iostream>
#include <cstring>
#define MOD 2147483647;
#define rS 7
#define cS 11

using namespace std;

int H, W, N, M;
char student[2000][2001], teacher[2000][2001];
long long powR[2000], powC[2000];
long long rowHash[2000], columnHash[2000][2000];

void getHash(long long& sh, long long& th) {
	long long temp;
	sh = 0;
	th = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			temp = ((student[i][j] == 'o') + 1);
			temp *= powR[H - 1 - i];
			temp %= MOD;
			temp *= powC[W - 1 - j];
			temp %= MOD;
			sh += temp;
			sh %= MOD;

			temp = ((teacher[i][j] == 'o') + 1);
			temp *= powR[H - 1 - i];
			temp %= MOD;
			temp *= powC[W - 1 - j];
			temp %= MOD;
			th += temp;
			th %= MOD;
		}
	}
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T = 0, count = 0;
	long long answer = 0, hash = 0, increase = 0, decrease = 0, temp = 0, save = 0;
	powR[0] = 1;
	powC[0] = 1;
	for (int i = 1; i < 2000; i++) {
		powR[i] = (powR[i - 1] * rS) % MOD;
		powC[i] = (powC[i - 1] * cS) % MOD;
	}


	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> H >> W >> N >> M;
		for (int i = 0; i < H; i++) {
			cin >> student[i];
		}
		for (int i = 0; i < N; i++) {
			cin >> teacher[i];
		}

		memset(rowHash, 0, sizeof(rowHash));
		memset(columnHash, 0, sizeof(columnHash));

		count = 0;
		getHash(answer, hash);
		//cout << answer << '\n';
		for (int i = 0; i < N - H + 1; i++) {
			save = hash;
			for (int j = 0; j < M - W + 1; j++) {
				//cout << hash << '\n';
				if (answer == hash) {
					count++;
				}
				if (j == M - W) {
					break;
				}

				decrease = 0;
				if (columnHash[i][j] > 0) {
					decrease = columnHash[i][j];
				}
				else if (i == 0) {
					for (int k = 0; k < H; k++) {
						temp = ((teacher[i + k][j] == 'o') + 1);
						temp *= powR[H - 1 - k];
						temp %= MOD;
						decrease += temp;
						decrease %= MOD;
					}
					columnHash[i][j] = decrease;
				}
				else {
					decrease = columnHash[i - 1][j];
					decrease -= ((teacher[i - 1][j] == 'o') + 1) * powR[H - 1];
					if (decrease < 0) {
						decrease += MOD;
					}
					decrease *= rS;
					decrease %= MOD;
					decrease += ((teacher[i + H - 1][j] == 'o') + 1);
					decrease %= MOD;
					columnHash[i][j] = decrease;
				}

				decrease *= powC[W - 1];
				decrease %= MOD;

				hash -= decrease;
				if (hash < 0) {
					hash += MOD;
				}
				hash *= cS;

				increase = 0;
				if (columnHash[i][j + W] > 0) {
					increase = columnHash[i][j + W];
				}
				else if (i == 0) {
					for (int k = 0; k < H; k++) {
						temp = ((teacher[i + k][j + W] == 'o') + 1);
						temp *= powR[H - 1 - k];
						temp %= MOD;
						increase += temp;
						increase %= MOD;
					}
					columnHash[i][j + W] = increase;
				}
				else {
					increase = columnHash[i - 1][j + W];
					increase -= ((teacher[i - 1][j + W] == 'o') + 1) * powR[H - 1];
					if (increase < 0) {
						increase += MOD;
					}
					increase *= rS;
					increase %= MOD;
					increase += ((teacher[i + H - 1][j + W] == 'o') + 1);
					increase %= MOD;
					columnHash[i][j + W] = increase;
				}

				hash += increase;
				hash %= MOD;
			}

			if (i == N - H) {
				break;
			}
			hash = save;
			decrease = 0;
			if (rowHash[i] == 0) {
				for (int k = 0; k < W; k++) {
					temp = ((teacher[i][k] == 'o') + 1);
					temp *= powC[W - 1 - k];
					temp %= MOD;
					decrease += temp;
					decrease %= MOD;
				}
				rowHash[i] = decrease;
			}
			else {
				decrease = rowHash[i];
			}

			decrease *= powR[H - 1];
			decrease %= MOD;
			hash -= decrease;
			if (hash < 0) {
				hash += MOD;
			}
			hash *= rS;

			increase = 0;
			for (int k = 0; k < W; k++) {
				temp = ((teacher[i + H][k] == 'o') + 1);
				temp *= powC[W - 1 - k];
				temp %= MOD;
				increase += temp;
				increase %= MOD;
			}
			hash += increase;
			hash %= MOD;
		}

		cout << '#' << t << ' ' << count << '\n';
	}
	return 0;
}