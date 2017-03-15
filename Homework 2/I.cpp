#include <iostream> 
using namespace std;
class Point { 
	private: 
		int x; 
		int y; 
	public: 
		Point() {x = y = 0;};

	friend istream& operator >>(istream &i, Point &u) {
		i >> u.x >> u.y;
		return i;
	}
	
	friend ostream& operator <<(ostream &o, Point u) {
		o << u.x << ',' << u.y << endl;
		return o;
	}
}; 

int main() 
{ 
 	Point p;
 	while(cin >> p) {
 		cout << p << endl;
	}
	return 0;
}