#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int N;
int vis[MAXN], sub[MAXN], maxsub[MAXN];
vector <int> g[MAXN], dfn;

void dfs(int x, int par) {
	dfn.push_back(x);
	sub[x] = 1; maxsub[x] = 0;
	for (auto &y : g[x]) {
		if (vis[y] || y == par) continue;
		dfs(y, x);
		maxsub[x] = max(maxsub[x], sub[y]);
		sub[x] += sub[y];
	}
}

int centroid(int x) {
	dfn.clear();
	dfs(x, -1);
	int dfns = dfn.size();
	int maxs = 1e9, center = -1;
	for (auto &t : dfn) {
		int sz = max(maxsub[t], dfns - sub[t]);
		if (maxs > sz) {
			maxs = sz;
			center = t;
		}
	}
	return center;
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i < N; i++) {
		int x, y; scanf("%d%d", &x, &y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	queue <int> qu; qu.push(1);
	while (!qu.empty()) {
		int x = qu.front(); qu.pop();
		x = centroid(x);
		//printf("%d\n", x);
		vis[x] = 1;
		for (auto &y : g[x]) if (!vis[y]) {
			qu.push(y);
		}
	}
}