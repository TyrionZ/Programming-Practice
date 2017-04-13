#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
	int **a;
public:
	Array2(int r = 0, int c = 0) {
		r++, c++;
		a = new int*[r];
		for (int i = 0; i < r; i++)
			a[i] = new int[c];
	}

	int*& operator[](int x) {
		return a[x];
	}

	int& operator()(int x, int y) 
		{return a[x][y];}
};

int main() {

    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }

    return 0;
}