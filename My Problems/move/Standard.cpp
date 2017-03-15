/*
知识点：右值引用和转移语义

题面：
补足A类，使程序输出指定结果

输入

多组数据，每组一行，是两个整型数字。

输出

对每组数据，先输出一行，打印输入中的数字。
然后再输出一行，打印输入中数字交换后的结果。

输入样例

3 5

输出样例 

3,5
5,3

*/
#include <iostream>
using namespace std;

class A {
public:
	int d;

	A(const int _d = 0): d(_d) {}

	A(const A& u) {
		d = u.d;
		cout << "Copy Construct is called!" << endl;
	}
	
	A& operator =(const A &u) {
		d = u.d;
		cout << "Copy Assignment is called!" << endl;
		return *this;
	}
//your code starts here
	A& operator =(A &&u) {
		d = u.d;
		u.d = 0;
		return *this;
	}

	A(A &&u) {
		d = u.d;
		u.d = 0;
	}

	void swap(A &b) {
		A t(move(*this));
		*this = move(b);
		b = move(t);
	}
//your code ends here
} ;

int main() {
	int x, y;
	while (cin >> x >> y) {
		A a, b;
		a.d = x;
		b.d = y;
		cout << a.d << ',' << b.d << endl;
		a.swap(b);
		cout << a.d << ',' << b.d << endl;
	}
	return 0;
}