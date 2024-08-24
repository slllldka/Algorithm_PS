#include <cstring>
#include <iostream>
#include <vector>
#include <utility>

#define min(a, b) (((a) < (b)) ? (a) : (b))

using namespace std;
using i2 = pair<int, int>;

#define MAX_ROW 40
#define MAX_COL 30

struct Result {
    int row;
    int col;
};

int R, C;
int map[MAX_ROW][MAX_COL];
vector<i2> hashMap[5][55555];
bool visited[MAX_ROW][MAX_COL];

int blockNum[5] = { 2, 3, 3, 4, 5 };
i2 blockPos[5][5] = { {i2(0, 0), i2(0, 1)}, {i2(0, 0), i2(0, 1), i2(0, 2)}, {i2(0, 0), i2(1, 0), i2(2, 0)}
    , {i2(0, 0), i2(0,1), i2(1, 1), i2(1, 2)}, {i2(0, 0), i2(1, 0),i2(1,1),i2(1,2), i2(2,2)} };
i2 blockOffset[5] = { i2(0, 1), i2(0, 2), i2(2, 0), i2(1, 2), i2(2, 2) };
int mod[5] = { 11, 111, 111, 1111, 11111 };

bool available(int x, int y, int type) {
    bool ret = false;
    if (type == 0) {
        ret = !visited[x][y] && !visited[x][y + 1];
    }
    else if (type == 1) {
        ret = !visited[x][y] && !visited[x][y + 1] && !visited[x][y + 2];
    }
    else if (type == 2) {
        ret = !visited[x][y] && !visited[x + 1][y] && !visited[x + 2][y];
    }
    else if (type == 3) {
        ret = !visited[x][y] && !visited[x][y + 1] && !visited[x + 1][y + 1]
            && !visited[x + 1][y + 2];
    }
    else if (type == 4) {
        ret = !visited[x][y] && !visited[x + 1][y] && !visited[x + 1][y + 1]
            && !visited[x + 1][y + 2] && !visited[x + 2][y + 2];
    }

    return ret;
}

void init(int mRows, int mCols, int mCells[MAX_ROW][MAX_COL])
{
    int hashValue = 0, a, b, c, d, e, minValue;
    R = mRows;
    C = mCols;
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            map[i][j] = mCells[i][j];
        }
    }
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 55555; j++) {
            hashMap[i][j].clear();
        }
    }

    //1st
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C - 1; j++) {
            a = map[i][j];
            b = map[i][j + 1];
            minValue = min(a, b);
            a -= minValue;
            b -= minValue;
            hashValue = 10 * a + b;
            hashMap[0][hashValue].push_back(i2(i, j));
        }
    }
    //2nd
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C - 2; j++) {
            a = map[i][j];
            b = map[i][j + 1];
            c = map[i][j + 2];
            minValue = min(min(a, b), c);
            a -= minValue;
            b -= minValue;
            c -= minValue;
            hashValue = 100 * a + 10 * b + c;
            hashMap[1][hashValue].push_back(i2(i, j));
        }
    }
    //3rd
    for (int i = 0; i < R - 2; i++) {
        for (int j = 0; j < C; j++) {
            a = map[i][j];
            b = map[i + 1][j];
            c = map[i + 2][j];
            minValue = min(min(a, b), c);
            a -= minValue;
            b -= minValue;
            c -= minValue;
            hashValue = 100 * a + 10 * b + c;
            hashMap[2][hashValue].push_back(i2(i, j));
        }
    }
    //4th
    for (int i = 0; i < R - 1; i++) {
        for (int j = 0; j < C - 2; j++) {
            a = map[i][j];
            b = map[i][j + 1];
            c = map[i + 1][j + 1];
            d = map[i + 1][j + 2];
            minValue = min(min(a, b), min(c, d));
            a -= minValue;
            b -= minValue;
            c -= minValue;
            d -= minValue;
            hashValue = 1000 * a + 100 * b + 10 * c + d;
            hashMap[3][hashValue].push_back(i2(i, j));
        }
    }

    //5th
    for (int i = 0; i < R - 2; i++) {
        for (int j = 0; j < C - 2; j++) {
            a = map[i][j];
            b = map[i + 1][j];
            c = map[i + 1][j + 1];
            d = map[i + 1][j + 2];
            e = map[i + 2][j + 2];
            minValue = min(min(min(a, b), min(c, d)), e);
            a -= minValue;
            b -= minValue;
            c -= minValue;
            d -= minValue;
            e -= minValue;
            hashValue = 10000 * a + 1000 * b + 100 * c + 10 * d + e;
            hashMap[4][hashValue].push_back(i2(i, j));
        }
    }
}

Result putPuzzle(int arr[3][3])
{
    Result ret = { -1, -1 };
    int hashValue = 0, a, b, c, d, e, minValue;
    int blockType = -1;
    int x = -1, y = -1;
    int newX = -1, newY = -1;

    if (arr[0][1] > 0) {
        if (arr[0][2] > 0) {
            blockType = 1;
        }
        else {
            if (arr[1][1] > 0) {
                blockType = 3;
            }
            else {
                blockType = 0;
            }
        }
    }
    else {
        if (arr[2][0] > 0) {
            blockType = 2;
        }
        else {
            blockType = 4;
        }
    }

    if (blockType == 0) {
        a = arr[0][0];
        b = arr[0][1];
        minValue = min(a, b);
        a -= minValue;
        b -= minValue;
        hashValue = 10 * a + b;
    }
    else if (blockType == 1) {
        a = arr[0][0];
        b = arr[0][1];
        c = arr[0][2];
        minValue = min(min(a, b), c);
        a -= minValue;
        b -= minValue;
        c -= minValue;
        hashValue = 100 * a + 10 * b + c;
    }
    else if (blockType == 2) {
        a = arr[0][0];
        b = arr[1][0];
        c = arr[2][0];
        minValue = min(min(a, b), c);
        a -= minValue;
        b -= minValue;
        c -= minValue;
        hashValue = 100 * a + 10 * b + c;
    }
    else if (blockType == 3) {
        a = arr[0][0];
        b = arr[0][1];
        c = arr[1][1];
        d = arr[1][2];
        minValue = min(min(a, b), min(c, d));
        a -= minValue;
        b -= minValue;
        c -= minValue;
        d -= minValue;
        hashValue = 1000 * a + 100 * b + 10 * c + d;
    }
    else if (blockType == 4) {
        a = arr[0][0];
        b = arr[1][0];
        c = arr[1][1];
        d = arr[1][2];
        e = arr[2][2];
        minValue = min(min(min(a, b), min(c, d)), e);
        a -= minValue;
        b -= minValue;
        c -= minValue;
        d -= minValue;
        e -= minValue;
        hashValue = 10000 * a + 1000 * b + 100 * c + 10 * d + e;
    }

    for (i2 pos : hashMap[blockType][hashValue]) {
        if (available(pos.first, pos.second, blockType)) {
            ret = { pos.first, pos.second };
            break;
        }
    }

    if (ret.row != -1 && ret.col != -1) {
        for (int i = 0; i < blockNum[blockType]; i++) {
            visited[ret.row + blockPos[blockType][i].first][ret.col + blockPos[blockType][i].second] = true;
        }
    }

    return ret;
}

void clearPuzzles()
{
    memset(visited, false, sizeof(visited));
    return;
}