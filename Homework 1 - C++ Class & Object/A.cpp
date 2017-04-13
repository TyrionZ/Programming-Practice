#include <bits/stdc++.h>
using namespace std;

class Student {
private:
	char name[20];
	int age, number, grades[4];
	double average_grade;

	int read_int(char *&s) {
		int res = 0; char c;
		do c = *s++;
		while (!isdigit(c));
		while (isdigit(c))
			res = res * 10 + c - '0', c = *s++;
		return res;
	}

public:
	Student() {memset(name, 0, sizeof name);}
	
	void input() {
		char s[50], *str = s;
		gets(s);
		for (char *c = name; *str != ','; ++c, ++str)
			*c = *str;
		age = read_int(str);
		number = read_int(str);
		for (int i = 0; i < 4; i++)
			grades[i] = read_int(str);
	}

	void calculate() {
		average_grade = 0;
		for (int i = 0; i < 4; i++)
			average_grade += grades[i];
		average_grade /= 4;
	}

	void output() {
		cout << name << ',' << age << ',' << number << ',' << average_grade << endl;
	}
} ;

int main() {
	Student student;
	student.input();
	student.calculate();
	student.output();
	return 0;
}