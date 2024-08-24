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

#include <iostream>
#include <utility>
#include <cmath>

using namespace std;
using i2 = pair<int, int>;

int sumArr[142];
i2 allPos[10001];
bool saved[10001];

i2 findPos(int n) {
	/*int start = 1, end = 141, middle;
	i2 ret = i2(0, 0);
	while (start <= end) {
		middle = (start + end) / 2;
		if (n <= sumArr[middle]) {
			if (n > sumArr[middle - 1]) {
				ret = i2(middle, n - sumArr[middle - 1]);
				break;
			}
			else {
				end = middle - 1;
			}
		}
		else {
			if (n <= sumArr[middle + 1]) {
				ret = i2(middle + 1, n - sumArr[middle]);
				break;
			}
			else {
				start = middle + 1;
			}
		}
	}
	return ret;*/

	if (!saved[n]) {
		int x = ceil((-1 + sqrt(1 + 8 * n)) / 2);
		int y = n - sumArr[x - 1];
		allPos[n] = i2(x, y);
		saved[n] = true;
	}
	return allPos[n];
}
int findMinCost(i2 sPos, i2 ePos) {
	if (sPos.first == ePos.first) {
		return (ePos.second - sPos.second);
	}
	else {
		if (ePos.second < sPos.second) {
			return (ePos.first - sPos.first + sPos.second - ePos.second);
		}
		else if (ePos.second == sPos.second) {
			return (ePos.first - sPos.first);
		}
		else {
			if ((ePos.second - sPos.second) <= (ePos.first - sPos.first)) {
				return (ePos.first - sPos.first);
			}
			else {
				return(ePos.second - sPos.second);
			}
		}
	}
}

int main(int argc, char** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int test_case;
	int T;
	int s, e, ans;
	i2 sPos, ePos, temp;
	/*
	   �Ʒ��� freopen �Լ��� input.txt �� read only �������� �� ��,
	   ������ ǥ�� �Է�(Ű����) ��� input.txt ���Ϸκ��� �о���ڴٴ� �ǹ��� �ڵ��Դϴ�.
	   //�������� �ۼ��� �ڵ带 �׽�Ʈ �� ��, ���Ǹ� ���ؼ� input.txt�� �Է��� ������ ��,
	   freopen �Լ��� �̿��ϸ� ���� cin �� ������ �� ǥ�� �Է� ��� ���Ϸκ��� �Է��� �޾ƿ� �� �ֽ��ϴ�.
	   ���� �׽�Ʈ�� ������ ������ �Ʒ� �ּ��� ����� �� �Լ��� ����ϼŵ� �����ϴ�.
	   freopen �Լ��� ����ϱ� ���ؼ��� #include <cstdio>, Ȥ�� #include <stdio.h> �� �ʿ��մϴ�.
	   ��, ä���� ���� �ڵ带 �����Ͻ� ������ �ݵ�� freopen �Լ��� ����ų� �ּ� ó�� �ϼž� �մϴ�.
	*/
	//freopen("input.txt", "r", stdin);
	cin >> T;
	/*
	   ���� ���� �׽�Ʈ ���̽��� �־����Ƿ�, ������ ó���մϴ�.
	*/

	for (int i = 1; i <= 141; i++) {
		sumArr[i] = i * (i + 1) / 2;
	}

	for (test_case = 1; test_case <= T; ++test_case)
	{
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			 �� �κп� �������� �˰��� ������ ���ϴ�.
		 */
		cin >> s >> e;
		sPos = findPos(s);
		ePos = findPos(e);
		if (sPos.first < ePos.first) {
			ans = findMinCost(sPos, ePos);
		}
		else if (sPos.first == ePos.first) {
			if (sPos.second < ePos.second) {
				ans = findMinCost(sPos, ePos);
			}
			else {
				ans = findMinCost(ePos, sPos);
			}
		}
		else {
			ans = findMinCost(ePos, sPos);
		}
		cout << '#' << test_case << ' ' << ans << '\n';
		/////////////////////////////////////////////////////////////////////////////////////////////


	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}