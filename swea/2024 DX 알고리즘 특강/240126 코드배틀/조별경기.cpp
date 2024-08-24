#include <iostream>
#include <cstring>
#include <list>

int n;
int playerScore[100001];
int teamScore[100001];
int playerTeam[100001];
int rank[100001];

void init(int N)
{
	n = N;
	memset(playerScore, 0, sizeof(playerScore));
	memset(teamScore, 0, sizeof(teamScore));
	memset(rank, 0, sizeof(rank));
	for (int i = 1; i <= n; i++) {
		playerTeam[i] = i;
	}
}

int find(int id) {
	if (id == playerTeam[id]) {
		return id;
	}
	else {
		int p = find(playerTeam[id]);
		if (p != playerTeam[id]) {
			teamScore[id] += teamScore[playerTeam[id]];
		}
		return (playerTeam[id] = p);
	}
}

void updateScore(int mWinnerID, int mLoserID, int mScore)
{
	int winner = find(mWinnerID), loser = find(mLoserID);
	teamScore[winner] += mScore;
	teamScore[loser] -= mScore;
}

void unionTeam(int mPlayerA, int mPlayerB)
{
	int a = find(mPlayerB), b = find(mPlayerA);
	if (rank[a] == rank[b]) {
		playerTeam[a] = b;
		teamScore[a] -= teamScore[b];
		rank[b]++;
	}
	else if (rank[a] > rank[b]) {
		playerTeam[b] = a;
		teamScore[b] -= teamScore[a];
	}
	else {
		playerTeam[a] = b;
		teamScore[a] -= teamScore[b];
	}
}

int getScore(int mID)
{
	int parent = find(mID);
	if (mID == parent) {
		return teamScore[mID];
	}
	return teamScore[mID] + teamScore[find(mID)];
}