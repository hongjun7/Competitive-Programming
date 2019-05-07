#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+5;

int N, K;
vector <int> g[MAXN];

bool ok(int d) {
	for (int i = 0; i < N; i++) {
		int j = (i+d)%N;
		if (g[i].size() != g[j].size()) return false;
		for (int k = g[i].size()-1; k >= 0; k--) {
			if (g[i][k] != g[j][k]) return false;
		}
	}
	return true;
}

int main() {
	scanf("%d%d",&N,&K);
	for (int i = 1; i <= K; i++) {
		int a, b; scanf("%d%d",&a,&b); a--; b--;
		g[a].push_back((b-a+N)%N);
		g[b].push_back((a-b+N)%N);
	}
	for (int i = 0; i < N; i++) {
		sort(g[i].begin(), g[i].end());
	}
	bool ans = false;
	for (int d = 1; d < N; d++) {
		if (N%d > 0) continue;
		if (ok(d)) {
			ans = true;
			break;
		}
	}
	puts(ans ? "Yes" : "No");
}