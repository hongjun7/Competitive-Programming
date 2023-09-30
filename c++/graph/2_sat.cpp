struct TwoSat {
	int n, var;
	int vcnt;
	vector<int> v;
	void init(int var_) {
		var = var_;
		n = var_ * 2;
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
	void dfs1(int nod) {
		v[nod] = vcnt;
		for (int next : graph[nod]) {
			if (v[next] == vcnt) continue;
			dfs1(next);
		}
		emit.push_back(nod);
	}
	void dfs2(int nod) {
		v[nod] = vcnt;
		for (int next : grev[nod]) {
			if (v[next] == vcnt) continue;
			dfs2(next);
		}
		emit.push_back(nod);
	}
	bool solve() {
		vector<int> scc_check(n);
		int scc_index = 0;
		++vcnt;
		emit.clear();
		for (int i = 0; i < n; i++) {
			if (v[i] == vcnt) continue;
			dfs1(i);
		}
		++vcnt;
		for (auto start : vector<int>(emit.rbegin(), emit.rend())) {
			if (v[start] == vcnt) continue;
			emit.clear();
			dfs2(start);
			++scc_index;
			for (auto node : emit) {
				scc_check[node] = scc_index;
				if (scc_check[negation(node)] == scc_index) return false;
			}
		}
		return true;
	}
};