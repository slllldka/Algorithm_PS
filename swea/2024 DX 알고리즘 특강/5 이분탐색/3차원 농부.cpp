#include <iostream>
#include <algorithm>

using namespace std;

int N, M;
int z_i[500000], z_j[500000];
int minD, num;

int absolute(int n) {
	return n > 0 ? n : -n;
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T;
	int start, end, mid, temp, c1, c2;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N >> M;
		cin >> c1 >> c2;
		for (int i = 0; i < N; i++) {
			cin >> z_i[i];
		}
		for (int i = 0; i < M; i++) {
			cin >> z_j[i];
		}
		sort(z_i, z_i + N);

		minD = 1000000000;
		num = 0;
		for (int i = 0; i < M; i++) {
			start = 0;
			end = N - 1;
			while (start <= end) {
				mid = (start + end) / 2;
				temp = absolute(z_j[i] - z_i[mid]);
				if (temp < minD) {
					minD = temp;
					num = 1;
				}
				else if (temp == minD) {
					num++;
				}

				if (z_i[mid] < z_j[i]) {
					start = mid + 1;
				}
				else {
					end = mid - 1;
				}
			}
		}
		cout << '#' << t << ' ' << (minD + abs(c1 - c2)) << ' ' << num << '\n';
	}
	return 0;
}

/*
절댓값이 0이 되는 방향으로 이분탐색 => 소의 z위치 == 말의 z위치 를 향하여 이분탐색 * 최대500000
*/