#include <bits/stdc++.h>
using namespace std;

const char warrior_name[5][10] = {"dragon", "ninja", "iceman", "lion", "wolf"};
const char weapon_name[3][10] = {"sword", "bomb", "arrow"};
char color[2][5] = {"red", "blue"};
int health_point[5], order[2][5] = {{2, 3, 4, 1, 0}, {3, 0, 1, 2, 4}};

class warrior {
public:
	int health_point, number;
	warrior() {}
	warrior(int h, int n)
		: health_point(h), number(n) {}
} ;

class dragon:public warrior {
public:
	int weapon; 
	double morale;
	dragon() {}
	dragon(int h, int n, double m)
		: warrior(h, n), weapon(n % 3), morale(m) {}
} ;

class ninja:public warrior {
public:
	int weapon[2];
	ninja() {}
	ninja(int h, int n): warrior(h, n)
		{weapon[0] = n % 3, weapon[1] = (n + 1) % 3;}
} ;

class iceman:public warrior {
public:
	int weapon;
	iceman() {}
	iceman(int h, int n)
		: warrior(h, n), weapon(n % 3) {}
} ;

class lion:public warrior {
public:
	int loyalty;
	lion() {}
	lion(int h, int n, int l)
		: warrior(h, n), loyalty(l) {}
} ;

class wolf:public warrior {
public:
	wolf() {}
	wolf(int h, int n) : warrior(h, n) {}
} ;

class barracks {
public:
	int vitality, number, *order, point, count[5];
	bool died;
	char *color;
	vector<warrior*> army;

	void clear(int n) {
		vitality = n;
		number = 0;
		point = -1;
		died = false;
		memset(count, 0, sizeof count);
	}

	bool process() {
		if (died) return false;
		++number;
		for (int i = 0; i < 5; ++i) 
			if (vitality >= health_point[order[(i + point + 1) % 5]]) {
				point = (i + point + 1) % 5;
				int x = order[point];
				warrior *u;
				vitality -= health_point[x];
				printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n", number - 1, color, warrior_name[x], number, health_point[x], ++count[x], warrior_name[x], color);
				switch(x) {
					case 0:
						u = new dragon(health_point[x], number, (double)vitality / health_point[x]);
						printf("It has a %s,and it's morale is %.2f\n", weapon_name[number % 3], (double)vitality / health_point[x]);
						break ;
					case 1:
						u = new ninja(health_point[x], number);
						printf("It has a %s and a %s\n", weapon_name[number % 3], weapon_name[(number + 1) % 3]);
						break ;
					case 2:
						u = new iceman(health_point[x], number);
						printf("It has a %s\n", weapon_name[number % 3]);
						break ;
					case 3:
						u = new lion(health_point[x], number, vitality);
						printf("It's loyalty is %d\n", vitality);
						break ;
					case 4:
						u = new wolf(health_point[x], number);
				}
				army.push_back(u);
				return true;
			}
		printf("%03d %s headquarter stops making warriors\n", number - 1, color); 
		died = true;
		return false;
	}
} red, blue;


void solve(int number) {
	printf("Case:%d\n", number);
	int n; cin >> n;
	for (int i = 0; i < 5; i++)
		cin >> health_point[i];
	
	red.clear(n); blue.clear(n);

	while (red.process()) 
		blue.process() ;
	while (blue.process()) ;
}

int main() {
	red.order = order[0]; red.color = color[0];
	blue.order = order[1]; blue.color = color[1];
	int test_number; cin >> test_number;
	for (int i = 1; i <= test_number; i++)
		solve(i);

	return 0;
}