#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
using namespace std;
class MyClass {	
public:
	int n;
	
	MyClass(int m):n(m) {}
	
	void f() {cout << n << " func." << endl;}
};

class MyAny {
private:
	class baseValue {
	public:
		virtual const type_info& type() const 
			{return typeid(void);};

		virtual baseValue* clone() const {return NULL;}
		
		virtual ~baseValue() {};
	} *content;
	template <typename T>
	class value:public baseValue {
	public:
		T v;
	
		value(const T &_v):v(_v) {}
		const T& getValue() {return v;}

		const type_info& type() const {
			return typeid(T);
		}

		baseValue* clone() const 
			{return new value(v);}

		~value() {}
	};

	const type_info& type() const 
	 	{return content->type();}
public:
	template<typename T>
	MyAny(const T &v): content(new value<T>(v)) {}

	MyAny(const MyAny &u) {content = u.content->clone();}

	MyAny& operator =(const MyAny &u) {
		content = u.content->clone();
		return *this;	
	}

	const MyAny* operator &() const {return this;}

	~MyAny() {if (content) delete content;}

	template<typename T>
	friend T* MyAny_cast(const MyAny *u) {
		return typeid(T) == u->type() ?
			&(reinterpret_cast<MyAny::value<T>* >(u->content)->v) : NULL;
	}

	template<typename T>
	friend T MyAny_cast(const MyAny &u) {
		return reinterpret_cast<MyAny::value<T>* >(u.content)->v;
	}
} ;


int main() 
{
	while(true) {
		int n;
		string s;
		cin >>  n >> s;
		if ( n == 0)
			break;
		MyAny a = n;
	 	cout << MyAny_cast<int>(a) << endl;
		a = s;
		cout << MyAny_cast<string>(a) << endl;
		a = MyClass(n+1);
		MyAny b = n + 2;
		MyAny * p = new MyAny(MyClass(n+3));
		MyAny c = MyClass(n+4);
	 	c = * p;
	  	b = * p;
		delete p;
		MyAny d = b;
		MyAny_cast<MyClass>(&a)->f();
		MyAny_cast<MyClass>(&b)->f();	
		MyAny_cast<MyClass>(&c)->f();	
		MyAny_cast<MyClass>(&d)->f();		
		c = s + "OK";
		cout << MyAny_cast<string>(c) << endl;	
		int * pi = MyAny_cast<int> ( & c);
		if( pi == NULL)
			cout << "not a int" << endl;
		else
			cout << "the int is " << * pi << endl;
		string * ps = MyAny_cast<string> ( & c);
		if( ps == NULL)
			cout << "not a string" << endl;
		else
			cout << "the string is " << * ps << endl;
	}

	return 0;
}