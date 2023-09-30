// Kuhn munkres algorithm by MolaMola(cki86201, dotorya, zigui)
// Computes a maximum weight matching in a bipartite graph
// Time Complexity : O(N^3)
// test : https://hochiminh17.kattis.com/problems/engaging

#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;

int in[1005][1005];
int mats[1005], matt[1005];
int Ls[1005], Lt[1005];
int revs[1005], revt[1005];
int valt[1005];
bool chks[1005], chkt[1005];

vector <int> Vu;
void vpush(int p, int N) {
	chks[p] = 1;
	for (int i = 1; i <= N; i++) {
		if (!valt[i]) continue;
		if (valt[i] > Ls[p] + Lt[i] - in[p][i]) {
			valt[i] = Ls[p] + Lt[i] - in[p][i];
			revt[i] = p;
			if (!valt[i]) Vu.push_back(i);
		}
	}
}

int main() {
	int N, M, K, i, j, k;
	scanf("%d%d%d", &M, &N, &K);
	N = max(N, M);
	for (int i = 1; i <= K; i++) {
		int x, y, w; scanf("%d%d%d", &x, &y, &w);
		in[x][y] = max(in[x][y], w);
	}
	for (i = 1; i <= N; i++) Lt[i] = -INF;
	for (i = 1; i <= N; i++) for (j = 1; j <= N; j++) Lt[j] = max(Lt[j], in[i][j]);
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) chks[j] = chkt[j] = 0;
		for (j = 1; j <= N; j++) valt[j] = INF;
		for (j = 1; j <= N; j++) revs[j] = revt[j] = 0;
		int p = 0;
		for (j = 1; j <= N; j++)
			if (!mats[j])
				break;
		p = j;
		vpush(p, N);
		while (1) {
			if (!Vu.empty()) {
				int t = Vu.back();
				Vu.pop_back();
				chkt[t] = 1;
				if (!matt[t]) {
					vector <int> Vu2;
					Vu2.push_back(t);
					while (1) {
						Vu2.push_back(revt[Vu2.back()]);
						if (Vu2.back() == p) break;
						Vu2.push_back(revs[Vu2.back()]);
					}
					reverse(Vu2.begin(), Vu2.end());
					for (j = 0; j < Vu2.size(); j += 2) {
						int s = Vu2[j], t = Vu2[j + 1];
						mats[s] = t;
						matt[t] = s;
					}
					break;
				}
				else {
					int s = matt[t];
					revs[s] = t;
					vpush(s, N);
				}
			}
			else {
				int mn = INF;
				for (j = 1; j <= N; j++) if (!chkt[j]) mn = min(mn, valt[j]);
				for (j = 1; j <= N; j++) {
					if (chks[j]) Ls[j] -= mn;
					if (chkt[j]) Lt[j] += mn;
					else { valt[j] -= mn; if (valt[j] == 0) Vu.push_back(j); }
				}
			}
		}
		Vu.clear();
	}
	int ans = 0;
	vector <pair <int, int> > res;
	for (i = 1; i <= N; i++) {
		ans += Ls[i] + Lt[i];
		if (in[i][mats[i]]) res.push_back({ i, mats[i] });
	}
	printf("%d\n", ans);
	printf("%d\n", res.size());
	for (auto &t : res) printf("%d %d\n", t.first, t.second);
}