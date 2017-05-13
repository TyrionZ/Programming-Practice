#include <iostream>
#include <queue>
#include <stack>

const int TYPE_STACK = 0;
const int TYPE_QUEUE = 1;
const int TYPE_PRIOR = 2;

class Container {
private:
	int kind;
	std::stack<int> s;
	std::priority_queue<int> p;
	std::queue<int> q;
public:
	Container(int k = 0): kind(k) {}

	void push(int x) {
		if (kind == TYPE_STACK)
			s.push(x);
		else if (kind == TYPE_PRIOR)
			p.push(x);
		else q.push(x);
	}

	int pull() {
		int res = -1;
		if (kind == TYPE_STACK)
			res = s.top(), s.pop();
		else if (kind == TYPE_PRIOR)
			res = p.top(), p.pop();
		else res = q.front(), q.pop();
		return res;
	}
};

int main() {
    int n;
    Container s(TYPE_STACK), q(TYPE_QUEUE), p(TYPE_PRIOR);
    std::cin >> n;
    while (n--) {
        int t, x;
        std::cin >> t;
        if (t) {
            std::cout << s.pull() << ' ' << q.pull() << ' ' << p.pull() << std::endl;
        } else {
            std::cin >> x;
            s.push(x);
            q.push(x);
            p.push(x);
        }
    }
    return 0;
}