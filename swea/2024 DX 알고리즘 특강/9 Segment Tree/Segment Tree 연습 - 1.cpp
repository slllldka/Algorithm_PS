#include <iostream>
#include <climits>
using namespace std;

int n, q;
int arr[100000];
int maxTree[400000], minTree[400000];

int buildMaxTree(int node, int start, int end) {
	if (start == end) {
		return (maxTree[node] = arr[start]);
	}
	int mid = (start + end) / 2;
	int a = buildMaxTree(node * 2, start, mid);
	int b = buildMaxTree(node * 2 + 1, mid + 1, end);
	return (maxTree[node] = a > b ? a : b);
}
int queryMaxTree(int node, int ts, int te, int qs, int qe) {
	if (ts >= qs && te <= qe) {
		return maxTree[node];
	}
	else if (qs > te || qe < ts) {
		return -1;
	}
	int mid = (ts + te) / 2;
	int a = queryMaxTree(node * 2, ts, mid, qs, qe);
	int b = queryMaxTree(node * 2 + 1, mid + 1, te, qs, qe);
	return a > b ? a : b;
}
int updateMaxTree(int node, int start, int end, int idx, int x) {
	if (idx >= start && idx <= end) {
		if (start == end) {
			return (maxTree[node] = x);
		}
		else {
			int mid = (start + end) / 2;
			int a = updateMaxTree(node * 2, start, mid, idx, x);
			int b = updateMaxTree(node * 2 + 1, mid + 1, end, idx, x);
			return (maxTree[node] = max(a, b));
		}
	}
	return maxTree[node];
}

int buildMinTree(int node, int start, int end) {
	if (start == end) {
		return (minTree[node] = arr[start]);
	}
	int mid = (start + end) / 2;
	int a = buildMinTree(node * 2, start, mid);
	int b = buildMinTree(node * 2 + 1, mid + 1, end);
	return (minTree[node] = a < b ? a : b);
}
int queryMinTree(int node, int ts, int te, int qs, int qe) {
	if (ts >= qs && te <= qe) {
		return minTree[node];
	}
	else if (qs > te || qe < ts) {
		return INT32_MAX;
	}
	int mid = (ts + te) / 2;
	int a = queryMinTree(node * 2, ts, mid, qs, qe);
	int b = queryMinTree(node * 2 + 1, mid + 1, te, qs, qe);
	return a < b ? a : b;
}
int updateMinTree(int node, int start, int end, int idx, int x) {
	if (idx >= start && idx <= end) {
		if (start == end) {
			return (minTree[node] = x);
		}
		else {
			int mid = (start + end) / 2;
			int a = updateMinTree(node * 2, start, mid, idx, x);
			int b = updateMinTree(node * 2 + 1, mid + 1, end, idx, x);
			return (minTree[node] = min(a, b));
		}
	}
	return minTree[node];
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T;
	int type, a, b;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> n >> q;
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
		}

		buildMaxTree(1, 0, n - 1);
		buildMinTree(1, 0, n - 1);

		cout << '#' << t << ' ';
		for (int i = 0; i < q; i++) {
			cin >> type >> a >> b;
			if (type == 0) {
				updateMaxTree(1, 0, n - 1, a, b);
				updateMinTree(1, 0, n - 1, a, b);
			}
			else if (type == 1) {
				cout << queryMaxTree(1, 0, n - 1, a, b - 1) - queryMinTree(1, 0, n - 1, a, b - 1) << ' ';
			}
		}
		cout << '\n';
	}
	return 0;
}