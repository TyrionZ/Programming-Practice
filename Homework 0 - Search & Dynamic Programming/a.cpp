#include <bits/stdc++.h>
using namespace std;

const int N = 408, dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
int n, m, T, Tx, Ty;
bool defended[N][N], visited[N][N][20];
char s[N];

struct node {
	int x, y, c, d;

	node (int _x, int _y, int _c, int _d) :
	x(_x), y(_y), c(_c), d(_d) {}
} ;
queue<node> Q;

int main() {
	cin >> n >> m >> T;
	for (int i = 0; i < n; i++) {
		cin >> s;
		for (int j = 0; j < m; j++)
			if (s[j] == '@')
				Q.push(node(i, j, T, 0));
			else if (s[j] == '+')
				Tx = i, Ty = j;
			else if (s[j] == '#')
				defended[i][j] = true; 
	}
	
	while (!Q.empty()) {
		node u = Q.front(); Q.pop(); u.c -= defended[u.x][u.y];
		if (u.x < 0 || u.y < 0 || u.x >= n || u.y >= m || u.c < 0 || visited[u.x][u.y][u.c])
			continue ;
		visited[u.x][u.y][u.c] = true;	
		if (u.x == Tx && u.y == Ty)
			{printf("%d", u.d); return 0;}
		for (int k = 0; k < 4; k++)
			Q.push(node(u.x + dx[k], u.y + dy[k], u.c, u.d + 1));
	}

	puts("-1"); 
	return 0;
}