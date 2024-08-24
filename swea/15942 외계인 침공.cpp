/////////////////////////////////////////////////////////////////////////////////////////////
// �⺻ �����ڵ�� ���� �����ص� ���� �����ϴ�. ��, ����� ���� ����
// �Ʒ� ǥ�� ����� ���� �ʿ�� �����ϼ���.
// ǥ�� �Է� ����
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            // int ���� 1�� �Է¹޴� ����
// cin >> b >> c;                       // float ���� 2�� �Է¹޴� ���� 
// cin >> d >> e >> f;                  // double ���� 3�� �Է¹޴� ����
// cin >> g;                            // char ���� 1�� �Է¹޴� ����
// cin >> var;                          // ���ڿ� 1�� �Է¹޴� ����
// cin >> AB;                           // long long ���� 1�� �Է¹޴� ����
/////////////////////////////////////////////////////////////////////////////////////////////
// ǥ�� ��� ����
// int a = 0;                            
// float b = 1.0, c = 2.0;               
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           // int ���� 1�� ����ϴ� ����
// cout << b << " " << c;               // float ���� 2�� ����ϴ� ����
// cout << d << " " << e << " " << f;   // double ���� 3�� ����ϴ� ����
// cout << g;                           // char ���� 1�� ����ϴ� ����
// cout << var;                         // ���ڿ� 1�� ����ϴ� ����
// cout << AB;                          // long long ���� 1�� ����ϴ� ����
/////////////////////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int n;
long long k, sum;
vector<int> arr(200000);
int visit[200000];

int solve();
int binarySearch(int, int, long long);
int findNotVisited(int);

int main(int argc, char** argv)
{
	int test_case;
	int T;
	/*
	   �Ʒ��� freopen �Լ��� input.txt �� read only �������� �� ��,
	   ������ ǥ�� �Է�(Ű����) ��� input.txt ���Ϸκ��� �о���ڴٴ� �ǹ��� �ڵ��Դϴ�.
	   //�������� �ۼ��� �ڵ带 �׽�Ʈ �� ��, ���Ǹ� ���ؼ� input.txt�� �Է��� ������ ��,
	   freopen �Լ��� �̿��ϸ� ���� cin �� ������ �� ǥ�� �Է� ��� ���Ϸκ��� �Է��� �޾ƿ� �� �ֽ��ϴ�.
	   ���� �׽�Ʈ�� ������ ������ �Ʒ� �ּ��� ����� �� �Լ��� ����ϼŵ� �����ϴ�.
	   freopen �Լ��� ����ϱ� ���ؼ��� #include <cstdio>, Ȥ�� #include <stdio.h> �� �ʿ��մϴ�.
	   ��, ä���� ���� �ڵ带 �����Ͻ� ������ �ݵ�� freopen �Լ��� ����ų� �ּ� ó�� �ϼž� �մϴ�.
	*/
	freopen("input.txt", "r", stdin);
	cin >> T;
	/*
	   ���� ���� �׽�Ʈ ���̽��� �־����Ƿ�, ������ ó���մϴ�.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int input = 0;
		cin >> n >> k;
		sum = 0;
		for (int i = 0; i < n; i++) {
			cin >> arr[i];
			sum += arr[i];
			visit[i] = i;
		}
		sort(arr.begin(), arr.begin() + n);

		cout << '#' << test_case << ' ' << solve() << endl;
	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}

int solve() {
	int startIdx = 0, endIdx = n - 1;
	int targetIdx = 0, targetNum = -1;
	int result = 0;

	while (true) {
		targetIdx = findNotVisited(binarySearch(startIdx, endIdx, k));
		if (targetIdx == -1) {
			return -1;
		}

		targetNum = arr[targetIdx];

		if (targetIdx == endIdx) {
			while (k < sum) {
				k += targetNum;
				result++;
				sum -= targetNum;

				visit[targetIdx] = (targetIdx = findNotVisited(targetIdx - 1));
				if (targetIdx == -1) {
					return -1;
				}
				targetNum = arr[targetIdx];
			}
			return result;
		}
		else {
			k += targetNum;
			result++;
			sum -= targetNum;
			visit[targetIdx] = findNotVisited(targetIdx - 1);
		}
	}
}

int binarySearch(int startIdx, int endIdx, long long num) {
	if (startIdx == endIdx) {
		if (arr[startIdx] <= num) {
			return startIdx;
		}
		else {
			return -1;
		}
	}

	int middleIdx = (startIdx + endIdx) / 2;
	if (arr[middleIdx] > num) {
		if (arr[middleIdx - 1] <= num) {
			return middleIdx - 1;
		}
		else {
			return binarySearch(startIdx, middleIdx - 1, num);
		}
	}
	else if (arr[middleIdx] < num) {
		if (arr[middleIdx + 1] > num) {
			return middleIdx;
		}
		else {
			return binarySearch(middleIdx + 1, endIdx, num);
		}
	}
	else {
		int result = middleIdx;
		while (arr[result] == arr[result + 1]) {
			result++;
		}

		return result;
	}
}

int findNotVisited(int idx) {
	if (idx == -1) {
		return -1;
	}
	else if (visit[idx] == idx) {
		return idx;
	}
	else {
		return (visit[idx] = findNotVisited(visit[idx]));
	}
}