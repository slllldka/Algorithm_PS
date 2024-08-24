#include <cstring>
#include <algorithm>
#include <utility>
#include <iostream>

using namespace std;
using i2 = pair<int, int>;

constexpr int int_max = 2147483647;

struct Result {
    int top;
    int count;
};

int C;

int maxHeight;
long long totalNum;
int minTree[1 << 21], maxTree[1 << 21], lazy[1 << 21];
int base;

i2 update(int node, int qs, int qe, int ts, int te, int val) {
    //cout << ts << ' ' << te << "tree\n";
    if (qs <= ts && te <= qe) {
        lazy[node] += val;
        minTree[node] += val;
        maxTree[node] += val;
        
        //lazy propagation
        /*if (node * 2 + 1 <= base << 1) {
            lazy[node * 2] = lazy[node];
            lazy[node * 2 + 1] = lazy[node];
            lazy[node] = 0;
            //cout << ts << ' ' << te << "tree\n";
            i2 a = update(node * 2, qs, qe, ts, (ts + te) / 2, val);
            i2 b = update(node * 2 + 1, qs, qe, (ts + te) / 2 + 1, te, val);

            minTree[node] = min(a.first, b.first);
            maxTree[node] = max(a.second, b.second);
        }*/
        return i2(minTree[node], maxTree[node]);
    }
    
    if (qe < ts || te < qs) {
        return i2(minTree[node], maxTree[node]);
    }



    i2 a = update(node * 2, qs, qe, ts, (ts + te) / 2, val);
    i2 b = update(node * 2 + 1, qs, qe, (ts + te) / 2 + 1, te, val);

    minTree[node] = min(a.first, b.first) + lazy[node];
    maxTree[node] = max(a.second, b.second) + lazy[node];
    return i2(minTree[node], maxTree[node]);
}

void init(int c)
{
    C = c;
    maxHeight = 0;
    totalNum = 0;
    base = 1;
    while (base < c) {
        base <<= 1;
    }
    //cout << c << ' ' << base << '\n';
    memset(minTree, 0, sizeof(minTree));
    memset(maxTree, 0, sizeof(maxTree));
    memset(lazy, 0, sizeof(lazy));

    for (int i = base; i < (base << 1); i++) {
        if (i < base + C) {
            minTree[i] = 0;
            maxTree[i] = 0;
        }
        else {
            minTree[i] = int_max;
            maxTree[i] = 0;
        }
    }
    for (int i = base - 1; i > 0; i--) {
        minTree[i] = min(minTree[i * 2], minTree[i * 2 + 1]);
        maxTree[i] = max(maxTree[i * 2], maxTree[i * 2 + 1]);
    }
}

Result dropBlocks(int mCol, int mHeight, int mLength)
{
    Result ret = {0, 0};
    totalNum += mHeight * mLength;
    
    update(1, mCol + 1, mCol + mLength, 1, base, mHeight);

    ret.top = maxTree[1] - minTree[1];
    //cout << minTree[1] << ' ' << maxTree[1] << '\n';
    ret.count = (totalNum - (long long)minTree[1] * C) % 1000000;
    //cout << ret.top << ' ' << ret.count << '\n';
    return ret;
}
