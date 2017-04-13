#include <bits/stdc++.h>
using namespace std;

priority_queue<double, vector<double>, greater<double> > h;
stack<double> num;

double calc(char opt) {
	double x = num.top(); num.pop();
	double y = num.top(); num.pop();
	if (opt == '+')
		return x + y;
	if (opt == '-')
		return y - x;
	if (opt == '*')
		return x * y;
	if (opt == '/')
		return y / x;
	if (opt == '^')
		return pow(y, x);
}

int main() {
	int n; cin >> n;
	char s[30]; double x;
	for (int i = 0; i < n; i++)
		scanf("%lf", &x), h.push(x);
	while(scanf("%s", s) != EOF) {
		if (strlen(s) > 1 || isdigit(s[0]))
			sscanf(s, "%lf", &x), num.push(x);
		else if (s[0] == '=') {
			printf("%e\n", num.top());
			h.pop(); 
			h.push(num.top());
			num.pop();
		}
		else num.push(calc(s[0]));
	}
	for (int i = 0; !h.empty(); ++i, h.pop()) {
		if (i % 10 == 0) puts("");
		printf("%e ", h.top());
	}
	return 0;
}