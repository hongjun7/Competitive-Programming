#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
typedef unsigned long long ll;
const int inf = 2e9;

int N, K;
int tt[MAXN];
vector <int> g[MAXN];
int singer[MAXN];
double J;

struct QUERY {
	int t, p, s;
} q[MAXN];

struct QG {
	int t, s;
};
vector <QG> qg[MAXN];
int cnt[MAXN];

struct BS {
	int s, e, m, i;
} b[MAXN];
int ans[MAXN], sub[MAXN];
ll tree[MAXN];

ll query(int p) {
	ll ret = 0;
	for (; p > 0; p -= p & -p) ret += tree[p];
	return ret;
}

void add(int p, int val) {
	for (; p <= N; p += p & -p) tree[p] += val;
}

double ts[MAXN];
int trans[MAXN];
bool ignore[MAXN];

void dfs(int x) {
	for (auto &t : qg[x]) {
		int s = 1, e = N, F = N + 1;
		while (s <= e) {
			int m = (s + e) / 2;
			if (b[m].m >= t.t) {
				F = min(F, m);
				e = m - 1;
			}
			else s = m + 1;
		}
		if (F != N + 1) add(F, t.s / sub[x]);
	}
	if (!ignore[singer[x]])
		ts[singer[x]] += (double)(query(trans[singer[x]])) / (double)(cnt[singer[x]]);
	for (auto &y : g[x]) {
		dfs(y);
	}
	for (auto &t : qg[x]) {
		int s = 1, e = N, F = N + 1;
		while (s <= e) {
			int m = (s + e) / 2;
			if (b[m].m >= t.t) {
				F = min(F, m);
				e = m - 1;
			}
			else s = m + 1;
		}
		if (F != N + 1) add(F, -(t.s / sub[x]));
	}
}

void go(int x) {
	sub[x]++;
	for (auto &y : g[x]) {
		go(y);
		sub[x] += sub[y];
	}
}

int main() {
	scanf("%d%d%lf", &N, &K, &J);
	for (int i = 2; i <= N; i++) {
		int j; scanf("%d", &j);
		g[j].push_back(i);
	}
	go(1);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &singer[i]);
		cnt[singer[i]]++;
	}
	for (int i = 1; i <= K; i++) {
		scanf("%d%d%d", &q[i].t, &q[i].p, &q[i].s);
		tt[i] = q[i].t;
	}
	sort(tt + 1, tt + K + 1);
	int pK = K;
	K = unique(tt + 1, tt + K + 1) - (tt + 1);
	for (int i = 1; i <= pK; i++) {
		int x = lower_bound(tt + 1, tt + K + 1, q[i].t) - (tt);
		qg[q[i].p].push_back({ x, q[i].s });
	}
	for (int i = 1; i <= N; i++) {
		b[i] = { 1, K }; b[i].i = i;
		ans[i] = inf;
	}
	for (int k = 0; k < 25; k++) {
		for (int i = 1; i <= N; i++) {
			if (b[i].s <= b[i].e) {
				b[i].m = (b[i].s + b[i].e) / 2;
				ignore[b[i].i] = 0;
			}
			else {
				b[i].m = 0;
				ignore[b[i].i] = 1;
			}
		}
		sort(b + 1, b + N + 1, [&](const BS &x, const BS &y) {
			return x.m < y.m;
		});
		for (int i = 1; i <= N; i++) {
			if (b[i].m == 0) continue;
			trans[b[i].i] = i;
		}
		dfs(1);
		for (int i = 1; i <= N; i++) {
			if (b[i].m == 0) continue;
			int x = b[i].i;
			if (ts[x] > J + (1e-9)) {
				ans[x] = min(ans[x], b[i].m);
				b[i].e = b[i].m - 1;
			}
			else {
				b[i].s = b[i].m + 1;
			}
		}
		for (int i = 1; i <= N; i++) {
			ts[i] = 0;
			tree[i] = 0;
		}
	}
	for (int i = 1; i <= N; i++) {
		if (ans[singer[i]] == inf) puts("-1");
		else printf("%d\n", tt[ans[singer[i]]]);
	}
}