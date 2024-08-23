#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct _s {
	char one, two, three, four, five, six, seven, eight, nine;
}Side;

Side Up, Down, Right, Left, Front, Back;

void Clear() {
	Up.one = Up.two = Up.three = Up.four = Up.five = Up.six = Up.seven = Up.eight = Up.nine = 'w';
	Down.one = Down.two = Down.three = Down.four = Down.five = Down.six = Down.seven = Down.eight = Down.nine = 'y';
	Front.one = Front.two = Front.three = Front.four = Front.five = Front.six = Front.seven = Front.eight = Front.nine = 'r';
	Back.one = Back.two = Back.three = Back.four = Back.five = Back.six = Back.seven = Back.eight = Back.nine = 'o';
	Left.one = Left.two = Left.three = Left.four = Left.five = Left.six = Left.seven = Left.eight = Left.nine = 'g';
	Right.one = Right.two = Right.three = Right.four = Right.five = Right.six = Right.seven = Right.eight = Right.nine = 'b';
}

void Clockwise(Side* ptr) {
	char temp1 = ptr->one;
	char temp2 = ptr->four;
	ptr->one = ptr->seven;
	ptr->four = ptr->eight;
	ptr->seven = ptr->nine;
	ptr->eight = ptr->six;
	ptr->nine = ptr->three;
	ptr->six = ptr->two;
	ptr->three = temp1;
	ptr->two = temp2;
}
void CounterClockwise(Side* ptr) {
	char temp1 = ptr->one;
	char temp2 = ptr->two;
	ptr->one = ptr->three;
	ptr->two = ptr->six;
	ptr->three = ptr->nine;
	ptr->six = ptr->eight;
	ptr->nine = ptr->seven;
	ptr->eight = ptr->four;
	ptr->seven = temp1;
	ptr->four = temp2;
}

void UP() {
	char temp1 = Front.one;
	char temp2 = Front.two;
	char temp3 = Front.three;
	Front.one = Right.one;
	Front.two = Right.two;
	Front.three = Right.three;
	Right.one = Back.one;
	Right.two = Back.two;
	Right.three = Back.three;
	Back.one = Left.one;
	Back.two = Left.two;
	Back.three = Left.three;
	Left.one = temp1;
	Left.two = temp2;
	Left.three = temp3;
	Clockwise(&Up);
}
void UM() {
	char temp1 = Front.one;
	char temp2 = Front.two;
	char temp3 = Front.three;
	Front.one = Left.one;
	Front.two = Left.two;
	Front.three = Left.three;
	Left.one = Back.one;
	Left.two = Back.two;
	Left.three = Back.three;
	Back.one = Right.one;
	Back.two = Right.two;
	Back.three = Right.three;
	Right.one = temp1;
	Right.two = temp2;
	Right.three = temp3;
	CounterClockwise(&Up);
}
void DP() {
	char temp1 = Front.seven;
	char temp2 = Front.eight;
	char temp3 = Front.nine;
	Front.seven = Left.seven;
	Front.eight = Left.eight;
	Front.nine = Left.nine;
	Left.seven = Back.seven;
	Left.eight = Back.eight;
	Left.nine = Back.nine;
	Back.seven = Right.seven;
	Back.eight = Right.eight;
	Back.nine = Right.nine;
	Right.seven = temp1;
	Right.eight = temp2;
	Right.nine = temp3;
	Clockwise(&Down);
}
void DM() {
	char temp1 = Front.seven;
	char temp2 = Front.eight;
	char temp3 = Front.nine;
	Front.seven = Right.seven;
	Front.eight = Right.eight;
	Front.nine = Right.nine;
	Right.seven = Back.seven;
	Right.eight = Back.eight;
	Right.nine = Back.nine;
	Back.seven = Left.seven;
	Back.eight = Left.eight;
	Back.nine = Left.nine;
	Left.seven = temp1;
	Left.eight = temp2;
	Left.nine = temp3;
	CounterClockwise(&Down);
}
void FP() {
	char temp1 = Up.seven;
	char temp2 = Up.eight;
	char temp3 = Up.nine;
	Up.seven = Left.nine;
	Up.eight = Left.six;
	Up.nine = Left.three;
	Left.nine = Down.three;
	Left.six = Down.two;
	Left.three = Down.one;
	Down.three = Right.one;
	Down.two = Right.four;
	Down.one = Right.seven;
	Right.one = temp1;
	Right.four = temp2;
	Right.seven = temp3;
	Clockwise(&Front);
}
void FM() {
	char temp1 = Up.seven;
	char temp2 = Up.eight;
	char temp3 = Up.nine;
	Up.seven = Right.one;
	Up.eight = Right.four;
	Up.nine = Right.seven;
	Right.one = Down.three;
	Right.four = Down.two;
	Right.seven = Down.one;
	Down.three = Left.nine;
	Down.two = Left.six;
	Down.one = Left.three;
	Left.nine = temp1;
	Left.six = temp2;
	Left.three = temp3;
	CounterClockwise(&Front);
}
void BP() {
	char temp1 = Up.one;
	char temp2 = Up.two;
	char temp3 = Up.three;
	Up.one = Right.three;
	Up.two = Right.six;
	Up.three = Right.nine;
	Right.three = Down.nine;
	Right.six = Down.eight;
	Right.nine = Down.seven;
	Down.nine = Left.seven;
	Down.eight = Left.four;
	Down.seven = Left.one;
	Left.seven = temp1;
	Left.four = temp2;
	Left.one = temp3;
	Clockwise(&Back);
}
void BM() {
	char temp1 = Up.one;
	char temp2 = Up.two;
	char temp3 = Up.three;
	Up.one = Left.seven;
	Up.two = Left.four;
	Up.three = Left.one;
	Left.seven = Down.nine;
	Left.four = Down.eight;
	Left.one = Down.seven;
	Down.nine = Right.three;
	Down.eight = Right.six;
	Down.seven = Right.nine;
	Right.three = temp1;
	Right.six = temp2;
	Right.nine = temp3;
	CounterClockwise(&Back);
}
void LP() {
	char temp1 = Up.one;
	char temp2 = Up.four;
	char temp3 = Up.seven;
	Up.one = Back.nine;
	Up.four = Back.six;
	Up.seven = Back.three;
	Back.nine = Down.one;
	Back.six = Down.four;
	Back.three = Down.seven;
	Down.one = Front.one;
	Down.four = Front.four;
	Down.seven = Front.seven;
	Front.one = temp1;
	Front.four = temp2;
	Front.seven = temp3;
	Clockwise(&Left);
}
void LM() {
	char temp1 = Up.one;
	char temp2 = Up.four;
	char temp3 = Up.seven;
	Up.one = Front.one;
	Up.four = Front.four;
	Up.seven = Front.seven;
	Front.one = Down.one;
	Front.four = Down.four;
	Front.seven = Down.seven;
	Down.one = Back.nine;
	Down.four = Back.six;
	Down.seven = Back.three;
	Back.nine = temp1;
	Back.six = temp2;
	Back.three = temp3;
	CounterClockwise(&Left);
}
void RP() {
	char temp1 = Up.three;
	char temp2 = Up.six;
	char temp3 = Up.nine;
	Up.three = Front.three;
	Up.six = Front.six;
	Up.nine = Front.nine;
	Front.three = Down.three;
	Front.six = Down.six;
	Front.nine = Down.nine;
	Down.three = Back.seven;
	Down.six = Back.four;
	Down.nine = Back.one;
	Back.seven = temp1;
	Back.four = temp2;
	Back.one = temp3;
	Clockwise(&Right);
}
void RM() {
	char temp1 = Up.three;
	char temp2 = Up.six;
	char temp3 = Up.nine;
	Up.three = Back.seven;
	Up.six = Back.four;
	Up.nine = Back.one;
	Back.seven = Down.three;
	Back.four = Down.six;
	Back.one = Down.nine;
	Down.three = Front.three;
	Down.six = Front.six;
	Down.nine = Front.nine;
	Front.three = temp1;
	Front.six = temp2;
	Front.nine = temp3;
	CounterClockwise(&Right);
}

void Turn(char s, char d) {
	if (s == 'U' && d == '+') {
		UP();
	}
	else if (s == 'U' && d == '-') {
		UM();
	}
	else if (s == 'D' && d == '+') {
		DP();
	}
	else if (s == 'D' && d == '-') {
		DM();
	}
	else if (s == 'F' && d == '+') {
		FP();
	}
	else if (s == 'F' && d == '-') {
		FM();
	}
	else if (s == 'B' && d == '+') {
		BP();
	}
	else if (s == 'B' && d == '-') {
		BM();
	}
	else if (s == 'L' && d == '+') {
		LP();
	}
	else if (s == 'L' && d == '-') {
		LM();
	}
	else if (s == 'R' && d == '+') {
		RP();
	}
	else if (s == 'R' && d == '-') {
		RM();
	}
}

int main() {
	char side, direction;
	char output[100][13];
	char turn[3001];
	int T, n;
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		Clear();
		scanf("%d", &n);
		while (getchar() != '\n');
		fgets(turn, 3 * n + 1, stdin);
		for (int j = 0; j < n; j++) {
			side = turn[3 * j];
			direction = turn[3 * j + 1];
			Turn(side, direction);
		}

		output[i][0] = Up.one;
		output[i][1] = Up.two;
		output[i][2] = Up.three;
		output[i][3] = '\n';
		output[i][4] = Up.four;
		output[i][5] = Up.five;
		output[i][6] = Up.six;
		output[i][7] = '\n';
		output[i][8] = Up.seven;
		output[i][9] = Up.eight;
		output[i][10] = Up.nine;
		output[i][11] = '\n';
		output[i][12] = '\0';
	}

	for (int i = 0; i < T; i++) {
		printf("%s", output[i]);
	}
	return 0;
}