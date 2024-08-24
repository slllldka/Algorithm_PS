#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>
#include <utility>
#include <cstring>
#include <queue>

using namespace std;
using i2 = pair<int, int>;

int N, K;

int userNum, channelNum;
unordered_map<int, int> userMap, channelMap; //(id, hash), (id, hash)
unordered_map<int, i2> newsMap; // (id, (time, channelID);
int subscribers[500];
vector<int> subscribedChannel[500];
set<i2> news[500]; //time, newsID
//set<i2> alarms[500]; //time, newsID;
int recentTime[500][500];

void getMaxIDs(auto iter, int count, i2 arr[]) {
	for (int i = 0; i < count; i++) {
		iter--;
		for (int j = 0; j < 3; j++) {
			if (*iter > arr[j]) {
				if (j == 1) {
					arr[2] = arr[1];
					arr[1] = *iter;
				}
				else if(j == 0) {
					arr[2] = arr[1];
					arr[1] = arr[0];
					arr[0] = *iter;
				}
				arr[j] = *iter;
				break;
			}
		}
	}
}

void init(int n, int k)
{
	N = n;
	K = k;
	userNum = 0;
	channelNum = 0;

	userMap.clear();
	channelMap.clear();
	newsMap.clear();
	memset(subscribers, 0, sizeof(subscribers));
	for (int i = 0; i < 500; i++) {
		subscribedChannel[i].clear();
		news[i].clear();
		//alarms[i].clear();
	}
	memset(recentTime, 0, sizeof(recentTime));
}

void registerUser(int mTime, int mUID, int mNum, int mChannelIDs[])
{
	int userID, channelID;
	if (!userMap.count(mUID)) {
		userMap[mUID] = userNum++;
	}
	userID = userMap[mUID];
	for (int i = 0; i < mNum; i++) {
		if (!channelMap.count(mChannelIDs[i])) {
			channelMap[mChannelIDs[i]] = channelNum++;
		}
		channelID = channelMap[mChannelIDs[i]];
		subscribers[channelID]++;
		subscribedChannel[userID].push_back(channelID);

		/*for (auto iter = news[channelID].lower_bound(i2(mTime + 1, 0)); iter != news[channelID].end(); iter++) {
			alarms[userID].insert(*iter);
		}*/
		recentTime[userID][channelID] = mTime + 1;
	}
}

int offerNews(int mTime, int mNewsID, int mDelay, int mChannelID)
{
	int channelID = channelMap[mChannelID];
	newsMap[mNewsID] = i2(mTime + mDelay, channelID);
	
	news[channelID].insert(i2(mTime + mDelay, mNewsID));
	/*for (int userID : subscribers[channelID]) {
		alarms[userID].insert(i2(mTime + mDelay, mNewsID));
	}*/

	//cout << subscribers[channelID].size() << '\n';
	return subscribers[channelID];
}

void cancelNews(int mTime, int mNewsID)
{
	if (newsMap[mNewsID].first == -1) {
		return;
	}
	i2 save = newsMap[mNewsID];
	newsMap[mNewsID] = i2(-1, -1);
	news[save.second].erase(i2(save.first, mNewsID));
	/*for (int i = 0; i < userNum; i++) {
		if (alarms[i].count(i2(save.first, mNewsID))) {
			alarms[i].erase(i2(save.first, mNewsID));
		}
	}*/
}

int checkUser(int mTime, int mUID, int mRetIDs[])
{
	int ret = 0;
	int userID = userMap[mUID];
	i2 arr[3] = { i2(0, 0), i2(0, 0), i2(0, 0) };
	/*auto start = alarms[userID].lower_bound(i2(recentTime[userID], 0));
	auto end = alarms[userID].lower_bound(i2(mTime + 1, 0));
	ret = distance(start, end);
	recentTime[userID] = mTime + 1;
	
	auto iter2 = end;
	for (int i = 0; i < 3; i++) {
		if (iter2 == alarms[userID].begin()) {
			break;
		}
		iter2--;
		mRetIDs[i] = (*iter2).second;
	}*/

	priority_queue<i2> pq;
	for (int channelID : subscribedChannel[userID]) {
		int count = 0;
		auto start = news[channelID].lower_bound(i2(recentTime[userID][channelID], 0));
		auto end = news[channelID].lower_bound(i2(mTime + 1, 0));
		count = distance(start, end);
		ret += count;
		recentTime[userID][channelID] = mTime + 1;

		getMaxIDs(end, count < 3 ? count : 3, arr);

		/*for (int i = 0; i < (count < 3 ? count : 3); i++) {
			end--;
			pq.push(*end);
		}*/
	}

	//cout << ret << '\n';
	for (int i = 0; i < (ret < 3 ? ret : 3); i++) {
		/*mRetIDs[i] = pq.top().second;
		pq.pop();*/
		mRetIDs[i] = arr[i].second;
		//cout << mRetIDs[i] << ' ';
	}
	//cout << '\n';

	return ret;
}