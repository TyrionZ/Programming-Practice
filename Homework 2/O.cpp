#include <iostream>
#include <iomanip> 
#include <cstring>
using namespace std;
template <class T>
class CArray3D
{
public:
	class Array2 {
	public:
		T *a; int r, c;
		Array2(int _r = 4, int _c = 5) 
			:r(_r), c(_c) {a = new T[r * c];}

		T* operator[](int x) {return a + x * c;}

		operator T*() {return a;}
	} *a; 
	int u, v, w;

	CArray3D(int x = 0, int y = 0, int z = 0)
		: u(x), v(y), w(z) {a = new Array2[x];}

	Array2& operator [](int x) {return a[x];}

	void PrintAll() {
		for( int i = 0; i < u; ++ i ) {
			cout << "layer " << i << ":" << endl;
			for( int j = 0; j < v; ++j ) {
				for( int k = 0; k < w; ++k )
					cout << a[i][j][k] << ',';
				cout << endl;
			}
		}
	}
};

int main()
{
	CArray3D<int> a(3,4,5);
	int No = 0;
	for( int i = 0; i < 3; ++ i )
		for( int j = 0; j < 4; ++j )
			for( int k = 0; k < 5; ++k )
				a[i][j][k] = No ++;
	a.PrintAll();
	memset(a[1],-1 ,20*sizeof(int));
	a.PrintAll();
	memset(a[1][1],0 ,5*sizeof(int));	
	a.PrintAll();
	CArray3D<double> b(3,2,2);
	for( int i = 0; i < 3; ++ i )
		for( int j = 0; j < 2; ++j )
			for( int k = 0; k < 2; ++k )
				b[i][j][k] = 10.0/(i+j+k+1);
	b.PrintAll(); 
	return 0;
}