#include <bits/stdc++.h>
using namespace std;

bool vis[100];
int sg[30], a[30], n, T;

void solve() {
	int count = 0;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		count ^= (a[i] & 1) * sg[n - i - 1];
	}

	cout << "Game " << ++T << ':';
	if (count) {
		for (int i = 0; i < n; ++i) 
			if (a[i]) for (int j = i + 1; j < n; ++j)
				for (int k = j; k < n; ++k)
					if (!(count ^ sg[n - i - 1] ^ sg[n - j - 1] ^ sg[n - k - 1]))
						{printf(" %d %d %d\n", i, j, k); return ;}
	} 
	puts(" -1 -1 -1");
}
int main() {
	sg[0] = 0;
	for (int i = 1; i <= 23; i++) {
		memset(vis, 0, sizeof vis);
		for (int j = 0; j < i; j++)
			for (int k = 0; k < i; k++)
				vis[sg[j] ^ sg[k]] = true;
		while (vis[sg[i]]) ++sg[i];
	}

	while (cin >> n, n != 0) solve();

	return 0;
}