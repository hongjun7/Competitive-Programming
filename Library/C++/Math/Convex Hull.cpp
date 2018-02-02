#include <stdio.h>

typedef long long ll;

const int SZ = 100005;

template <typename T> void myswap(T &a, T &b) {
	T tmp = a; a = b; b = tmp;
}

struct Point {
	int x, y;
	Point() {}
	Point(int x, int y) : x(x), y(y) {}
};

class ConvexHull {
public:
	int N;
	/* P : Given Points, H : Points making a convex hull */
	Point P[SZ], tmp[SZ], H[SZ];
	int st[SZ], top;
	void init(){
		N = 0;
	}
	void add(int x, int y) {
		P[++N] = Point(x, y);
	}
	int dir(int i, int j, int k) {
		ll x1 = P[j].x - P[i].x, y1 = P[j].y - P[i].y;
		ll x2 = P[k].x - P[i].x, y2 = P[k].y - P[i].y;
		ll outer_product = x1*y2 - x2*y1;
		if (outer_product > 0) return 1;
		if (outer_product < 0) return -1;
		return 0;
	}
	ll dist(int i, int j) {
		ll dx = P[i].x - P[j].x, dy = P[i].y - P[j].y;
		return dx*dx + dy*dy;
	}
	bool cmp(int i, int j) {
		int t = dir(1, i, j);
		if (t > 0 || (t == 0 && dist(1, i) <= dist(1, j))) return 1;
		return 0;
	}
	void sort(int s, int e) {
		if (s < e) {
			int m = (s + e) / 2;
			sort(s, m);
			sort(m + 1, e);
			int p1 = s, p2 = m + 1, p3 = s;
			while (p1 <= m && p2 <= e) {
				if (cmp(p1, p2)) tmp[p3++] = P[p1++];
				else tmp[p3++] = P[p2++];
			}
			while (p1 <= m) tmp[p3++] = P[p1++];
			while (p2 <= e) tmp[p3++] = P[p2++];
			for (int i = s; i <= e; i++) P[i] = tmp[i];
		}
	}
	void compute() {
		/*
		Step 1. Find the lowest, the most left side point
		Make the point as the first point with swapping
		*/
		int p = 1;
		for (int i = 2; i <= N; i++) {
			if (P[i].y < P[p].y || (P[i].y == P[p].y && P[i].x < P[p].x))
				p = i;
		}
		myswap(P[1], P[p]);
		/* Step 2. Sorting */
		sort(2, N);
		/* Step 3. Push & Pop */
		st[top = 1] = 1;
		for (int i = 2; i <= N; i++) {
			if (top < 2) st[++top] = i;
			else {
				while (top >= 2 && dir(st[top - 1], st[top], i) <= 0) top--;
				st[++top] = i;
			}
		}
		for (int i = 1; i <= top; i++) H[i] = P[st[i]];
		N = top;
	}
};

ConvexHull C;

int main(){
	int T; for (scanf("%d", &T); T--;) {
		int n;
		scanf("%d", &n);
		C.init();
		for (int i = 0; i < n; i++) {
			int x, y; scanf("%d%d", &x, &y);
			C.add(x, y);
		}
		C.compute();
		static int tc = 0;
		printf("#%d %d\n", ++tc, C.N);
	}
}