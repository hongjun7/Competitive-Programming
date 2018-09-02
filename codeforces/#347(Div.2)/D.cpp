#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+5;

// usage
// TwoSat ts;
// ts.init(n);
// for(each implication) ts.add(p,q); (both p => q and ~q => ~p are added)
// for(each implication) ts.add(p+n,q); (both ~p => q and ~q => p are added)
// for(each implication) ts.add(p,q+n); (both p => ~q and q => ~p are added)
// ts.negation(p) => p+n
// ts.negation(p+n) => p
//
// vector<bool> result = ts.solve();
// if (n > 0 && result.empty()): NOT satisfiable. ***n > 0*** check is IMPORTANT
// if (result[p] == true): variable p is true
// if (result[p] == false): variable p is false
//
// caution: n != TwoSat.n

struct TwoSat {
	int n;
	int var;
	vector<vector<int>> graph;
	vector<vector<int>> grev;

	int vcnt;
	vector<int> v;

	void init(int var_) {
		var = var_;
		n = var_*2;
		graph.clear(); graph.resize(n);
		grev.clear(); grev.resize(n);

		vcnt = 0;
		v.clear(); v.resize(n);
	}

	int negation(int nod) {
		return nod >= var ? nod - var : nod + var;
	}

	// p implies q. p -> q
	void add(int p, int q) {
		graph[p].push_back(q);
		graph[negation(q)].push_back(negation(p));
		grev[q].push_back(p);
		grev[negation(p)].push_back(negation(q));
	}

	// and (p or q)
	void addCNF(int p, int q) {
		add(negation(p), q);
	}

	vector<int> emit;
	void dfs(int nod, vector<vector<int>> &graph) {
		v[nod] = vcnt;
		for(int next : graph[nod]){
			if (v[next] == vcnt) continue;
			dfs(next, graph);
		}
		emit.push_back(nod);
	}

	vector<bool> solve() {
		vector<bool> solution(var);
		vector<int> scc_check(n);
		int scc_index = 0;

		++vcnt;
		emit.clear();
		for(int i = 0; i < n; i++) {
			if (v[i] == vcnt) continue;
			dfs(i, graph);
		}

		++vcnt;
		for(auto start : vector<int>(emit.rbegin(),emit.rend())) {
			if (v[start] == vcnt) continue;
			emit.clear();
			dfs(start, grev);
			++scc_index;
			for(auto node : emit) {
				scc_check[node] = scc_index;
				if (scc_check[negation(node)] == scc_index) {
					// contradiction found
					solution.clear();
					return solution;
				}
				solution[node >= var ? node-var : node] = (node < var);
			}
		}

		return solution;
	}
};

struct EDGE {
	int x, y, c;
} E[MAXN];

int N, M;
int Gx[MAXN], Gn, deg[MAXN];
vector <int> G[MAXN];
vector <int> ans;
bool valid;

void solve(int k) {
	TwoSat twosat;
	twosat.init(N);
	for (int i = 1; i <= M; i++) {
		int x = E[i].x, y = E[i].y, c = E[i].c;
		if (c != k) twosat.add(x, y+N), twosat.add(x+N, y);
		else twosat.add(x, y), twosat.add(x+N, y+N);
	}
	auto ret = twosat.solve();
	if (ret.empty()) return;
	vector <int> cur;
	for (int g = 1; g <= Gn; g++) {
		int cnt = 0;
		for (auto x : G[g]) {
			cnt += (ret[x] == true);
		}
		int Gsz = (int)G[g].size();
		for (auto x : G[g]) {
			if (ret[x] == (cnt < Gsz-cnt))
			cur.push_back(x+1);
		}
	}
	if (!valid || (int)cur.size() < (int)ans.size()) {
		valid = true;
		ans = cur;
	}
}

vector <int> g[MAXN];
bool vis[MAXN];

void dfs(int x) {
	vis[x] = 1; Gx[x] = Gn;
	G[Gn].push_back(x);
	for (auto &y : g[x]) {
		if (!vis[y]) dfs(y);
	}
}

int main() {
	scanf("%d%d",&N,&M);
	for (int i = 1; i <= M; i++) {
		char s[2]; int x, y; scanf("%d%d%s",&x,&y,&s[0]); x--; y--;
		E[i] = {x, y, s[0]=='B'};
		g[x].push_back(y);
		g[y].push_back(x);
		deg[x]++; deg[y]++;
	}
	for (int i = 0; i < N; i++) {
		if (!vis[i]) {
			++Gn;
			dfs(i);
		}
	}
	solve(0); solve(1);
	if (!valid) puts("-1");
	else {
		printf("%d\n", (int)ans.size());
		for (auto x : ans) printf("%d ", x);
	}
}