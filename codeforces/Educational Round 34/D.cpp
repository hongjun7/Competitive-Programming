#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5+5;

pair <long double, int> tree[2*MAXN]; int SZ;
// Returns the sum from index 1 to p, inclusive
pair <long double, int> query(int p) {
    pair <long double, int> ret = {0, 0};
    for (; p > 0; p -= p & -p) {
    	ret.first += tree[p].first;
    	ret.second += tree[p].second;
    }
    return ret;
}
// Adds val to element with index pos
void add(int p, pair <long double, int> val) {
    for (; p <= SZ; p += p & -p) {
    	tree[p].first += val.first;
    	tree[p].second += val.second;
    }
}

long double solve(vector <int> a) {
	memset(tree, 0, sizeof(tree));
	long double ret = 0;
	vector <int> x;
	for (auto &t : a) {
		x.push_back(t);
		x.push_back(t-2);
	}
	sort(x.begin(), x.end());
	x.erase(unique(x.begin(), x.end()), x.end());
	SZ = (int)x.size()+1;
	for (auto &t : a) {
		int p = (int)(lower_bound(x.begin(), x.end(), t-2)-x.begin())+1;
		auto cur = query(p);
		ret += (long double)cur.second*t - cur.first;
		p = (int)(lower_bound(x.begin(), x.end(), t)-x.begin())+1;
		add(p, {t, 1});
	}
	return ret;
}

int main() {
	int N; scanf("%d",&N);
	vector <int> a;
	for (int i = 0; i < N; i++) {
		int x; scanf("%d",&x);
		a.push_back(x);
	}
	long double ans = 0;
	ans += solve(a);
	reverse(a.begin(), a.end());
	ans -= solve(a);
	printf("%.0Lf\n", ans);
}