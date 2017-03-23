#include <bits/stdc++.h>
using namespace std;

multiset<int> s;
map<int, bool> m;

int main() {
	int T;
	for (cin >> T; T; T--) {
		char opt[10]; int x;
		scanf("%s%d", opt, &x);
		if (opt[1] == 'd') {
			s.insert(x), m[x] = true;
			printf("%d\n", s.count(x));
		}
		else if (opt[1] == 'e') {
			printf("%d\n", s.count(x));
			s.erase(x);
		}
		else 
			printf("%d %d\n", m[x] ? 1 : 0, s.count(x));
	}

	return 0;
}