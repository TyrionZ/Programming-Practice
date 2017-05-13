#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
template<class T>
class Array{
	public:
	virtual Array* operator [] (int K){};
	virtual operator T(){};
};

template<typename T, int dim>
class DArray:public Array<T> {
private:
	T *a;
	vector<int> s;
	int depth;
public:
	DArray() {}
	DArray(vector<int> size): s(size) {}

	void init() {
		depth = 0;
		int count = 1;
		for (int i = 0; i < dim; i++)
			count *= s[i];
		a = new T[count];
		for (int i = 0; i < count; i++)
			cin >> a[i];
	}

	Array<T>* operator [](int K) {
		int count = 1;
		static DArray<T, dim> r(s);
		for (int i = depth + 1; i < dim; i++)
			count *= s[i];
		r.a = a + K * count;
		r.depth = depth + 1;
		return &r;
	}

	operator T() {return *a;}
} ;

// 在此处补充你的代码
int main(){
	freopen("input", "r", stdin);
	ios::sync_with_stdio(false); //主要是加快 cin 和 cout的速度 
	int n=5,q; vector<int>size;
	for (int i=1;i<=n;i++){
		int si; 
		cin>>si; size.push_back(si);
		//读入五维数组每一维的大小放入vector si中 
	}
	DArray<int,5> A(size);
	A.init(); cin>>q;
	//对五维数组的访问次数 
	for (int i=1;i<=q;i++){
		Array<int>*K=&A;
		//每一次访问输入 5 个数表示访问位置的下标 
		for (int j=1;j<=n;j++){
			int x; cin>>x; K=(*K)[x];
		}
		cout<<(*K)<<endl;
	}
	
	n=10; size.clear();
	for (int i=1;i<=n;i++){
		int si; cin>>si; size.push_back(si);
		//读入十维数组每一维的大小放入vector si中 
	}
	DArray<double,10> B(size);
	B.init(); 
	cin>>q;
	//对十维数组的访问次数 
	for (int i=1;i<=q;i++){
		Array<double>*K=&B;
		//每一次访问输入 10 个数表示访问位置的下标 
		for (int j=1;j<=n;j++){
			int x; cin>>x; K=(*K)[x];
		}
		cout<<(*K)<<endl;
	}
}