// Edmond's Blossom Algorithm
// Computes maximum matchings for a general graph

// usage:
// Blossom::init(|V|,|E|) // G = (V, E)
// for (each edges) Blossom::add_edge(u, v);
// Blossom::solve(); // matched pair
// Time Complexity : O(|E|*|V|^2)
// Space Complexity : O(|V|^2)

// test : https://uoj.ac/problem/79

#include <vector>
#include <algorithm>
using namespace std;

#define rep(i, n) for(int i=0;i<n;i++)
typedef pair<int, int> pii;

namespace Blossom {
	const int MAXN = 505;
	const int MAXM = 124755;
	struct struct_edge { int v; struct_edge* n; };
	typedef struct_edge* edge;
	struct_edge pool[MAXM * 2];
	edge top, adj[MAXN];
	int V, E, match[MAXN], qh, qt, q[MAXN], par[MAXN], base[MAXN];
	bool inq[MAXN], inb[MAXN], C[MAXN][MAXN];
	void init(int n, int m) {
		V = n; E = m;
		rep(i, V) rep(j, V) C[i][j] = 0;
		top = pool;
		rep(i, E * 2) pool[i].v = 0, pool[i].n = NULL;
		rep(i, V) adj[i] = NULL;
		rep(i, V) match[i] = q[i] = par[i] = base[i] = 0;
		rep(i, V) inq[i] = inb[i] = 0;
		qh = qt = 0;
	}
	void add_edge(int u, int v) {
		u--; v--;
		if (C[u][v]) return;
		top->v = v, top->n = adj[u], adj[u] = top++;
		top->v = u, top->n = adj[v], adj[v] = top++;
		C[u][v] = C[v][u] = 1;
	}
	int LCA(int root, int u, int v) {
		static bool inp[MAXN];
		for (int i = 0; i < V; i++) inp[i] = 0;
		while (1) {
			inp[u = base[u]] = true;
			if (u == root) break;
			u = par[match[u]];
		}
		while (1) {
			if (inp[v = base[v]]) return v;
			else v = par[match[v]];
		}
	}
	void mark_blossom(int lca, int u) {
		while (base[u] != lca) {
			int v = match[u];
			inb[base[u]] = inb[base[v]] = true;
			u = par[v];
			if (base[u] != lca) par[u] = v;
		}
	}
	void contraction(int s, int u, int v) {
		int lca = LCA(s, u, v);
		rep(i, V) inb[i] = 0;
		mark_blossom(lca, u);
		mark_blossom(lca, v);
		if (base[u] != lca) par[u] = v;
		if (base[v] != lca) par[v] = u;
		for (int u = 0; u<V; u++)
			if (inb[base[u]]) {
				base[u] = lca;
				if (!inq[u]) inq[q[++qt] = u] = true;
			}
	}
	int find_augment(int s) {
		rep(i, V) par[i] = -1, inq[i] = 0;
		rep(i, V) base[i] = i;
		inq[q[qh = qt = 0] = s] = true;
		while (qh <= qt) {
			int u = q[qh++];
			for (edge e = adj[u]; e; e = e->n) {
				int v = e->v;
				if (base[u] != base[v] && match[u] != v) {
					if ((v == s) || (match[v] != -1 && par[match[v]] != -1))
						contraction(s, u, v);
					else if (par[v] == -1) {
						par[v] = u;
						if (match[v] == -1) return v;
						else if (!inq[match[v]]) {
							inq[q[++qt] = match[v]] = 1;
						}
					}
				}
			}
		}
		return -1;
	}
	int augment(int s, int t) {
		int u = t, v, w;
		while (u != -1) {
			v = par[u]; w = match[v];
			match[v] = u; match[u] = v;
			u = w;
		}
		return t != -1;
	}
	int edmonds() {
		int cnt = 0;
		rep(i, V) match[i] = -1;
		for (int u = 0; u < V; u++) {
			if (match[u] == -1) cnt += augment(u, find_augment(u));
		}
		return cnt;
	}
	vector <pii> solve() {
		vector <pii> con;
		con.clear();
		if (E == 0) return con;
		int ret = edmonds();
		rep(i, V) if (i < match[i]) con.emplace_back(i + 1, match[i] + 1);
		return con;
	}
}
