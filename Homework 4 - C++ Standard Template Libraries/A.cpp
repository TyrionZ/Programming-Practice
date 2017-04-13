#include <bits/stdc++.h>
using namespace std;

list<int> seq[10008];

int main() {
	int T;
	for (cin >> T; T; T--) {
		char s[10]; int x, y;
		scanf("%s%d", s, &x);
		switch (s[0]) {
			case 'a':
				scanf("%d", &y);
				seq[x].push_back(y);
				break ;
			case 'o':
				seq[x].sort();
				for (auto it : seq[x])
					printf("%d ", it);
				puts("");
				break ;
			case 'm':
				scanf("%d", &y);
				seq[x].merge(seq[y]);
				break ;
			case 'u':
				seq[x].sort();
				seq[x].unique();
				break ;
			case 'n':
				list<int> ().swap(seq[x]);
				break ;
		}
	}
	return 0;
}