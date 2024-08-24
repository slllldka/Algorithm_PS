#include <unordered_map>
#include <vector>
#include <queue>
#include <cstring>
#include <utility>
#include <iostream>

using namespace std;
using i2 = pair<int, int>;

int num;
unordered_map<int, int> hashMap;
vector<i2> graph[10000];

void init(int mDevice)
{
	num = 0;
	hashMap.clear();
	for (int i = 0; i < 10000; i++) {
		graph[i].clear();
	}
	hashMap[mDevice] = num++;
	return;
}

void connect(int mOldDevice, int mNewDevice, int mLatency)
{
	hashMap[mNewDevice] = num++;
	graph[hashMap[mOldDevice]].push_back(i2(hashMap[mNewDevice], mLatency));
	graph[hashMap[mNewDevice]].push_back(i2(hashMap[mOldDevice], mLatency));
	return;
}

int measure(int mDevice1, int mDevice2)
{
	bool visited[10000];
	int start = hashMap[mDevice1], end = hashMap[mDevice2];
	int cur = 0, latency = 0, ret = 0;
	queue<i2> q;

	memset(visited, false, sizeof(visited));
	q.push(i2(start, 0));
	visited[start] = true;
	while (!q.empty()) {
		cur = q.front().first;
		latency = q.front().second;
		q.pop();
		for (i2 data : graph[cur]) {
			if (!visited[data.first]) {
				if (data.first == end) {
					ret = latency + data.second;
					q = queue<i2>();
					break;
				}
				visited[data.first] = true;
				q.push(i2(data.first, latency + data.second));
			}
		}
	}
	//cout << ret << '\n';
	return ret;
}

int test(int mDevice)
{
	bool visited[10000];
	int mid = hashMap[mDevice];
	int cur = 0, latency = 0;
	int size = 0, maxArr[10000];
	int max1 = 0, max2 = 0, ret = 0;
	memset(visited, false, sizeof(visited));
	memset(maxArr, 0, sizeof(maxArr));

	visited[mid] = true;
	for (i2 data1 : graph[mid]) {
		queue<i2> q;
		q.push(data1);
		visited[data1.first] = true;
		while (!q.empty()) {
			cur = q.front().first;
			latency = q.front().second;
			q.pop();
			maxArr[size] = maxArr[size] > latency ? maxArr[size] : latency;
			for (i2 data2 : graph[cur]) {
				if (!visited[data2.first]) {
					visited[data2.first] = true;
					q.push(i2(data2.first, latency + data2.second));
				}
			}
		}
		size++;
	}

	for (int i = 0; i < size; i++) {
		if (maxArr[i] > max1) {
			if (max1 > max2) {
				max2 = max1;
			}
			max1 = maxArr[i];
		}
		else if (maxArr[i] > max2) {
			max2 = maxArr[i];
		}
	}
	ret = max1 + max2;
	//cout << max1 << ' ' << max2 << ' ' << ret << '\n';
	return ret;
}
