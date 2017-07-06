#include <iostream>
#include <cstdio>
#include <math.h>
#include <iomanip>

using namespace std;

struct Point
{
	double x;
	double y_r;
};

int main()
{
	freopen("in.txt", "r", stdin);

	int n;
	cin>>n;

	double number;
	Point *points = new Point[n+1];
	for (int i = 0; i < n; i++)
	{
		cin>>number;
		points[i].y_r = number;
	}
	
	double h;
	double k;
	double length;
	points[0].x = points[0].y_r;
	for (int i = 1; i < n; i++)
	{
		h = points[i-1].y_r + points[i].y_r;
		k = abs(points[i].y_r - points[i-1].y_r);
		length = sqrt((h * h) - (k * k));
		points[i].x = points[i-1].x + length;
		for (int j = i-2; j > -1; j--)
		{
			h = points[j].y_r + points[i].y_r;
			k = abs(points[i].y_r - points[j].y_r);
			length = sqrt((h * h) - (k * k));
			if (points[j].x + length > points[i].x)
			{
				points[i].x = points[j].x + length;
			}
		}
	}
	double MIN; 
	MIN= points[0].x - points[0].y_r;
	double MAX;
	MAX = points[0].x + points[0].y_r;
	for(int i = 1; i < n; i++)
	{
		if (MIN > points[i].x - points[i].y_r)
		{
			MIN = points[i].x - points[i].y_r;
		}
		if (MAX < points[i].x + points[i].y_r)
		{
			MAX = points[i].x + points[i].y_r;
		}
	}

	double result;
	result = MAX - MIN;

	freopen("out.txt", "w", stdout);
	cout<<fixed<<setprecision(5)<<result;
	
	return 0;
}