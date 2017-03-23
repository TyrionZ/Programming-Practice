#include <bits/stdc++.h>
using namespace std;

multiset<pair<int, int> > s;
int divide(int x) {
	int res = 0;
	for (int i = 2; i * i <= x; i++) 
		if (x % i == 0) {
			++res;
			while (x % i == 0)
				x /= i;
		}
	if (x != 1 && res) ++res;
	return res;
}

int main() {
	int T;
	for (cin >> T; T; T--) {
		for (int x, i = 0; i < 10; i++)
			scanf("%d", &x), s.insert(make_pair(divide(x), x));
		printf("%d %d\n", s.rbegin()->second, s.begin()->second);
		auto it = s.begin();
		s.erase(it); 
		it = s.end();
		--it;
		s.erase(it);
	}
	return 0;
}