#include <deque>
#include <cstring>

using namespace std;

int h, w, cursorH, cursorW, len;
deque<char> str[300];
int countArr[300][26];

void init(int H, int W, char mStr[])
{
	int height = 0, idx = 0;
	h = H;
	w = W;
	cursorH = 0;
	cursorW = 0;
	len = 0;
	for (int i = 0; i < h; i++) {
		str[i].clear();
	}
	memset(countArr, 0, sizeof(countArr));

	while (mStr[idx] != 0) {
		str[height].push_back(mStr[idx]);
		countArr[height][mStr[idx++] - 'a']++;
		if (str[height].size() == w) {
			height++;
		}
		len++;
	}
}

void insert(char mChar)
{
	char poppedChar = 0;
	str[cursorH].insert(str[cursorH].begin() + cursorW, mChar);
	countArr[cursorH][mChar - 'a']++;
	for (int i = cursorH; i < h - 1; i++) {
		if (str[i].size() > w) {
			poppedChar = str[i].back();
			countArr[i][poppedChar - 'a']--;
			str[i].pop_back();
			str[i + 1].push_front(poppedChar);
			countArr[i + 1][poppedChar - 'a']++;
		}
		else {
			break;
		}
	}
	cursorW++;
	if (cursorW == w) {
		cursorW = 0;
		cursorH++;
	}
	len++;
}

char moveCursor(int mRow, int mCol)
{
	cursorH = mRow - 1;
	cursorW = mCol - 1;
	if (cursorH * w + cursorW >= len) {
		cursorH = len / w;
		cursorW = len - cursorH * w;
		return '$';
	}
	return str[mRow - 1][mCol - 1];
}

int countCharacter(char mChar)
{
	int ret = 0;
	for (int i = cursorW; i < str[cursorH].size(); i++) {
		if (str[cursorH][i] == mChar) {
			ret++;
		}
	}

	for (int i = cursorH + 1; i < h; i++) {
		ret += countArr[i][mChar - 'a'];
	}

	return ret;
}
