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
			if (power - p->first < opponent - power)
				opponent = p->first;
			else if (power - p->first == opponent - power)
				if (p->second < M[opponent]) opponent = p->first;
		} 
		printf("%d %d\n", index, M[opponent]);
		if (!M[power])
			M[power] = index;
		else M[power] = min(M[power], index);
	
	}
	return 0;
}