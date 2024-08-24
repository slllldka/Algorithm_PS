#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <climits>

using namespace std;
using i2 = pair<long long, long long>;

int N, M;
long long d[200001], minD[200001];
vector<i2> road[200001];
vector<i2> graph[200001];

long long dijkstra() {
	long long curCost, cur, nextCost, next;
	priority_queue<i2> pq;
	for (int i = 1; i <= N; i++) {
		d[i] = LLONG_MAX;
		minD[i] = LLONG_MAX;
		road[i].clear();
	}
	d[1] = 0;
	minD[1] = 0;

	pq.push(i2(0, 1));
	while (!pq.empty()) {
		curCost = -pq.top().first;
		cur = pq.top().second;
		pq.pop();
		for (i2 nextData : graph[cur]) {
			nextCost = nextData.second;
			next = nextData.first;
			if (curCost + nextCost <= d[next]) {
				d[next] = curCost + nextCost;
				road[cur].push_back(i2(nextCost, next));
				pq.push(i2(-d[next], next));
			}
		}
	}
	
	for (i2 data : road[1]) {
		pq.push(i2(-data.first, data.second));
	}
	while (!pq.empty()) {
		curCost = -pq.top().first;
		cur = pq.top().second;
		pq.pop();
		if (curCost < minD[cur]) {
			minD[cur] = curCost;
			for (i2 data : road[cur]) {
				if (data.first < minD[data.second]) {
					pq.push(i2(-data.first, data.second));
				}
			}
		}
	}
	
	long long totalCost = 0;
	for (int i = 2; i <= N; i++) {
		totalCost += minD[i];
	}
	return totalCost;
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T, s, e, c;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N >> M;
		for (int i = 1; i <= N; i++) {
			graph[i].clear();
		}
		for (int i = 0; i < M; i++) {
			cin >> s >> e >> c;
			graph[s].push_back(i2(e, c));
			graph[e].push_back(i2(s, c));
		}

		cout << '#' << t << ' ' << dijkstra() << '\n';
	}
	return 0;
}