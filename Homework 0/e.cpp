#include <cstring>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const int N = 208;
int n, m, a[N], color[N], num[N], dp[N][N][N];

int square(int x) {return x * x;}

int find(int l, int r, int len) {
	if (dp[l][r][len])
		return dp[l][r][len];
	if (l == r - 1)
		return dp[l][r][len] = square(num[l] + len);
	dp[l][r][len] = find(l, r - 1, 0) + square(len + num[r - 1]);
	for (int k = l; k < r - 1; k++)
		if (color[k] == color[r - 1])
			dp[l][r][len] = max(dp[l][r][len], find(l, k + 1, num[r - 1] + len) + find(k + 1, r - 1, 0));
	return dp[l][r][len];
}

void solve() {
	cin >> n; m = 0;
	memset(dp, 0, sizeof dp);
	for (int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		if (a[i] == a[i - 1])
			num[m - 1]++;
		else 
			color[m] = a[i], num[m++] = 1;
	}

	cout << find(0, m, 0) << endl;
}

int main() {
	int cases; cin >> cases;
	for (int i = 1; i <= cases; ++i)
		printf("Case %d: ", i), solve();
	return 0;
}