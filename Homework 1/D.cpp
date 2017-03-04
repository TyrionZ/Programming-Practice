#include <bits/stdc++.h>
using namespace std;

const char warrior_name[5][10] = {"dragon", "ninja", "iceman", "lion", "wolf"};
char color[2][5] = {"red", "blue"};
int health_point[5], order[2][5] = {{2, 3, 4, 1, 0}, {3, 0, 1, 2, 4}};
class barracks {
public:
	int vitality, number, *order, point, count[5];
	bool died;
	char *color;

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
				vitality -= health_point[order[point]];
				printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n", number - 1, color, warrior_name[order[point]], number, health_point[order[point]], ++count[order[point]], warrior_name[order[point]], color);
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