#include <cstring>
#include <queue>
#include <climits>
#include <iostream>
#include <vector>

#define MAX_N 350

using namespace std;
using i2 = pair<int, int>;

constexpr int rDir[4] = { 1, 0, -1, 0 };
constexpr int cDir[4] = { 0, 1, 0, -1 };

struct i3 {
	int first = 0, second = 0, third = 0;
	i3() {

	}
	i3(int first, int second, int third) {
		this->first = first;
		this->second = second;
		this->third = third;
	}
};

struct customQueue {
	int f, r;
	i3 data[20000];

	customQueue() {
		f = 0;
		r = 0;
	}

	void push(i3 item) {
		data[r++] = item;
		r %= 20000;
	}
	i3 front() {
		return data[f];
	}
	void pop() {
		f++;
		f %= 20000;
	}
	bool empty() {
		return f == r;
	}
};

bool visit[MAX_N][MAX_N];
int map[MAX_N][MAX_N];
int N;
int range;

int num = 0;
//int dist[200][200];
vector<i2> dist[200];
int dp[200];

void init(int n, int mRange, int mMap[MAX_N][MAX_N])
{
	N = n;
	range = mRange;
	num = 0;
	memcpy(map, mMap, sizeof(map));
	for (int i = 0; i < 200; i++) {
		/*for (int j = 0; j < 200; j++) {
			dist[i][j] = -1;
		}*/
		dist[i].clear();
	}

	return;
}

void add(int mID, int mRow, int mCol)
{
	num++;
	map[mRow][mCol] = mID + 10;
	if (mID == 0) {
		return;
	}

	memset(visit, 0, sizeof(visit));
	int count = 0;
	customQueue q;
	q.push(i3(mRow, mCol, 0));
	visit[mRow][mCol] = true;
	while (!q.empty() && count < mID) {
		int r = q.front().first;
		int c = q.front().second;
		int d = q.front().third;
		q.pop();

		if (d > range) {
			break;
		}

		int newR = 0, newC = 0;
		for (int i = 0; i < 4; i++) {
			newR = r + rDir[i];
			newC = c + cDir[i];
			if (newR >= 0 && newR < N && newC >= 0 && newC < N) {
				if (!visit[newR][newC]) {
					visit[newR][newC] = true;
					int val = map[newR][newC];
					if (val == 0) {
						q.push(i3(newR, newC, d + 1));
					}
					else if (val >= 10) {
						//dist[mID][val - 10] = d + 1;
						//dist[val - 10][mID] = d + 1;
						dist[mID].push_back(i2(val - 10, d + 1));
						dist[val - 10].push_back(i2(mID, d + 1));
						q.push(i3(newR, newC, d + 1));
						count++;
					}
				}
			}
		}
	}

	/*for (int i = 0; i < mID; i++) {
		cout << dist[i][mID] << ' ';
	}
	cout << '\n';*/

	return;
}

int distance(int mFrom, int mTo)
{
	for (int i = 0; i < 200; i++) {
		dp[i] = INT32_MAX;
	}

	priority_queue<i2> pq;
	dp[mFrom] = 0;
	pq.push(i2(0, mFrom));
	while (!pq.empty()) {
		int d = -pq.top().first;
		int node = pq.top().second;
		pq.pop();
		if (node == mTo) {
			//cout << d << '\n';
			return d;
		}

		/*for (int i = 0; i < num; i++) {
			if (i != mFrom && i != node) {
				if (dist[node][i] > 0 && dist[node][i] <= range) {
					if (dp[node] + dist[node][i] < dp[i]) {
						dp[i] = dp[node] + dist[node][i];
						pq.push(i2(-dp[i], i));
					}
				}
			}
		}*/
		for (i2 data : dist[node]) {
			int next = data.first;
			int nextD = data.second;
			if (next != mFrom && nextD <= range) {
				if (dp[node] + nextD < dp[next]) {
					dp[next] = dp[node] + nextD;
					pq.push(i2(-dp[next], next));
				}
			}
		}
	}
	//cout << -1 << '\n';
	return -1;
}