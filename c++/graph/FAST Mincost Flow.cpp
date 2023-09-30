const int inf = 0x3f3f3f3f;
const int MAXN = 2505;
const int MAXM = 100005;
//variable 'ending' determines maxflow or not.
struct MinCostFlow {
	int sz, n, ending;
	int st, en, maxflow, mincost;
	bool vis[MAXN];
	int net[MAXN], pre[MAXN], cur[MAXN], dis[MAXN], Q[100 * MAXN], fr, re;
	struct EDGE {
		int v, cap, cost, next;
		EDGE() {}
		EDGE(int a, int b, int c, int d) {
			v = a, cap = b, cost = c, next = d;
		}
	} E[MAXM];
	void init(int _n) {
		ending = 0;
		n = _n, sz = 0;
		memset(net, -1, sizeof(net));
	}
	void addEdge(int u, int v, int cost, int cap) {
		E[sz] = EDGE(v, cap, cost, net[u]);
		net[u] = sz++;
		E[sz] = EDGE(u, 0, -cost, net[v]);
		net[v] = sz++;
	}
	bool adjust() {
		int v, min = inf;
		for (int i = 0; i <= n; i++) {
			if (!vis[i]) continue;
			for (int j = net[i]; v = E[j].v, j != -1; j = E[j].next)
				if (E[j].cap && !vis[v] && dis[v] - dis[i] + E[j].cost < min)
					min = dis[v] - dis[i] + E[j].cost;
		}
		if (min == inf) return false;
		for (int i = 0; i <= n; i++) if (vis[i]) cur[i] = net[i], vis[i] = false, dis[i] += min;
		return true;
	}
	int augment(int i, int flow) {
		if (i == en) {
			if (dis[st] < 0) mincost += dis[st] * flow;
			else ending = 1; //mcf, not mcmf
			maxflow += flow;
			return flow;
		}
		vis[i] = true;
		for (int j = cur[i], v; v = E[j].v, j != -1; j = E[j].next) {
			if (!E[j].cap) continue;
			if (vis[v] || dis[v] + E[j].cost != dis[i]) continue;
			int delta = augment(v, std::min(flow, E[j].cap));
			if (delta) {
				E[j].cap -= delta;
				E[j ^ 1].cap += delta;
				cur[i] = j;
				return delta;
			}
		}
		return 0;
	}
	void spfa() {
		int u, v;
		for (int i = 0; i <= n; i++) vis[i] = false, dis[i] = inf;
		dis[st] = 0;
		Q[fr = re = 0] = st;
		vis[st] = true;
		while (fr <= re) {
			u = Q[fr++];
			vis[u] = false;
			for (int i = net[u]; v = E[i].v, i != -1; i = E[i].next) {
				if (!E[i].cap || dis[v] <= dis[u] + E[i].cost) continue;
				dis[v] = dis[u] + E[i].cost;
				if (!vis[v]) {
					vis[v] = true;
					Q[++re] = v;
					if (dis[Q[fr]] > dis[Q[re]]) swap(Q[fr], Q[re]);
				}
			}
		}
		for (int i = 0; i <= n; i++) dis[i] = dis[en] - dis[i];
	}
	int solve(int s, int t, int need) {
		st = s, en = t;
		spfa();
		mincost = maxflow = 0;
		for (int i = 0; i <= n; i++) vis[i] = false, cur[i] = net[i];
		do {
			while (augment(st, inf)) {
				if (ending) return mincost; //mcf, not mcmf
				memset(vis, false, sizeof(vis));
			}
		} while (adjust());
		return mincost;
	}
};
