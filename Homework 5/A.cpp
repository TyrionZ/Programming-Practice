#include <iostream>
#include <string>
using namespace std;
template <class T>
void PrintArray(T *begin, T *end) {
	for (T *e = begin; e != end; e++)
		cout << *e << ',';
	cout << endl;
}
int main() {
	string array[4] = { "Tom","Jack","Mary","John"};
	PrintArray(array,array+4);
	int a[4] = { 1, 2, 3, 4};
	PrintArray(a,a+4);
	return 0;
}