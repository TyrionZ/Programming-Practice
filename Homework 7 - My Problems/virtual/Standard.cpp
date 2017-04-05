/*
知识点：多态
题面：
完成A，B类，使程序输出指定结果

输入

多组数据，每组一行，是两个整型数字。

输出

对每组数据，先输出一行，打印输入中的数字。
然后再输出一行，打印输入中数字inc后的结果。

输入样例

3 4

输出样例 

3,4
4,6

*/
#include <iostream>
using namespace std;

// your code starts here.
class A {
public:
	int d;

	A(const int _d): d(_d) {} 
	virtual void inc() {
		d++;
	}
} ;

class B: public A {
public:
	B(const int _d): A(_d) {}
	void inc() {
		d += 2;
	}
} ;

// your code ends here.
int main() {
	int x, y;
	while (cin >> x >> y) {
		A *a, *b;
		a = new A(x);
		b = new B(y);
		cout << a->d << ',' << b->d << endl;
		a->inc(); b->inc();
		cout << a->d << ',' << b->d << endl;
	}
	return 0;
}