#include <utility>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;
using i2 = pair<int, int>;
int nodeNum = 0;

int forwardDistance[601], reverseDistance[601];
vector<i2> forwardGraph[601], reverseGraph[601];
unordered_map<int, int> hashMap;

int dijkstra(int start) {
	int curCost, cur, nextCost, next;
	priority_queue<i2> pq; // cost, node

	for (int i = 1; i <= nodeNum; i++) {
		forwardDistance[i] = 1000000;
		reverseDistance[i] = 1000000;
	}
	forwardDistance[start] = 0;
	reverseDistance[start] = 0;

	pq.push(i2(0, start));
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
	pq.push(i2(0, start));
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

	int totalDistance = 0;
	for (int i = 1; i <= nodeNum; i++) {
		if (i != start) {
			totalDistance += (forwardDistance[i] + reverseDistance[i]);
		}
	}
	return totalDistance;
}

int init(int N, int sCity[], int eCity[], int mCost[]) {
	nodeNum = 0;
	for (int i = 1; i <= 600; i++) {
		forwardGraph[i].clear();
		reverseGraph[i].clear();
	}
	hashMap.clear();

	for (int i = 0; i < N; i++) {
		if (!hashMap.count(sCity[i])) {
			hashMap.insert(i2(sCity[i], ++nodeNum));
		}
		if (!hashMap.count(eCity[i])) {
			hashMap.insert(i2(eCity[i], ++nodeNum));
		}

		forwardGraph[hashMap[sCity[i]]].push_back(i2(hashMap[eCity[i]], mCost[i]));
		reverseGraph[hashMap[eCity[i]]].push_back(i2(hashMap[sCity[i]], mCost[i]));
	}

	return nodeNum;
}

void add(int sCity, int eCity, int mCost) {
	forwardGraph[hashMap[sCity]].push_back(i2(hashMap[eCity], mCost));
	reverseGraph[hashMap[eCity]].push_back(i2(hashMap[sCity], mCost));
	return;
}

int cost(int mHub) {
	return dijkstra(hashMap[mHub]);
}