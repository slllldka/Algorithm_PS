#include <iostream>
#define max(a, b) (((a) > (b)) ? (a) : (b))

using namespace std;

int N, triangle[125250];

int getLineStartIdx(int);
void calculateMaxSum(int, int);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < i; j++) {
			cin >> triangle[getLineStartIdx(i) + j];
		}
	}

	for (int i = 2; i <= N; i++) {
		for (int j = 0; j < i; j++) {
			calculateMaxSum(i, j);
		}
	}


	int result = 0, lineStartIdx = getLineStartIdx(N);
	for (int i = 0; i < N; i++) {
		result = max(result, triangle[lineStartIdx + i]);
	}
	cout << result;

	return 0;
}

int getLineStartIdx(int line) {
	return (line - 1) * line / 2;
}

void calculateMaxSum(int line, int idx) {
	int prevLineStartIdx = getLineStartIdx(line - 1);
	int curLineStartIdx = getLineStartIdx(line);
	if (idx == 0) {
		triangle[curLineStartIdx + idx] += triangle[prevLineStartIdx];
	}
	else if (idx == (line - 1)) {
		triangle[curLineStartIdx + idx] += triangle[prevLineStartIdx + (line - 2)];
	}
	else {
		triangle[curLineStartIdx + idx] +=
			max(triangle[prevLineStartIdx + idx - 1], triangle[prevLineStartIdx + idx]);
	}
}