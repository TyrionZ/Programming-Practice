#include <iostream>
using namespace std;
class MyCin
{
public:
	template<class T>
	istream& operator >>(T &a) {
		cin >> a;
		if (a == -1) 
			while (cin >> a) ;

		return cin;
	} 
};
int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2) 
        cout  << n1 << " " << n2 << endl;
    return 0;
}