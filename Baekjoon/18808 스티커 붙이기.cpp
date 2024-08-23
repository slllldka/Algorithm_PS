#include <iostream>
#include <utility>

using namespace std;

typedef pair<int, int> i2;

int N, M, K;
int laptop[40][40];
int stickers[100][10][10];
i2 stickerSize[100];

void checkSticker(int idx) {
	int sticker[10][10];
	int R = stickerSize[idx].first, C = stickerSize[idx].second;
	
	//0
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			sticker[i][j] = stickers[idx][i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (R > N - i) {
				i = N;
				break;
			}
			else if (C > M - j) {
				break;
			}
			else {
				bool canPut = true;
				for (int a = 0; a < R; a++) {
					for (int b = 0; b < C; b++) {
						if (sticker[a][b] == 1) {
							if (laptop[i + a][j + b] == 1) {
								a = R;
								canPut = false;
								break;
							}
						}
					}
				}

				if (canPut) {
					for (int a = 0; a < R; a++) {
						for (int b = 0; b < C; b++) {
							if (sticker[a][b] == 1) {
								laptop[i + a][j + b] = sticker[a][b];
							}
						}
					}

					//cout << i << j << '\n';
					return;
				}

			}
		}
	}

	//90
	for (int i = 0; i < C; i++) {
		for (int j = 0; j < R; j++) {
			sticker[i][R - 1 - j] = stickers[idx][j][i];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (C > N - i) {
				i = N;
				break;
			}
			else if (R > M - j) {
				break;
			}
			else {
				bool canPut = true;
				for (int a = 0; a < C; a++) {
					for (int b = 0; b < R; b++) {
						if (sticker[a][b] == 1) {
							if (laptop[i + a][j + b] == 1) {
								a = C;
								canPut = false;
								break;
							}
						}
					}
				}

				if (canPut) {
					for (int a = 0; a < C; a++) {
						for (int b = 0; b < R; b++) {
							if (sticker[a][b] == 1) {
								laptop[i + a][j + b] = sticker[a][b];
							}
						}
					}

					//cout << i << j << '\n';
					return;
				}

			}
		}
	}

	//180
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			sticker[i][j] = stickers[idx][R - 1 - i][C - 1 - j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (R > N - i) {
				i = N;
				break;
			}
			else if (C > M - j) {
				break;
			}
			else {
				bool canPut = true;
				for (int a = 0; a < R; a++) {
					for (int b = 0; b < C; b++) {
						if (sticker[a][b] == 1) {
							if (laptop[i + a][j + b] == 1) {
								a = R;
								canPut = false;
								break;
							}
						}
					}
				}

				if (canPut) {
					for (int a = 0; a < R; a++) {
						for (int b = 0; b < C; b++) {
							if (sticker[a][b] == 1) {
								laptop[i + a][j + b] = sticker[a][b];
							}
						}
					}

					//cout << i << j << '\n';
					return;
				}

			}
		}
	}

	//270
	for (int i = 0; i < C; i++) {
		for (int j = 0; j < R; j++) {
			sticker[C - 1 - i][j] = stickers[idx][j][i];
		}
	}


	/*for (int i = 0; i < C; i++) {
		for (int j = 0; j < R; j++) {
			cout << sticker[i][j];
		}
		cout << '\n';
	}
	cout << '\n';*/

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (C > N - i) {
				i = N;
				break;
			}
			else if (R > M - j) {
				break;
			}
			else {
				bool canPut = true;
				for (int a = 0; a < C; a++) {
					for (int b = 0; b < R; b++) {
						if (sticker[a][b] == 1) {
							if (laptop[i + a][j + b] == 1) {
								a = C;
								canPut = false;
								break;
							}
						}
					}
				}

				if (canPut) {
					for (int a = 0; a < C; a++) {
						for (int b = 0; b < R; b++) {
							if (sticker[a][b] == 1) {
								laptop[i + a][j + b] = sticker[a][b];
							}
						}
					}

					//cout << i << j << '\n';
					return;
				}

			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> N >> M >> K;

	int r, c;
	for (int i = 0; i < K; i++) {
		cin >> r >> c;
		stickerSize[i] = i2(r, c);
		for (int j = 0; j < r; j++) {
			for (int k = 0; k < c; k++) {
				cin >> stickers[i][j][k];
			}
		}
	}

	for (int i = 0; i < K; i++) {
		checkSticker(i);
		/*for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cout << laptop[i][j];
			}
			cout << '\n';
		}
		cout << '\n';*/
	}


	int sum = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (laptop[i][j] == 1) {
				sum++;
			}
		}
	}

	cout << sum;

	return 0;
}