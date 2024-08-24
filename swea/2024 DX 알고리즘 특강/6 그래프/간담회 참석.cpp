#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <climits>

using namespace std;
using i2 = pair<int, int>; //node, cost

int N, M, X;
int forwardDistance[50001], reverseDistance[50001];
vector<i2> forwardGraph[50001], reverseGraph[50001];

int dijkstra() {
	int curCost, cur, nextCost, next;
	priority_queue<i2> pq; // cost, node
	pq.push(i2(0, X));
	while (!pq.empty()) {
		curCost = -pq.top().first;
		cur = pq.top().second;
		pq.pop();
		for (i2 nextData : forwardGraph[cur]) {
			nextCost = nextData.second;
			next = nextData.first;
			if (curCost + nextCost < forwardDistance[next]) {
				forwardDistance[next] = curCost + nextCost;
				pq.push(i2(-forwardDistance[next], next));
			}
		}
	}
	
	pq = priority_queue<i2>();
	pq.push(i2(0, X));
	while (!pq.empty()) {
		curCost = -pq.top().first;
		cur = pq.top().second;
		pq.pop();
		for (i2 nextData : reverseGraph[cur]) {
			nextCost = nextData.second;
			next = nextData.first;
			if (curCost + nextCost < reverseDistance[next]) {
				reverseDistance[next] = curCost + nextCost;
				pq.push(i2(-reverseDistance[next], next));
			}
		}
	}
	
	int maxD = 0;
	int d;
	for (int i = 1; i <= N; i++) {
		d = forwardDistance[i] + reverseDistance[i];
		maxD = maxD > d ? maxD : d;
	}
	return maxD;
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T, s, e, t;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> M >> X;
		for (int i = 1; i <= N; i++) {
			forwardGraph[i].clear();
			reverseGraph[i].clear();
			forwardDistance[i] = 50000001;
			reverseDistance[i] = 50000001;
		}
		forwardDistance[X] = 0;
		reverseDistance[X] = 0;

		for (int i = 0; i < M; i++) {
			cin >> s >> e >> t;
			forwardGraph[s].push_back(i2(e, t));
			reverseGraph[e].push_back(i2(s, t));
		}
		cout << '#' << tc << ' ' << dijkstra() << '\n';
	}
	return 0;
}