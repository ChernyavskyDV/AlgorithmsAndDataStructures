#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct ToolRoad 
{
	int number;
	int cost;
};

int main()
{
	FILE* cin = fopen("campaign.in", "r");
	FILE* cout = fopen("campaign.out", "w");

	int n;
	int m;
	fscanf(cin, "%d", &n);
	fscanf(cin, "%d", &m);

	int *cost = new int[n];
	for (int i = 0; i < n; ++i)
		fscanf(cin, "%d", &cost[i]);

	ToolRoad **MSmez = new ToolRoad*[n];
	for (int i = 0; i < n; ++i)
		MSmez[i] = new ToolRoad[n];
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		{
			MSmez[i][j].number = -1;
			MSmez[i][j].cost = 0;
		}

	bool *pos = new bool[n];
	for (int i = 0; i < n; ++i)
		pos[i] = false;

	long long **road = new long long*[2];
	for (int i = 0; i < 2; ++i)
		road[i] = new long long[n];
	for (int i = 0; i < n; ++i)
	{
		road[0][i] = LLONG_MAX;
		road[1][i] = -1;
	}
	road[0][0] = 0;

	vector<int>myRoads;
	vector<int>otherRoads;
	int a, b, p, c;
	int money = 0;
	for (int i = 0; i < m; ++i)
	{
		fscanf(cin, "%d", &a);
		fscanf(cin, "%d", &b);
		--a;
		--b;
		fscanf(cin, "%d", &p);
		--p;
		fscanf(cin, "%d", &c);
		MSmez[a][b].cost = c;
		MSmez[b][a].cost = c;
		MSmez[a][b].number = i;
		MSmez[b][a].number = i;
		if (p == 0)
		{
			money += c;
			myRoads.push_back(i);
		}
		else
		{
			otherRoads.push_back(i);
		}
	}

	long long min;
	int iMin = 0;
	while (iMin < INT_MAX)
	{
		min = LLONG_MAX;
		iMin = INT_MAX;
		for (int i = 0; i < n; ++i)
		{
			if (pos[i] == false && road[0][i] < min)
			{
				min = road[0][i];
				iMin = i;
			}
		}
		if (iMin != INT_MAX)
		{
			for (int i = 0; i < n; ++i)
			{
				if (MSmez[iMin][i].cost > 0 && road[0][i] > min + MSmez[iMin][i].cost + cost[i])
				{
					road[0][i] = min + MSmez[iMin][i].cost + cost[i];
					road[1][i] = iMin + 1;
				}
			}
			pos[iMin] = true;
		}
	}

	if (money < road[0][n - 1])
	{
		fprintf(cout, "%d", -1);
		return 0;
	}

	vector<int>path;
	path.push_back(n);
	for (int i = n - 1; i > -1; i = road[1][i] - 1)
		path.push_back(road[1][i]);

	vector<int>Road;
	for (int i = path.size() - 2; i > 0; --i)
	{
		Road.push_back(MSmez[path[i] - 1][path[i - 1] - 1].number);
	}

	vector<int>A;
	bool flag;
	for (int i = 0; i < myRoads.size(); i++)
	{
		flag = false;
		for (int j = 0; j < Road.size(); j++)
		{
			if (myRoads[i] == Road[j])
				flag = true;
		}
		if (flag == false)
		{
			A.push_back(myRoads[i]);
		}
	}
	vector<int>B;
	for (int i = 0; i < otherRoads.size(); i++)
	{
		for (int j = 0; j < Road.size(); j++)
		{
			if (otherRoads[i] == Road[j])
			{
				B.push_back(otherRoads[i]);
			}
		}
	}


	fprintf(cout, "%d", A.size());
	fprintf(cout, "%c", ' ');
	for (int i = 0; i < A.size(); i++) 
	{
		fprintf(cout, "%d", A[i] + 1);
		fprintf(cout, "%c", ' ');
	}
	fprintf(cout, "%c", '\n');
	fprintf(cout, "%d", B.size());
	fprintf(cout, "%c", ' ');
	for (int i = 0; i < B.size(); i++)
	{
		fprintf(cout, "%d", B[i] + 1);
		fprintf(cout, "%c", ' ');
	}
	fprintf(cout, "%c", '\n');
	for (int i = path.size() - 2; i >= 0; --i)
	{
		fprintf(cout, "%d", path[i]);
		fprintf(cout, "%c", ' ');
	}
	return 0;
}