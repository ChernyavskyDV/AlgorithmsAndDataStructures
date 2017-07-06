#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

using namespace std;

struct Road {
	int from;
	int to;
	long long cost;
};

void addToMinHeap(vector<Road> &v, Road n)
{
	v.push_back(n);
	for (int i = v.size() - 1; i > 0; i = i >> 1)
	{
		int iT = i >> 1;
		if (n.cost < v[iT].cost)
		{
			v[i] = v[iT];
		}
		else
		{
			v[i] = n;
			break;
		}
	}
}

void deleteFromMinHeap(vector<Road> &v)
{
	if (v.size() > 1)
	{
		Road n = v[v.size() - 1];
		v[1] = v[v.size() - 1];
		v.erase(v.begin() + (v.size() - 1));
		for (int i = 1; i <= (v.size() - 1) >> 1;)
		{
			int iT = i << 1;
			if (iT <= v.size() - 2)
			{
				if (v[iT].cost <= v[iT + 1].cost)
				{
					if (n.cost > v[iT].cost)
					{
						v[i] = v[iT];
						v[iT] = n;
						i = i << 1;
					}
					else
					{
						break;
					}
				}
				else
				{
					if (n.cost > v[iT + 1].cost)
					{
						v[i] = v[iT + 1];
						v[iT + 1] = n;
						i = i << 1;
						i = i + 1;
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				if (n.cost > v[iT].cost)
				{
					v[i] = v[iT];
					v[iT] = n;
					i = i << 1;
				}
				else
				{
					break;
				}
			}
		}
	}
}

int main() {

	FILE* cin = fopen("in.txt", "r");
	FILE* cout = fopen("out.txt", "w");

	int N;
	int M;
	fscanf(cin, "%d", &N);
	fscanf(cin, "%d", &M);
	int MN = M*N;

	long long **terrainPlan = new long long*[N];
	for (int i = 0; i < N; ++i)
	{
		terrainPlan[i] = new long long[M];
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			fscanf(cin, "%lld", &terrainPlan[i][j]);
		}
	}

	long long K;
	fscanf(cin, "%lld", &K);

	int X1, Y1, X2, Y2;
	fscanf(cin, "%d", &X1);
	fscanf(cin, "%d", &Y1);
	fscanf(cin, "%d", &X2);
	fscanf(cin, "%d", &Y2);
	--X1;
	--Y1;
	--X2;
	--Y2;
	int from = X1 * M + Y1;
	int to = X2 * M + Y2;


	vector<vector<Road>> SSmez(MN);
	Road tempRoad;
	int w;
	for (int i = 0; i < N; ++i) {
		w = i*M;
		for (int j = 0; j < M - 1; ++j) {
			tempRoad.from = i*M + j;
			tempRoad.to = tempRoad.from + 1;
			tempRoad.cost = abs(terrainPlan[i][j] - terrainPlan[i][j + 1]);
			SSmez[w].push_back(tempRoad);
			++tempRoad.from;
			--tempRoad.to;
			++w;
			SSmez[w].push_back(tempRoad);
		}
	}
	for (int j = 0; j < M; ++j) {
		w = j;
		for (int i = 0; i < N - 1; ++i) {
			tempRoad.from = i*M + j;
			tempRoad.to = tempRoad.from + M;
			tempRoad.cost = abs(terrainPlan[i][j] - terrainPlan[i + 1][j]);
			SSmez[w].push_back(tempRoad);
			tempRoad.from = tempRoad.to;
			tempRoad.to -= M;
			w += M;
			SSmez[w].push_back(tempRoad);
		}
	}

	bool *visitedSquare = new bool[MN];
	for (int i = 0; i < MN; ++i)
		visitedSquare[i] = false;

	long long *route = new long long[MN];
	for (int i = 0; i < MN; ++i)
		route[i] = LLONG_MAX;
	route[from] = 0;

	vector<Road> minHeap;
	tempRoad.from = -1;
	tempRoad.to = -1;
	tempRoad.cost = -1;
	addToMinHeap(minHeap, tempRoad);
	tempRoad.from = -1;
	tempRoad.to = from;
	tempRoad.cost = 0;
	addToMinHeap(minHeap, tempRoad);
	int dest;
	long long cost;
	while (minHeap[1].to != to) {
		dest = minHeap[1].to;
		cost = minHeap[1].cost;
		deleteFromMinHeap(minHeap);
		if (!visitedSquare[dest]) {
			for (int i = 0; i < SSmez[dest].size(); ++i) {
				if (!visitedSquare[SSmez[dest][i].to]) {
					tempRoad.from = dest;
					tempRoad.to = SSmez[dest][i].to;
					tempRoad.cost = route[dest] + SSmez[dest][i].cost + K;
					if (tempRoad.cost < route[tempRoad.to]) {
						addToMinHeap(minHeap, tempRoad);
						route[tempRoad.to] = tempRoad.cost;
					}
				}
			}
			visitedSquare[dest] = true;
		}
	}
	fprintf(cout, "%lld", minHeap[1].cost);
	return 0;
}