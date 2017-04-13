#include <bits/stdc++.h>
using namespace std;

int n, k, d[55][55][55], dd[55][55], ddd[55][55];

long long divide(int n, int k, int sup = 51) {
	if (n < 0) return 0;
	if (!k) 
		return !n;
	if (d[n][k][sup] != -1) 
		return d[n][k][sup];
	d[n][k][sup] = 0;
	for (int i = sup; i; --i)
		d[n][k][sup] += divide(n - i, k - 1, i);
	return d[n][k][sup];
}

long long divide_diversity(int n, int sup = 50) {
	if (!n) return 1;
	if (n < 0) return 0;
	if (dd[n][sup] != -1) 
		return dd[n][sup]; 
	dd[n][sup] = 0;
	for (int i = sup; i; --i)
		dd[n][sup] += divide_diversity(n - i, i - 1);
	return dd[n][sup];
}

long long divide_odd(int n, int sup = 49) {
	if (!n) return 1;
	if (n < 0) return 0;
	int &x = ddd[n][sup];
	if (x != -1) return x;
	x = 0;
	for (int i = sup; i > 0; i -= 2) 
		ddd[n][sup] += divide_odd(n - i, i);
	return x;
}

int main() {
	memset(d, -1, sizeof d);
	memset(dd, -1, sizeof dd);
	memset(ddd, -1, sizeof ddd);
	while (cin >> n >> k) 
		cout << divide(n, k) << endl << divide_diversity(n) << endl << divide_odd(n) << endl;
	return 0;
}