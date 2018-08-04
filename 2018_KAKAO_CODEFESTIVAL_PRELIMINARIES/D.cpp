#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 250005;

int N, Q;
struct PT {
	int x, y, i;
} P[MAXN], Px[MAXN], Py[MAXN];

int G[MAXN];
int group(int x) {
	if (x == G[x]) return x;
	return (G[x] = group(G[x]));
}

struct QUERY {
	int a, b, x, t;
} q[MAXN];

bool ans[MAXN];

struct PQ {
	int a, b, w;
	bool operator < (const PQ &x) const {
		return w > x.w;
	}
};

int main() {
	scanf("%d%d", &N, &Q);
	for (int i = 1; i <= N; i++) {
		scanf("%d%d", &P[i].x, &P[i].y); P[i].i = i;
		G[i] = i;
		Px[i] = Py[i] = P[i];
	}
	for (int i = 1; i <= Q; i++) {
		scanf("%d%d%d", &q[i].a, &q[i].b, &q[i].x);
		q[i].t = i;
	}
	sort(Px + 1, Px + N + 1, [&](const PT &x, const PT &y) {
		return x.x < y.x;
	});
	sort(Py + 1, Py + N + 1, [&](const PT &x, const PT &y) {
		return x.y < y.y;
	});
	priority_queue <PQ> pqx, pqy;
	for (int i = 2; i <= N; i++) {
		if (Px[i - 1].x == Px[i].x) {
			G[group(Px[i - 1].i)] = group(Px[i].i);
		}
		else {
			pqx.push({ group(Px[i - 1].i), group(Px[i].i), Px[i].x - Px[i - 1].x });
		}
	}
	for (int i = 2; i <= N; i++) {
		if (Py[i - 1].y == Py[i].y) {
			G[group(Py[i - 1].i)] = group(Py[i].i);
		}
		else {
			pqy.push({ group(Py[i - 1].i), group(Py[i].i), Py[i].y - Py[i - 1].y });
		}
	}
	sort(q + 1, q + Q + 1, [&](const QUERY &x, const QUERY &y) {
		return x.x < y.x;
	});
	int cur = 0;
	for (int k = 1; k <= Q; k++) {
		int X = q[k].x;
		if (cur < X) {
			while (pqx.size() > 0 && pqx.top().w <= X) {
				auto t = pqx.top(); pqx.pop();
				G[group(t.a)] = group(t.b);
			}
			while (pqy.size() > 0 && pqy.top().w <= X) {
				auto t = pqy.top(); pqy.pop();
				G[group(t.a)] = group(t.b);
			}
			cur = X;
		}
		if (group(q[k].a) == group(q[k].b)) {
			ans[q[k].t] = 1;
		}
	}
	for (int i = 1; i <= Q; i++) {
		puts(ans[i] ? "YES" : "NO");
	}
}