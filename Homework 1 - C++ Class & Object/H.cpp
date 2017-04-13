#include <iostream> 
#include <cstring> 
#include <cstdlib> 
#include <cstdio> 
using namespace std;
const int MAX = 110; 
class CHugeInt {
private:
	int len, a[210];
	
public:
	CHugeInt(int x = 0) {
		memset(a, 0, sizeof a);
		for (len = 0; x; x /= 10)
			a[len++] = x % 10;
	}

	CHugeInt(char *s) {
		memset(a, 0, sizeof a);
		len = strlen(s);
		for (int i = 0; i < len; i++)
			a[i] = s[len - i - 1] - '0';
	}

	CHugeInt operator +(const CHugeInt &u) const {
		CHugeInt c; c.len = max(len, u.len);
		for (int i = 0; i < c.len; i++)
			c.a[i + 1] = (c.a[i] + a[i] + u.a[i]) / 10, c.a[i] = (c.a[i] + u.a[i] + a[i]) % 10;
		if (c.a[c.len]) c.len++;
		return c;
	}

	CHugeInt& operator +=(const CHugeInt &u) 
		{return *this = *this + u;} 

	friend CHugeInt operator +(int a, const CHugeInt &b) ;
	friend ostream& operator <<(ostream & o, CHugeInt u) ;
	//普通函数不能访问私有成员，需要重载为友元函数。

	CHugeInt& operator +=(int x) 
		{return *this += CHugeInt(x);}

	CHugeInt& operator ++() 
		{return *this += 1;}
	
	CHugeInt operator ++(int u) {
		CHugeInt r = *this;
		++*this;
		return r;
	}

	
};

CHugeInt operator +(int a, const CHugeInt &b) 
	{return CHugeInt(a) + b;}

ostream& operator <<(ostream & o, CHugeInt u) {
	for (int i = u.len - 1; i >= 0; i--)
		o << u.a[i];
	if (!u.len) o << 0;
	return o;
}

int  main() 
{ 
	char s[210];
	int n;

	while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout  << ++ b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}
	return 0;
}