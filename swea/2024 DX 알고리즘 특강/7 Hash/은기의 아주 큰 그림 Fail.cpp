#include <iostream>
#include <cstring>
#define MOD 1000000007;

using namespace std;

class i2 {
private:
	long long first, second;
public:
	i2():first(0), second(0){}
	i2(long long val) {
		this->first = val;
		this->second = val;
	}
	i2(long long first, long long second) {
		this->first = first;
		this->second = second;
	}
	i2(const i2& ref) {
		this->first = ref.first;
		this->second = ref.second;
	}

	i2& operator=(long long val) {
		this->first = val;
		this->second = val;
		return *this;
	}
	i2& operator=(const i2& ref) {
		this->first = ref.first;
		this->second = ref.second;
		return *this;
	}

	i2 operator+(const i2& ref) {
		return i2(this->first + ref.first, this->second + ref.second);
	}
	i2& operator+=(const i2& ref) {
		this->first += ref.first;
		this->second += ref.second;
		return *this;
	}
	i2 operator-(const i2& ref) {
		return i2(this->first - ref.first, this->second - ref.second);
	}
	i2& operator-=(const i2& ref) {
		this->first -= ref.first;
		this->second -= ref.second;
		return *this;
	}
	i2 operator*(const i2& ref) {
		return i2(this->first * ref.first, this->second * ref.second);
	}
	i2& operator*=(const i2& ref) {
		this->first *= ref.first;
		this->second *= ref.second;
		return *this;
	}
	i2 operator%(const long long mod) {
		return i2(this->first % mod, this->second % mod);
	}
	i2& operator%=(const long long mod) {
		this->first &= mod;
		this->second &= mod;
		return *this;
	}
	bool operator==(const i2& ref) {
		return ((this->first == ref.first) && (this->second == ref.second));
	}
	bool operator!=(const i2& ref) {
		return ((this->first != ref.first) || (this->second != ref.second));
	}
	bool operator<(const int val) {
		return ((this->first < val) && (this->second < val));
	}
};

static const i2 rS = i2(3, 5), cS = i2(7, 11);

int H, W, N, M;
char student[2000][2001], teacher[2000][2001];
i2 powR[2000], powC[2000];
i2 rowHash[2000], columnHash[2000][2000];

void getHash(i2& sh, i2& th) {
	i2 temp;
	sh = i2(0);
	th = i2(0);
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			temp = i2((student[i][j] == 'o') + 1);
			temp *= powR[H - 1 - i];
			temp %= MOD;
			temp *= powC[W - 1 - j];
			temp %= MOD;
			sh += temp;
			sh %= MOD;

			temp = i2((teacher[i][j] == 'o') + 1);
			temp *= powR[H - 1 - i];
			temp %= MOD;
			temp *= powC[W - 1 - j];
			temp %= MOD;
			th += temp;
			th %= MOD;
			//cout << temp.first << temp.second << '\n';
		}
	}
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T = 0, count = 0;
	i2 answer = 0, hash = 0, increase = 0, decrease = 0, temp = 0, save = 0;
	powR[0] = i2(1, 1);
	powC[0] = i2(1, 1);
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
		for (int i = 0; i < N - H + 1; i++) {
			save = hash;
			for (int j = 0; j < M - W + 1; j++) {
				if (answer == hash) {
					count++;
				}
				if (j == M - W) {
					break;
				}

				decrease = i2(0, 0);
				if (columnHash[i][j] != i2(0, 0)) {
					decrease = columnHash[i][j];
				}
				else if (i == 0) {
					for (int k = 0; k < H; k++) {
						temp = i2((teacher[i + k][j] == 'o') + 1);
						temp *= powR[H - 1 - k];
						temp %= MOD;
						decrease += temp;
						decrease %= MOD;
					}
					columnHash[i][j] = decrease;
				}
				else {
					decrease = columnHash[i - 1][j];
					decrease -= i2((teacher[i - 1][j] == 'o') + 1) * powR[H - 1];
					decrease *= rS;
					decrease += i2((teacher[i + H - 1][j] == 'o') + 1);
					decrease %= MOD;
					columnHash[i][j] = decrease;
				}
				decrease *= powC[W - 1];
				hash -= decrease;
				if (hash < 0) {
					hash += MOD;
				}
				hash *= rS;

				increase = i2(0, 0);
				if (columnHash[i][j + W] != 0) {
					increase = columnHash[i][j + W];
				}
				else if (i == 0) {
					for (int k = 0; k < H; k++) {
						temp = i2((teacher[i + k][j + W] == 'o') + 1);
						temp *= powR[H - 1 - k];
						temp %= MOD;
						increase += temp;
						increase %= MOD;
					}
					columnHash[i][j + W] = increase;
				}
				else {
					increase = columnHash[i - 1][j + W];
					increase -= i2((teacher[i - 1][j + W] == 'o') + 1) * powR[H - 1];
					if (increase < 0) {
						increase += MOD;
					}
					increase *= rS;
					increase += i2((teacher[i + H - 1][j + W] == 'o') + 1);
					increase %= MOD;
					columnHash[i][j + W] = increase;
				}

				increase %= MOD;
				hash += increase;
				hash %= MOD;
			}

			if (i == N - H) {
				break;
			}
			hash = save;
			decrease = i2(0, 0);
			if (rowHash[i] == 0) {
				for (int k = 0; k < W; k++) {
					temp = i2((teacher[i][k] == 'o') + 1);
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
			hash -= decrease;
			if (hash < 0) {
				hash += MOD;
			}

			increase = i2(0, 0);
			for (int k = 0; k < W; k++) {
				temp = i2((teacher[i + H][k] == 'o') + 1);
				temp *= powC[W - 1 - k];
				temp %= MOD;
				increase += temp;
				increase %= MOD;
			}
			increase %= MOD;
			hash += increase;
			hash %= MOD;
		}

		cout << '#' << t << ' ' << count << '\n';
	}
	return 0;
}