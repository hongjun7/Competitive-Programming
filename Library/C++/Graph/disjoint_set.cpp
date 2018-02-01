#include <stdio.h>

const int SZ = 10;

class DisjointSet {
private:
	int Parent[SZ];
public:
	void init(int n) {
		for (int i = 1; i <= n; i++) Parent[i] = i;
	}
	int findRoot(int x) {
		if (x == Parent[x]) return x;
		return (Parent[x] = findRoot(Parent[x]));
	}
	void Union(int x, int y) {
		Parent[findRoot(x)] = findRoot(y);
	}
	bool sameGroup(int x, int y) {
		return (findRoot(x) == findRoot(y));
	}
};

int main() {
	DisjointSet s;
	s.init(5);
	s.Union(1, 2);
	s.Union(4, 5);
	s.Union(1, 4);
	printf("%d\n", (int)s.sameGroup(1, 3));
	printf("%d\n", (int)s.sameGroup(2, 4));
}