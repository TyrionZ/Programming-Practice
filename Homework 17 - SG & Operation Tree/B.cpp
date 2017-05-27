#include <bits/stdc++.h>
using namespace std;

int m, n, b[30];
void solve() {
	memset(b, 0, sizeof b);
	cin >> m >> n;
	for (int i = 0; i < m; i++) {
		int x; scanf("%d", &x);
		for (int j = 0; j < 30; j++)
			(b[j] += x & 1) %= (n + 1), x >>= 1;
	}
	for (int i = 0; i < 30; i++)
		if (b[i]) {puts("Yes"); return ;}
	puts("No");
}

int main() {
	int T; cin >> T;
	while (T--) 
		solve();
	return 0;
}