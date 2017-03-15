#include <iostream>
using namespace std;
class MyCin
{
public:
	istream &c;

	MyCin(): c(cin) {}
	friend MyCin& operator >>(MyCin &o, int &x) {
		o.c >> x;
		return o;
	}

	operator bool () {return bool(c);}
};


int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2) 
        cout  << n1 << " " << n2 << endl;
    return 0;
}