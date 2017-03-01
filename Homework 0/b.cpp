#include <bits/stdc++.h>
using namespace std;

int N, M, ans, mv[50][100][25], ms[25];

int max_volume(int r, int h, int m) {
	if (!m) return 0;
	if (r <= 40 && m <= 90 && mv[r][h][m]) 
		return mv[r][h][m];
	int x = max_volume(r - 1, h - 1, m - 1) + r * r * h;
	if (r <= 40 && m <= 90) mv[r][h][m] = x;
	return x;
}

bool search(int n, int m, int s, int r, int h) {
	if (n < 0 || s + ms[m] >= ans || max_volume(m, m, m) > n) 
		return false;
	if (r < 0 || h < 0 || max_volume(r, h, m) < n) 
		return true;

	if (!m) {
		if (!n)
			{ans = min(ans, s); return false;}
		return true;
	}

	for (int i = r; i >= m; i--)
		for (int j = h; j >= m; j--) 
			if (search(n - i * i * j, m - 1, s + 2 * i * j + (m == M) * i * i, i - 1, j - 1))
				break ;
	return false;
}

int main() {
	for (int i = 1; i <= 21; i++)
		ms[i] = ms[i - 1] + 2 * i * i;

	while (cin >> N >> M) {
		int R = sqrt((N - max_volume(M - 1, M - 1, M - 1)) / M) + 1;
		int H = (N - max_volume(M - 1, M - 1, M - 1)) / (M * M) + 1;
		ans = 1 << 30; search(N, M, 0, R, H);
		cout << (ans == (1 << 30) ? 0 : ans) << endl;
	}

	return 0;
}