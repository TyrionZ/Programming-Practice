/*
知识点：运算符重载
题面：
自己完成mmp类，使程序输出指定结果

输入
无

输出

"1"
1
1
'1'
7.9
1

输入样例

无

输出样例 

"1"
1
1
'1'
7.9
1

*/
#include <iostream>
#include <string>
using namespace std;


class mmp {
// your code starts here.
public:
	class element {
	public:
		string s;
		int type, i;
		double d;
		char c;

		element() {}

		element(const char *u)
			: s(u), type(0) {}

		element(char u) 
			: c(u), type(1) {}

		element(int u) 
			: i(u), type(2) {}

		element(double u) 
			: d(u), type(3) {}

		bool operator ==(const element &u) const {
			if (type != u.type) return false;
			switch (type) {
				case 0: return s == u.s;
				case 1: return c == u.c;
				case 2: return i == u.i;
				case 3: return d == u.d;
			}
		}

		void print() {
			switch (type) {
				case 0: 
					cout << '\"' << s << '\"' << endl;
					break ;
				case 1: 
					cout << '\'' << c << '\'' << endl;
					break ;
				case 2: 
					cout << i << endl;
					break ;
				case 3: 
					cout << d << endl;
					break ;
			}
		}
	} A[20], B[20];
	int total;

	
	element& operator[](element e) {
		for (int i = 0; i < total; i++)
			if (A[i] == e) return B[i];
		A[total] = e;
		return B[total++];
	}
// your code ends here.
} M;


int main() {
	M[1] = "1";
	M[1].print();
	M["1"] = 1;
	M["1"].print();
	M['1'] = M["1"];
	M['1'].print();
	M[2.3] = '1';
	M[2.3].print();
	M[2.3] = 7.9;
	M[2.3].print();
	M[7.9] = M['1'];
	M[7.9].print();
	return 0;
}