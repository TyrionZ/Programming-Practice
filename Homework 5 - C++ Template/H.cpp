#include <iostream>
#include <cstring>
using namespace std;
template <int bitNum>

struct MyBitset 
{
	char a[bitNum/8+1];
	MyBitset() { memset(a,0,sizeof(a));};
	void Set(int i,int v) {
		char & c = a[i/8];
		int bp = i % 8;
		if( v ) 
			c |= (1 << bp);
		else 
			c &= ~(1 << bp);
	}

	struct byte {
		char *d; int x;

		byte() {}

		byte(char *_d, int _x) {d = _d; x = _x;}

		byte& operator =(int k) {
			if (k)
				*d |= (1 << x);
			else *d &= ~(1 << x);
			return *this;
		}

		operator int() {
			return (*d >> x) & 1;
		}

		byte& operator =(byte x) {
			*this = int(x);
			return *this;
		}
	} ;

	byte operator [](int pos) {
		int x = pos / 8, y = pos % 8;
		return byte(a + x, y);
	}

	void Print() {
		for(int i = 0;i < bitNum; ++i) 
			cout << (*this) [i];
		cout << endl;
	}

};

int main()
{
	int n;
	int i,j,k,v;
	while( cin >>  n) {
		MyBitset<20> bs;
		for(int i = 0;i < n; ++i) {
			int t;
			cin >> t;
			bs.Set(t,1);
		}
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		bs[i] = bs[j] = bs[k];
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		(bs[i] = bs[j]) = bs[k];
		bs.Print();
	}
	return 0;
}