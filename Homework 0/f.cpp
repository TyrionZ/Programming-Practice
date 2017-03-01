#include <bits/stdc++.h>
using namespace std;

int n;
int a[10][10], f[8][8][8][8][20];

int count(int x, int y, int _x, int _y) 
	{return a[x][y] + a[_x][_y] - a[x][_y] - a[_x][y];}

int square(int x) {return x * x;}

int find(int x, int y, int _x, int _y, int n) {
	int &dp = f[x][y][_x][_y][n];
	if (dp != -1) return dp; dp = 1e9;
	if (n == 1) return dp = square(count(x, y, _x, _y));
	for (int k = x + 1; k < _x; k++)
		dp = min(dp, find(x, y, k, _y, 1) + find(k, y, _x, _y, n - 1)),
		dp = min(dp, find(x, y, k, _y, n - 1) + find(k, y, _x, _y, 1));
	for (int k = y + 1; k < _y; k++)
		dp = min(dp, find(x, y, _x, k, n - 1) + find(x, k, _x, _y, 1)),
		dp = min(dp, find(x, y, _x, k, 1) + find(x, k, _x, _y, n - 1));
	return dp;
}

int main() {
	cin >> n;
	memset(f, -1, sizeof f);
	for (int i = 1; i <= 8; ++i)
		for (int j = 1; j <= 8; ++j)
			cin >> a[i][j], a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
	
	double average = (double)count(0, 0, 8, 8) / n;
	printf("%.3lf\n", sqrt(((double)find(0, 0, 8, 8, n) / n - average * average)));

	return 0;
}