#include <set>
#include <utility>
#include <algorithm>
//#include <iostream>

using namespace std;
using i2 = pair<int, int>; // -ability, id;

int N, L;
int num;
set<i2> maxHeap[10], minHeap[10];

void init(int n, int l, int mAbility[])
{
    N = n;
    L = l;
    num = N / L;
    i2 ability[40000];
    for (int i = 0; i < n; i++) {
        ability[i] = i2(-mAbility[i], i);
    }

    for (int i = 0; i < L; i++) {
        maxHeap[i].clear();
        minHeap[i].clear();

        sort(ability + num * i, ability + num * (i + 1));

        auto maxIter = maxHeap[i].begin();
        auto minIter = minHeap[i].begin();

        for (int j = num - 1; j >= 0; j--) {
            if (j <= num / 2) {
                maxIter = maxHeap[i].insert(maxIter, ability[num * i + j]);
            }
            else {
                minIter = minHeap[i].insert(minIter, ability[num * i + j]);
            }
        }

        /*maxHeap[i].insert(i2(-mAbility[i * num + 0], i * num + 0));
        minHeap[i].insert(i2(-mAbility[i * num + 1], i * num + 1));
        for (int j = 2; j < num; j++) {
            if (j % 2 == 0) {
                maxHeap[i].insert(i2(-mAbility[i * num + j], i * num + j));
                if (*maxHeap[i].rbegin() > *minHeap[i].begin()) {
                    i2 temp1 = *maxHeap[i].rbegin();
                    i2 temp2 = *minHeap[i].begin();
                    maxHeap[i].erase(temp1);
                    maxHeap[i].insert(temp2);
                    minHeap[i].erase(temp2);
                    minHeap[i].insert(temp1);
                }
            }
            else {
                minHeap[i].insert(i2(-mAbility[i * num + j], i * num + j));
            }
        }*/

        /*for (i2 data : maxHeap[i]) {
            cout << data.second << ' ';
        }
        for (i2 data : minHeap[i]) {
            cout << data.second << ' ';
        }
        cout << '\n';*/
    }
}

int move()
{
    int ret = 0;
    i2 minP[10], maxP[10];
    set<i2>::iterator minIter[10], maxIter[10];
    for (int i = 0; i < L; i++) {
        if (i > 0) {
            maxHeap[i].erase(maxIter[i - 1]);
            maxHeap[i].insert(minP[i - 1]);
        }
        if (i < L - 1) {
            minIter[i] = prev(minHeap[i].end());
            maxIter[i] = maxHeap[i + 1].begin();
            minP[i] = *minIter[i];
            maxP[i] = *maxIter[i];
            ret += minP[i].second;
            ret += maxP[i].second;
            minHeap[i].erase(minIter[i]);
            minHeap[i].insert(maxP[i]);
        }
        if (*maxHeap[i].rbegin() > *minHeap[i].begin()) {
            set<i2>::iterator iter1 = prev(maxHeap[i].end());
            set<i2>::iterator iter2 = minHeap[i].begin();
            i2 temp1 = *iter1;
            i2 temp2 = *iter2;
            maxHeap[i].erase(iter1);
            maxHeap[i].insert(temp2);
            minHeap[i].erase(iter2);
            minHeap[i].insert(temp1);
        }

    }

    /*for (int i = 0; i<L; i++) {
        for (i2 data : maxHeap[i]) {
            cout << data.second << ' ';
        }
        cout << '/';
        for (i2 data : minHeap[i]) {
            cout << data.second << ' ';
        }
        cout << '\n';
    }*/

    //cout << ret << '\n';
    return ret;
}

int trade()
{
    int ret = 0;
    i2 middleP[10], maxP[10];
    set<i2>::iterator middleIter[10], maxIter[10];
    for (int i = 0; i < L - 1; i++) {
        middleIter[i] = prev(maxHeap[i].end());
        maxIter[i] = maxHeap[i + 1].begin();
        middleP[i] = *middleIter[i];
        maxP[i] = *maxIter[i];
        ret += middleP[i].second;
        ret += maxP[i].second;
    }
    for (int i = 0; i < L - 1; i++) {
        maxHeap[i].erase(middleIter[i]);
        maxHeap[i].insert(maxP[i]);
        maxHeap[i + 1].erase(maxIter[i]);
        maxHeap[i + 1].insert(middleP[i]);
        if (*maxHeap[i].rbegin() > *minHeap[i].begin()) {
            set<i2>::iterator iter1 = prev(maxHeap[i].end());
            set<i2>::iterator iter2 = minHeap[i].begin();
            i2 temp1 = *iter1;
            i2 temp2 = *iter2;
            maxHeap[i].erase(iter1);
            maxHeap[i].insert(temp2);
            minHeap[i].erase(iter2);
            minHeap[i].insert(temp1);
        }
    }
    if (*maxHeap[L - 1].rbegin() > *minHeap[L - 1].begin()) {
        set<i2>::iterator iter1 = prev(maxHeap[L - 1].end());
        set<i2>::iterator iter2 = minHeap[L - 1].begin();
        i2 temp1 = *iter1;
        i2 temp2 = *iter2;
        maxHeap[L - 1].erase(iter1);
        maxHeap[L - 1].insert(temp2);
        minHeap[L - 1].erase(iter2);
        minHeap[L - 1].insert(temp1);
    }
    //cout << ret << '\n';
    return ret;
}