#include <bits/stdc++.h>
using namespace std;

int n;
string s[20];

int get_int() ;

int to_digit(string &s) {
	if (s.length() > 5) 
		return -1;
	int res = 0;
	for (int i = 0; i < s.length(); i++) {
		if (!isdigit(s[i])) 
			return -1;
		res = res * 10 + s[i] - '0';
	}
	return res;
} 

string i_string(int x) {
	char c[10];
	int len = 0, t = x;
	while (t) 
		t /= 10, ++len;
	if (!len) ++len;
	c[len] = 0;
	while (x)
		c[--len] = x % 10 + '0', x /= 10;
	return string(c);
} 

string get_string() {
	string op;
	cin >> op;
	if (op == "copy") {
		int n = get_int() - 1, x = get_int(), l = get_int();
		return s[n].substr(x, l);
	}
	if (op == "add") {
		string x = get_string(), y = get_string();
		int a = to_digit(x), b = to_digit(y);
		if (a != -1 && b != -1)
			return i_string(a + b);
		return x + y;
	}
	return op;
}

int get_int() {
	string op;
	cin >> op;
	if (op == "find") {
		string t = get_string();
		int n = get_int() - 1;
		auto found = s[n].find(t);
		if (found != string::npos)
			return found;
		return s[n].length();
	}
	if (op == "rfind") {
		string t = get_string();
		int n = get_int() - 1;
		auto found = s[n].rfind(t);
		if (found != string::npos)
			return found;
		return s[n].length();
	}
	if (op == "add") {
		int x = get_int(), y = get_int();
		return x + y;
	}
	return to_digit(op);
}
void insert() {
	string t = get_string();
	int n = get_int() - 1, x = get_int();
	s[n].insert(x, t);
}

void reset() {
	string t = get_string();
	int n = get_int() - 1;
	s[n] = t;
}

void print() {
	int n = get_int() - 1;
	cout << s[n] << endl;
}

void printall() {
	for (int i = 0; i < n; i++)
		cout << s[i] << endl;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> s[i];
	while (true) {
		string op;
		cin >> op;
		if (op == "over")
			break ;
		if (op == "reset") reset();
		else if (op == "insert") insert();
		else if (op == "print") print();
		else if (op == "printall") printall();
	}
	return 0;
}