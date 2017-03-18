#include <iostream>
#include <cstdio>
using namespace std;
//#define MySharedPtr shared_ptr

template <class T> 
struct MySharedPtr
{
public:
	struct point {
		T *p;
		int count;
	} *mp;

	MySharedPtr(T* p = NULL) {
		mp = new point();
		mp->p = p;
		mp->count = 1;
	} ;

	MySharedPtr(const MySharedPtr &u) {(mp = u.mp)->count++;}
	
	T* get() {return mp->p;}

	void reset(T *x = NULL) {*this = MySharedPtr(x);}

	MySharedPtr& operator =(const MySharedPtr &u) {
		if (!(--mp->count) && mp->p)
			delete mp->p;
		(mp = u.mp)->count++;
		return *this;
	}

	T* operator ->() const {return mp->p;}

	T& operator *() {return *mp->p;}

	bool operator !() {return mp->p == NULL;}

	~MySharedPtr() {
		if (!(--mp->count) && mp->p)
			delete mp->p;
	}
};

struct A   {    
 	 int n;
	 A(int v = 0):n(v){ } 
	 ~A() { cout << n << " destructor" << endl; }
};


int main()
{
	freopen("output", "w", stdout);
	MySharedPtr<A> sp1(new A(2)); 
	MySharedPtr<A> sp2(sp1);        
	cout << "1)" << sp1->n  << "," << sp2->n << endl; 
	MySharedPtr<A> sp3;
	A * p = sp1.get();  
	cout << "2)" << p->n << endl;
	sp3 = sp1; 
	cout << "3)" << (*sp3).n << endl;  
	sp1.reset();     
	if( !sp1 )
		cout << "4)sp1 is null" << endl; //会输出 
	A * q = new A(3);
	sp1.reset(q); // 
	cout << "5)" << sp1->n << endl;
	MySharedPtr<A> sp4(sp1); 
	MySharedPtr<A> sp5;
	sp5.reset(new A(8));
	sp1.reset();          
	cout << "before end main" <<endl;
	sp4.reset();          
	cout << "end main" << endl;
	return 0; //程序结束，会delete 掉A(2)
}