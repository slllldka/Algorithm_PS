#include <iostream>
#include <cstring>
#include <queue>
#include <tuple>

using namespace std;

typedef tuple<int, int, int, bool> Data;

int N, M;
char Map[1000][1001];
int BrokenCost[1000][1000];
int UnbrokenCost[1000][1000];
int ND[] = { 1, -1, 0, 0 };
int MD[] = { 0, 0, 1 ,-1 };

int Find();
void Push(queue<Data>&, Data&);

int main() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> Map[i];
	}

	cout << Find();
	return 0;
}

int Find() {
	Data temp;
	queue<Data> q;
	UnbrokenCost[0][0] = 1;
	q.push(Data(0, 0, 1, false));

	while (!q.empty()) {
		temp = q.front();
		q.pop();
		if ((get<0>(temp) == N - 1) && (get<1>(temp) == M - 1)) {
			return get<2>(temp);
		}
		Push(q, temp);
	}

	return -1;
}

void Push(queue<Data>& ref, Data& temp) {
	int _n = get<0>(temp);
	int _m = get<1>(temp);
	int _cost = get<2>(temp);
	bool _broken = get<3>(temp);

	for (int i = 0; i < 4; i++) {
		if ((_n + ND[i] >= 0) && (_n + ND[i] < N) && (_m + MD[i] >= 0) && (_m + MD[i] < M)) {
			//벽이 아닌 곳으로 이동
			if (Map[_n + ND[i]][_m + MD[i]] == '0') {
				//벽을 이미 부숨
				if (_broken) {
					if (BrokenCost[_n + ND[i]][_m + MD[i]] > 0) {
						if (BrokenCost[_n + ND[i]][_m + MD[i]] > _cost + 1) {
							BrokenCost[_n + ND[i]][_m + MD[i]] = _cost + 1;
							ref.push(Data(_n + ND[i], _m + MD[i], _cost + 1, true));
						}
					}
					else {
						BrokenCost[_n + ND[i]][_m + MD[i]] = _cost + 1;
						ref.push(Data(_n + ND[i], _m + MD[i], _cost + 1, true));
					}
				}
				//벽을 아직 안부숨
				else {
					if (UnbrokenCost[_n + ND[i]][_m + MD[i]] > 0) {
						if (UnbrokenCost[_n + ND[i]][_m + MD[i]] > _cost + 1) {
							UnbrokenCost[_n + ND[i]][_m + MD[i]] = _cost + 1;
							ref.push(Data(_n + ND[i], _m + MD[i], _cost + 1, false));
						}
					}
					else {
						UnbrokenCost[_n + ND[i]][_m + MD[i]] = _cost + 1;
						ref.push(Data(_n + ND[i], _m + MD[i], _cost + 1, false));
					}
				}
			}
			//벽으로 이동
			else if (Map[_n + ND[i]][_m + MD[i]] == '1') {
				if (!_broken) {
					if (BrokenCost[_n + ND[i]][_m + MD[i]] > 0) {
						if (BrokenCost[_n + ND[i]][_m + MD[i]] > _cost + 1) {
							BrokenCost[_n + ND[i]][_m + MD[i]] = _cost + 1;
							ref.push(Data(_n + ND[i], _m + MD[i], _cost + 1, true));
						}
					}
					else {
						BrokenCost[_n + ND[i]][_m + MD[i]] = _cost + 1;
						ref.push(Data(_n + ND[i], _m + MD[i], _cost + 1, true));
					}
				}
			}
		}
	}
}