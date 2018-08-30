#include <bits/stdc++.h>
using namespace std;

const int MAXN = 132675;

int N;
struct PT {
	int x, y;
};
struct RECT {
	PT p1, p2;
} r[MAXN];

struct SEG {
	int x, w;
};

int main() {
	scanf("%d",&N);
	vector <SEG> X, Y;
	for (int i = 1; i <= N; i++) {
		scanf("%d%d%d%d",&r[i].p1.x,&r[i].p1.y,&r[i].p2.x,&r[i].p2.y);
		X.push_back({r[i].p1.x, 1}); X.push_back({r[i].p2.x, -1});
		Y.push_back({r[i].p1.y, 1}); Y.push_back({r[i].p2.y, -1});
	}
	sort(X.begin(), X.end(), [&](SEG x, SEG y) {
		if (x.x != y.x) return x.x < y.x;
		return x.w > y.w;
	});
	sort(Y.begin(), Y.end(), [&](SEG x, SEG y) {
		if (x.x != y.x) return x.x < y.x;
		return x.w > y.w;
	});
	vector <int> cx, cy;
	int cnt = 0;
	for (auto &t : X) {
		cnt += t.w;
		if (cnt >= N-1) cx.push_back(t.x);
	}
	for (auto &t : Y) {
		cnt += t.w;
		if (cnt >= N-1) cy.push_back(t.x);
	}
	for (auto &x : cx) {
		for (auto &y : cy) {
			int cnt = 0;
			for (int i = 1; i <= N; i++) {
				cnt += (r[i].p1.x <= x && x <= r[i].p2.x && r[i].p1.y <= y && y <= r[i].p2.y);
			}
			if (cnt >= N-1) {
				printf("%d %d\n", x, y);
				return 0;
			}
		}
	}
	return 0;
}