#include <cstdlib>
#include <iostream>
using namespace std;
int strlen(const char * s) 
{	int i = 0;
	for(; s[i]; ++i);
	return i;
}
void strcpy(char * d,const char * s)
{
	int i = 0;
	for( i = 0; s[i]; ++i)
		d[i] = s[i];
	d[i] = 0;
		
}
int strcmp(const char * s1,const char * s2)
{
	for(int i = 0; s1[i] && s2[i] ; ++i) {
		if( s1[i] < s2[i] )
			return -1;
		else if( s1[i] > s2[i])
			return 1;
	}
	return 0;
}
void strcat(char * d,const char * s)
{
	int len = strlen(d);
	strcpy(d+len,s);
}
class MyString
{
public:
	int len; char s[30];
	MyString() {s[len = 0] = 0;}
	MyString(char *_s) {
		len = strlen(_s);
		for (int i = 0; i < len; i++)
			s[i] = _s[i];
		s[len] = 0;
	}

	MyString& operator +=(MyString u) {
		len += u.len;
		strcat(s, u.s);
		return *this;
	} 

	MyString operator +(MyString u) {
		MyString r = *this;
		return r += u;
	}

	bool operator ==(MyString u) {
		if (len == u.len) {
			for (int i = 0; i < len; i++)
				if (s[i] != u.s[i]) 
					return false;
			return true;
		}
		return false;
	}

	bool operator <(MyString u) {
		if (*this == u)
			return false;
		for (int i = 0; ; i++) 
			if (s[i] != u.s[i])
				return s[i] < u.s[i];
	}

	bool operator >(MyString u) 
		{return !(*this == u || *this < u);}

	char* operator ()(int start, int len) {
		static char str[30];
		for (int i = 0; i < len; i++)
			str[i] = s[start + i];
		return str;
	}

	char& operator [](int pos) 
		{return s[pos];}
	
	friend MyString operator +(char *s, MyString u) ;
};

MyString operator +(char *s, MyString u) 
	{return MyString(s) + u;}

int CompareString( const void * e1, const void * e2)
{
	MyString * s1 = (MyString * ) e1;
	MyString * s2 = (MyString * ) e2;
	if( * s1 < *s2 )
	return -1;
	else if( *s1 == *s2)
	return 0;
	else if( *s1 > *s2 )
	return 1;
}

ostream& operator <<(ostream &o, MyString x) {
	o << x.s;
	return o;
}

int main()
{
	MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
	MyString SArray[4] = {"big","me","about","take"};
	cout << "1. " << s1 << s2 << s3<< s4<< endl;
	s4 = s3;
	s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A' ;
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
	qsort(SArray,4,sizeof(MyString),CompareString);
	for( int i = 0;i < 4;i ++ )
	cout << SArray[i] << endl;
	//s1的从下标0开始长度为4的子串
	cout << s1(0,4) << endl;
	//s1的从下标5开始长度为10的子串
	cout << s1(5,10) << endl;
	return 0;
}