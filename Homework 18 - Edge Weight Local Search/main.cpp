#include <bits/stdc++.h>
using namespace std;

int maxSteps;
int delta;
int ans;

int points, edges, upperbound;

class Point;
class PointSet;

class Edge {
public:
	int weight, order;
	Point *endPoint[2];
	Edge(Point* u = nullptr, Point* v = nullptr, int o = -1): 
		weight(1), order(o) {
		endPoint[0] = u, endPoint[1] = v;
	}
};
vector<Edge*> es;
list<Edge*> *L;

class Point {
public:
	vector<Edge*> cover;
	int dscore, order;

	Point(int o = -1):
		order(o) { 
		dscore = 0;
		cover.clear(); 
	}

	friend class PointSet;
} *tabuRemove, *tabuAdd;
vector<Point*> ps;

class PointSet {
private:
	vector<Point*> pointList;
	vector<bool> selected;
	
public:
	static vector<bool> tmp;
	vector<int> coverEdge;

	PointSet() {
		pointList.clear();
		coverEdge.resize(edges, 0);
		selected.resize(points, false);
	}

	void modifyPoint(Point *p, bool update = true) {
		if (update == true) {
			p->dscore = 0;
			if (selected[p->order] == false) {
				pointList.push_back(p);
				selected[p->order] = true;
				for (auto e : p->cover) {
					if (++coverEdge[e->order] == 1)
						tmp[e->order] = true, p->dscore -= e->weight;

					for (int i = 0; i < 2; ++i)
						if (e->endPoint[i] != p)
							e->endPoint[i]->dscore += e->weight * (selected[e->endPoint[i]->order] ? 1 : -1);
				}

				for (auto e = L->begin(); e != L->end(); ) {
					auto te = e; ++e;
					if (tmp[(*te)->order] == true)
						L->erase(te);
				}

				for (auto e : p->cover)
					if (coverEdge[e->order] == 1)
						tmp[e->order] = false;
			}
			else {
				for (int i = 0; i <= pointList.size(); ++i)
					if (pointList[i] == p) {
						swap(pointList[i], pointList[pointList.size() - 1]);
						pointList.pop_back();
						break;
					}
				selected[p->order] = false;
				for (auto e : p->cover) {
					if (--coverEdge[e->order] == 0)
						L->push_back(e), p->dscore += e->weight;

					for (int i = 0; i < 2; ++i)
						if (e->endPoint[i] != p)
							e->endPoint[i]->dscore += e->weight * (selected[e->endPoint[i]->order] ? -1 : 1);
				}
			}
		}
		else {
			if (selected[p->order] == false) {
				pointList.push_back(p);
				selected[p->order] = true;
				for (auto e : p->cover) 
					++coverEdge[e->order];
			}
			else {
				for (int i = 0; i <= pointList.size(); ++i)
					if (pointList[i] == p) {
						swap(pointList[i], pointList[pointList.size() - 1]);
						pointList.pop_back();
						break;
					}
				selected[p->order] = false;
				for (auto e : p->cover) 
					--coverEdge[e->order];
			}
		}
	}

	int getCost() {
		int result = 0;
		for (auto e : es)
			if (coverEdge[e->order] == 0)
				result += e->weight;
		return result;
	}

	int size() { return pointList.size(); }

	friend class Point;

	friend PointSet* extend(const PointSet* base) { 
		PointSet* result = new PointSet(*base);
		
		while (count(result->coverEdge.begin(), result->coverEdge.end(), 0) > 0) {
			Point *tp = nullptr;
			int tc = -1;
			for (auto p : ps) 
				if (result->selected[p->order] == false) {
					int uncover = 0;
					for (auto e : p->cover)
						uncover += (result->coverEdge[e->order] == 0);
					if (uncover > tc)
						tp = p, tc = uncover;
				}

			result->modifyPoint(tp, false);
		}

		return result;
	}

	bool chooseSwapPair(Point *&u, Point *&v) {
		Point *tu = new Point(); tu->dscore = -1e9;
		for (auto p : pointList) 
			if (p != tabuRemove && p->dscore > tu->dscore)
				tu = p;
		
		for (auto e = L->begin(); e != L->end(); ++e)
			for (int i = 0; i < 2; ++i) {
				v = (*e)->endPoint[i]; u = tu;
				if (v != tabuAdd && u->dscore + v->dscore > 0)
					return true;
				for (auto _e : v->cover)
					for (int j = 0; j < 2; j++)
						if (selected[_e->endPoint[j]->order]) {
							u = _e->endPoint[j];
							if (u != tabuRemove && v != tabuAdd && u->dscore + v->dscore + _e->weight > 0)
								return true;
						}
			}

		for (auto e = L->begin(); e != L->end(); ++e) {
			++(*e)->weight;
			u = (*e)->endPoint[0], v = (*e)->endPoint[1];
			u->dscore += (selected[u->order] ? -1 : 1) * !(selected[v->order]);
			v->dscore += (selected[v->order] ? -1 : 1) * !(selected[u->order]);
		}

		int r = rand() % L->size();
		auto e = L->begin();
		while (r--)
			++e;
		v = (*e)->endPoint[rand() % 2];
		u = pointList[rand() % pointList.size()];
	}


	void greedy() {
		for (int i = 0; i < points; i++) {
			Point *p = ps[i];
			for (auto e : p->cover)
				p->dscore += e->weight;
		}

		while (count(coverEdge.begin(), coverEdge.end(), 0) > 0) {
			Point *tp = nullptr;
			int tc = -1;
			for (auto p : ps)
				if (selected[p->order] == false) 
					if (p->dscore > tc)
						tp = p, tc = p->dscore;

			modifyPoint(tp);
		}

	}

	void remove() {
		while (size() > upperbound - delta) {
			Point *tp = nullptr;
			int tc = -1e9;
			for (auto p : ps)
				if (selected[p->order] == true) {
					if (p->dscore > tc)
						tp = p, tc = p->dscore;
				}

			modifyPoint(tp);
		}
	}
} *C, *_C;
vector<bool> PointSet::tmp;

void readGraph() {
	char s[20];
	cin >> s; cin >> s;
	cin >> points >> edges;
	for (int i = 0; i < points; i++)
		ps.push_back(new Point(i));
	for (int i = 0; i < edges; i++) {
		int u, v; 
		scanf("%s%d%d", s, &u, &v);
		--u, --v;
		es.push_back(new Edge(ps[u], ps[v], i));
		ps[u]->cover.push_back(es[i]);
		ps[v]->cover.push_back(es[i]);
	}
}

int main(int argc, char* argv[]) {
	maxSteps = atoi(argv[1]);
	delta = atoi(argv[2]);
	ans = atoi(argv[3]);

	freopen("input", "r", stdin);
	freopen("output", "w", stdout);

	srand(time(NULL));
	readGraph();
	PointSet::tmp.resize(edges, false);

	L = new list<Edge*>();
	C = new PointSet();

	C->greedy(); 
	upperbound = C->size(); 
	//_C = new PointSet(*C);
	C->remove();

	for (int step = 0; step < maxSteps; step++) {
		Point  *u, *v;
		if (L->size()) {
			C->chooseSwapPair(u, v);

			tabuAdd = u;
			tabuRemove = v;

			C->modifyPoint(u);
			C->modifyPoint(v);
		}

		if (C->size() + L->size() < upperbound) {
			upperbound = C->size() + L->size();
			//_C = C;
			C->remove();
		}
		if (upperbound == ans) {
			cout << ans << endl;
			return 0;
		}
	//	if (step % 10000 == 0)
	//		cout << "current step: " << step << endl;
	}

	//_C = extend(_C);
	cout << upperbound << endl;
	return 0;
}