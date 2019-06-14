#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+5;

int N;
vector <int> g[MAXN];
int D[MAXN], dist[MAXN], deg[MAXN];

bool ok(int root) {
	queue <int> qu; qu.push(root);
	for (int i = 0; i <= N; i++) D[i] = dist[i] = 0;
	dist[root] = 1;
	while (!qu.empty()) {
		int x = qu.front(); qu.pop();
		for (auto &y : g[x]) {
			if (dist[y]) continue;
			qu.push(y);
			dist[y] = dist[x]+1;
			if (D[dist[y]] == 0) D[dist[y]] = (int)g[y].size();
			else if (D[dist[y]] != (int)g[y].size()) return false;
		}
	}
	return true;
}

bool solve(int fin) {
	queue <int> qu;
	for (int i = 0; i <= N; i++) dist[i] = 0;
	qu.push(fin); dist[fin] = 1;
	while (!qu.empty()) {
		int x = qu.front(); qu.pop();
		for (auto &y : g[x]) {
			if (dist[y]) continue;
			dist[y] = dist[x]+1;
			qu.push(y);
		}
	}
	int u, v, minL = 2e9, maxL = -2e9;
	for (int i = 1; i <= N; i++) {
		int sz = (int)g[i].size();
		if (sz != 1) continue;
		if (minL > dist[i]) minL = dist[i], u = i;
		if (maxL < dist[i]) maxL = dist[i], v = i;
	}
	if (ok(fin)) {
		printf("%d\n", fin);
		return true;
	}
	else if (ok(u)) {
		printf("%d\n", u);
		return true;
	}
	else if (ok(v)) {
		printf("%d\n", v);
		return true;
	}
	return false;
}

int main() {
	scanf("%d",&N);
	for (int i = 1; i < N; i++) {
		int x, y; scanf("%d%d",&x,&y);
		g[x].push_back(y);
		g[y].push_back(x);
		deg[x]++; deg[y]++;
	}
	queue <int> qu;
	for (int i = 1; i <= N; i++) {
		if ((int)g[i].size() <= 1) qu.push(i);
	}
	int fin = -1, fin2 = -1;
	while (!qu.empty()) {
		int x = qu.front(); qu.pop();
		fin2 = fin; fin = x;
		for (auto &y : g[x]) {
			if (--deg[y] == 1) qu.push(y);
		}
	}
	if (solve(fin)) return 0;
	if (solve(fin2)) return 0;
	puts("-1");
	return 0;
}