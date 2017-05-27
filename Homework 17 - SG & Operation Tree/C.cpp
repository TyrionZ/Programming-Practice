#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5 + 8, maxDepth = 20;
int dep[maxN], f[maxN][maxDepth];
vector<int> val, ope;

void explore(int u, int fa) {
	dep[u] = dep[f[u][0] = fa] + 1;
	for (int i = 1; i < maxDepth; ++i)
		f[u][i] = f[f[u][i - 1]][i - 1];
}

int find(int u, int depth) {
	for (int i = maxDepth - 1; i >= 0; --i)
		if (dep[f[u][i]] >= depth)
			u = f[u][i];
	return u;
}

void solve() {
	int T, lastAns = 0; cin >> T;
	val.clear(); ope.clear();
	ope.push_back(0);
	while (T--) {
		int a, b; scanf("%d%d", &a, &b);
		a ^= lastAns, b ^= lastAns;
		if (a == 1) {
			val.push_back(b);
			explore(val.size(), ope.back());
			ope.push_back(val.size()); 
		}
		else if (a == 2)
			ope.push_back(ope[ope.size() - b - 1]);
		else
			printf("%d\n", lastAns = val[find(ope.back(), b) - 1]);
	}
}

int main() {
	int T; cin >> T;
	while (T--) solve();
	return 0;
}