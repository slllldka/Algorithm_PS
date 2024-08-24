#include <iostream>
#include <vector>
int n, m;
int timeArr[100000];
int timeTree[400000];
std::vector<int> segmentIdxes[1000];

int buildTree(int node, int start, int end) {
	if (start == end) {
		return timeTree[node] = timeArr[start];
	}
	int mid = (start + end) / 2;
	int a = buildTree(node * 2, start, mid);
	int b = buildTree(node * 2 + 1, mid + 1, end);
	return (timeTree[node] = (a + b));
}

int updateTreeByValue(int node, int start, int end, int idx, int value) {
	if (idx >= start && idx <= end) {
		if (start == end) {
			timeArr[start] = value;
			return (timeTree[node] = timeArr[start]);
		}
		int mid = (start + end) / 2;
		int a = updateTreeByValue(node * 2, start, mid, idx, value);
		int b = updateTreeByValue(node * 2 + 1, mid + 1, end, idx, value);
		return (timeTree[node] = (a + b));
	}
	return timeTree[node];
}
int updateTreeByRatio(int node, int start, int end, int idx, int ratio) {
	if (idx >= start && idx <= end) {
		if (start == end) {
			timeArr[start] *= ratio;
			timeArr[start] /= 256;
			return (timeTree[node] = timeArr[start]);
		}
		int mid = (start + end) / 2;
		int a = updateTreeByRatio(node * 2, start, mid, idx, ratio);
		int b = updateTreeByRatio(node * 2 + 1, mid + 1, end, idx, ratio);
		return (timeTree[node] = (a + b));
	}
	return timeTree[node];
}
int query(int node, int ts, int te, int qs, int qe) {
	if (qs > te || qe < ts) {
		return 0;
	}
	else if (ts >= qs && te <= qe) {
		return timeTree[node];
	}
	else {
		int mid = (ts + te) / 2;
		int a = query(node * 2, ts, mid, qs, qe);
		int b = query(node * 2 + 1, mid + 1, te, qs, qe);
		return a + b;
	}
}

void init(int N, int M, int mType[], int mTime[])
{
	//std::cout << "is\n";
	n = N;
	m = M;
	for (int i = 0; i < M; i++) {
		segmentIdxes[i].clear();
	}
	for (int i = 0; i < N - 1; i++) {
		segmentIdxes[mType[i]].push_back(i);
		timeArr[i] = mTime[i];
	}
	buildTree(1, 0, n - 2);
	//std::cout << "ie\n";
}

void destroy()
{

}

void update(int mID, int mNewTime)
{
	//std::cout << "us\n";
	updateTreeByValue(1, 0, n - 2, mID, mNewTime);
	//std::cout << "ue\n";
}

int updateByType(int mTypeID, int mRatio256)
{
	//std::cout << "uts\n";
	int result = 0;
	for (int idx : segmentIdxes[mTypeID]) {
		updateTreeByRatio(1, 0, n - 2, idx, mRatio256);
		result += timeArr[idx];
	}
	//std::cout << "ute\n";
	return result;
}

int calculate(int mA, int mB)
{
	//std::cout << "cs\n";
	int start = mA < mB ? mA : mB;
	int end = mA > mB ? mA : mB;
	/*for (int i = 0; i < n - 1; i++) {
		std::cout << timeArr[i] << ' ';
	}
	std::cout << '\n';*/
	int result = query(1, 0, n - 2, start, end - 1);
	//std::cout << result << '\n';
	//std::cout << "ce\n";
	return result;
}