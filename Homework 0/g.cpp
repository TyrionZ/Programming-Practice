#include <bits/stdc++.h>
using namespace std;

const int N = 108, K = 10008;
int n, m, k, dis[N][K];
bool inQueue[N];
queue<int> Q;

struct edge {
	int point, dist, cost;
	edge *next;
} *head[N];

void add_edge(int u, int v, int d, int c) {
	edge *e = new edge(); 
	e->point = v; e->dist = d; e->cost = c;
	e->next = head[u]; head[u] = e;
}
int main() {
	cin >> k >> n >> m;
	while (m--) {
		int u, v, d, c;
		scanf("%d%d%d%d", &u, &v, &d, &c);
		add_edge(u, v, d, c);
	}

	memset(dis, 1, sizeof dis);

	dis[1][k] = 0; Q.push(1);
	while (!Q.empty()) {
		int u = Q.front(); 
		Q.pop(); inQueue[u] = false;

		for (edge *e = head[u]; e; e = e->next) 
			for (int i = e->cost; i <= k; i++)
				if (dis[u][i] + e->dist < dis[e->point][i - e->cost]) {
					dis[e->point][i - e->cost] = dis[u][i] + e->dist;
					if (!inQueue[e->point]) Q.push(e->point), inQueue[e->point] = true;
				}
	}

	int ans = 1e9;
	for (int i = 0; i <= k; i++) 
		ans = min(ans, dis[n][i]);
	cout << (ans <= 1e5 ? ans : -1) << endl;
	
	return 0;
}