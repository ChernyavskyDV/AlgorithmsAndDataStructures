#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct Module {
	int number;
	int node;
	int cost1;
	int cost2;
};

struct Ancestor
{
	int node;
	double cost;
	int module;
};

struct Node {
	int number;
	double cost;
	int prev;
	int module;
};
bool operator < (const Node &a, const Node &b)
{
	return a.cost>b.cost;
}

int gcd(int n1, int n2)
{
	int A = n1;
	int B = n2;
	if (A == 0 || B == 0)
		return A + B;
	if (A > B)
		return gcd(A%B, B);
	else
		return gcd(A, B%A);
}

long long lcm(long long n1, long long n2)
{
	return n1*n2 / gcd(n1, n2);
}

int main() {

	FILE* in = fopen("input.txt", "r");

	int N;
	int M;
	fscanf(in, "%d", &N);
	fscanf(in, "%d", &M);

	bool *visitedRooms = new bool[N];
	for (int i = 0; i < N; ++i)
		visitedRooms[i] = false;

	vector<vector<Module>> adjList(N);
	int R1, T1, R2, T2;
	Module tempModule;
	for (int i = 0; i < M; ++i)
	{
		fscanf(in, "%d", &R1);
		fscanf(in, "%d", &T1);
		fscanf(in, "%d", &R2);
		fscanf(in, "%d", &T2);
		R1--;
		R2--;
		tempModule.number = i;
		tempModule.node = R2;
		tempModule.cost1 = T1;
		tempModule.cost2 = T2;
		adjList[R1].push_back(tempModule);
		tempModule.node = R1;
		tempModule.cost1 = T2;
		tempModule.cost2 = T1;
		adjList[R2].push_back(tempModule);
	}

	vector<Ancestor> ancestor(N);
	for (int i = 0; i < N; i++)
	{
		ancestor[i].cost = DBL_MAX;
		ancestor[i].node = -1;
		ancestor[i].module = -1;

	}
	ancestor[0].cost = 0;

	priority_queue<Node> minHeap;
	Node tempNode;
	tempNode.number = 0;
	tempNode.cost = 0;
	tempNode.prev = -1;
	tempNode.module = -1;
	minHeap.push(tempNode);
	double minCost;
	int minNumber;
	long long LCM;
	double p;
	long long k;
	while (minHeap.top().number != N - 1) {
		minCost = minHeap.top().cost;
		minNumber = minHeap.top().number;
		minHeap.pop();
		if (!visitedRooms[minNumber]) {
			for (int i = 0; i < adjList[minNumber].size(); ++i) {
				if (!visitedRooms[adjList[minNumber][i].node]) {
					tempNode.module = adjList[minNumber][i].number;
					tempNode.number = adjList[minNumber][i].node;
					tempNode.prev = minNumber;
					LCM = lcm(adjList[minNumber][i].cost1, adjList[minNumber][i].cost2);
					p = minCost / LCM;
					k = p + 1;
					tempNode.cost = k*LCM + 0.5;
					if (ancestor[tempNode.number].cost > tempNode.cost)
					{
						ancestor[tempNode.number].node = tempNode.prev;
						ancestor[tempNode.number].cost = tempNode.cost;
						ancestor[tempNode.number].module = tempNode.module;
						minHeap.push(tempNode);
					}
				}
			}
			visitedRooms[minNumber] = true;
		}
	}
	ancestor[N - 1].node = minHeap.top().prev;
	ancestor[N - 1].cost = minHeap.top().cost;
	ancestor[N - 1].module = minHeap.top().module; vector<int> path;
	int o = N - 1;
	while (ancestor[o].module != -1)
	{
		path.push_back(ancestor[o].module);
		o = ancestor[o].node;
	}

	FILE* out = fopen("output.txt", "w");
	fprintf(out, "%.1f", minHeap.top().cost);
	fprintf(out, "%c", '\n');

	for (int i = path.size() - 1; i > -1; i--)
	{
		fprintf(out, "%d", path[i] + 1);
		fprintf(out, "%c", ' ');
	}

	return 0;
}
