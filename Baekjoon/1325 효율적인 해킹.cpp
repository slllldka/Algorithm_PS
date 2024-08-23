#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstring>

using namespace std;

using pii = pair<int, int>;

int N, M;

vector<int> graph[10001];
bool visit[10001];
priority_queue<pii> pq;

void resetVisit() {
	memset(visit, false, sizeof(visit));
}

int bfs(int num) {
	int ret = 0;
	queue<int> q;
	q.push(num);
	visit[num] = true;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		ret++;

		for (int next : graph[cur]) {
			if (!visit[next]) {
				q.push(next);
				visit[next] = true;
			}
		}
	}

	return ret;
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int s = 0, e = 0;
		cin >> e >> s;
		graph[s].push_back(e);
	}

	for (int i = 1; i <= N; i++) {
		pq.push(pii(bfs(i), -i));
		resetVisit();
	}

	int ans = pq.top().first;
	while (!pq.empty() && pq.top().first == ans) {
		cout << -pq.top().second << ' ';
		pq.pop();
	}

	return 0;
}