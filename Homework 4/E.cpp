#include <bits/stdc++.h>
using namespace std;

int n;
map<int, int> M;
map<int, int>::iterator p;
int main() {
	M[1000000000] = 1;
	cin >> n;
	while (n--) {
		int index, power; 
		scanf("%d%d", &index, &power);

		p = M.lower_bound(power);
		int opponent = p->first;
		if (p != M.begin()) {
			p--;
			if (power - p->first <= opponent - power)
				opponent = p->first;
		} 
		printf("%d %d\n", index, M[opponent]);
		M[power] = index;
	
	}
	return 0;
}