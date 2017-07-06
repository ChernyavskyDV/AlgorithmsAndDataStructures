#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

using namespace std;

int main()
{
	FILE* cin = fopen("input.in", "r");
	FILE* cout = fopen("output.out", "w");

	int N;
	int K;
	fscanf(cin, "%d", &N);
	fscanf(cin, "%d", &K);

	int I;
	int J;
	fscanf(cin, "%d", &I);
	fscanf(cin, "%d", &J);
	I--;
	J--;
	
	int**MSmez = new int*[N];
	for (int i = 0; i < N; ++i)
		MSmez[i] = new int[N];
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			MSmez[i][j] = 0;	
	
	int *num = new int[N];
	for (int i = 0; i < N; ++i)
		num[i] = 0;

	bool *pos = new bool[N];
	for (int i = 0; i < N; ++i)
		pos[i] = false;

	long long **route = new long long*[2];
	for (int i = 0; i < 2; ++i)
		route[i] = new long long[N];
	for (int i = 0; i < N; ++i)
	{
		route[0][i] = LLONG_MAX;
		route[1][i] = -1;
	}
	route[0][I] = 0;

	int k;
	int m;
	int cost;
	for (int i = 0; i < K; ++i)
	{
		fscanf(cin, "%d", &k);
		--k;
		fscanf(cin, "%d", &m);
		--m;
		fscanf(cin,"%d",&cost);
		MSmez[k][m] = cost;
		MSmez[m][k] = cost;
		++num[k];
		++num[m];
	}

	long long min;
	int iMin = 0;
	while(iMin < INT_MAX)
	{
		min = LLONG_MAX;
		iMin = INT_MAX;
		for (int i = 0; i < N; ++i)
		{
			if (pos[i] == false && route[0][i] < min)
			{
				min = route[0][i];
				iMin = i;
			}
		}
		if (iMin != INT_MAX)
		{
			for (int i = 0; i < N; ++i)
			{
				if (MSmez[iMin][i] > 0 && route[0][i] > min + MSmez[iMin][i] + num[i])
				{
						route[0][i] = min + MSmez[iMin][i] + num[i];
						route[1][i] = iMin + 1;	
				}
			}
			pos[iMin] = true;
		}
	}
	vector<int>path;
	path.push_back(J + 1);
	for (int i = J; i > -1; i = route[1][i] - 1)
		path.push_back(route[1][i]);

	fprintf(cout, "%d", route[0][J] - num[J]);
	fprintf(cout, "%c", '\n');
	for (int i = path.size() - 2; i >= 0; --i)
	{
		fprintf(cout, "%d", path[i]);
		fprintf(cout, "%c", ' ');
	}

	fclose(cin);
	fclose(cout);
	delete[]MSmez;
	delete[]num;
	delete[]pos;
	delete[]route;
	path.clear();
	return 0;
}