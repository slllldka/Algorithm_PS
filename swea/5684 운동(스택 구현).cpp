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

#include<iostream>

#define min(a, b) (((a) < (b)) ? (a) : (b))

constexpr int inf = 100000, MAX_SIZE = 400;

using namespace std;

int weight[401][401];
int result[401][401];
bool visit[401];

class pii {
public:
	int first = 0, second = 0;
	
	pii(){}
	pii(int _first, int _second): first(_first), second(_second){}
};

template <typename T>
class stackk {
private:
	T arr[MAX_SIZE];
	int topIdx = -1;
public:
	stackk(){}

	bool empty() {
		return (topIdx == -1);
	}
	void push(T item) {
		arr[++topIdx] = item;
	}
	void pop() {
		topIdx--;
	}
	T& top() {
		return arr[topIdx];
	}
	

};

int main(int argc, char** argv)
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int test_case;
	int T;

	int N = 0, M = 0;
	int s = 0, e = 0, c = 0;
	int minCycle = inf;
	int tempCycle = 0;
	int start = 0, end = 0;
	
	bool canMove = false;

	stackk<pii> stackNode;

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
	for (test_case = 1; test_case <= T; ++test_case)
	{

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			 �� �κп� �������� �˰��� ������ ���ϴ�.
		 */

		cin >> N >> M;
		
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				weight[i][j] = inf;
				result[i][j] = inf;
			}
		}

		for (int i = 0; i < M; i++) {
			cin >> s >> e >> c;
			weight[s][e] = c;
		}

		//floyd-warshall
		/*
		for (int j = 1; j <= N; j++) {
			for (int i = 1; i <= N; i++) {
				if (result[i][j] == inf) {
					result[i][j] = weight[i][j];
				}
				for (int k = 1; k <= N; k++) {
					if (result[j][k] == inf) {
						result[i][j] = weight[i][j];
					}

					if (i == j && j == k) {
						result[i][k] = weight[i][k];
					}
					else if (i != j && j != k) {
						result[i][k] = min(result[i][k], result[i][j] + result[j][k]);
					}
				}
			}
		}
		
		minCycle = inf;
		for (int i = 1; i <= N; i++) {
			minCycle = min(minCycle, result[i][i]);
		}*/

		//DFS
		minCycle = inf;
		for (int i = 1; i <= N; i++) {
			visit[i] = false;
		}

		for (int i = 1; i <= N; i++) {
			stackNode.push(pii(i, 0));
			visit[i] = true;
			tempCycle = 0;
			while (!stackNode.empty()) {
				start = stackNode.top().first;
				canMove = false;

				if (weight[start][i] != inf) {
					minCycle = min(minCycle, tempCycle + weight[start][i]);
				}
				else {
					for (int j = stackNode.top().second + 1; j <= N; j++) {
						if (!visit[j]) {
							if (tempCycle + weight[start][j] >= minCycle) {
								continue;
							}
							visit[j] = true;
							canMove = true;
							tempCycle += weight[start][j];
							stackNode.top().second = j;
							stackNode.push(pii(j, 0));
							break;
						}
					}
				}

				if (!canMove) {
					stackNode.pop();
					end = start;
					if (!stackNode.empty()) {
						start = stackNode.top().first;
						visit[end] = false;
						tempCycle -= weight[start][end];
					}
				}
			}
		}
		 /////////////////////////////////////////////////////////////////////////////////////////////


		cout << '#' << test_case << ' ';
		if (minCycle == inf) {
			cout << -1;
		}
		else {
			cout << minCycle;
		}
		cout << '\n';

	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}