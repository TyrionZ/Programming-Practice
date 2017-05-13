#include <iostream>
#include <cmath>
using namespace std;

class Vector {
private:
	int a[30], len;
public:
	Vector(int m): len(m) {}

	friend istream& operator >>(istream &is, Vector &u) {
		for (int i = 0; i < u.len; i++)
			is >> u.a[i];
		return is;
	}

	friend ostream& operator <<(ostream &os, const Vector &u) {
		for (int i = 0; i < u.len; i++)
			os << u.a[i] << (i != u.len - 1 ? "," : "");
		return os;
	}

	Vector operator +(const Vector &u) const {
		Vector r = Vector(len);
		for (int i = 0; i < len; i++)
			r.a[i] = u.a[i] + a[i];
		return r;
	}

	Vector& operator +=(const Vector &u) {
		return *this = *this + u;
	}

	int operator [](int x) {
		return a[x];
	}

	long long operator *(const Vector &u) const {
		long long res = 0;
		for (int i = 0; i < len; i++)
			res += u.a[i] * a[i];
		return res;
	}

	Vector operator *(int k) const {
		Vector r = Vector(len);
		for (int i = 0; i < len; i++)
			r.a[i] = k * a[i];
		return r;
	}

	double mo() {
		double r = 0;
		for (int i = 0; i < len; i++)
			r += a[i] * a[i];
		return sqrt(r);
	}
};

int main() {
    int n, m, c;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> m;
        Vector a(m), b(m);
        cin >> a >> b >> c;
        a += b;
        Vector d(b * c);
        cout << a + d << endl;
        cout << d * c << endl;
        cout << b.mo() << endl;
        cout << a[0] << endl;
        cout << endl;
    } return 0;
}