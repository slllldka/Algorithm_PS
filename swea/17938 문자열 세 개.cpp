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

using namespace std;

int main(int argc, char** argv)
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int test_case;
	int T;

	int X = 0, Y = 0, Z = 0;
	string A = "", B = "", C = "";
	string first = "", second = "", third = "";
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

		A = "";
		B = "";
		C = "";
		first = "";
		second = "";
		third = "";

		cin >> X >> Y >> Z;
		if (X == Y && Y == Z && Z == X) {
			for (int i = 0; i < X; i++) {
				A += "0";
			}
			B = A;
			C = A;
		}
		else if (X == Y) {
			for (int i = 0; i < X; i++) {
				A += "0";
			}
			B = A;
			C = A;

			for (int i = X; i < Z; i++) {
				A += "1";
				C += "1";
			}
		}
		else if (Y == Z) {
			for (int i = 0; i < Y; i++) {
				A += "0";
			}
			B = A;
			C = A;

			for (int i = Y; i < X; i++) {
				A += "1";
				B += "1";
			}
		}
		else if (Z == X) {
			for (int i = 0; i < Z; i++) {
				A += "0";
			}
			B = A;
			C = A;

			for (int i = Z; i < Y; i++) {
				B += "1";
				C += "1";
			}
		}
		else {
			if (X > Y && Y > Z) {
				for (int i = 0; i < Z; i++) {
					first += "0";
				}
				second = first;
				for (int i = Z; i < Y; i++) {
					second += "1";
				}
				for (int i = 0; i < X; i++) {
					third += "1";
				}
				C = second;
				A = third + first;
				B = first + third;
			}
			else if (X > Z && Z > Y) {
				for (int i = 0; i < Y; i++) {
					first += "0";
				}
				second = first;
				for (int i = Y; i < Z; i++) {
					second += "1";
				}
				for (int i = 0; i < X; i++) {
					third += "1";
				}
				C = second;
				B = third + first;
				A = first + third;
			}
			else if (Y > X && X > Z) {
				for (int i = 0; i < Z; i++) {
					first += "0";
				}
				second = first;
				for (int i = Z; i < X; i++) {
					second += "1";
				}
				for (int i = 0; i < Y; i++) {
					third += "1";
				}
				A = second;
				C = third + first;
				B = first + third;
			}
			else if (Y > Z && Z > X) {
				for (int i = 0; i < X; i++) {
					first += "0";
				}
				second = first;
				for (int i = X; i < Z; i++) {
					second += "1";
				}
				for (int i = 0; i < Y; i++) {
					third += "1";
				}
				A = second;
				B = third + first;
				C = first + third;
			}
			else if (Z > X && X > Y) {
				for (int i = 0; i < Y; i++) {
					first += "0";
				}
				second = first;
				for (int i = Y; i < X; i++) {
					second += "1";
				}
				for (int i = 0; i < Z; i++) {
					third += "1";
				}
				B = second;
				C = third + first;
				A = first + third;
			}
			else if (Z > Y && Y > X) {
				for (int i = 0; i < X; i++) {
					first += "0";
				}
				second = first;
				for (int i = X; i < Y; i++) {
					second += "1";
				}
				for (int i = 0; i < Z; i++) {
					third += "1";
				}
				B = second;
				A = third + first;
				C = first + third;
			}
		}

		
		cout << "#" << test_case << ' ' << A + ' ' << B + ' ' << C + '\n';
		 /////////////////////////////////////////////////////////////////////////////////////////////


	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}