import java.util.Scanner;
import java.io.*;

public class Main {
	final String warrior_name[] = {"dragon", "ninja", "iceman", "lion", "wolf"};
	final String weapon_name[] = {"sword", "bomb", "arrow"};
	String color[] = {"red", "blue"};
	String ccolor[] = {"red", "blue"};
	int now, n, kkk, d[], win[], ww[], bel[], hp[], rrr, health_point[], aggressivity[], order[][] = {{2, 3, 4, 1, 0}, {3, 0, 1, 2, 4}};

	public class warrior {
		public int health_point, number, position, color, force, name;
		public int sword, arrow; boolean bomb, died;

		warrior() {}
		warrior(int h, int n) {
			health_point = h;
			number = n;
			sword = arrow = 0;
			bomb = died = false;
		}

		void equip(int x) {
			switch (x) {
				case 0:
					sword = floor(0.2 * force); break ;
				case 1: 
					bomb = true; break ;
				case 2: arrow = 3;
			}
		}

		void attack(warrior enemy, boolean hah) {}

		void attack(warrior enemy) {}

		boolean respond(warrior enemy, int hit) {}

		boolean explode(warrior enemy) {
			if (health_point < 0 || enemy.health_point < 0) 
				return false;
			public int hit = force + sword;
			if (enemy.bomb && enemy.health_point <= hit) {
				System.out.printf("%.3d:38 %s %s %d used a bomb and killed %s %s %d\n", now, ccolor[enemy.color], warrior_name[enemy.name], enemy.number, ccolor[color], warrior_name[name], number);
				return died = enemy.died = true;
			}
			if (enemy.name == 1 || enemy.health_point <= hit) return false;
			hit = enemy.force / 2 + enemy.sword;
			if (bomb && health_point <= hit) {
				System.out.printf("%.3d:38 %s %s %d used a bomb and killed %s %s %d\n", now, ccolor[color], warrior_name[name], number, ccolor[enemy.color], warrior_name[enemy.name], enemy.number);
				return died = enemy.died = true;
			}
			return false;
		}



		void step() {
			position += color ? -1 : 1;
			if (!position) {
				System.out.printf("%.3d:10 %s %s %d reached %s headquarter with %d elements and force %d\n", now, ccolor[color], warrior_name[name], number, ccolor[color ^ 1], health_point, force);
				d[0] += 1;
				if (d[0] == 2) 
					System.out.printf("%.3d:10 red headquarter was taken\n", now);
			}
			else if (position == n + 1) {
				System.out.printf("%.3d:10 %s %s %d reached %s headquarter with %d elements and force %d\n", now, ccolor[color], warrior_name[name], number, ccolor[color ^ 1], health_point, force);
				d[1] += 1;
				if (d[1] == 2) 
					System.out.printf("%.3d:10 blue headquarter was taken\n", now);
			}
			else System.out.printf("%.3d:10 %s %s %d marched to city %d with %d elements and force %d\n", now, ccolor[color], warrior_name[name], number, position, health_point, force);
		}

		void have() {
			System.out.printf("%.3d:55 %s %s %d has ", now, ccolor[color], warrior_name[name], number);
			int cnt = 0;
			if (arrow) {System.out.printf("arrow(%d)", arrow); cnt += 1;}
			if (bomb) {System.out.printf("%sbomb", cnt ? "," : ""); cnt += 1;}
			if (sword) {System.out.printf("%ssword(%d)", cnt ? "," : "", sword); cnt += 1;}
			if (!cnt) System.out.printf("no weapon");
			puts("");
		}
	} 
	
	warrior c[][] = new warrior[2][30];

	boolean survive(warrior x) 
		{return (x && !x.died);}

	void shot(warrior x) {
		warrior enemy = c[x.color ^ 1][x.position + (x.color ? -1 : 1)];
		if (x.arrow && enemy && survive(enemy)) {
			x.arrow -= 1;
			if ((enemy.health_point -= rrr) <= 0) 
				System.out.printf("%.3d:35 %s %s %d shot and killed %s %s %d\n", now, ccolor[x.color], warrior_name[x.name], x.number, ccolor[enemy.color], warrior_name[enemy.name], enemy.number);
			else System.out.printf("%.3d:35 %s %s %d shot\n", now, ccolor[x.color], warrior_name[x.name], x.number);
		}
	}

	class dragon extends warrior {
		double morale;
		dragon() {}
		dragon(int h, int nu, double m, String c) {
			super(h, nu);
			morale = m;
			name = 0; 
			force = aggressivity[name];
			color = (c == "red" ? 0 : 1);
			position = color ? n + 1 : 0;
			equip(nu % 3);
		}

		void attack(warrior enemy, boolean hah) {
			if (health_point <= 0) {
				if (enemy.health_point > 0)
					enemy.attack(this, true);
				return ;
			}
			if (enemy.health_point > 0) {
				System.out.printf("%.3d:40 %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n", now, ccolor[color], warrior_name[name], number, ccolor[enemy.color], warrior_name[enemy.name], enemy.number, position, health_point, force);
				int hit = force + sword;
				sword = floor(0.8 * sword);
				enemy.respond(this, hit);
			}
			else enemy.died = true;
			if (enemy.health_point <= 0)
				morale += 0.2;
			else morale -= 0.2;
			if (health_point <= 0) {
				died = true;
				System.out.printf("%.3d:40 %s %s %d was killed in city %d\n", now, ccolor[color], warrior_name[name], number, position);
				return ;
			}
		}

		void attack(warrior enemy) {
			if (health_point <= 0) {
				if (enemy.health_point > 0)
					enemy.attack(this, true);
				return ;
			}
			if (enemy.health_point > 0) {
				System.out.printf("%.3d:40 %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n", now, ccolor[color], warrior_name[name], number, ccolor[enemy.color], warrior_name[enemy.name], enemy.number, position, health_point, force);
				int hit = force + sword;
				sword = floor(0.8 * sword);
				enemy.respond(this, hit);
			}
			else enemy.died = true;
			if (enemy.health_point <= 0)
				morale += 0.2;
			else morale -= 0.2;
			if (health_point <= 0) {
				died = true;
				System.out.printf("%.3d:40 %s %s %d was killed in city %d\n", now, ccolor[color], warrior_name[name], number, position);
				return ;
			}
			else if (morale > 0.8) 
				System.out.printf("%.3d:40 %s %s %d yelled in city %d\n", now, ccolor[color], warrior_name[name], number, position);
		}

		boolean respond(warrior enemy, int hit) {
			health_point -= hit;
			if (health_point <= 0) {
				System.out.printf("%.3d:40 %s %s %d was killed in city %d\n", now, ccolor[color], warrior_name[name], number, position);
				return died = true;
			}
			System.out.printf("%.3d:40 %s %s %d fought back against %s %s %d in city %d\n", now, ccolor[color], warrior_name[name], number, ccolor[enemy.color], warrior_name[enemy.name], enemy.number, position);	
			hit = force / 2 + sword;
			sword = floor(0.8 * sword);
			enemy.health_point -= hit;
			if (enemy.health_point <= 0)
				morale += 0.2;
			else morale -= 0.2;
			return false;
		}
	}

	class ninja extends warrior {
		ninja() {}
		ninja(int h, int nu, String c) {
			super(h, nu);
			name = 1; 
			force = aggressivity[name];
			equip(nu % 3); 
			equip((nu + 1) % 3); 
			color = (c == "red" ? 0 : 1);
			position = color ? n + 1 : 0;
		}

		void attack(warrior enemy, boolean hah) {
			if (health_point <= 0) {
				if (enemy.health_point > 0)
					enemy.attack(this, true);
				return ;
			}
			if (enemy.health_point > 0) {
				System.out.printf("%.3d:40 %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n", now, ccolor[color], warrior_name[name], number, ccolor[enemy.color], warrior_name[enemy.name], enemy.number, position, health_point, force);
				int hit = force + sword;
				sword = floor(0.8 * sword);
				enemy.respond(this, hit);
			}
			else enemy.died = true;
			if (health_point <= 0) {
				died = true;
				System.out.printf("%.3d:40 %s %s %d was killed in city %d\n", now, ccolor[color], warrior_name[name], number, position);
				return ;
			}
		}

		void attack(warrior enemy) {
			if (health_point <= 0) {
				if (enemy.health_point > 0)
					enemy.attack(this, true);
				return ;
			}
			if (enemy.health_point > 0) {
				System.out.printf("%.3d:40 %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n", now, ccolor[color], warrior_name[name], number, ccolor[enemy.color], warrior_name[enemy.name], enemy.number, position, health_point, force);
				int hit = force + sword;
				sword = floor(0.8 * sword);
				enemy.respond(this, hit);
			}
			else enemy.died = true;
			if (health_point <= 0) {
				died = true;
				System.out.printf("%.3d:40 %s %s %d was killed in city %d\n", now, ccolor[color], warrior_name[name], number, position);
				return ;
			}
		}

		boolean respond(warrior enemy, int hit) {	
			health_point -= hit;
			if (health_point <= 0) {
				System.out.printf("%.3d:40 %s %s %d was killed in city %d\n", now, ccolor[color], warrior_name[name], number, position);
				return died = true;
			}
			return false;
		}
	}

	class iceman extends warrior {
		iceman() {}
		iceman(int h, int nu, String c) {
			super(h, nu);
			name = 2; 
			force = aggressivity[name];
			equip(nu % 3); 
			color = (c == "red" ? 0 : 1);
			position = color ? n + 1 : 0;
		}

		void attack(warrior enemy, boolean hah) {
			if (health_point <= 0) {
				if (enemy.health_point > 0)
					enemy.attack(this, true);
				return ;
			}
			if (enemy.health_point > 0) {
				System.out.printf("%.3d:40 %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n", now, ccolor[color], warrior_name[name], number, ccolor[enemy.color], warrior_name[enemy.name], enemy.number, position, health_point, force);
				int hit = force + sword;
				sword = floor(0.8 * sword);
				enemy.respond(this, hit);
			}
			else enemy.died = true;
			if (health_point <= 0) {
				died = true;
				System.out.printf("%.3d:40 %s %s %d was killed in city %d\n", now, ccolor[color], warrior_name[name], number, position);
				return ;
			}
		}

		void attack(warrior enemy) {
			if (health_point <= 0) {
				if (enemy.health_point > 0)
					enemy.attack(this, true);
				return ;
			}
			if (enemy.health_point > 0) {
				System.out.printf("%.3d:40 %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n", now, ccolor[color], warrior_name[name], number, ccolor[enemy.color], warrior_name[enemy.name], enemy.number, position, health_point, force);
				int hit = force + sword;
				sword = floor(0.8 * sword);
				enemy.respond(this, hit);
			}
			else enemy.died = true;
			if (health_point <= 0) {
				died = true;
				System.out.printf("%.3d:40 %s %s %d was killed in city %d\n", now, ccolor[color], warrior_name[name], number, position);
			}
		}
				

		boolean respond(warrior enemy, int hit) {
			health_point -= hit;
			if (health_point <= 0) {
				System.out.printf("%.3d:40 %s %s %d was killed in city %d\n", now, ccolor[color], warrior_name[name], number, position);
				return died = true;
			}
			System.out.printf("%.3d:40 %s %s %d fought back against %s %s %d in city %d\n", now, ccolor[color], warrior_name[name], number, ccolor[enemy.color], warrior_name[enemy.name], enemy.number, position);	
			hit = force / 2 + sword;
			sword = floor(0.8 * sword);
			enemy.health_point -= hit;
			return false;
		}

		void step() {
			position += color ? -1 : 1;
			int distance = color ? n + 1 - position : position;
			if (!(distance & 1))
				{health_point = max(health_point - 9, 1); force += 20;}
			if (!position) {
				System.out.printf("%.3d:10 %s %s %d reached %s headquarter with %d elements and force %d\n", now, ccolor[color], warrior_name[name], number, ccolor[color ^ 1], health_point, force);
				d[0] += 1;
				if (d[0] == 2) 
					System.out.printf("%.3d:10 red headquarter was taken\n", now);
			}
			else if (position == n + 1) {
				System.out.printf("%.3d:10 %s %s %d reached %s headquarter with %d elements and force %d\n", now, ccolor[color], warrior_name[name], number, ccolor[color ^ 1], health_point, force);
				d[1] += 1;
				if (d[1] == 2) 
					System.out.printf("%.3d:10 blue headquarter was taken\n", now);
			}
			else System.out.printf("%.3d:10 %s %s %d marched to city %d with %d elements and force %d\n", now, ccolor[color], warrior_name[name], number, position, health_point, force);	
		}
	}

	class lion extends warrior {
		int loyalty;
		lion() {}
		lion(int h, int nu, int l, String c) {
			super(h, nu);
			loyalty = l;
			name = 3; 
			force = aggressivity[name];
			color = (c == "red" ? 0 : 1);
			position = color ? n + 1 : 0;
		}

		boolean run() {
			if (loyalty > 0)
				return false;
			System.out.printf("%.3d:05 %s lion %d ran away\n", now, color ? "blue" : "red", number);
			return died = true;
				
		}

		void attack(warrior enemy, boolean hah) {
			int last = health_point;
			if (health_point <= 0) {
				if (enemy.health_point > 0)
					enemy.attack(this, true);
				return ;
			}
			if (enemy.health_point > 0) {
				System.out.printf("%.3d:40 %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n", now, ccolor[color], warrior_name[name], number, ccolor[enemy.color], warrior_name[enemy.name], enemy.number, position, health_point, force);
				int hit = force + sword;
				sword = floor(0.8 * sword);
				if (!enemy.respond(this, hit))
					loyalty -= kkk;
			}
			else enemy.died = true;
			if (health_point <= 0) {
				died = true;
				System.out.printf("%.3d:40 %s %s %d was killed in city %d\n", now, ccolor[color], warrior_name[name], number, position);
				enemy.health_point += last;
				return ;
			}	
		}

		void attack(warrior enemy) {
			int last = health_point;
			if (health_point <= 0) {
				if (enemy.health_point > 0)
					enemy.attack(this, true);
				return ;
			}
			if (enemy.health_point > 0) {
				System.out.printf("%.3d:40 %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n", now, ccolor[color], warrior_name[name], number, ccolor[enemy.color], warrior_name[enemy.name], enemy.number, position, health_point, force);
				int hit = force + sword;
				sword = floor(0.8 * sword);
				if (!enemy.respond(this, hit))
					loyalty -= kkk;
			}
			else enemy.died = true;
			if (health_point <= 0) {
				died = true;
				System.out.printf("%.3d:40 %s %s %d was killed in city %d\n", now, ccolor[color], warrior_name[name], number, position);
				enemy.health_point += last;
				return ;
			}	
		}

		boolean respond(warrior enemy, int hit) {
			int last = health_point;
			health_point -= hit;
			if (health_point <= 0) {
				System.out.printf("%.3d:40 %s %s %d was killed in city %d\n", now, ccolor[color], warrior_name[name], number, position);
				enemy.health_point += last;
				return died = true;
			}
			System.out.printf("%.3d:40 %s %s %d fought back against %s %s %d in city %d\n", now, ccolor[color], warrior_name[name], number, ccolor[enemy.color], warrior_name[enemy.name], enemy.number, position);	
			hit = force / 2 + sword;
			sword = floor(0.8 * sword);
			enemy.health_point -= hit;
			if (enemy.health_point > 0)
				loyalty -= kkk;
			return false;
		}
	}

	class wolf extends warrior {
		wolf() {}
		wolf(int h, int nu, String c) {
			super(h, nu);
			name = 4; 
			force = aggressivity[name];
			color = (c == "red" ? 0 : 1);
			position = color ? n + 1 : 0;
		}

		void attack(warrior enemy, boolean hah) {
			if (health_point <= 0) {
				if (enemy.health_point > 0)
					enemy.attack(this, true);
				return ;
			}
			if (enemy.health_point > 0) {
				System.out.printf("%.3d:40 %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n", now, ccolor[color], warrior_name[name], number, ccolor[enemy.color], warrior_name[enemy.name], enemy.number, position, health_point, force);
				int hit = force + sword;
				sword = floor(0.8 * sword);
				enemy.respond(this, hit);
			}
			else enemy.died = true;
			if (enemy.health_point <= 0) {
				if (!sword) sword = enemy.sword;
				if (!arrow) arrow = enemy.arrow;
				if (!bomb) bomb = enemy.bomb;
			}
			if (health_point <= 0) {
				died = true;
				System.out.printf("%.3d:40 %s %s %d was killed in city %d\n", now, ccolor[color], warrior_name[name], number, position);
				return ;
			}
		}

		void attack(warrior enemy) {
			if (health_point <= 0) {
				if (enemy.health_point > 0)
					enemy.attack(this, true);
				return ;
			}
			if (enemy.health_point > 0) {
				System.out.printf("%.3d:40 %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n", now, ccolor[color], warrior_name[name], number, ccolor[enemy.color], warrior_name[enemy.name], enemy.number, position, health_point, force);
				int hit = force + sword;
				sword = floor(0.8 * sword);
				enemy.respond(this, hit);
			}
			else enemy.died = true;
			if (enemy.health_point <= 0) {
				if (!sword) sword = enemy.sword;
				if (!arrow) arrow = enemy.arrow;
				if (!bomb) bomb = enemy.bomb;
			}
			if (health_point <= 0) {
				died = true;
				System.out.printf("%.3d:40 %s %s %d was killed in city %d\n", now, ccolor[color], warrior_name[name], number, position);
				return ;
			}
		}

		boolean respond(warrior enemy, int hit) {	
			health_point -= hit;
			if (health_point <= 0) {
				System.out.printf("%.3d:40 %s %s %d was killed in city %d\n", now, ccolor[color], warrior_name[name], number, position);
				return died = true;
			}
			System.out.printf("%.3d:40 %s %s %d fought back against %s %s %d in city %d\n", now, ccolor[color], warrior_name[name], number, ccolor[enemy.color], warrior_name[enemy.name], enemy.number, position);	
			hit = force / 2 + sword;
			sword = floor(0.8 * sword);
			enemy.health_point -= hit;
			if (enemy.health_point <= 0) {
				if (!sword) sword = enemy.sword;
				if (!arrow) arrow = enemy.arrow;
				if (!bomb) bomb = enemy.bomb;
			}
			return false;
		}
	}

	class barracks {
		int vitality, number, order, point;
		String color;

		void clear(int n) {
			vitality = n;
			number = 0;
			point = -1;
		}

		void produce() {
			if (vitality >= health_point[order[(point + 1) % 5]]) {
				number += 1;
				point = (point + 1) % 5;
				int x = order[point];
				double d;
				warrior u;
				vitality -= health_point[x];
				System.out.printf("%.3d:00 %s %s %d born\n", now, color.data(), warrior_name[x], number, health_point[x], number, warrior_name[x], color.data());
				switch(x) {
					case 0:
						u = new dragon(health_point[x], number, (double)vitality / health_point[x], color);
						d = (double)vitality / (double)health_point[x];
						System.out.printf("Its morale is %.2lf\n", d);
						break ;
					case 1:
						u = new ninja(health_point[x], number, color);
						break ;
					case 2:
						u = new iceman(health_point[x], number, color);
						break ;
					case 3:
						u = new lion(health_point[x], number, vitality, color);
						System.out.printf("Its loyalty is %d\n", vitality);
						break ;
					case 4:
						u = new wolf(health_point[x], number, color);
				}
				if (color == "red")
					c[0][0] = u;
				else c[1][n + 1] = u;
			}
		}
	} 
	
	barracks red, blue;
	public static void solve(int number) {
		System.out.printf("Case %d:\n", number);
		int m, t;
		m = System.in.nextInt();
		n = System.in.nextInt();
		rrr = System.in.nextInt();
		kkk = System.in.nextInt();
		t = System.in.nextInt();
		int xs = t / 60, fz = t % 60;
		for (int i = 0; i < 5; i += 1)
			health_point[i] = System.in.nextInt();
		for (int i = 0; i < 5; i += 1)
			aggressivity[i]  = System.in.nextInt();;

		for (int i = 0; i < n; i++) {
			bel[i] = -1;
			win[i] = -1;
			ww[i] = -1;
			hp[i] = 0;
			c[0][i] = null;
			c[1][i] = null;
		}
		d[0] = d[1] = now = 0;
		
		red.clear(m); blue.clear(m);

		while (true) {
			red.produce();
			blue.produce();

			if (now >= xs && fz < 5)
				break ;
			for (int j = 0; j <= n + 1; j += 1)
				for (int i = 0; i < 2; i += 1)
					if (survive(c[i][j]) && c[i][j].name == 3)
						lion(c[i][j]).run();

			if (now >= xs && fz < 10)
				break ;
			for (int j = 0; j <= n; j += 1)
				for (int i = 1; i >= 0; i -= 1)
					if (survive(c[i][j + i]))
						c[i][j + i].step();
			
			for (int j = n; j >= 0; j -= 1)
				if (survive(c[0][j])) 
					c[0][j + 1] = c[0][j];
				else if (j < n) c[0][j + 1] = NULL;
			for (int j = 1; j <= n + 1; j += 1)
				if (survive(c[1][j])) 
					c[1][j - 1] = c[1][j];
				else if (j > 1) c[1][j - 1] = NULL;

			c[0][0] = c[1][n + 1] = NULL;

			if (d[0] == 2 || d[1] == 2)
				return ;

			if (now >= xs && fz < 30)
				break ;
			for (int j = 1; j <= n; j += 1) {
				hp[j] += 10;
				if (survive(c[0][j]) && !survive(c[1][j])) {
					System.out.printf("%.3d:30 %s %s %d earned %d elements for his headquarter\n", now,  ccolor[c[0][j].color], warrior_name[c[0][j].name], c[0][j].number, hp[j]);
					red.vitality += hp[j];
					hp[j] = 0;
				}
				if (survive(c[1][j]) && !survive(c[0][j])) {
					System.out.printf("%.3d:30 %s %s %d earned %d elements for his headquarter\n", now,  ccolor[c[1][j].color], warrior_name[c[1][j].name], c[1][j].number, hp[j]);
					blue.vitality += hp[j];
					hp[j] = 0;
				}
			}

			if (now >= xs && fz < 35)
				break ;
			for (int j = 0; j <= n + 1; j += 1)
				for (int i = 0; i < 2; i += 1)
					if (survive(c[i][j]))
						if ((i && j != 0) || (!i && j != n + 1))
							shot(c[i][j]);

			if (now >= xs && fz < 38)
				break ;
			for (int j = 1; j <= n; j += 1) 
				if (survive(c[0][j]) && survive(c[1][j])) 
					if (bel[j] == 0) 
						c[0][j].explode(c[1][j]);
					else if (bel[j] == 1) 
						c[1][j].explode(c[0][j]);
					else if (j & 1)
						c[0][j].explode(c[1][j]);
					else c[1][j].explode(c[0][j]);

			if (now >= xs && fz < 40)
				break ;
			for (int j = 1; j <= n; j += 1) 
				if (survive(c[0][j]) && survive(c[1][j])) {
					boolean st = false;
					if (c[0][j].health_point <= 0 && c[1][j].health_point <= 0) 
						c[0][j].died = c[1][j].died = st = true;
					else if (bel[j] == 0) 
						c[0][j].attack(c[1][j]);
					else if (bel[j] == 1) 
						c[1][j].attack(c[0][j]);
					else if (j & 1)
						c[0][j].attack(c[1][j]);
					else c[1][j].attack(c[0][j]);
					if (survive(c[0][j])) {
						if (survive(c[1][j])) {
							win[j] = -1;
						}
						else {
							System.out.printf("%.3d:40 %s %s %d earned %d elements for his headquarter\n", now,  ccolor[c[0][j].color], warrior_name[c[0][j].name], c[0][j].number, hp[j]);
							red.vitality += hp[j];
							hp[j] = 0;
							if (win[j] == 0) {
								if (bel[j] != 0) 
									{bel[j] = 0; System.out.printf("%.3d:40 %s flag raised in city %d\n", now, ccolor[0], j);}
							}
							else win[j] = 0;
						}
					}
					else if (survive(c[1][j])) {
						System.out.printf("%.3d:40 %s %s %d earned %d elements for his headquarter\n", now,  ccolor[c[1][j].color], warrior_name[c[1][j].name], c[1][j].number, hp[j]);
						blue.vitality += hp[j];
						hp[j] = 0;
						if (win[j] == 1) {
							if (bel[j] != 1) 
								{bel[j] = 1; System.out.printf("%.3d:40 %s flag raised in city %d\n", now, ccolor[1], j);}
						}
						else win[j] = 1;
					}
					ww[j] = win[j];
					if (st) ww[j] = -1;
				}
				else ww[j] = -1;
			
			for (int j = 1; j <= n; j += 1)
				if (ww[j] == 0) 
					if (red.vitality >= 8)
						{red.vitality -= 8; c[0][j].health_point += 8;}
			
			for (int j = 20; j >= 1; j -= 1)
				if (ww[j] == 1) 
					if (blue.vitality >= 8)
						{blue.vitality -= 8; c[1][j].health_point += 8;}

			if (now >= xs && fz < 50)
				break ;
			System.out.printf("%.3d:50 %d elements in red headquarter\n%.3d:50 %d elements in blue headquarter\n", now, red.vitality, now, blue.vitality);
			
			if (now >= xs && fz < 55)
				break ;
			for (int i = 0; i < 2; i += 1)
				for (int j = 0; j <= n + 1; j += 1) {
					if (c[i][j] && c[i][j].health_point <= 0)
						c[i][j].died = true;
					if (survive(c[i][j]))
						c[i][j].have();
				}
			now += 1;
			if (now > xs)
				break ;
		}
	}
        public static void main(String args[]) {
		red = new barracks();
		blue = new barracks();
		red.order = order[0]; red.color = String(color[0]);
		blue.order = order[1]; blue.color = String(color[1]);
		int test_number; 
		test_number = System.in.nextInt();
		for (int i = 1; i <= test_number; i += 1)
			solve(i);
	}
}