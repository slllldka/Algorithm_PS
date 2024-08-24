#include <iostream>
using namespace std;

int n, q, evenN, oddN;
long long evenArr[50000], oddArr[50000];
long long evenTree[200000], oddTree[200000];

long long buildTree(long long* tree, long long* arr, int node, int start, int end) {
	if (start == end) {
		return (tree[node] = arr[start]);
	}
	int mid = (start + end) / 2;
	long long a = buildTree(tree, arr, node * 2, start, mid);
	long long b = buildTree(tree, arr, node * 2 + 1, mid + 1, end);
	return (tree[node] = (a + b));
}
long long queryTree(long long* tree, int node, int ts, int te, int qs, int qe) {
	if (ts >= qs && te <= qe) {
		return tree[node];
	}
	else if (qs > te || qe < ts) {
		return 0;
	}
	int mid = (ts + te) / 2;
	long long a = queryTree(tree, node * 2, ts, mid, qs, qe);
	long long b = queryTree(tree, node * 2 + 1, mid + 1, te, qs, qe);
	return a + b;
}
long long updateTree(long long* tree, int node, int start, int end, int idx, int x) {
	if (idx >= start && idx <= end) {
		if (start == end) {
			return (tree[node] = x);
		}
		else {
			int mid = (start + end) / 2;
			long long a = updateTree(tree, node * 2, start, mid, idx, x);
			long long b = updateTree(tree, node * 2 + 1, mid + 1, end, idx, x);
			return (tree[node] = (a + b));
		}
	}
	return tree[node];
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T;
	int type, a, b;
	long long result = 0;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		evenN = 0;
		oddN = 0;
		cin >> n >> q;
		for (int i = 0; i < n; i++) {
			if (i % 2 == 0) {
				cin >> evenArr[i / 2];
				evenN++;
			}
			else {
				cin >> oddArr[i / 2];
				oddN++;
			}
		}

		buildTree(evenTree, evenArr, 1, 0, evenN - 1);
		buildTree(oddTree, oddArr, 1, 0, oddN - 1);

		cout << '#' << t << ' ';
		for (int i = 0; i < q; i++) {
			cin >> type >> a >> b;
			if (type == 0) {
				if (a % 2 == 0) {
					updateTree(evenTree, 1, 0, evenN - 1, a / 2, b);
				}
				else {
					updateTree(oddTree, 1, 0, oddN - 1, a / 2, b);
				}
			}
			else if (type == 1) {
				b--;
				int evenStart, evenEnd, oddStart, oddEnd;
				if (a % 2 == 0) {
					evenStart = a / 2;
					oddStart = a / 2;
				}
				else {
					evenStart = a / 2 + 1;
					oddStart = a / 2;
				}
				if (b % 2 == 0) {
					evenEnd = b / 2;
					oddEnd = b / 2 - 1;
				}
				else {
					evenEnd = b / 2;
					oddEnd = b / 2;
				}
				if (evenStart <= oddStart) {
					result = queryTree(evenTree, 1, 0, evenN - 1, evenStart, evenEnd)
						- queryTree(oddTree, 1, 0, oddN - 1, oddStart, oddEnd);
				}
				else {
					result = queryTree(oddTree, 1, 0, oddN - 1, oddStart, oddEnd)
						- queryTree(evenTree, 1, 0, evenN - 1, evenStart, evenEnd);
				}
				cout << result << ' ';
			}
		}
		cout << '\n';
	}
	return 0;
}