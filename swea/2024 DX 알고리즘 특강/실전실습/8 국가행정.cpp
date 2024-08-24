#include <queue>
#include <utility>
#include <cstring>
#include <iostream>

using namespace std;
using i2 = pair<int, int>;

int N;

priority_queue<i2> pq; // time, cityNum
int population[10000];
int addedRoadNum[10000];
int timeTree[1 << 15];
int base;

void update(int idx, int val) {
	int parent = (base + idx) / 2;
	timeTree[base + idx] = val;
	while (parent > 0) {
		timeTree[parent] = timeTree[parent * 2] + timeTree[parent * 2 + 1];
		parent /= 2;
	}
}
int query(int node, int qs, int qe, int ts, int te) {
	if (qs <= ts && te <= qe) {
		return timeTree[node];
	}
	if (qe < ts || te < qs) {
		return 0;
	}

	int mid = (ts + te) / 2;
	int a = query(node * 2, qs, qe, ts, mid);
	int b = query(node * 2 + 1, qs, qe, mid + 1, te);
	return a + b;
}

void init(int n, int mPopulation[])
{
	N = n;
	pq = priority_queue<i2>();
	memset(population, 0, sizeof(population));
	memset(addedRoadNum, 0, sizeof(addedRoadNum));
	memset(timeTree, 0, sizeof(timeTree));

	for (int i = 0; i < N; i++) {
		population[i] = mPopulation[i];
		if (i >= 1) {
			pq.push(i2(population[i - 1] + population[i], -(i - 1)));
		}
	}

	base = 1;
	while (base < (N - 1)) {
		base <<= 1;
	}
	for (int i = 0; i < base; i++) {
		if (i < (N - 1)) {
			timeTree[base + i] = (population[i] + population[i + 1]);
		}
		else {
			timeTree[base + i] = 0;
		}
	}
	for (int i = base - 1; i > 0; i--) {
		timeTree[i] = timeTree[i * 2] + timeTree[i * 2 + 1];
	}
	return;
}

int expand(int M)
{
	int ret = 0;
	for (int i = 0; i < M;) {
		int time = pq.top().first;
		int idx = -pq.top().second;
		int check = (population[idx] + population[idx + 1]) / (addedRoadNum[idx] + 1);
		pq.pop();
		if (time == check) {
			addedRoadNum[idx]++;
			ret = (population[idx] + population[idx + 1]) / (addedRoadNum[idx] + 1);
			update(idx, ret);
			pq.push(i2(ret, -idx));
			i++;
		}
	}
	//cout << ret << '\n';
	return ret;
}

int calculate(int mFrom, int mTo)
{
	if (mFrom > mTo) {
		int temp = mFrom;
		mFrom = mTo;
		mTo = temp;
	}
	int ret = query(1, mFrom, mTo - 1, 0, base - 1);
	//cout << ret << '\n';
	return ret;
}

int divide(int mFrom, int mTo, int K)
{
	int ret = 10000000;
	int start = 1, end = 10000000;
	while (start <= end) {
		int mid = (start + end) / 2;
		int count = 0;
		int sum = 0;
		//cout << mid << '\n';
		for (int i = mFrom; i <= mTo;) {
			if (population[i] > mid) {
				count = K + 1;
				break;
			}
			if (sum + population[i] <= mid) {
				sum += population[i];
				i++;
			}
			else {
				//cout << sum << '\n';
				count++;
				sum = 0;
			}
		}
		if (sum > 0) {
			count++;
		}

		if (count <= K) {
			ret = mid < ret ? mid : ret;
			end = mid - 1;
		}
		else {
			start = mid + 1;
		}
	}
	//cout << ret << '\n';
	return ret;
}