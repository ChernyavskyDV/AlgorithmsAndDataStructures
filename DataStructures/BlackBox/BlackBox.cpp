#include<iostream>
#include<vector>

using namespace std;

void addToMinHeap(vector<int> &v, int n)
{
	v.push_back(n);
	for (int i = v.size() - 1; i > 0; i = i >> 1)
	{
		int iT = i >> 1;
		if (n < v[iT])
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

void deleteFromMinHeap(vector<int> &v)
{
	if (v.size() > 1)
	{
		int n = v[v.size() - 1];
		v[1] = v[v.size() - 1];
		v.erase(v.begin() + (v.size() - 1));
		for (int i = 1; i <= (v.size() - 1) >> 1;)
		{
			int iT = i << 1;
			if (iT <= v.size() - 2)
			{
				if (v[iT] <= v[iT + 1])
				{
					if (n > v[iT])
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
					if (n > v[iT + 1])
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
				if (n > v[iT])
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

void addToMaxHeap(vector<int> &v, int n)
{
	v.push_back(n);
	for (int i = v.size() - 1; i > 0; i = i >> 1)
	{
		int iT = i >> 1;
		if (n > v[iT])
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

void deleteFromMaxHeap(vector<int> &v)
{
	if (v.size() > 1)
	{
		int n = v[v.size() - 1];
		v[1] = v[v.size() - 1];
		v.erase(v.begin() + (v.size() - 1));
		for (int i = 1; i <= (v.size() - 1) >> 1;)
		{
			int iT = i << 1;
			if (iT <= v.size() - 2)
			{
				if (v[iT] >= v[iT + 1])
				{
					if (n < v[iT])
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
					if (n < v[iT + 1])
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
				if (n < v[iT])
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

int main()
{
	FILE* cin = fopen("input.txt", "r");
	FILE* cout = fopen("output.txt", "w");
	int M;
	fscanf(cin, "%d", &M);
	int N;
	fscanf(cin, "%d", &N);
	int *Add = new int[M];
	int *Get = new int[N];


	for (int i = 0; i < M; i++)
	{
		fscanf(cin, "%d", &Add[i]);
	}
	for (int i = 0; i < N; i++)
	{
		fscanf(cin, "%d", &Get[i]);
	}
	vector<int> minHeap;
	minHeap.push_back(-2000000001);
	vector<int> maxHeap;
	maxHeap.push_back(2000000001);
	int j = 0;
	addToMinHeap(minHeap, Add[0]);
	for (int i = 1; i <= M; i++)
	{
		while ((j < N) && (Get[j] == i))
		{
			addToMaxHeap(maxHeap, minHeap[1]);
			deleteFromMinHeap(minHeap);
			fprintf(cout, "%d", maxHeap[1]);
			if (j != N - 1)
			{
				fprintf(cout, "%c", ' ');
			}
			j++;
		}
		if (i < M)
		{
			if (maxHeap.size() < 2)
			{
				addToMinHeap(minHeap, Add[i]);
			}
			else
			{
				if (Add[i] >= maxHeap[1])
				{
					addToMinHeap(minHeap, Add[i]);
				}
				else
				{
					addToMinHeap(minHeap, maxHeap[1]);
					deleteFromMaxHeap(maxHeap);
					addToMaxHeap(maxHeap, Add[i]);
				}
			}
		}
	}
	fclose(cin);
	fclose(cout);
	delete[]Add;
	delete[]Get;
	return 0;
}