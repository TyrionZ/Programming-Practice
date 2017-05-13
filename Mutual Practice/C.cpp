#include <iostream>
using namespace std;

class Error{
public:
	string info;
	Error(const char*s="Error"):info(s){}
};

class DividedByZero:public Error{
public:
	DividedByZero(const char*s="Error"):Error(s){}
};
class FunctionFail:public Error{
public:
	FunctionFail(const char*s="Error"):Error(s){}
};

int divide(int a,int b){
	if (b == 0) {
		cout << "divided by 0" << endl;
		throw FunctionFail("divide() fails because b==0");
	}
	if (a == 0) 
		throw FunctionFail("divide() fails because a==0");
	return a / b;
}

int func(int a, int b){
	try{
		return divide(a,b);
	}
	catch(FunctionFail& e){
		cout<<e.info<<endl;
		return 0;
	}
}

int main(){	
	int a,b;
	while (cin>>a>>b){
		int c=func(a,b);
		cout<<c<<endl;
	}
	return 0;
}