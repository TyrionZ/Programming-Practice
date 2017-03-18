#include <iostream>
using namespace std;

template<typename T1, typename T2>
auto f = [](T1 a) {
	return [a](T2 b) {
		return b + a;
	} ;
} ;

int main()
{

   cout << f<int,int>(7)(9) << endl;   //16
   cout << f<string,string> (" hello!")("world")  <<endl; // world hello!
   cout << f<char,string> ('!')("world") << endl;
   
   
   return 0;    //world!
}