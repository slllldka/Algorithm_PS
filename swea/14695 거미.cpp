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

long long points[100000][3];
#include<iostream>

using namespace std;

long long innerProduct(long long src1[3], long long src2[3]) {
	return (src1[0] * src2[0] + src1[1] * src2[1] + src1[2] * src2[2]);
}

void crossProduct(long long src1[3], long long src2[3], long long dst[3]) {
	dst[0] = src1[1] * src2[2] - src1[2] * src2[1];
	dst[1] = src1[2] * src2[0] - src1[0] * src2[2];
	dst[2] = src1[0] * src2[1] - src1[1] * src2[0];
}

int main(int argc, char** argv)
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	int test_case;
	int T;
	long long N;
	long long vec1[3] = { 0, 0, 0 };
	long long vec2[3] = { 0, 0, 0 };
	long long normalVec[3] = { 0, 0, 0 };
	bool vec1Exist = false, vec2Exist = false;
	bool result = false;
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
		vec1[0] = 0;
		vec1[1] = 0;
		vec1[2] = 0;
		vec2[0] = 0;
		vec2[1] = 0;
		vec2[2] = 0;
		normalVec[0] = 0;
		normalVec[1] = 0;
		normalVec[2] = 0;
		vec1Exist = false;
		vec2Exist = false;
		result = true;

		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> points[i][0] >> points[i][1] >> points[i][2];
		}

		if (N <= 3) {
			result = true;
		}
		else {
			for (int i = 1; i < N; i++) {
				if (!vec1Exist) {
					vec1Exist = true;
					vec1[0] = points[i][0] - points[0][0];
					vec1[1] = points[i][1] - points[0][1];
					vec1[2] = points[i][2] - points[0][2];
				}
				else if(!vec2Exist){
					vec2[0] = points[i][0] - points[0][0];
					vec2[1] = points[i][1] - points[0][1];
					vec2[2] = points[i][2] - points[0][2];
					crossProduct(vec1, vec2, normalVec);
					if (normalVec[0] == 0 && normalVec[1] == 0 && normalVec[2] == 0) {
						continue;
					}
					else {
						vec2Exist = true;
					}
				}
				else {
					vec2[0] = points[i][0] - points[0][0];
					vec2[1] = points[i][1] - points[0][1];
					vec2[2] = points[i][2] - points[0][2];
					if (innerProduct(vec2, normalVec) == 0) {
						continue;
					}
					else {
						result = false;
						break;
					}

				}
			}
		}


		cout << '#' << test_case << ' ';
		if (result) {
			cout << "TAK\n";
		}
		else {
			cout << "NIE\n";
		}

		 /////////////////////////////////////////////////////////////////////////////////////////////


	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}